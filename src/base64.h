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

#ifndef _BASE64_H_
#define _BASE64_H_

#include <stddef.h>

#define base64_encoded_len(inlen) ((((inlen) + 2) / 3) << 2)
#define base64_decoded_len(inlen) ((3 * ((inlen) >> 2)) + 2)

enum {
    BASE64_NORMAL     = (1<<0),
    BASE64_URL_SAFE   = (1<<1),
    BASE64_NO_PADDING = (1<<2),
};

size_t base64_encode(const char *in, size_t inlen, char *out, int mode);

size_t base64_decode(const char *in, size_t inlen, char *out);

#endif // _BASE64_H_
