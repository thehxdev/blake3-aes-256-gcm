/*
 * blake3-aes-256-gcm algorithm implementation
 */

#pragma once

#include <blake3.h>
#include <wolfssl/options.h>
#include <wolfssl/wolfcrypt/random.h>
#include <wolfssl/wolfcrypt/aes.h>

#define AES256_IV_LENGTH (12)

#define AES256_KEY_LENGTH (32)
#define AES256_BASE64_KEY_LENGTH (44)

#define AES256_SALT_LENGTH AES256_KEY_LENGTH
#define AES256_AUTH_TAG_LENGTH (16)

typedef struct blake3_aes256gcm {
    Aes aes;
    byte key_with_salt[AES256_KEY_LENGTH+AES256_SALT_LENGTH];
    byte derived_key[BLAKE3_OUT_LEN];
    byte iv[AES256_IV_LENGTH];
    WC_RNG rng;
} Blake3Aes256Gcm_t;

enum {
    AES256_KEY_TYPE_PLAIN,
    AES256_KEY_TYPE_BASE64,
};


int blake3aes256gcm_set_key(Blake3Aes256Gcm_t *self, const byte *key, size_t keytype);

int blake3aes256gcm_set_salt(Blake3Aes256Gcm_t *self);

int blake3aes256gcm_set_iv(Blake3Aes256Gcm_t *self);

int blake3aes256gcm_set_derived_key(Blake3Aes256Gcm_t *self);

int blake3aes256gcm_init(Blake3Aes256Gcm_t *self, const byte *key, size_t keytype);

void blake3aes256gcm_encrypt(Blake3Aes256Gcm_t *self, byte *out,
                             const byte *in, size_t in_size,
                             byte *out_iv,
                             byte *auth_tag, size_t auth_tag_size,
                             const byte *auth_in, size_t auth_in_size);

int blake3aes256gcm_decrypt(Blake3Aes256Gcm_t *self, byte *out,
                             const byte *in, size_t in_size,
                             const byte *iv,
                             const byte *auth_tag, size_t auth_tag_size,
                             const byte *auth_in, size_t auth_in_size);

void blake3aes256gcm_destroy(Blake3Aes256Gcm_t *self);

