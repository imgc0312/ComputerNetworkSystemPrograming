
O1 = main.o lookup9.o
O2 = udp_server.o lookup5.o
PROGS = udp_server udp_client
	

all : $(PROGS) clean

udp_server: $(O2)
	$(CC) -o $@ $(O2)

udp_client: $(O1)
	$(CC) -o $@ $(O1)

clean :
	rm -f *.o 

remove: clean
	rm $(PROGS)
