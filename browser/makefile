OBJOP = -c
OBJS = exec.o
OUTFILE = browser.bin

all: exec.o
	$(CC) browser.c $(OBJS) -o $(OUTFILE)

exec.o: exec.c
	$(CC) $(OBJOP) $< -o $@