#include <stdio.h>
//#include <windows.h>
//#include <defs.h>
#include <immintrin.h>
#include <sys/stat.h>
#include <stdint.h>

#define __fastcall 

int *__fastcall read100(char *file, int a2)
{
  int *buf; // rbx
  int inH; // er8
  int v4; // eax
  int *result; // rax
  int v6; // eax
  void *v7; // rdi

  buf = malloc(0x1014uLL);
  buf[1024] = 0;
  buf[1025] = 0;
  buf[1028] = a2;
  if ( a2 == 1 )
  {
    v6 = open(file, 65, 420LL);
    buf[1027] = v6;
    if ( v6 == -1 )
    {
LABEL_9:
      v7 = buf;
      buf = 0LL;
      free(v7);
      return buf;
    }
    memset(buf, 0, 0x1000uLL);
    result = buf;
  }
  else
  {
    if ( !a2 )
    {
      inH = open(file, 0);
      buf[1027] = inH;
      if ( inH != -1 )
      {
        memset(buf, 0, 0x1000uLL);
        v4 = read(inH, buf, 0x1000uLL);
        buf[1026] = v4;
        if ( v4 != -1 )
          return buf;
      }
      goto LABEL_9;
    }
    result = 0LL;
  }
  return result;
}

uint64_t __fastcall readMore1000(void *buf)
{
  int *v1; // rbx
  int v2; // eax
  int v3; // esi
  int v4; // edx
  char v5; // bp
  int v6; // eax
  int v8; // eax
  bool v9; // zf
  unsigned uint64_t v10; // rdi
  int v11; // eax
  int v12; // eax

  if ( *((int *)buf + 1028) )
    return 0xFFFFFFFFLL;
  v1 = buf;
  v2 = *((int *)buf + 1024);
  if ( v2 != 8 )
  {
    v3 = *((int *)buf + 1025);
    v4 = v2 + 1;
    v5 = 7 - v2;
LABEL_4:
    v6 = *((unsigned char *)v1 + v3);
    v1[1024] = v4;
    return (v6 >> v5) & 1;
  }
  v8 = *((int *)buf + 1025);
  *((int *)buf + 1024) = 0;
  v4 = 1;
  v5 = 7;
  v3 = v8 + 1;
  v9 = v8 + 1 == *((int *)buf + 1026);
  *((int *)buf + 1025) = v8 + 1;
  if ( !v9 )
    goto LABEL_4;
  *(_QWORD *)buf = 0LL;
  *((_QWORD *)buf + 511) = 0LL;
  v10 = (unsigned uint64_t)buf + 8;
  *(int *)(v10 + 4092) = 0;
  memset((void *)(v10 & 0xFFFFFFFFFFFFFFF8LL), 0, 8 * (((unsigned int)v1 - (v10 & 0xFFFFFFF8) + 4096) >> 3));
  v11 = read(v1[1027], v1, 0x1000uLL);
  v1[1026] = v11;
  if ( v11 )
  {
    v12 = v1[1024];
    v3 = v1[1025];
    v5 = 7 - v12;
    v4 = v12 + 1;
    goto LABEL_4;
  }
  return 0xFFFFFFFFLL;
}

uint64_t __fastcall dycryptWrite(void *buf)
{
  int v1; // eax
  int v2; // edx
  int v3; // edx

  v1 = *((int *)buf + 1028);
  if ( v1 == 2 )
    return 0LL;
  if ( v1 )
  {
    if ( *((int *)buf + 1024) <= 0 )
    {
      v2 = *((int *)buf + 1025);
    }
    else
    {
      v2 = *((int *)buf + 1025) + 1;
      *((int *)buf + 1025) = v2;
    }
    write(*((int *)buf + 1027), buf, v2);
    close(*((int *)buf + 1027));
    v3 = *((int *)buf + 1024);
    *((int *)buf + 1028) = 2;
    if ( v3 )
      return (unsigned int)(8 - v3);
  }
  else
  {
    close(*((int *)buf + 1027));
    *((int *)buf + 1028) = 2;
  }
  return 0LL;
}

