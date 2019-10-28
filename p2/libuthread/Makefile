# Target library
lib := libuthread.a

all: $(lib)
 Target library

## TODO: Phase 1.1

main: test_queue.c libuthread.a
	gcc test_queue.c -L. -luthread -o main

libuthread.a: queue.o
	ar -rc libuthread.a queue.o

queue.o: queue.c queue.h
	gcc -Wall -Werror -c -o queue.o queue.c

clean:
	rm -f queue.o libuthread.a main

