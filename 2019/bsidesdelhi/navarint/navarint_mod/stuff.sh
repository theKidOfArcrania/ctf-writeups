#/bin/bash
num=0
while true; do
  num2=$(printf "%06d" $num)
  if ! [ -f out/crashes/id\:$num2* ]; then
    break;
  fi

  AFL_PRELOAD=./libhaha.so:/lib/x86_64-linux-gnu/libdl.so.2 afl-tmin \
    -i out/crashes/id\:$num2* \
    -o crash$num2 ./interp

  let "num++"
done
