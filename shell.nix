{ pkgs ? import <nixpkgs> { system = "x86_64-linux"; } }:

pkgs.mkShell {
  name = "sleepy-dwm-dev-shell";

  buildInputs = [
    pkgs.xorg.libX11
    pkgs.xorg.libXft
    pkgs.xorg.libXinerama
    pkgs.xorg.libXrandr
    pkgs.xorg.libXScrnSaver
    pkgs.imlib2
    pkgs.pkgconf
  ];

  shellHook = ''
    echo "To build Sleepy-DWM use 'make'"
  '';
}
