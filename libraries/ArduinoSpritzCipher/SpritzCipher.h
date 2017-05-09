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


#ifndef _SPRITZCIPHER_H
#define _SPRITZCIPHER_H


#include <stdint.h> /* For uint8_t */


/** \def SAFE_TIMING_CRUSH
 * do safe timing swap in crush(), Because of the compiler optimization this may be not useful
 */
#define SAFE_TIMING_CRUSH

/** \def WIPE_AFTER_USAGE
 * wipe sensitive buffers and variables in functions when they are no longer needed
 */
#define WIPE_AFTER_USAGE

#define SPRITZ_N 256


/** \typedef spritz_t
 * \brief the context (contain the state), holds indices and S-Box.
 */
typedef struct
{
  uint8_t s[SPRITZ_N], i, j, k, z, a, w;
} spritz_t;


class SpritzCipher
{
  public:
    SpritzCipher();

    /** \fn void setup(spritz_t *ctx, const uint8_t *key, uint8_t keyLen)
     * \brief setup spritz state (spritz_t) with a key
     * \param ctx the context
     * \param key the key
     * \param keyLen length of the key in bytes
     */
    void
    setup(spritz_t *ctx,
          const uint8_t *key, uint8_t keyLen);


    /** \fn void setupIV(spritz_t *ctx, const uint8_t *key, uint8_t keyLen, const uint8_t *nonce, uint8_t nonceLen)
     * \brief setup spritz state (spritz_t) with a key and nonce (Salt)
     * \param ctx the context
     * \param key the key
     * \param keyLen length of the key in bytes
     * \param nonce the nonce (salt)
     * \param nonceLen length of the nonce in bytes
     */
    void
    setupIV(spritz_t *ctx,
            const uint8_t *key, uint8_t keyLen,
            const uint8_t *nonce, uint8_t nonceLen);


    /** \fn void wipe_spritz_ctx(spritz_t *ctx)
     * \brief Wipe spritz context (spritz_t) data
     * \param ctx the context
     */
    void
    wipe_spritz_ctx(spritz_t *ctx);


    /** \fn uint8_t spritz_rand_byte(spritz_t *ctx)
     * \brief generates a byte of keystream from spritz state (spritz_t)
     * \param ctx the context
     * \return byte of keystream
     */
    uint8_t
    spritz_rand_byte(spritz_t *ctx);


    /** \fn void hash(uint8_t *digest, uint8_t digestLen, const uint8_t *data, unsigned int dataLen)
     * \brief cryptographic hash function
     * \param digest digest (Hash) output.
     * \param digestLen length of the digest in bytes
     * \param data data to hash
     * \param dataLen length of the data in bytes
     */
    void
    hash(uint8_t *digest, uint8_t digestLen,
         const uint8_t *data, unsigned int dataLen);


    /** \fn void mac(uint8_t *digest, uint8_t digestLen, const uint8_t *msg, unsigned int msgLen, const uint8_t *key, uint8_t keyLen)
     * \brief message authentication code (MAC) function
     * \param digest MAC output.
     * \param digestLen length of the digest in bytes
     * \param msg the message to be authenticated
     * \param msgLen length of the message in bytes
     * \param key the secret key
     * \param keyLen length of the key in bytes
     */
    void
    mac(uint8_t *digest, uint8_t digestLen,
        const uint8_t *msg, unsigned int msgLen,
        const uint8_t *key, uint8_t keyLen);


  private:
    void stateInit(spritz_t *ctx);
    void update(spritz_t *ctx);
    void whip(spritz_t *ctx);
    void crush(spritz_t *ctx);
    void shuffle(spritz_t *ctx);
    void absorbNibble(spritz_t *ctx, const uint8_t nibble);
    void absorb(spritz_t *ctx, const uint8_t octet);
    void absorbStop(spritz_t *ctx);
    uint8_t output(spritz_t *ctx);
    uint8_t drip(spritz_t *ctx);
    void squeeze(spritz_t *ctx, uint8_t *out, uint8_t len);
};


#endif /* SpritzCipher.h */
