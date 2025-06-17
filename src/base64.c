/*
 * Base64 encoder and decoder implementation.
 * Author: Hossein Khosravi
 *
 * MIT License
 * Copyright (c) Hossein Khosravi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stddef.h>
#include "base64.h"

#define CHARSET_LENGTH (65)

static const char base64_chars[CHARSET_LENGTH] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char safe_base64_chars[CHARSET_LENGTH] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

// This table maps a character to it's index in the base64 charset.
// char_to_idx_map[(ASCII_CHAR)] => INDEX
static const char char_to_idx_map[130] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, 63, -1, 63, -1, 64, 52, 53,
    54, 55, 56, 57, 58, 59, 60, 61, -1, -1,
    -1, -1, -1, -1, -1,  0,  1,  2,  3,  4,
     5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
    25, -1, -1, -1, -1, 64, -1, 26, 27, 28,
    29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
    39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
    49, 50, 51, -1, -1, -1, -1, -1, -1, -1,
};

static inline long idx_in_charset(int ch) {
    return (char_to_idx_map[ch]);
}

static inline unsigned char uchar(char ch) {
    return ch;
}

size_t base64_encode(const char *in, size_t inlen, char *out, int mode) {
    size_t i = 0;
    unsigned char idx = 0;
    const char padd_char = (mode & BASE64_NO_PADDING) ? '\0' : '=';
    const char *charset = (mode & BASE64_URL_SAFE) ? safe_base64_chars : base64_chars;

    while (inlen) {
        idx = (uchar(in[0]) >> 2) & 0x3F;
        out[i++] = charset[idx];

        idx = ((uchar(in[0]) << 4) | ((inlen -= 1) ? (uchar(in[1]) >> 4) : 0)) & 0x3F;
        out[i++] = charset[idx];

        idx = ((uchar(in[1]) << 2) | ((inlen - 1) ? (uchar(in[2]) >> 6) : 0)) & 0x3F;
        out[i++] = ((inlen) ? charset[idx] : padd_char);
        if (inlen)
            inlen -= 1;

        idx = (uchar(in[2]) & 0x3F);
        out[i++] = ((inlen) ? (charset[idx]) : padd_char);

        if (inlen)
            inlen -= 1;

        if (inlen)
            in += 3;
    }
    return i;
}

size_t base64_decode(const char *in, size_t inlen, char *out) {
    size_t i, j = 0;
    long idx1, idx2, idx3, idx4;

    for (i = 0; i < inlen; i += 4) {
        if ((idx1 = idx_in_charset(in[i])) == -1)
            break;

        idx2 = ((i+1) >= inlen) ? 0 : idx_in_charset(in[i+1]);
        if (idx2 == -1)
            break;

        out[j++] = ((uchar(idx1) & 0x3F) << 2) | ((uchar(idx2) & 0x3F) >> 4);

        idx3 = ((i+2) >= inlen) ? 0 : idx_in_charset(in[i+2]);
        if (idx3 == -1)
            break;

        out[j++] = ((uchar(idx2) & 0x3F) << 4) | ((uchar(idx3) & 0x3F) >> 2);

        idx4 = ((i+3) >= inlen) ? 0 : idx_in_charset(in[i+3]);
        if (idx4 == -1)
            break;

        out[j++] = ((uchar(idx3) & 0x3F) << 6) | (uchar(idx4) & 0x3F);
    }
    return j;
}
