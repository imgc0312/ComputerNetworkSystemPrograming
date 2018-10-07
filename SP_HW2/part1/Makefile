C=gcc -Wall
O1=hostinfo.o 
O2=mydate.o
O3=printdir.o
O4=mycat.o
O5=pipe_ls.o

.SUFFIXS: .c .o

all: hostinfo mydate printdir mycat pipe_ls clean
	


hostinfo: $(O1)
	$(C) $(O1) -o $@

mydate: $(O2)
	$(C) $(O2) -o $@

printdir: $(O3)
	$(C) $(O3) -o $@

mycat: $(O4)
	$(C) $(O4) -o $@

pipe_ls: $(O5)
	$(C) $(O5) -o $@

dep: *.c
	$(C) -E -MM *c > depend


remove: clean
	rm hostinfo mydate printdir mycat pipe_ls


clean:
	rm -rf *.o depend
