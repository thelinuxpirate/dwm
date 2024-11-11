{
  description = "The Sleepy Suckless' NixOS Module";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }: {


    packages = {
      default = nixpkgs.lib.mkFlake {
        inherit self;
        packages = {
          dmenu = import ./default.nix { inherit nixpkgs; app = "dmenu"; };
          slstatus = import ./default.nix { inherit nixpkgs; app = "slstatus"; };
          st = import ./default.nix { inherit nixpkgs; app = "st"; };
        };
      };
    };

    nixosModules = {
      sleepy = ./modules/sleepy.nix;
    };
  };
}
