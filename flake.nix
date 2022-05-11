{
  description = "UPPAAL Timed Automata Parser";

  inputs.nixpkgs.url = "nixpkgs/master";

  outputs = { self, nixpkgs }:
    let
      # System types to support.
      supportedSystems = [ "x86_64-linux" "x86_64-darwin" "aarch64-linux" "aarch64-darwin" ];
      # Helper function to generate an attrset '{ x86_64-linux = f "x86_64-linux"; ... }'.
      forAllSystems = nixpkgs.lib.genAttrs supportedSystems;
      # Nixpkgs instantiated for supported system types.
      nixpkgsFor = forAllSystems (system: import nixpkgs { inherit system; });
      crossNixpkgsFor = forAllSystems (system: import nixpkgs {
        inherit system;
        crossSystem = (nixpkgsFor.${system}).lib.systems.examples.mingwW64;
        overlays = [
          (self: super: {
            # Waiting for https://github.com/NixOS/nixpkgs/pull/172144 to get merged
            rhash = super.rhash.overrideAttrs (oldAttrs: rec {
              configureFlags = oldAttrs.configureFlags ++ [ "--target=${super.stdenv.hostPlatform.config}" ];
            });
          })
        ];

      });
    in
    {
      defaultPackage = forAllSystems (system:
      let pkgs = nixpkgsFor.${system};
          staticLibxml = pkgs.libxml2.override { enableStatic = true; };
        in
        pkgs.stdenv.mkDerivation {
          pname = "UTAP";
          version = "1.0.0";
          src = ./.;
          nativeBuildInputs = with pkgs; [ cmake flex bison ];
          buildInputs = with pkgs; [ boost174 staticLibxml doctest ];
          cmakeFlags = [ "-DTESTING=ON" ];

          doCheck = true;
        });


      # To build this, use `nix build .\#utapWindows.x86_64-linux`
      # Unless you're using a different OS
      utapWindows = forAllSystems (system:
        let
          nativePkgs = nixpkgsFor.${system};
          pkgs = crossNixpkgsFor.${system};
          staticLibxml = pkgs.libxml2.override { enableStatic = true; enableShared = false; };
          staticBoost = pkgs.boost174.override { enableStatic = true; enableShared = false; };
        in
        pkgs.stdenv.mkDerivation {
          pname = "UTAP";
          version = "1.0.0";
          src = ./.;
          nativeBuildInputs = with nativePkgs; [ cmake flex bison ];
          buildInputs = with pkgs; [ staticBoost staticLibxml zlib.static doctest ];
          cmakeFlags = [ "-DTESTING=ON" "-DSTATIC=ON" "-DCMAKE_TOOLCHAIN_FILE=toolchains/mingw.cmake" ];
          WINEPATH = "${pkgs.windows.mcfgthreads}/bin;${nativePkgs.wine64Packages.stableFull}/lib/wine/x86_64-windows/";
          CROSSCOMPILING_EMULATOR = "${nativePkgs.wine64Packages.stableFull}/bin/wine64";

          # mkDerivation disables checkPhase when cross compiling.
          postPhases = [ "crossCheck" ];
          crossCheck = "WINEPREFIX=$(pwd) ctest --output-on-failure";
        });
    };
}
