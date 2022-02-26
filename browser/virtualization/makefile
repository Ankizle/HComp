O_FLAGS = -c -fPIC
SHARED_FLAGS = -shared
OBJS = elf_l.o run.o dynamic.o load.o
PROJ_NAME = virtualizer

.PHONY: all
all: virtualizer

.PHONY: virtualizer
virtualizer: $(OBJS)
# $(CC) $(SHARED_FLAGS) $(OBJS) run.c -o $(PROJ_NAME).so
	$(CC) $(OBJS) run.c -o $(PROJ_NAME).bin -lc -g

elf_l.o: elf_l.c
	$(CC) $(O_FLAGS) $< -o $@

dynamic.o: dynamic.c
	$(CC) $(O_FLAGS) $< -o $@

load.o: load.c
	$(CC) $(O_FLAGS) $< -o $@

run.o: run.s
	nasm -f elf64 $< -o $@

.PHONY: clean
clean:
	rm $(OBJS)
	rm $(PROJ_NAME).so