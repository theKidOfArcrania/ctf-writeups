set -e

BIN=light_fence.elf
PATCH=$BIN.patched

cp $BIN $PATCH

TEMP=$(mktemp)
exec 3<> $TEMP

# Patch the call at 0xb67
echo -e "\x44\x11" >&3
dd conv=nocreat,notrunc bs=1 count=2 if=$TEMP of=$PATCH seek=2920
rm $TEMP

nasm unencrypt.asm
dd conv=nocreat,notrunc bs=1 count=526 if=unencrypt of=$PATCH seek=7344
