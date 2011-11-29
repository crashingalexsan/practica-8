all: createvd dumpsec vdformat dumpseclog

vdisk.o: vdisk.c vdisk.h
	cc -c vdisk.c

createvd: createvd.c vdisk.o
	gcc -o createvd createvd.c vdisk.o

dumpsec: dumpsec.c vdisk.o
	gcc -o dumpsec dumpsec.c vdisk.o

dumpseclog: dumpseclog.c vdisk.o
	gcc -o dumpseclog dumpseclog.c vdisk.o

vdformat: vdformat.c vdisk.o
	gcc -o vdformat vdformat.c vdisk.o 
