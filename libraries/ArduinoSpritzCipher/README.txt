SpritzCipher
============

Spritz library for Arduino.
A spongy RC4-like stream cipher. This library contains cryptographically secure
pseudo-random bytes generator, Hash & MAC with configurable output length.

This library can be used to:
  * Encrypt data.
  * Generate random numbers.
  * Hash & authenticate data.

Home page: <https://github.com/abderraouf-adjal/ArduinoSpritzCipher>

Spritz paper: <https://people.csail.mit.edu/rivest/pubs/RS14.pdf>


Library content for user
========================

* Types
  spritz_t - The context/ctx (contain the state), holds indices and S-Box.

* Functions
  setup(ctx, key, keyLen) - Setup spritz state (spritz_t) with a key.
  setupIV(ctx, key, keyLen, nonce, nonceLen) - Setup spritz state (spritz_t) with a key and nonce (Salt).
  wipe_spritz_ctx(ctx)    - Wipe spritz context data.
  spritz_rand_byte(ctx)   - Generates a byte of keystream from spritz state (spritz_t).
  hash(digest, digestLen, data, dataLen)           - Cryptographic hash function.
  mac(digest, digestLen, msg, msgLen, key, keyLen) - Message Authentication Code (MAC) function.

See <SpritzCipher.h> for the details.


Examples
========

* Hash data:
  ./examples/SpritzCipherHashTest/SpritzCipherHashTest.ino

* Generate random bytes:
  ./examples/SpritzCipherStreamTest/SpritzCipherStreamTest.ino


Installation Guide
==================

<https://www.arduino.cc/en/Guide/Libraries>


Reporting bugs
==============

Create an issue on GitHub:
<https://github.com/abderraouf-adjal/ArduinoSpritzCipher/issues>


Copyright
=========

Copyright (c) 2015 Abderraouf Adjal
License: The MIT License.
