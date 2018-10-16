C=gcc -Wall
O1=mymv_B043040044.o 


.SUFFIXS: .c .o

all: mymv clean
	


mymv: $(O1)
	$(C) $(O1) -o $@

dep: *.c
	$(C) -E -MM *c > depend


remove: clean
	rm mymv


clean:
	rm -rf *.o depend
