C=gcc -Wall
O1=myls_B043040044.o 


.SUFFIXS: .c .o

all: myls clean
	


myls: $(O1)
	$(C) $(O1) -o $@

dep: *.c
	$(C) -E -MM *c > depend


remove: clean
	rm myls


clean:
	rm -rf *.o depend
