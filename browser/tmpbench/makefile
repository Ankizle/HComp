.PHONY: default
default: all

.PHONY: test
all: bench1.bin bench2.bin bench3.bin

bench1.bin:
	gcc bench1.c -o bench1.bin

bench2.bin:
	go build -o bench2.bin bench2.go

bench3.bin:
	gcc bench3.c -o bench3.bin

.PHONY: test
test:
	g++ -o benchtest.bin benchtest.cc
	./benchtest.bin