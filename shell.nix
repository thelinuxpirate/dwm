{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {

  packages = [
    pkgs.xorg.libX11
    pkgs.xorg.libXft
    pkgs.xorg.libXinerama
    pkgs.xorg.xrdb
    pkgs.imlib2
    pkgs.alsa-lib
  ];

  shellHook = ''
    echo "Building Sleepy-DWM..."
    make clean
    make
  '';
}
