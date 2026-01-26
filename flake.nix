{
  description = "QMK firmware development shell";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      systems = [ "aarch64-darwin" "x86_64-linux" "aarch64-linux" "x86_64-darwin" ];
      forAllSystems = nixpkgs.lib.genAttrs systems;
    in
    {
      devShells = forAllSystems (system:
        let
          pkgs = import nixpkgs { inherit system; };
        in
        {
          default = pkgs.mkShell {
            packages = with pkgs; [
              qmk
              python3
              python3Packages.appdirs
            ];

            shellHook = ''
              echo "🧠 QMK dev shell ready"
              echo "Run: qmk setup (first time only)"
            '';
          };
        });
    };
}
