{ pkgs ? import <nixpkgs> {} }:

let
  capnproto = pkgs.capnproto.overrideAttrs (oldAttrs: rec {
    name = "capnproto-${version}";
    version = "0.6.0";
    src = pkgs.fetchurl {
      url = "https://capnproto.org/capnproto-c++-${version}.tar.gz";
      sha256 = "0gpp1cxsb9nfd7qkjjykzknx03y0z0n4bq5q0fmxci7w38ci22g5";
    };
    enableParallelBuilding = true;
    nativeBuildInputs = with pkgs; [ cmake extra-cmake-modules ];
  });
in
pkgs.stdenv.mkDerivation rec {
  name = "wzNet-${version}";
  version = "0.0.1.0";
  nativeBuildInputs = with pkgs; [ cmake gnumake gcc ];
  buildInputs = [
    pkgs.qt5.qtbase
    pkgs.qt5.qtscript
    capnproto
  ];
  shellHook = ''
    echo "to compile:"
    echo "mkdir -p build && cd build && cmake ../ && make"
  '';
}
