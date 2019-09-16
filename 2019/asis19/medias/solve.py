import random, hashlib

valid = [51, 55, 114, 73, 118, 23, 81, 41, -68, 67, 75, 86, 91, 116, 126,
    93, 88, 110, 37, 63, -25, 125, 72, 38, 113, 117, -109, 67, 65, 99, 92, 87,
    -123, 113, 96, -125, 126, 52, 51, 93, 84, 80, 40, 33, -116, 73, 81, -110]
valid = bytes([b & 0xff for b in valid])


def numbcheck(num):
    n = []
    for c in num:
        c = ord(c)
        if not (0x30 <= c <= 0x39):
            return False
        n.append(c-0x30)
    for i in range(1, len(num) - 1):
        if n[i-1] == 0:
            return False
        #if n[i+1] + n[i-1] <= 2*n[i]:
        if n[i+1] - n[i] <= n[i] - n[i-1]:
            return False
    return True


def check(msg):
    part = len(msg) // 3
    if len(msg) % 3:
        return False

    a = msg[:part]
    b = msg[part:part*2]
    c = msg[part*2:]

    if numbcheck(a) and numbcheck(b) and numbcheck(c):
        a = int(a) + 1000000
        b = int(b) + 100000
        c = int(c) + 10000
        if a > b:
            return False
        if b > c:
            return False
        return True
    else:
        return False

def check_hash(msg):
    return hashlib.md5(msg.encode('utf8')).digest() == valid

if __name__ == '__main__':
    num = input('Input number: ')
    if check(num) and check_hash(num):
        print('Success!')

