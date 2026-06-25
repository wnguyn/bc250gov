{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  packages = [
    pkgs.gcc
    pkgs.gnumake
    pkgs.pkg-config
    pkgs.libdrm
    pkgs.yaml-cpp
  ];

  PKG_CONFIG_PATH = "${pkgs.libdrm}/lib/pkgconfig";
}
