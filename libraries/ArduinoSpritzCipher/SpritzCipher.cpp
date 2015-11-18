/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Abderraouf Adjal
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


#include "SpritzCipher.h"


#define SPRITZ_N_MINUS_1 255 /* SPRITZ_N - 1 */
#define SPRITZ_N_HALF 128 /* SPRITZ_N / 2 */


SpritzCipher::SpritzCipher() { }


static void
swap(uint8_t *a, uint8_t *b)
{
  uint8_t t = *a;
  *a = *b;
  *b = t;
}


void
SpritzCipher::stateInit(spritz_t *ctx)
{
  uint8_t i;
  ctx->i = ctx->j = ctx->k = ctx->z = ctx->a = 0;
  ctx->w = 1;
  for (i = 0; i < SPRITZ_N_MINUS_1; i++) {
    ctx->s[i] = i;
  }
  ctx->s[255] = 255;
}

void
SpritzCipher::update(spritz_t *ctx)
{
  ctx->i += ctx->w;
  ctx->j  = ctx->k + ctx->s[(uint8_t)(ctx->j + ctx->s[ctx->i])];
  ctx->k += ctx->i + ctx->s[ctx->j];
  swap(&ctx->s[ctx->i], &ctx->s[ctx->j]);
}

void
SpritzCipher::whip(spritz_t *ctx)
{
  uint8_t i;
  for (i = 0; i < SPRITZ_N_HALF; i++) {
    update(ctx);
    update(ctx);
    update(ctx);
    update(ctx);
  }
  ctx->w += 2;
}

void
SpritzCipher::crush(spritz_t *ctx)
{
  uint8_t i, j = SPRITZ_N_MINUS_1;
#ifdef SAFE_TIMING_CRUSH
  uint8_t s_i, s_j;
  for (i = 0; i < SPRITZ_N_HALF; i++, j--) {
    if ((s_i = ctx->s[i]) > (s_j = ctx->s[j])) {
      ctx->s[i] = s_j;
      ctx->s[j] = s_i;
    }
    else {
      ctx->s[i] = s_i;
      ctx->s[j] = s_j;
    }
  }
#else /* SAFE_TIMING_CRUSH */
  for (i = 0; i < SPRITZ_N_HALF; i++, j--) {
    if (ctx->s[i] > ctx->s[j]) {
      swap(&ctx->s[i], &ctx->s[j]);
    }
  }
#endif
}

void
SpritzCipher::shuffle(spritz_t *ctx)
{
  whip(ctx);
  crush(ctx);
  whip(ctx);
  crush(ctx);
  whip(ctx);
  ctx->a = 0;
}

/* Tip: nibble=4bit; octet=2*nibble=8bit; byte=octet in modern computers */
void
SpritzCipher::absorbNibble(spritz_t *ctx, const uint8_t nibble)
{
  if (ctx->a == SPRITZ_N_HALF) {
    shuffle(ctx);
  }
  swap(&ctx->s[ctx->a], &ctx->s[SPRITZ_N_HALF + nibble]);
  ctx->a++;
}
void
SpritzCipher::absorb(spritz_t *ctx, const uint8_t octet)
{
  absorbNibble(ctx, octet % 16); /* Low */
  absorbNibble(ctx, octet / 16); /* High */
}

void
SpritzCipher::absorbStop(spritz_t *ctx)
{
  if (ctx->a == SPRITZ_N_HALF) {
    shuffle(ctx);
  }
  ctx->a++;
}

uint8_t
SpritzCipher::output(spritz_t *ctx)
{
  ctx->z = ctx->s[(uint8_t)(ctx->j + ctx->s[(uint8_t)(ctx->i + ctx->s[(uint8_t)(ctx->z + ctx->k)])])];
  return ctx->z;
}
uint8_t
SpritzCipher::drip(spritz_t *ctx)
{
  if (ctx->a) {
    shuffle(ctx);
  }
  update(ctx);
  return output(ctx);
}

/* squeeze() for hash() and mac() */
void
SpritzCipher::squeeze(spritz_t *ctx, uint8_t *out, uint8_t len)
{
  uint8_t i;
  if (ctx->a) {
    shuffle(ctx);
  }
  for (i = 0; i < len; i++) {
    out[i] = drip(ctx);
  }
}


/* ================ User Functions ================ */

/* Setup spritz state (spritz_t) with a key */
void
SpritzCipher::setup(spritz_t *ctx,
                    const uint8_t *key, uint8_t keyLen)
{
  uint8_t i;
  stateInit(ctx);
  for (i = 0; i < keyLen; i++) {
    absorb(ctx, key[i]);
  }
}

/* Setup spritz state (spritz_t) with a key and nonce (Salt) */
void
SpritzCipher::setupIV(spritz_t *ctx,
                      const uint8_t *key, uint8_t keyLen,
                      const uint8_t *nonce, uint8_t nonceLen)
{
  uint8_t i;
  setup(ctx, key, keyLen);
  absorbStop(ctx);
  for (i = 0; i < nonceLen; i++) {
    absorb(ctx, nonce[i]);
  }
}

/* Wipe spritz context (spritz_t) data */
void
SpritzCipher::wipe_spritz_ctx(spritz_t *ctx)
{
  uint8_t i;
  ctx->i = ctx->j = ctx->k = ctx->z = ctx->a = ctx->w = 0;
  for (i = 0; i < SPRITZ_N_MINUS_1; i++) {
    ctx->s[i] = 0;
  }
  ctx->s[255] = 0;
}


/* Generates a byte of keystream from spritz state (spritz_t) */
uint8_t
SpritzCipher::spritz_rand_byte(spritz_t *ctx)
{
  return drip(ctx);
}


/* Cryptographic hash function */
void
SpritzCipher::hash(uint8_t *digest, uint8_t digestLen,
                   const uint8_t *data, unsigned int dataLen)
{
  spritz_t ctx;
  unsigned int i;
  stateInit(&ctx);
  for (i = 0; i < dataLen; i++) {
    absorb(&ctx, data[i]);
  }
  absorbStop(&ctx);
  absorb(&ctx, digestLen);
  squeeze(&ctx, digest, digestLen);
#ifdef WIPE_AFTER_USAGE
  wipe_spritz_ctx(&ctx);
#endif
}

/* Message Authentication Code (MAC) function */
void
SpritzCipher::mac(uint8_t *digest, uint8_t digestLen,
                  const uint8_t *msg, unsigned int msgLen,
                  const uint8_t *key, uint8_t keyLen)
{
  spritz_t ctx;
  unsigned int i;
  stateInit(&ctx);
  for (i = 0; i < keyLen; i++) {
    absorb(&ctx, key[i]);
  }
  absorbStop(&ctx);
  for (i = 0; i < msgLen; i++) {
    absorb(&ctx, msg[i]);
  }
  absorbStop(&ctx);
  absorb(&ctx, digestLen);
  squeeze(&ctx, digest, digestLen);
#ifdef WIPE_AFTER_USAGE
  wipe_spritz_ctx(&ctx);
#endif
}
