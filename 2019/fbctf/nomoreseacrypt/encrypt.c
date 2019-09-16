#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

void random_letters(char* buff, size_t size) {
  static const char *letters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  while (size --> 0)
    *(buff++) = letters[rand() % 0x3e];
}

char hard_key[] = {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
    0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
    0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
    0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
    0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
    0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
    0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
    0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
    0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
    0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
    0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
    0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
    0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
    0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
    0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
    0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
    0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};

char key2[] = {0xe4, 0xb8, 0xc7, 0x5a, 0xcc, 0xb8, 0x77, 0xda,
    0xb0, 0xf5, 0xa6, 0xf0, 0xa7, 0xaa, 0x0e, 0x67};

char key3[] = {0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40};

void expand_key(char *a1, char *a2)
{
  uint64_t v4; // rax
  char *ptr; // rax
  unsigned int v6; // er11
  unsigned char v7; // r10
  unsigned char v8; // r9
  unsigned char v9; // r8
  unsigned char v10; // rsi
  unsigned char v11; // bp
  unsigned char v12; // r10
  unsigned char v13; // r9
  unsigned char v14; // r8
  unsigned char v15; // si

  v4 = 0LL;
  do
  {
    a1[v4] = a2[v4];
    a1[v4 + 1] = a2[v4 + 1];
    a1[v4 + 2] = a2[v4 + 2];
    a1[v4 + 3] = a2[v4 + 3];
    v4 += 4LL;
  }
  while ( v4 != 32 );
  ptr = a1;
  v6 = 8;
  do
  {
    v7 = ptr[28];
    v8 = ptr[29];
    v9 = ptr[30];
    v10 = ptr[31];
    if ( v6 & 7 )
    {
      if ( (v6 & 7) == 4 )
      {
        v7 = hard_key[v7];
        v8 = hard_key[v8];
        v9 = hard_key[v9];
        v10 = hard_key[v10];
      }
    }
    else
    {
      v11 = hard_key[v8];
      v8 = hard_key[v9];
      v9 = hard_key[v10];
      v10 = hard_key[v7];
      v7 = key3[v6 >> 3] ^ v11;
    }
    v12 = *ptr ^ v7;
    v13 = ptr[1] ^ v8;
    ++v6;
    v14 = ptr[2] ^ v9;
    v15 = ptr[3] ^ v10;
    ptr += 4;
    ptr[28] = v12;
    ptr[29] = v13;
    ptr[30] = v14;
    ptr[31] = v15;
  }
  while ( v6 != 60 );
  memcpy(a1 + 0xf0, key2, 0x10);
}

void xor_block(uint16_t keyrow, char *blk, char *key)
{
  char *v3; // rcx
  char *v4; // rdx
  size_t v5; // rax

  v3 = blk + 16;
  v4 = &key[16 * keyrow & 0xFF0];
  do
  {
    v5 = 0LL;
    do
    {
      blk[v5] ^= v4[v5];
      ++v5;
    }
    while ( v5 != 4 );
    blk += 4;
    v4 += 4;
  }
  while ( blk != v3 );
}

