#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>


typedef struct chk {
  uint64_t size;
  uint32_t free;
  uint32_t pad;
  struct chk *next;
  char data[0];
} chk;

chk *head, *tail;
uint64_t mem_size;


#define ENV_SIZE 512

char mem[100000];
char env_list[16][ENV_SIZE];
char *env_values[16];


static void init_heap(void *mem, uint64_t size) {
  chk *cmem = mem;
  
  tail = head = cmem;
  head = mem;
  head->size = size - sizeof(chk);
  head->free = 1;
  head->next = 0;
  mem_size = size;
}

static void split(chk *p, uint64_t need) {
  chk *next = (chk *)(&p->data[need]);
  next->size = p->size - need - 24;
  next->free = 1;
  next->next = p->next;

  p->size = need;
  p->free = 0;
  p->next = next;
}

static void *malloc(uint64_t request) {
  assert(head->size);

  chk *p = head;
  while (1) {
    if (request <= p->size && p->free)
      break;
    if (!p->next)
      break;
    p = p->next;
  }

  if (p->size == request)
    p->free = 0;
  else if (p->size > request)
    split(p, request);
  else
    return NULL;
  printf("[*] malloc(%d) = %p\n", request, p->data);
  return (void*)p->data;
}

void expand(char *value, int64_t read_bytes, char *output) {
  int64_t out_ind = 0, inp_ind = 0;
  while (inp_ind < read_bytes) {
    if (value[inp_ind] == '$') {
      for (int i = 0; i < 16; i++) {
        char *mat = env_list[i];
        /* BUGFIX */
        if (!strlen(mat)) 
          continue;
        /* END BUGFIX */
        if (strncmp(value + inp_ind + 1, mat, strlen(mat)))
          continue;
        memcpy(output + out_ind, env_values[i], strlen(env_values[i]));
        out_ind += strlen(env_values[i]);
        inp_ind += strlen(env_values[i]);
      }
    }
    output[out_ind++] = value[inp_ind++];
  }
}

void do_command(char *line, uint64_t read_bytes) {
  int i, j, k, inp_ind;
  char *key, *value;
  if (!strncmp("export ", line, strlen("export "))) {
    key = &line[strlen("export ")];
    value = NULL;
    for (i = 0; i < strlen(key); i++) {
      if (key[i] == '=') {
        value = &key[i+1];
        key[i] = 0;
        break;
      }
    }

    for (i = 0; i < 16; i++) {
      if (!strlen(env_list[i]))
        continue;
      if (strcmp(env_list[i], key))
        continue;

      read_bytes -= strlen(key) + strlen("export");
      expand(value, read_bytes, env_values[i]);
    }

    for (i = 0; i < 16; i++) {
      if (strlen(env_list[i]))
        continue;

      memcpy(env_list[i], key, strlen(key));
      env_values[i] = malloc(ENV_SIZE - strlen(key) - strlen("export ") + 1);

      read_bytes = ENV_SIZE - strlen(key) - strlen("export");
      expand(value, read_bytes, env_values[i]);
      break;
    }
  } else if (!strcmp(line, "env")) {
    for (i = 0; i < 16; i++) {
      if (strlen(env_list[i]))
        printf("%s=%s\n", env_list[i], env_values[i]);
    }
  } else {
    puts("Invalid command");
  }
}

void cmd(char *line) {
  puts(line);
  do_command(line, strlen(line));
}

struct timespec pause = {
  .tv_sec = 0,
  .tv_nsec = 10
};

/// CLIENT CODE

void clientA() {
  char buff[512];
  while (1) {
    printf("$ ");
    fgets(buff, sizeof(buff), stdin);
    for (int i = 0; buff[i]; i++) {
      if (buff[i] == '\n') {
        buff[i] = 0;
        break;
      }
    }
    cmd(buff);
  }
}

void clientB() {
  char buff[512];
  char buff2[512];
  memset(buff, 0, sizeof(buff));

  strcpy(buff, "export A=3");
  cmd(buff);
  strcpy(buff, "export B=4");
  cmd(buff);

  strcpy(buff, "export C=");
  memset(buff2, 'A', sizeof(buff2));
  buff2[450] = 0;
  strcat(buff, buff2);
  cmd(buff);

   
  strcpy(buff, "export X=");
  memset(buff2, 'B', sizeof(buff2));
  buff2[505-450] = 0;
  strcat(buff, buff2);
  strcat(buff, "$C");
  cmd(buff);


  strcpy(buff, "env");
  cmd(buff);
}

int main() {

  setbuf(stdout, 0);

  init_heap(mem, sizeof(mem));

  clientB();

  //nanosleep(&pause, NULL);
}
