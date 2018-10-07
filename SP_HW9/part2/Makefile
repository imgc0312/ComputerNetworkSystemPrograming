
O1 = main.o lookup8.o
O2 = isock_server.o lookup5.o
PROGS = isock_server isock_client
	

all : $(PROGS) clean

isock_server: $(O2)
	$(CC) -o $@ $(O2)

isock_client: $(O1)
	$(CC) -o $@ $(O1)

clean :
	rm -f *.o 

remove: clean
	rm $(PROGS)
