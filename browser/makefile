CC = gcc
CXX = g++
OBJOP = -c
OBJS = openapp.o spawntab.o
OUTFILE = browser.bin
QTL = $$(pkg-config --cflags --libs Qt5Widgets)

all: $(OBJS)
	$(CXX) $(QTL) -fPIC $(OBJS) main.cc -lX11 -o $(OUTFILE)

openapp.o: openapp.c
	$(CC) $(OBJOP) $< -o $@

spawntab.o: spawntab.c
	$(CC) $(OBJOP) $< -o $@