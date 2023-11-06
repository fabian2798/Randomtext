CC = gcc
CFLAGS = -Wall

shakespeare: shakespeare.C
	$(CC) $(CFLAGS) -o shakespeare shakespeare.c


run: shakespeare
	./shakespeare -s2  ./7zara10.txt

run1: shakespeare
	./shakespeare -s3 -l100 ./7zara10.txt

run2: shakespeare
	./shakespeare -s5 -l500 ./7zara10.txt

run3: shakespeare
	./shakespeare -s6 -l1000 ./7zara10.txt

run4: shakespeare
	./shakespeare -s7 -l1000 ./7zara10.txt

run5: shakespeare
	./shakespeare -s8 -l1000 ./7zara10.txt

run6: shakespeare
	./shakespeare -s9 -l1000 ./7zara10.txt

run7: shakespeare
	./shakespeare -s10 -l1000 ./7zara10.txt

run8: shakespeare
	./shakespeare -s11 -l1000 ./7zara10.txt

run9: shakespeare
	./shakespeare -s12 -l1000 ./7zara10.txt