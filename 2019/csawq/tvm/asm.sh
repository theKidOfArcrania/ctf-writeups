#!/bin/sh

if [ "$#" -ne 2 ]; then
  echo "Usage: $0 FILE OUTPUT" 
  exit
fi

if ! cat asm.h $1 > tmp.c; then
  rm tmp.c
  exit 1
fi

gcc tmp.c -o tmp
rm -f tmp.c
./tmp > $2
rm tmp

