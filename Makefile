tester: tester.c list.c
	gcc -Wall -std=c99 -o tester tester.c list.c

clean:	
	rm -f tester *.o 