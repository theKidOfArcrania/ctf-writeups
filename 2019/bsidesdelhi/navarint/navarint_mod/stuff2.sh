#!/bin/bash
for crash in crash??????; do
  x=$(cat $crash)
  if [ "$x" == '[' ]; then
    echo "rm $crash"
    rm $crash
  fi
done
