# Blake3-AES-256-GCM
This is a blake3-aes-256-gcm encryption and decryption algorithm implementation with BLAKE3 and WolfSSL.

## Build
First read [DEPS.md](DEPS.md) file to setup dependencies without installing them system-wide. Then build the example program:
```bash
mkdir -p build
cmake -B build -S .
cmake --build build
```

## Run
The example program takes a base64 encoded 32-byte (256-bit) key and encrypts a hard-coded string then decrypts it.
You can generate this key with following command:
```bash
export KEY=$(openssl rand -base64 32)
./build/src/blake3aes256gcm $KEY
```
