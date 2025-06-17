/*
 * blake3-aes-256-gcm algorithm implementation
 */

#pragma once

#include <blake3.h>
#include <wolfssl/options.h>
#include <wolfssl/wolfcrypt/random.h>
#include <wolfssl/wolfcrypt/aes.h>

#define AES256_IV_SIZE (12)

#define AES256_KEY_SIZE (32)
#define AES256_BASE64_KEY_SIZE (44)

#define AES256_SALT_SIZE AES256_KEY_SIZE
#define AES256_AUTH_TAG_SIZE (16)

typedef struct blake3_aes256gcm {
    Aes aes;
    byte derived_key[BLAKE3_OUT_LEN];
    byte iv[AES256_IV_SIZE];
} Blake3Aes256Gcm_t;

int blake3aes256gcm_zero_iv(byte *iv_out);

int blake3aes256gcm_gen_derived_key(const byte *key, const byte *salt, byte *derived_key_out);

int blake3aes256gcm_init(Blake3Aes256Gcm_t *self, const byte *key, const byte *salt);

void blake3aes256gcm_encrypt(Blake3Aes256Gcm_t *self, byte *out,
                             const byte *in, size_t in_size,
                             byte *out_iv, byte *auth_tag,
                             const byte *auth_in, size_t auth_in_size);

int blake3aes256gcm_decrypt(Blake3Aes256Gcm_t *self, byte *out,
                            const byte *in, size_t in_size,
                            const byte *iv, const byte *auth_tag,
                            const byte *auth_in, size_t auth_in_size);

void blake3aes256gcm_destroy(Blake3Aes256Gcm_t *self);

