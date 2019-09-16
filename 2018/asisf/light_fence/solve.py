import struct

def find_min_ind(arr):
    min_ind = 0
    size = len(data)
    for i in range(size):
        if not min_ind or data[i] < data[min_ind]:
            min_ind = i
        elif data[i] == data[min_ind]:
            for off in range(size):
                comp = data[(i + off) % size] - data[(min_ind + off) % size]
                if comp > 0:
                    break
                elif comp < 0:
                    min_ind = i
                    break
            else:
                print("Warning: undeterminate minimum")
    return min_ind


def encode_nsg(data):
    def nsg_block(blk):
        min_ind = find_min_ind(blk)
        out = b''

        table = [i for i in range(255)]
        invtable = [i for i in range(255)]

        for ch in blk:
            for i in range(255):
                table[invtable[i]] = i
            
            # Rotate first 'ent' elements in table
            ent = table[ch]
            invtable[1:ent + 1] = invtable[0:ent]
            invtable[0] = ch

            out += tab


    out = b''
    for i in range(0, data, 0x2000):
        out += nsg_block(data[i:min(i + 0x2000, len(data))])



      ind = 0LL;
      do
      {
        cur_table[next_table[ind]] = ind;
        ++ind;
      }
      while ( ind != 255 );
      write(outfd, &cur_table[*ptr], 1uLL);
      c = *ptr;
      v9 = cur_table[c];
      c_ = *ptr;
      v11 = cur_table[c];
      if ( v9 )
        // memmove(byte_206200 + 1, byte_206200, v9)
        memmove(&next_table[v11 - (v9 - 1)], &next_table[v11 - (v9 - 1 + 1LL)], v9 - 1 + 1LL);
      ++ptr;
      next_table[0] = c_;


