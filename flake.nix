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
          st = import ./default.nix { inherit nixpkgs; app = "st"; };
          slstatus = import ./default.nix { inherit nixpkgs; app = "slstatus"; };
        };
      };
    };

    nixosModules = {
      sleepy = ./modules/sleepy.nix;
    };
  };
}
