#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#include <wolfssl/options.h>
#include <wolfssl/wolfcrypt/types.h>
#include <wolfssl/wolfcrypt/random.h>

#include "blake3aes256gcm.h"
#include "base64.h"

#define INPUT "This is Blake3-AES-256-GCM!"

int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;

    WC_RNG rng;
    Blake3Aes256Gcm_t aes;
    byte salt[AES256_SALT_SIZE];
    byte key[AES256_KEY_SIZE];
    size_t decoded_len;
    const size_t input_len = strlen(INPUT);

    wc_InitRng(&rng);
    printf("Base64 Key:\n%s\n\n", argv[1]);

    // Generate random salt
    wc_RNG_GenerateBlock(&rng, salt, sizeof(salt));

    // Decode base64 encoded key
    decoded_len = base64_decode(argv[1], AES256_BASE64_KEY_SIZE, (char*)key);
    assert(decoded_len == AES256_KEY_SIZE);

    blake3aes256gcm_init(&aes, key, salt);

    byte input[AES_BLOCK_SIZE*3];
    memset(input, 0, sizeof(input));
    memmove(input, INPUT, input_len);

    byte cipher[sizeof(input)];
    memset(cipher, 0, sizeof(cipher));

    byte auth_tag[AES256_AUTH_TAG_SIZE];
    byte enc_iv[AES256_IV_SIZE];

    blake3aes256gcm_encrypt(&aes, cipher, input, input_len, enc_iv, auth_tag, NULL, 0);

    size_t i;
    ssize_t j;
    printf("Encrypted data (HEX):\n");
    for (i = 0; i < input_len; i++)
        printf("%02x", cipher[i]);

    printf("\n\nEncryption IV (HEX):\n");
    for (j = sizeof(enc_iv)-1; j >= 0; j--)
        printf("%02x", enc_iv[j]);

    printf("\n\nAuth tag (HEX):\n");
    for (i = 0; i < sizeof(auth_tag); i++)
        printf("%02x", auth_tag[i]);

    memset(input, 0, sizeof(input));
    blake3aes256gcm_decrypt(&aes, input, cipher, input_len, enc_iv, auth_tag, NULL, 0);
    printf("\n\nDecrypted data (HEX):\n%s\n", input);

    printf("\nIV after encrypt and decrypt (HEX):\n");
    for (j = sizeof(enc_iv)-1; j >= 0; j--)
        printf("%02x", aes.iv[j]);
    putchar('\n');

    blake3aes256gcm_destroy(&aes);
    wc_FreeRng(&rng);
    return 0;
}
