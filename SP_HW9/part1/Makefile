
O1 = main.o lookup7.o
O2 = usock_server.o lookup5.o
PROGS = usock_server usock_client
	

all : $(PROGS) clean

usock_server: $(O2)
	$(CC) -o $@ $(O2)

usock_client: $(O1)
	$(CC) -o $@ $(O1)

clean :
	rm -f *.o 

remove: clean
	rm $(PROGS)
