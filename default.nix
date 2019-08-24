with import <nixpkgs> {}; {
  unnamedOSEnv = stdenv.mkDerivation {
    name = "unnamedOSenv";
    buildInputs = [
      stdenv
      gcc
      cmake
      nasm
    ];
  };
}
