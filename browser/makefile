CC = gcc
CXX = g++
OBJOP = -c
OUTFILE = browser2.bin
QTL = $$(pkg-config --cflags --libs Qt5Widgets Qt5OpenGL)

all: $(OBJS)
	$(CXX) $(QTL) -fPIC $(OBJS) main.cc -lX11 -o $(OUTFILE)