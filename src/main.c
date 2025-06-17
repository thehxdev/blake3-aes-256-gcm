#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include "blake3aes256gcm.h"

#define INPUT "This is Blake3-AES-256-GCM!"

int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;

    const size_t input_len = strlen(INPUT);
    Blake3Aes256Gcm_t aes;

    printf("Base64 Key:\n%s\n\n", argv[1]);

    blake3aes256gcm_init(&aes, (byte*)argv[1], AES256_KEY_TYPE_BASE64);

    byte input[AES_BLOCK_SIZE*3];
    memset(input, 0, sizeof(input));
    memmove(input, INPUT, input_len);

    byte cipher[sizeof(input)];
    memset(cipher, 0, sizeof(cipher));

    byte auth_tag[AES256_AUTH_TAG_LENGTH];
    byte enc_iv[AES256_IV_LENGTH];

    blake3aes256gcm_encrypt(&aes, cipher, input, input_len, enc_iv, auth_tag, sizeof(auth_tag), NULL, 0);

    size_t i;
    ssize_t j;
    printf("Encrypted data:\n");
    for (i = 0; i < input_len; i++)
        printf("%02x", cipher[i]);

    printf("\n\nEncryption IV:\n");
    for (j = sizeof(enc_iv)-1; j >= 0; j--)
        printf("%02x", enc_iv[j]);

    printf("\n\nAuth tag:\n");
    for (i = 0; i < sizeof(auth_tag); i++)
        printf("%02x", auth_tag[i]);

    memset(input, 0, sizeof(input));
    blake3aes256gcm_decrypt(&aes, input, cipher, input_len, enc_iv, auth_tag, sizeof(auth_tag), NULL, 0);
    printf("\n\nDecrypted data:\n%s\n", input);

    printf("\nIV after encrypt and decrypt:\n");
    for (j = sizeof(enc_iv)-1; j >= 0; j--)
        printf("%02x", aes.iv[j]);
    putchar('\n');

    blake3aes256gcm_destroy(&aes);
    return 0;
}
