typedef struct node{
  char *data;
  struct node *next;
} node;

node *head;

void myst(node *n) {
  // n -> r9
  int size; // r3
  int ind; // r4

  if (!n)
    return;

  size = sizeof(n->data);
  char buff[0x40];
  for (ind = 0; ind != size; ind++) {
    buff[ind] = n->data[ind];
  }

  write(1, buff, size);
  write(


}

int main() {
  int c;
  int ind;  // r4
  int incr = 1; // r15
  char *arr; // r6
  node *n; // r0

  write("Prompt>");
  c = getchar();
  if (c == '1') {
    // PUSH
    char buff[0x40];
    int len = read(0, buff, 0x80);
    
    arr = malloc(len);
    for (ind = 0; ind != len; ind++) {
      arr[ind] = buff[ind];
    }

    n->data = arr;
    n->next = head;
    head = n;

    // buff deallocated
    

  }
}
