/* ccm-aes256.c
 *
 * Counter with CBC-MAC mode using AES256 as the underlying cipher.
 */

/* nettle, low-level cryptographics library
 *
 * Copyright (C) 2014 Exegin Technologies Limited
 * Copyright (C) 2014 Owen Kirby
 *
 * The nettle library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 * 
 * The nettle library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with the nettle library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02111-1301, USA.
 */

#if HAVE_CONFIG_H
# include "config.h"
#endif

#include <assert.h>

#include "aes.h"
#include "ccm.h"


void
ccm_aes256_set_key(struct ccm_aes256_ctx *ctx, const uint8_t *key)
{
  aes256_set_encrypt_key(&ctx->cipher, key);
}

void
ccm_aes256_set_nonce(struct ccm_aes256_ctx *ctx,
		     size_t length, const uint8_t *nonce,
		     size_t authlen, size_t msglen, size_t taglen)
{
  ccm_set_nonce(&ctx->ccm, &ctx->cipher, (nettle_cipher_func *) aes256_encrypt,
		length, nonce, authlen, msglen, taglen);
}

void
ccm_aes256_update(struct ccm_aes256_ctx *ctx,
		  size_t length, const uint8_t *data)
{
  ccm_update(&ctx->ccm, &ctx->cipher, (nettle_cipher_func *) aes256_encrypt,
	     length, data);
}

void
ccm_aes256_encrypt(struct ccm_aes256_ctx *ctx,
		   size_t length, uint8_t *dst, const uint8_t *src)
{
  ccm_encrypt(&ctx->ccm, &ctx->cipher, (nettle_cipher_func *) aes256_encrypt,
	      length, dst, src);
}

void
ccm_aes256_decrypt(struct ccm_aes256_ctx *ctx,
		   size_t length, uint8_t *dst, const uint8_t *src)
{
  ccm_decrypt(&ctx->ccm, &ctx->cipher, (nettle_cipher_func *) aes256_encrypt,
	      length, dst, src);
}

void
ccm_aes256_digest(struct ccm_aes256_ctx *ctx,
		  size_t length, uint8_t *digest)
{
  ccm_digest(&ctx->ccm, &ctx->cipher, (nettle_cipher_func *) aes256_encrypt,
	     length, digest);
}

void
ccm_aes256_encrypt_message(struct ccm_aes256_ctx *ctx,
			   size_t nlength, const uint8_t *nonce,
			   size_t alength, const uint8_t *adata,
			   size_t tlength,
			   size_t clength, uint8_t *dst, const uint8_t *src)
{
  ccm_encrypt_message(&ctx->cipher, (nettle_cipher_func *) aes256_encrypt,
		      nlength, nonce, alength, adata,
		      tlength, clength, dst, src);
}

int
ccm_aes256_decrypt_message(struct ccm_aes256_ctx *ctx,
			   size_t nlength, const uint8_t *nonce,
			   size_t alength, const uint8_t *adata,
			   size_t tlength,
			   size_t clength, uint8_t *dst, const uint8_t *src)
{
  return ccm_decrypt_message(&ctx->cipher, (nettle_cipher_func *) aes256_encrypt,
			     nlength, nonce, alength, adata,
			     tlength, clength, dst, src);
}
