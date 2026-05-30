APPNAME = my_app
CFLAGS = -o $(APPNAME) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Wextra -Werror

CFILES = main.c getopt.c plot_functions.c

all: runnable 
	make clean
	make runnable

runnable: CFILES
	gcc $(CFLAGS) $(CFILES)

clean:
	rm $(APPNAME)