uint64_t __fastcall compar(const void *a1, const void *a2)
{
  uint64_t result; // rax

  result = (unsigned int)(*(int *)(*(_QWORD *)a1 + 20LL) - *(int *)(*(_QWORD *)a2 + 20LL));
  if ( *(int *)(*(_QWORD *)a1 + 20LL) == *(int *)(*(_QWORD *)a2 + 20LL) )
    result = **(unsigned char **)a1 - (unsigned int)**(unsigned char **)a2;
  return result;
}

typedef int(* __compar_fn_t)(const void *, const void *);

uint64_t __fastcall sub_4190(const void *a1, const void *a2)
{
    return *(unsigned char *)a1 - (unsigned int)*(unsigned char *)a2;
}

__m128i xmmword_4A20;

void __fastcall sub_4340(void *dest, signed int a2, int a3)
{
    char *v3; // r12
    signed int v4; // ebp
    char *v5; // rbx
    signed int *v6; // r13
    __m128i v7; // xmm6
    unsigned uint64_t v8; // rdi
    int v9; // esi
    unsigned int v10; // er8
    unsigned int v11; // edx
    char *v12; // r9
    signed uint64_t v13; // r10
    int v14; // eax
    int v15; // ecx
    int v16; // er11
    unsigned int v17; // er10
    int v18; // er14
    unsigned int v19; // er15
    __m128i v20; // xmm7
    __m128i v21; // xmm0
    __m128i v22; // xmm7
    const __m128i *v23; // r8
    __m128i v24; // xmm7
    __m128i v25; // xmm1
    __m128i v26; // xmm1
    __m128i v27; // xmm3
    __m128i v28; // xmm2
    __m128i v29; // xmm1
    __m128i v30; // xmm8
    __m128i v31; // xmm0
    __m128i v32; // xmm2
    __m128i v33; // xmm0
    __m128i zero = { 0 };
    int v34; // er8
    int v35; // ecx
    uint64_t v36; // rcx
    int v37; // er8
    uint64_t v38; // rax
    size_t n; // [rsp+20h] [rbp-48h]
    int v40; // [rsp+28h] [rbp-40h]
    unsigned int v41; // [rsp+2Ch] [rbp-3Ch]

    v3 = dest;
    v4 = a2;
    v40 = a3;
    n = a2;
    v5 = (char *)malloc(a2);
    v6 = (signed int *)malloc(4LL * a2);
    if (a2 <= 0)
    {
        qsort(v5, a2, 1uLL, (__compar_fn_t)sub_4190);
        goto LABEL_37;
    }
    v41 = a2 - 1;
    memcpy(v5, dest, (unsigned int)(a2 - 1) + 1LL);
    qsort(v5, a2, 1uLL, (__compar_fn_t)sub_4190);
    v7 = _mm_load_si128((const __m128i *)&xmmword_4A20);
    v8 = 1LL;
    v9 = 0;
    do
    {
        v10 = v8;
        v11 = (unsigned char)v5[v8 - 1];
        if ((-(signed int)v5 & 0xFu) <= (unsigned int)v8)
            v10 = -(signed int)v5 & 0xF;
        v12 = v5;
        if (v8 > 0x13)
        {
            if (!v10)
            {
                v15 = 0;
                v14 = 0;
            LABEL_10:
                v16 = v8 - v10;
                v17 = (((unsigned int)v8 - v10 - 16) >> 4) + 1;
                v18 = 16 * v17;
                if (v9 - v10 <= 0xE)
                    goto LABEL_43;
                v19 = 0;
                v20 = _mm_cvtsi32_si128(v11);
                v21 = zero;
                v22 = _mm_unpacklo_epi8(v20, v20);
                v23 = (const __m128i *)&v5[v10];
                v24 = _mm_shuffle_epi32(_mm_unpacklo_epi16(v22, v22), 0);
                do
                {
                    ++v19;
                    v25 = _mm_cmpeq_epi8(_mm_load_si128(v23), v24);
                    ++v23;
                    v26 = _mm_and_si128(v25, v7);
                    v27 = _mm_cmpgt_epi8(zero, v26);
                    v28 = _mm_unpacklo_epi8(v26, v27);
                    v29 = _mm_unpackhi_epi8(v26, v27);
                    v30 = _mm_cmpgt_epi16(zero, v28);
                    v31 = _mm_add_epi32(_mm_add_epi32(v21, _mm_unpacklo_epi16(v28, v30)), _mm_unpackhi_epi16(v28, v30));
                    v32 = _mm_cmpgt_epi16(zero, v29);
                    v21 = _mm_add_epi32(_mm_add_epi32(v31, _mm_unpacklo_epi16(v29, v32)), _mm_unpackhi_epi16(v29, v32));
                } while (v17 > v19);
                v15 += v18;
                v33 = _mm_add_epi32(v21, _mm_srli_si128(v21, 8));
                v14 += _mm_cvtsi128_si32(_mm_add_epi32(v33, _mm_srli_si128(v33, 4)));
                if (v18 != v16)
                {
                LABEL_43:
                    v14 += (char)v11 == v5[v15];
                    if (v15 + 1 <= v9)
                    {
                        v14 += (char)v11 == v5[v15 + 1];
                        if (v9 >= v15 + 2)
                        {
                            v14 += (char)v11 == v5[v15 + 2];
                            if (v9 >= v15 + 3)
                            {
                                v14 += (char)v11 == v5[v15 + 3];
                                if (v9 >= v15 + 4)
                                {
                                    v14 += (char)v11 == v5[v15 + 4];
                                    if (v9 >= v15 + 5)
                                    {
                                        v14 += (char)v11 == v5[v15 + 5];
                                        if (v9 >= v15 + 6)
                                        {
                                            v14 += (char)v11 == v5[v15 + 6];
                                            if (v9 >= v15 + 7)
                                            {
                                                v14 += (char)v11 == v5[v15 + 7];
                                                if (v9 >= v15 + 8)
                                                {
                                                    v14 += (char)v11 == v5[v15 + 8];
                                                    if (v9 >= v15 + 9)
                                                    {
                                                        v14 += (char)v11 == v5[v15 + 9];
                                                        if (v9 >= v15 + 10)
                                                        {
                                                            v14 += (char)v11 == v5[v15 + 10];
                                                            if (v9 >= v15 + 11)
                                                            {
                                                                v14 += (char)v11 == v5[v15 + 11];
                                                                if (v9 >= v15 + 12)
                                                                {
                                                                    v14 += (char)v11 == v5[v15 + 12];
                                                                    v34 = v15 + 13;
                                                                    if (v9 >= v15 + 13)
                                                                    {
                                                                        v35 = v15 + 14;
                                                                        v14 += (char)v11 == v5[v34];
                                                                        if (v9 >= v35)
                                                                            v14 += (char)v11 == v5[v35];
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                goto LABEL_29;
            }
        }
        else
        {
            v10 = v8;
        }
        v13 = 1LL;
        v14 = 0;
        do
        {
            v14 += (char)v11 == v5[v13 - 1];
            v15 = v13++;
        } while (v13 != v10 - 1 + 2LL);
        if ((int)v8 != v10)
            goto LABEL_10;
    LABEL_29:
        v36 = 0LL;
        v37 = 0;
        do
        {
            while ((char)v11 != v3[v36] || v14 != ++v37)
            {
                if (v4 <= (signed int)++v36)
                    goto LABEL_34;
            }
            v6[v8 - 1] = v36++;
        } while (v4 > (signed int)v36);
    LABEL_34:
        ++v9;
        ++v8;
    } while (v4 != v9);
    v38 = v40;
    do
    {
        v38 = v6[v38];
        *(++v12 - 1) = v3[v38];
    } while (v12 < &v5[v41 + 1]);
LABEL_37:
    memcpy(v3, v5, n);
    free(v5);
    free(v6);
}


char xmmword_48C0[] = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F";
char xmmword_48D0[] = "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F";
char xmmword_48E0[] = " !\"#$%&'()*+,-./";
char xmmword_48F0[] = "0123456789:;<=>?";
char xmmword_4900[] = "@ABCDEFGHIJKLMNO";
char xmmword_4910[] = "PQRSTUVWXYZ[\]^_";
char xmmword_4920[] = "`abcdefghijklmno";
char xmmword_4930[] = "pqrstuvwxyz{|}~\x7F";
char xmmword_4940[] = "\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8A\x8B\x8C\x8D\x8E\x8F";
char xmmword_4950[] = "\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9A\x9B\x9C\x9D\x9E\x9F";
char xmmword_4960[] = "\xA0\xA1\xA2\xA3\xA4\xA5\xA6\xA7\xA8\xA9\xAA\xAB\xAC\xAD\xAE\xAF";
char xmmword_4970[] = "\xB0\xB1\xB2\xB3\xB4\xB5\xB6\xB7\xB8\xB9\xBA\xBB\xBC\xBD\xBE\xBF";
char xmmword_4980[] = "\xC0\xC1\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xCA\xCB\xCC\xCD\xCE\xCF";
char xmmword_4990[] = "\xD0\xD1\xD2\xD3\xD4\xD5\xD6\xD7\xD8\xD9\xDA\xDB\xDC\xDD\xDE\xDF";
char xmmword_49A0[] = "\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF";

__m128i xmmword_206100 = {0};
__m128i xmmword_206110 = {0};
__m128i xmmword_206120 = {0};
__m128i xmmword_206130 = {0};
__m128i xmmword_206140 = {0};
__m128i xmmword_206150 = {0};
__m128i xmmword_206160 = {0};
__m128i xmmword_206170 = {0};
__m128i xmmword_206180 = {0};
__m128i xmmword_206190 = {0};
__m128i xmmword_2061A0 = {0};
__m128i xmmword_2061B0 = {0};
__m128i xmmword_2061C0 = {0};
__m128i xmmword_2061D0 = {0};
__m128i xmmword_2061E0 = {0};

char byte_2061F0 = {0};
char byte_2061F1 = {0};
char byte_2061F2 = {0};
char byte_2061F3 = {0};
char byte_2061F4 = {0};
char byte_2061F5 = {0};
char byte_2061F6 = {0};
char byte_2061F7 = {0};
char byte_2061F8 = {0};
char byte_2061F9 = {0};
char byte_2061FA = {0};
char byte_2061FB = {0};
char byte_2061FC = {0};
char byte_2061FD = {0};
char byte_2061FE = {0};

__m128i xmmword_206200 = {0};
__m128i xmmword_206210 = {0};
__m128i xmmword_206220 = {0};
__m128i xmmword_206230 = {0};
__m128i xmmword_206240 = {0};
__m128i xmmword_206250 = {0};
__m128i xmmword_206260 = {0};
__m128i xmmword_206270 = {0};
__m128i xmmword_206280 = {0};
__m128i xmmword_206290 = {0};
__m128i xmmword_2062A0 = {0};
__m128i xmmword_2062B0 = {0};
__m128i xmmword_2062C0 = {0};
__m128i xmmword_2062D0 = {0};
__m128i xmmword_2062E0 = {0};

char byte_2062F0 = {0};
char byte_2062F1 = {0};
char byte_2062F2 = {0};
char byte_2062F3 = {0};
char byte_2062F4 = {0};
char byte_2062F5 = {0};
char byte_2062F6 = {0};
char byte_2062F7 = {0};
char byte_2062F8 = {0};
char byte_2062F9 = {0};
char byte_2062FA = {0};
char byte_2062FB = {0};
char byte_2062FC = {0};
char byte_2062FD = {0};
char byte_2062FE = {0};


int __fastcall my_wtf2(const char *a1, const char *a2)
{
    signed int v2; // eax
    signed int v3; // er12
    signed int v4; // ebp
    char *v5; // rax
    int v6; // edx
    size_t v7; // r12
    uint64_t v8; // r14
    char v9; // r13
    const char *v11; // rdx
    uint64_t fd; // [rsp+0h] [rbp-2058h]
    int v13; // [rsp+1Ch] [rbp-203Ch]
    char buf[8248]; // [rsp+20h] [rbp-2038h]

    LODWORD(fd) = open(a1, 0);
    if ((int)fd == -1)
    {
        v11 = a1;
        goto LABEL_15;
    }
    HIDWORD(fd) = open(a2, 65, 420LL, fd);
    if (HIDWORD(fd) == -1)
    {
        v11 = a2;
    LABEL_15:
        fprintf(stderr, "%s: could not open file\n", v11, fd);
        exit(1);
    }
    xmmword_206100 = _mm_load_si128((const __m128i *)&xmmword_48C0);
    xmmword_206200 = xmmword_206100;
    xmmword_206110 = _mm_load_si128((const __m128i *)&xmmword_48D0);
    xmmword_206210 = xmmword_206110;
    xmmword_206120 = _mm_load_si128((const __m128i *)&xmmword_48E0);
    xmmword_206220 = xmmword_206120;
    xmmword_206130 = _mm_load_si128((const __m128i *)&xmmword_48F0);
    xmmword_206230 = xmmword_206130;
    xmmword_206140 = _mm_load_si128((const __m128i *)&xmmword_4900);
    xmmword_206240 = xmmword_206140;
    xmmword_206150 = _mm_load_si128((const __m128i *)&xmmword_4910);
    xmmword_206250 = xmmword_206150;
    xmmword_206160 = _mm_load_si128((const __m128i *)&xmmword_4920);
    xmmword_206260 = xmmword_206160;
    xmmword_206170 = _mm_load_si128((const __m128i *)&xmmword_4930);
    xmmword_206270 = xmmword_206170;
    xmmword_206180 = _mm_load_si128((const __m128i *)&xmmword_4940);
    xmmword_206280 = xmmword_206180;
    xmmword_206190 = _mm_load_si128((const __m128i *)&xmmword_4950);
    xmmword_206290 = xmmword_206190;
    xmmword_2061A0 = _mm_load_si128((const __m128i *)&xmmword_4960);
    xmmword_2062A0 = xmmword_2061A0;
    byte_2061F0 = -16;
    byte_2062F0 = -16;
    xmmword_2061B0 = _mm_load_si128((const __m128i *)&xmmword_4970);
    byte_2061F1 = -15;
    byte_2062F1 = -15;
    xmmword_2062B0 = xmmword_2061B0;
    byte_2061F2 = -14;
    byte_2062F2 = -14;
    xmmword_2061C0 = _mm_load_si128((const __m128i *)&xmmword_4980);
    byte_2061F3 = -13;
    byte_2062F3 = -13;
    xmmword_2062C0 = xmmword_2061C0;
    byte_2061F4 = -12;
    byte_2062F4 = -12;
    xmmword_2061D0 = _mm_load_si128((const __m128i *)&xmmword_4990);
    byte_2061F5 = -11;
    byte_2062F5 = -11;
    xmmword_2062D0 = xmmword_2061D0;
    byte_2061F6 = -10;
    byte_2062F6 = -10;
    xmmword_2061E0 = _mm_load_si128((const __m128i *)&xmmword_49A0);
    byte_2061F7 = -9;
    byte_2062F7 = -9;
    xmmword_2062E0 = xmmword_2061E0;
    byte_2061F8 = -8;
    byte_2062F8 = -8;
    byte_2061F9 = -7;
    byte_2062F9 = -7;
    byte_2061FA = -6;
    byte_2062FA = -6;
    byte_2061FB = -5;
    byte_2062FB = -5;
    byte_2061FC = -4;
    byte_2062FC = -4;
    byte_2061FD = -3;
    byte_2062FD = -3;
    byte_2061FE = -2;
    byte_2062FE = -2;
    while (1)
    {
        v2 = read(fd, buf, 0x2000uLL);
        v3 = v2;
        v4 = v2;
        if (v2 <= 0)
            break;
        if (v2 == 0x2000)
        {
            v7 = 0x2000LL;
            read(fd, &v13, 4uLL);
        }
        else
        {
            v4 = v2 - 4;
            v5 = malloc(4uLL);
            v5[3] = buf[v3 - 1];
            v5[2] = buf[v3 - 2];
            v6 = v3 - 3;
            v7 = v4;
            v5[1] = buf[v6];
            *v5 = buf[v4];
            v13 = *(int *)v5;
            free(v5);
            if (v4 <= 0)
                goto LABEL_11;
        }
        v8 = 0LL;
        do
        {
            v9 = *((char *)&xmmword_206200 + (unsigned char)buf[v8]);
            if (buf[v8])
                memmove(
                (char *)&xmmword_206200 + (unsigned char)buf[v8] - (signed uint64_t)((unsigned char)buf[v8] - 1),
                    (char *)&xmmword_206200 + (unsigned char)buf[v8] - ((unsigned char)buf[v8] - 1 + 1LL),
                    (unsigned char)buf[v8] - 1 + 1LL);
            buf[v8++] = v9;
            LOchar(xmmword_206200) = v9;
        } while (v4 > (signed int)v8);
    LABEL_11:
        sub_4340(buf, v4, v13);
        write(SHIDWORD(fd), buf, v7);
    }
    close(SHIDWORD(fd));
    return close(fd);
}

int __fastcall my_wtf(char *file, char *outputFile, unsigned char *pwtf, unsigned char a4)
{
    char *v4; // r12
    uint64_t v5; // rbx
    char *inFile; // rbp
    int v7; // esi
    char *v8; // rcx
    char *v9; // rax
    unsigned char *ptr; // rax
    int v11; // er13
    int c; // edx
    uint64_t v13; // rdx
    uint64_t v14; // rdi
    int v15; // er9
    uint64_t *v16; // rdx
    signed uint64_t v17; // rax
    bool v18; // zf
    signed uint64_t v19; // r10
    int v20; // ebp
    unsigned uint64_t idx; // r12
    uint64_t v22; // r14
    uint64_t *v23; // r15
    signed uint64_t v24; // rbx
    signed int v25; // er14
    int rw; // eax
    signed uint64_t v27; // rax
    uint64_t *v28; // rbx
    int *v29; // rsi
    char *v31; // rdx
    int *first1000bytes; // [rsp+8h] [rbp-30E0h]
    unsigned uint64_t v33; // [rsp+10h] [rbp-30D8h]
    struct stat stat_buf; // [rsp+20h] [rbp-30C8h]
    uint64_t base[256]; // [rsp+B0h] [rbp-3038h]
    static char v36[0x2800]; // [rsp+8B0h] [rbp-2838h]
    char v37; // [rsp+30B0h] [rbp-38h]

    v4 = outputFile;
    v5 = a4;
    inFile = file;
    v7 = 0;
    v8 = &v36;
    v9 = &v36;
    do
    {
        *v9 = v7++;
        *((int *)v9 + 4) = 0;
        *((int *)v9 + 5) = 0;
        *((_QWORD *)v9 + 1) = 0LL;
        v9 += 40;
        *((_QWORD *)v9 - 1) = 0LL;
        *((_QWORD *)v9 - 2) = 0LL;
    } while (v7 != 256);
    ptr = pwtf;
    printf("my_wtf::0\n");
    v11 = 0;
    do
    {
        c = *ptr;
        *((int *)v8 + 5) = c;
        if (c)
        {
            v13 = v11++;
            base[v13] = (uint64_t)v8;
        }
        v8 += 40;
        ++ptr;

    } while (v8 <= &v36[0x2800]);
    printf("my_wtf::01\n");
    qsort(base, v11, 8uLL, (__compar_fn_t)compar);
    printf("my_wtf::1\n");
    v14 = base[0];
    v15 = *(int *)(base[0] + 20);
    if (v11)
    {
        v16 = base;
        v17 = 0LL;
        while (1)
        {
            v19 = v17 + 1;
            *(_QWORD *)(v14 + 8) = v17;
            if (v16 == &base[v11 - 1])
                break;
            v14 = v16[1];
            v17 = v19 << (*(char *)(v14 + 20) - (unsigned char)v15);
            v18 = *(int *)(v14 + 20) == v15;
            v15 = *(int *)(v14 + 20);
            if (v18)
                v17 = v19;
            ++v16;
        }
    }
    first1000bytes = read100(inFile, 0);
    if (!first1000bytes)
    {
        v31 = inFile;
    LABEL_27:
        fprintf(stderr, "%s: error\n", v31);
        exit(0);
    }
    v20 = open(v4, 65, 420LL);
    if (v20 == -1)
    {
        v31 = v4;
        goto LABEL_27;
    }
    idx = 0LL;
    __fxstat(1, first1000bytes[1027], &stat_buf);
    printf("stat_buf.st_size = %d", stat_buf.st_size);
    v22 = 8 * stat_buf.st_size - v5;
    v23 = &base[(unsigned int)(v11 - 1) + 1];
    v24 = 0LL;
    v33 = v22;
    v25 = 1;
    while (1)
    {
        rw = readMore1000(first1000bytes);
        if (idx >= v33 || rw == -1)
            break;
        v27 = v24 | rw;
        if (v11)
        {
            v28 = base;
            do
            {
                while (1)
                {
                    v29 = (int *)*v28;
                    if (*(_QWORD *)(*v28 + 8) == v27 && v29[5] == v25)
                        break;
                    ++v28;
                    if (v23 == v28)
                        goto LABEL_24;
                }
                ++v28;
                write(v20, v29, 1uLL);
                v25 = 0;
                v27 = 0LL;
            } while (v23 != v28);
        }
    LABEL_24:
        v24 = 2 * v27;
        ++v25;
        ++idx;
    }
    dycryptWrite(first1000bytes);
    free(first1000bytes);
    return close(v20);
}


void __fastcall unencrypt(const char *inputFile)
{
  char *v1; // rax
  uint64_t v2; // rbx
  char *header; // r13
  int encH; // er12
  int nsgHuffH; // ebp
  int v6; // eax
  char buf; // [rsp+10h] [rbp-1038h]
  char encFile; // [rsp+410h] [rbp-C38h]
  char nsgHuff; // [rsp+810h] [rbp-838h]
  char nsgName; // [rsp+C10h] [rbp-438h]
  int rw;
  uint64_t fd;

  header = (char *)malloc(0x104uLL);

  fd = open(inputFile, 0);
  if (fd == -1){
    printf("can't open %s\b", inputFile);
    return;
  }

  rw = read(fd, header, 0x104);
  if (rw != 0x104){
    printf("can't read 0x104 bytes\n");
    close(fd);
    return;
  }

  printf("[+] header read ok\n");

  //0x18a0
  my_wtf("./flag.png.enc.huff", "./flag.png.enc.nsg", (header+4), 0);
  //0x14a0
  my_wtf2("./flag.png.enc.nsg", "./flag.png");


}

int main(int argc, char** argv) {
    if (argc != 2){
        printf("wtf?\n");
    }
    printf("[*] decrypting %s\n", argv[1]);
    unencrypt(argv[1]);
}
