mod = 0x9d
code = 'B7 0C 0C E9 12 17 1D 22 0f 17 09 6a 0f 0c 0c e9 5a 16 32 22 0f 1d 0f 17 52 4a 0f 54 0f 32 0f 17 52 4a 23 ad 40 22'

code = list(map(lambda x: int(x, 16), code.split(' ')))

tab = [0, 1]

for i in range(len(tab), 0x100):
    tab.append((tab[i - 1] + tab[i - 2]) % mod)

print(''.join([chr(tab[x+1]) for x in code])[::-1])

