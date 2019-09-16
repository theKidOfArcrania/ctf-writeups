from binascii import hexlify, unhexlify

k = unhexlify('8877665544332211')

i = 0
with open("encrypt_main", "rb") as inFile:
    data = inFile.read()

with open("main_help", "wb") as outFile:
    
    bx = []
    for c in data:
        bx += [c ^ k[i]]
        i = (i + 1) % len(k)
    outFile.write(bytes(bx))
