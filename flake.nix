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
    });
      version = "1.1.0";
    in
    {
      defaultPackage = forAllSystems (system:
        let
          pkgs = nixpkgsFor.${system};
          staticLibxml = pkgs.libxml2.override { enableStatic = true; };
        in
        pkgs.stdenv.mkDerivation {
          pname = "UTAP";
          inherit version;
          src = ./.;
          nativeBuildInputs = with pkgs; [ cmake flex bison ];
          buildInputs = with pkgs; [ staticLibxml doctest ];
          cmakeFlags = [ "-DTESTING=ON" ];

          doCheck = true;
        });

      devShell = forAllSystems (system:
        let
          pkgs = nixpkgsFor.${system};
        in
        pkgs.mkShell {
          nativeBuildInputs = with pkgs; [ cmake flex bison ];
          buildInputs = with pkgs; [ libxml2 doctest ];
        });



      # To build this, use `nix build .\#utapWindows.x86_64-linux`
      # Unless you're using a different OS
      utapWindows = forAllSystems (system:
        let
          nativePkgs = nixpkgsFor.${system};
          pkgs = crossNixpkgsFor.${system};
          staticLibxml = pkgs.libxml2.override { enableStatic = true; enableShared = false; };
        in
        pkgs.stdenv.mkDerivation {
          pname = "UTAP";
          inherit version;
          src = ./.;
          nativeBuildInputs = with nativePkgs; [ cmake flex bison ];
          buildInputs = with pkgs; [ staticLibxml zlib.static doctest ];
          cmakeFlags = [ "-DTESTING=ON" "-DSTATIC=ON" "-DCMAKE_TOOLCHAIN_FILE=toolchains/mingw.cmake" ];
          WINEPATH = "${pkgs.windows.mcfgthreads}/bin;${nativePkgs.wine64Packages.stableFull}/lib/wine/x86_64-windows/";
          CROSSCOMPILING_EMULATOR = "${nativePkgs.wine64Packages.stableFull}/bin/wine64";

          # mkDerivation disables checkPhase when cross compiling.
          postPhases = [ "crossCheck" ];
          crossCheck = "WINEPREFIX=$(pwd) ctest --output-on-failure";
        });
    };
}
