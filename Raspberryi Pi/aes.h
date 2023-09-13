#ifndef _AES_H_
#define _AES_H_

#include <stdint.h>
#include <stddef.h>


#define AES128 1
//#define AES192 1
//#define AES256 1

#define AES_BLOCKLEN 16 // Block length in bytes - AES is 128b block only


#define AES_KEYLEN 16   // Key length in bytes
#define AES_keyExpSize 176


struct AES_ctx
{
  uint8_t RoundKey[AES_keyExpSize];
};

void AES_init_ctx(struct AES_ctx* ctx, const uint8_t* key);

uint16_t AES_encode(uint8_t *data_buffer, uint8_t *enc_buffer,  uint16_t data_buffer_len);

void AES_decode(uint8_t *enc_buffer, uint8_t *dec_buffer,  uint16_t data_buffer_len);



#endif // _AES_H_
