# Dependencies
This document describes how to build dependencies without installing them system-wide.

## First steps
In the project root directory, create `deps` directory to install all the dependencies there.
```bash
mkdir -p deps
```
Then change the current working directory to `deps` and set the `DEPS_DIR` environment variable:
```bash
cd deps
export DEPS_DIR=$PWD
```

## WolfSSL
Download WolfSSL latest release zip archive from [WolfSSL Official Website](https://www.wolfssl.com/download/) to the `deps` directory.
Extract the archive and build WolfSSL.
```bash
# In the wolfssl directory
./configure --prefix=$DEPS_DIR --enable-all --enable-sniffer --enable-static

make -j$(nproc)

make install

# Go back to dependencies directory
cd $DEPS_DIR
```

## BLAKE3
Clone BLAKE3 source code to `deps` directory:
```bash
# Clone version 1.8.2
git clone --depth=1 --branch=1.8.2 'https://github.com/BLAKE3-team/BLAKE3'

cd BLAKE3/c
```
Then build BLAKE3:
```bash
mkdir -p build

cmake -B build -S . -DCMAKE_INSTALL_PREFIX=$DEPS_DIR -DBLAKE3_EXAMPLES=0 -DBLAKE3_USE_TBB=0

cmake --build build -- -j$(nproc)

cmake --build build -- install
```

## Done!
Go back to source root directory:
```bash
cd $DEPS_DIR/..
```
