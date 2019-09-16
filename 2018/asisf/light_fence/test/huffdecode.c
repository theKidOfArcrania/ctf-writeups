#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/stat.h>

typedef struct file {
  char buff[0x1000];
  int bitind;
  int maxbits;
  int fd;
  int mode;
} file;

struct huffnode {
  int c;
  int bitlen;
  int bitpat;
};

file* openfile(const char *filename) {
  int fd = open(filename, 0);
  if (fd < 0) {
    printf("Wtf2\n");
    exit(1);
  }
  file* f = malloc(sizeof(file));
  if (!f) {
    printf("Wtf3\n");
    exit(1);
  }

  f->bitind = 0;
  f->maxbits = 0;
  f->fd = fd;
  f->mode = 0;
  return f;
}

int readbit(struct file* f) {
  if (f->mode) {
    printf("Wtf\n");
    exit(1);
  }
  
  if (f->bitind >= f->maxbits) {
    if ((f->maxbits = read(f->fd, f->buff, sizeof(f->buff))) <= 0)
      return -1;
    f->maxbits *= 8;
    f->bitind = 0;
  }

  int bit = (f->buff[f->bitind >> 3] >> (7 - (f->bitind & 0x7))) & 1;
  f->bitind++;
  return bit;
}

int closefile(struct file* file) {
  if (file->mode != 2) {
    file->mode = 2;
    close(file->fd);
    free(file);
  }
}

int compare(struct huffnode **first, struct huffnode **second) {
  struct huffnode *a = *first;
  struct huffnode *b = *second;

  if (a->bitlen == b->bitlen)
    return a->c - b->c;
  else
    return a->bitlen - b->bitlen;
}

int bitflip(int bits, int bitlen) {
  int res = 0;
  for (int i = 0; i < bitlen; i++) {
    if (bits & (1 << i)) {
      res |= (1 << (bitlen - i - 1));
    }
  }
  return res;
}

void decode_huff(char *infile, char *outfile) {
  int table_size = 0, max_len = 0, bitcrop = 0;

  char magic[4];
  char bitlens[256];
  struct huffnode nodes[256];
  struct huffnode *table[256];

  file* f = openfile(infile);
  read(f->fd, magic, sizeof(magic));
  read(f->fd, bitlens, sizeof(bitlens));

  bitcrop = magic[3];

  for (int i = 0; i < 256; i++) {
    if (bitlens[i]) {
      if (max_len < bitlens[i])
        max_len = bitlens[i];
      nodes[table_size] = (struct huffnode) {.c = i, .bitlen = bitlens[i]};
      table[table_size] = &nodes[table_size];
      table_size++;
    }
  }

  qsort(table, table_size, 8, compare);

  int next_bitpat = 0;
  int prev_len = 0, cur_len;
  for (int i = 0; i < table_size; i++) {
    cur_len = table[i]->bitlen;
    next_bitpat <<= cur_len - prev_len;
    prev_len = cur_len;

    table[i]->bitpat = next_bitpat;
    printf("%02x -> %d\n", table[i]->c & 0xff, next_bitpat);
    next_bitpat++;
  }

  

  int outfd = open(outfile, 65, 0644);
  int bit, cur_bits = 0, cur_bitlen = 0, numread = 0, maxread;
  struct stat st;
  
  fstat(f->fd, &st);
  maxread = st.st_size - bitcrop;
  while (numread < maxread && (bit = readbit(f)) != -1) {
    cur_bits = (cur_bits << 1) | bit;
    printf("%d", bit);
    cur_bitlen++;

    if (cur_bitlen > max_len) {
      printf("Wtf6\n");
      exit(1);
    }

    // Find our huffman table to see if we have a match
    for (int i = 0; i < table_size; i++) {
      if (nodes[i].bitlen == cur_bitlen && nodes[i].bitpat == cur_bits) {
        printf(": %d %d\n", nodes[i].c, cur_bits);
        write(outfd, &nodes[i].c, 1);
        cur_bits = 0;
        cur_bitlen = 0;
        break;
      }
    }
  }

  closefile(f);
  close(outfd);
}



int main(int argc, char** argv) {
  char header[0x104];

  if (argc != 3){
    printf("wtf?\n");
    return 1;
  }

  decode_huff(argv[1], argv[2]);
}


