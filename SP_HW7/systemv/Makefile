C = gcc -Wall
O1 = producer.o
O2 = consumer.o
PROGS = producer consumer
	

all : $(PROGS) clean

producer: $(O1)
	$(C) -o $@ $(O1)

consumer: $(O2)
	$(C) -o $@ $(O2)

clean :
	rm -f *.o 

remove: clean
	rm $(PROGS)
