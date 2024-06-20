
CC=cc
FLAGS=-c -Wall
LIBS=-lm -lpthread 
OBS=main.o execute.o parse.o socp.o redirects.o  notice.o socpth.o  lists.o 
all :  sshell

main.o : shell.h main.c
	$(CC) $(FLAGS) main.c
execute.o : shell.h execute.c
	$(CC) $(FLAGS) execute.c


 lists.o : shell.h  lists.c
	$(CC) $(FLAGS)  lists.c
parse.o : shell.h parse.c
	$(CC) $(FLAGS) parse.c
 notice.o : shell.h  notice.c
	$(CC) $(FLAGS)  notice.c
socpth.o : shell.h socpth.c
	$(CC) $(FLAGS) socpth.c
redirects.o : shell.h redirects.c
	$(CC) $(FLAGS) redirects.c
sshell : $(OBS)
	$(CC)  -o myshell  $(OBS) $(LIBS)
socp.o : shell.h socp.c
	$(CC) $(FLAGS) socp.c
clean limpar:
	rm -f myshell *.o
	rm -f *~
	#Cleaning executable files, objects and gedit junk
