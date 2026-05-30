APPNAME = my_app
CFLAGS = -Wall -Wextra -Werror
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

CFILES = main.c getopt.c plot_functions.c

all: runnable 

runnable: $(CFILES)
	gcc $(CFILES) -o $(APPNAME) $(CFLAGS) $(LIBS)

clean:
	rm -f $(APPNAME)
