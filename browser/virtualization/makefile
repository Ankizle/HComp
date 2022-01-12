O_FLAGS = -c -fPIC
SHARED_FLAGS = -shared
OBJS = mem.o elf_l.o
PROJ_NAME = virtualizer

.PHONY: all
all: virtualizer

.PHONY: virtualizer
virtualizer: $(OBJS)
# $(CC) $(SHARED_FLAGS) $(OBJS) run.c -o $(PROJ_NAME).so
	$(CC) $(OBJS) run.c -o $(PROJ_NAME).bin

mem.o: mem.c
	$(CC) $(O_FLAGS) $<

elf_l.o: elf_l.c
	$(CC) $(O_FLAGS) $<

.PHONY: clean
clean:
	rm $(OBJS)
	rm $(PROJ_NAME).so