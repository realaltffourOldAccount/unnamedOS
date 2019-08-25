with import <nixpkgs> {}; {
  unnamedOSEnv = stdenv.mkDerivation {
    name = "unnamedOSenv";
    buildInputs = [
      stdenv
      cmake
      nasm
      gcc
    ];
  };
}
