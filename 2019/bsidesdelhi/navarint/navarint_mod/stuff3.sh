#!/bin/bash
for crash in crash??????; do
  echo "<================ $crash"
  cat -v $crash
  echo -e "\n===========================>"
  read -p "Delete? (y/n) " DEL

  if [ "$DEL" == 'y' -o "$DEL" == 'Y' ]; then
    rm $crash
  fi
done
