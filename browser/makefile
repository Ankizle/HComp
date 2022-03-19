CC = gcc
CXX = g++

OPS = -fPIC
OBJS = hcompx.o

OUTFILE = browser.bin

GTK = $(shell pkg-config --cflags --libs gtk4)
GDK = $(shell pkg-config --cflags --libs gtk4-x11)
X11 = -lX11
LINK = $(GTK) $(GDK) $(X11)

all: $(OBJS) xvfbwrapper.py
	$(CXX) $(LINK) $(OPS) $(OBJS) browser.cc -o $(OUTFILE)

hcompx.o: hcompx.c
	$(CC) -c $(X11) $< -o $@

xvfbwrapper.py:
	wget https://raw.githubusercontent.com/cgoldberg/xvfbwrapper/master/xvfbwrapper.py