CC=g++
PATH_SRC=src
CFLAGS=-O3
LIBS=

main: main.o ap_rv.o apt.o
		$(CC) $(CFLAGS) -o main main.o ap_rv.o apt.o

apt.o: $(PATH_SRC)/aptemplate.h $(PATH_SRC)/aptemplate.cc
		$(CC) $(CFLAGS) -c -o apt.o $(PATH_SRC)/aptemplate.cc $(LIBS) 

ap_rv.o: $(PATH_SRC)/ap_rv.h $(PATH_SRC)/ap_rv.cc
		$(CC) $(CFLAGS) -c -o ap_rv.o $(PATH_SRC)/ap_rv.cc $(LIBS) 

main.o: $(PATH_SRC)/main.cpp
		$(CC) $(CFLAGS) -c -o main.o $(PATH_SRC)/main.cpp $(LIBS) 

clean:
	rm *.o main
			
