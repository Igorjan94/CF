{ nixpkgs ? import <nixpkgs> {}, compiler ? "default" }:

let

  inherit (nixpkgs) pkgs;

  f = { mkDerivation, acid-state, aeson, async, base, containers
      , http-conduit, lens, lens-aeson, mtl, regex-base, regex-posix
      , safecopy, stdenv, text, vector
      }:
      mkDerivation {
        pname = "telegramExchangeBot";
        version = "0.1.0.0";
        src = /home/igorjan/206round/trash/hs/l;
        isLibrary = false;
        isExecutable = true;
        executableHaskellDepends = [
          acid-state aeson async base containers http-conduit lens lens-aeson
          mtl regex-base regex-posix safecopy text vector
        ];
        license = stdenv.lib.licenses.unfree;
      };

  haskellPackages = if compiler == "default"
                       then pkgs.haskellPackages
                       else pkgs.haskell.packages.${compiler};

  drv = haskellPackages.callPackage f {};

in

  if pkgs.lib.inNixShell then drv.env else drv
