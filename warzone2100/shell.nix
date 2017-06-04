{ pkgs ? import <nixpkgs> {} }:

with pkgs;

let
  stdenv = pkgs.stdenv;
in rec {
  wz2100 = stdenv.mkDerivation {
    name = "warzone2100";
    nativeBuildInputs = with pkgs; [ autoconf automake cmake gcc perl zip unzip pkgconfig libtool 
      asciidoc python3 docbook_xml_dtd_45
#      docbook5_xsl docbook_xml_xslt
    ];
    buildInputs = with pkgs; [
      qt5.qtbase
      qt5.qtscript
      SDL2
      libtheora
      openal
      glew
      physfs
      fribidi
    ];
#    NIX_QT5_TMP="/tmp/__nix_qt5__/";
#    preHook = ''
#      rm -rf $NIX_QT5_TMP
#    '';

    hardeningDisable = [ "format" ];
    postPatch = ''
      substituteInPlace lib/exceptionhandler/dumpinfo.cpp \
                        --replace "which %s" "${which}/bin/which %s"
      substituteInPlace lib/exceptionhandler/exceptionhandler.cpp \
                        --replace "which %s" "${which}/bin/which %s"
    '';
    shellHook = ''
      echo "=== Environment for Warzone2100 prepared ==="
      echo "./configure --prefix=/tmp/wz-plugins --with-distributor=NixOS --with-qtplugins=yes"
      echo "make -j8"
    '';
  };
}
