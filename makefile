output.exe : main.o create.o display.o search.o save.o update.o utility.o validate.o
	gcc -o output.exe main.o create.o display.o search.o save.o update.o utility.o validate.o

main.o : main.c inverted.h
	gcc -c main.c

create.o : create.c inverted.h
	gcc -c create.c

display.o : display.c inverted.h
	gcc -c display.c

search.o : search.c inverted.h
	gcc -c search.c

save.o : save.c inverted.h
	gcc -c save.c
update.o : update.c inverted.h
	gcc -c update.c

utility.o : utility.c inverted.h
	gcc -c utility.c

validate.o : validate.c inverted.h
	gcc -c validate.c

clean :
	rm -f *.o *.exe