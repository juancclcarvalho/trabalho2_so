all:	test libt.a

libt.a:	
	cd ../../lib && make

test: test.c libt.a
	gcc -no-pie -I../../include test.c -L../../lib -lt -lrt -o test

clean:
	rm -f *.o *~ test core
