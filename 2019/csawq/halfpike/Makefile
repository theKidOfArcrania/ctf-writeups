all: chal.asm

./emu/emu2.cc: subdirs


.PRECIOUS: chal.trace

%.trace: %.rom ./emu/emu2.cc
	echo | ./emu/dump $< $(addr) 2> $@ || true

%.asm: %.trace process.py
	python3 process.py $< > $@

subdirs:
	make -C emu

