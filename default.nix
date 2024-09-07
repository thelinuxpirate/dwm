# Build Suckless Util
{ app, nixpkgs }:

let
  commonBuild = src:
    nixpkgs.stdenv.mkDerivation {
      pname = "${app}";
      version = "1.0";

      src = ./${app};

      buildInputs = [ nixpkgs.xorg.libX11 nixpkgs.xorg.libXft ];

      installPhase = ''
        make PREFIX=$out install
      '';

      meta = with nixpkgs.lib; {
        description = "${app} build with the 'Sleepy' modifications";
        license = licenses.gpl3Plus;
        platforms = platforms.unix;
      };
    };
in
  commonBuild ./${app}
