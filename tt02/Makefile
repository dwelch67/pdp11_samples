
AOPS = --warn --fatal-warnings
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding

all : notmain.sim

clean :
	rm -f *.o
	rm -f *.list
	rm -f *.elf
	rm -f *.sim
	rm -f *.bin
	rm -f bintosimh

start.o : start.s
	pdp11-aout-as $(AOPS) start.s -o start.o

notmain.o : notmain.c
	pdp11-aout-gcc -O2 -c $(COPS) notmain.c -o notmain.o

notmain.elf : memmap start.o notmain.o
	pdp11-aout-ld -T memmap start.o notmain.o -o notmain.elf

notmain.bin : notmain.elf
	pdp11-aout-objdump -D notmain.elf > notmain.list
	pdp11-aout-objcopy notmain.elf -O binary notmain.bin

notmain.sim : notmain.bin bintosimh
	./bintosimh notmain.bin notmain.sim

bintosimh : bintosimh.c
	gcc bintosimh.c -o bintosimh