void encrypt(char *big_key, char *data, uint64_t size, char *hard_key)
{
  int v4; // er14
  char *data_; // r12
  signed int v9; // eax
  int64_t v10; // rbx
  int v11; // edi
  int v13; // er11
  char v14; // rdx
  char *v15; // r10
  int64_t v16; // rax
  int64_t v17; // rcx
  char tmp;
  char *v19; // rsi
  uint64_t v25; // rax
  int v26; // ecx
  int v27; // eax
  int v28; // ecx
  int v29; // eax
  int v30; // eax
  int v31; // eax
  int v32; // edi
  int v33; // eax
  int v34; // eax
  char *v35; // r8
  char *v36; // r10
  int64_t v38; // rax
  char v39; // al
  char v40; // dl
  char v41; // dl
  char v42; // dl
  char v43; // al
  char v44; // dl
  int64_t v45; // rax
  char v46; // dl
  int64_t v47; // rdx
  unsigned int v48; // [rsp+Ch] [rbp-6Ch]
  uint64_t v49; // [rsp+18h] [rbp-60h]
  char block[16]; // [rsp+28h] [rbp-50h]

  data_ = data;
  v49 = size;
  v48 = 0;
  v9 = 16;
  while ( 1 )
  {
    v10 = v48;
    if ( v48 >= v49 )
      break;
    if ( v9 == 16 )
    {
      v11 = 0;
      memcpy(block, big_key + 0xf0, 16);
      xor_block(0, block, big_key);
      v13 = 1;
      do
      {
        v15 = block;
        v36 = &block[4];
        do
        {
          v16 = 0LL;
          do
          {
            v15[4 * v16] = hard_key[(uint8_t)v15[4*v16]];
            v16++;
          }
          while ( v16 != 4 );
          ++v15;
        }
        while ( v36 != v15 );

        tmp = block[1];
        block[1] = block[5];
        block[5] = block[9];
        block[9] = block[13];
        block[13] = tmp;

        tmp = block[10];
        block[10] = block[2];
        block[2] = tmp;

        tmp = block[14];
        block[14] = block[6];
        block[6] = tmp;

        tmp = block[3];
        block[3] = block[15];
        block[15] = block[11];
        block[11] = block[7];
        block[7] = tmp;

        v19 = block;
        char *end = v19 + 0x10;
        do
        {
          (v14) = *v19;
          (v17) = v19[1];
          v19 += 4;
          (v11) = *(v19 - 1) ^ *(v19 - 2);
          v26 = (unsigned int)v14 ^ v17;
          (v25) = v26;
          (v4) = v26;
          v26 *= 2;
          (v25) = (unsigned char)v25 >> 7;
          v4 ^= v11;
          v27 = v26 ^ 27 * (int)v25;
          (v26) = (char)v14;
          (v14) = *(v19 - 1) ^ (unsigned char)v14;
          v28 = v4 ^ v26;
          v29 = v28 ^ v27;
          (v28) = *(v19 - 2) ^ *(v19 - 3);
          *(v19 - 4) = v29;
          (v29) = v28;
          v28 *= 2;
          (v29) = (unsigned char)v29 >> 7;
          v30 = v28 ^ 27 * v29;
          (v28) = *(v19 - 3);
          (v17) = v4 ^ v28;
          v31 = v17 ^ v30;
          *(v19 - 3) = v31;
          (v31) = v11;
          v32 = 2 * v11;
          (v31) = (unsigned char)v31 >> 7;
          v33 = v32 ^ 27 * v31;
          (v32) = *(v19 - 2);
          v11 = v4 ^ v32;
          (v4) = *(v19 - 1) ^ v4;
          v34 = v11 ^ v33;
          *(v19 - 2) = v34;
          (v34) = (unsigned char)v14 >> 7;
          (v25) = 27 * v34;
          (v14) = v4 ^ (unsigned int)v25 ^ 2 * (int)v14;
          *(v19 - 1) = (char)v14;
        }
        while ( end != v19 );
        v11 = v13;
        xor_block(v13, block, big_key);
        v13++;
      }
      while ( v13 != 14 );
      v35 = block;
      v36 = &block[4];
      do
      {
        v38 = 0LL;
        do
        {
          v35[4 * v38] = hard_key[(uint8_t)v35[4 * v38]];
          ++v38;
        }
        while ( v38 != 4 );
        ++v35;
      }
      while ( v36 != v35 );
      v39 = block[1];
      block[1] = block[5];
      block[5] = block[9];
      v40 = block[13];
      block[13] = v39;
      block[9] = v40;
      v41 = block[10];
      block[10] = block[2];
      block[2] = v41;
      v42 = block[14];
      block[14] = block[6];
      v43 = block[3];
      block[6] = v42;
      block[3] = block[15];
      block[15] = block[11];
      v44 = block[7];
      block[7] = v43;
      block[11] = v44;
      xor_block(14, block, big_key);
      v45 = 15LL;
      while ( 1 )
      {
        v46 = big_key[v45 + 240];
        if ( v46 != -1 )
          break;
        big_key[v45-- + 240] = 0;
        if ( v45 == -1 )
          goto LABEL_20;
      }
      big_key[(signed int)v45 + 240] = v46 + 1;
LABEL_20:
      v9 = 0;
    }
    v47 = v9;
    ++v48;
    ++v9;
    data_[v10] ^= block[v47];
  }
}

void dump_hex(char *buff, size_t s) {
  for (int i = 0; i < s; i++) {
    printf("%02hhx ", buff[i]);
    if ((i + 1) % 16 == 0) {
      puts("");
    }
  }
}

const char begin[] = "// Copyright 2019 - QwarkSoft";

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Usage: %s FILE TIME\n", argv[0]);
    return 1;
  }

  char letters[0x20];
  char big_key[0x100];

  int fd = open(argv[1], O_RDONLY);
  int size = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);
  char *data = malloc(size);


  int base = atoi(argv[2]);
  
  for (int j = -24; j < 24; j++) {
    for (int i = -100; i < 100; i++) {
  //    srand(1552354950 + i);

      fd = open(argv[1], O_RDONLY);
      read(fd, data, size);
      srand(base + i + j * 3600);

      random_letters(letters, 0x20LL);
      //printf("Key: %s\n", letters);

      expand_key(big_key, letters);
      //dump_hex(big_key, sizeof(big_key));

      encrypt(big_key, data, size, hard_key);

      if (!strncmp(begin, data, sizeof(begin) - 1)) {
        puts(data);
        return 0;
      }
      close(fd);
    }
  }
  puts("Failed...");
}
