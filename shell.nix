{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  packages = [
    pkgs.gcc
    pkgs.gnumake
    pkgs.pkg-config
    pkgs.libdrm.dev
    pkgs.yaml-cpp
    pkgs.libgbm
  ];


}
