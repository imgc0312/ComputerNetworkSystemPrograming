C=gcc -Wall
O1=shell.o parse.o builtin.o is_background.o run_command.o pipe_command.o pipe_present.o redirect_in.o redirect_out.o timer.o


.SUFFIXS: .c .o

all: main clean
	


main: $(O1)
	$(C) $(O1) -o $@

dep: *.c
	$(C) -E -MM *c > depend


remove: clean
	rm main


clean:
	rm -rf *.o depend
