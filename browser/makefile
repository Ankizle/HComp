CC = gcc
CXX = g++

OPS = -fPIC
OBJS = hcompx.o xvfbwrapper.o vnc.o

OUTFILE = browser.bin

GTK = $(shell pkg-config --cflags --libs gtk4)
GDK = $(shell pkg-config --cflags --libs gtk4-x11)
X11 = -lX11
LINK = $(GTK) $(GDK) $(X11)

all: $(OBJS)
	$(CXX) $(LINK) $(OPS) $(OBJS) browser.cc -o $(OUTFILE)

hcompx.o: hcompx.c
	$(CC) -c $(X11) $< -o $@

xvfbwrapper.o: xvfbwrapper.c
	$(CC) -c $< -o $@

vnc.o: vnc.c
	$(CC) -c $< -o $@
