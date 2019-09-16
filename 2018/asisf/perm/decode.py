# A - B
# B - A
# C - @
# D
# E
# F

with open('flag.enc', 'rb') as f:
    data = f.read()[1::2]

with open('flag.dec', 'wb') as f:
    f.write(data)
