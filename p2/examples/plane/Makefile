all:	plane libt.a

libt.a:	
	cd ../../lib && make

plane: plane.c sum_to_100.c simple_sleep.c libt.a
	gcc -Wall -no-pie -I../../include plane.c sum_to_100.c simple_sleep.c -L../../lib -lt -o plane

clean:
	rm -f *.o *~ plane core
