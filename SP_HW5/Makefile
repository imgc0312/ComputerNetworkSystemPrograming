
O1=  main.o
PROGS = vm
	

all : $(PROGS) clean

vm: $(O1)
	$(CC) -o $@ $(O1) -pthread

clean :
	rm -f *.o 

remove: clean
	rm $(PROGS)
