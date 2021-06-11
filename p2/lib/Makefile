all:	libt 

libt:	thread.o queue.o entry.o util.o lock.o
	ar rcs libt.a thread.o queue.o entry.o util.o lock.o

thread.o: thread.c ../include/thread.h ../include/queue.h
	gcc -Wall -no-pie -I../include -c thread.c

queue.o: queue.c ../include/queue.h 
	gcc -Wall -no-pie -I../include -c queue.c

util.o: util.c ../include/util.h
	gcc -Wall -no-pie -I../include -c util.c

lock.o: lock.c ../include/lock.h 
	gcc -Wall -no-pie -I../include -c lock.c

entry.o: entry.S
	gcc -Wall -no-pie -c entry.S

clean:
	rm -f *.o *~ core libt.a
