{
  description = "UPPAAL Timed Automata Parser";

  inputs.nixpkgs.url = "nixpkgs/nixos-21.11";

  outputs = { self, nixpkgs }:
  let
      # System types to support.
      supportedSystems = [ "x86_64-linux" "x86_64-darwin" "aarch64-linux" "aarch64-darwin" ];
      # Helper function to generate an attrset '{ x86_64-linux = f "x86_64-linux"; ... }'.
      forAllSystems = nixpkgs.lib.genAttrs supportedSystems;
      # Nixpkgs instantiated for supported system types.
      nixpkgsFor = forAllSystems (system: import nixpkgs { inherit system; });
  in
  {
    defaultPackage = forAllSystems (system:
    let pkgs = nixpkgsFor.${system};
    in pkgs.stdenv.mkDerivation {
      pname = "UTAP";
        version = "1.0.0";
        src = ./.;
        buildInputs = with pkgs; [ cmake boost174 libxml2 flex bison ];
    });
  };
}
