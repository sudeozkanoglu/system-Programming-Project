CFLAGS = -O3 -Iinclude
LDFLAGS = -Llib -lfdr

all: program

program: lib/libfdr.a obj/main.o
	gcc $(LDFLAGS) -o program obj/main.o -lfdr
	
obj/main.o: src/main.c
	gcc $(CFLAGS) -c -o obj/main.o src/main.c

OBJS = obj/dllist.o obj/fields.o obj/jval.o

lib/libfdr.a: $(OBJS)
	ar ru lib/libfdr.a $(OBJS)
	ranlib lib/libfdr.a 

clean:
	rm -f obj/* lib/* program

obj/fields.o: src/fields.c include/fields.h
	gcc $(CFLAGS) -c -o obj/fields.o src/fields.c

obj/jval.o: src/jval.c include/jval.h
	gcc $(CFLAGS) -c -o obj/jval.o src/jval.c

obj/dllist.o: src/dllist.c include/dllist.h include/jval.h
	gcc $(CFLAGS) -c -o obj/dllist.o src/dllist.c
	
