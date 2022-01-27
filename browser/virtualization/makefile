O_FLAGS = -c -fPIC
SHARED_FLAGS = -shared
OBJS = mem.o elf_l.o util.o executor/cpu/load_elf.o executor/cpu/exec_elf.o executor/cpu/modrm.o
PROJ_NAME = virtualizer

.PHONY: all
all: virtualizer

.PHONY: virtualizer
virtualizer: $(OBJS)
# $(CC) $(SHARED_FLAGS) $(OBJS) run.c -o $(PROJ_NAME).so
	$(CC) $(OBJS) run.c -o $(PROJ_NAME).bin

mem.o: mem.c
	$(CC) $(O_FLAGS) $< -o $@

elf_l.o: elf_l.c
	$(CC) $(O_FLAGS) $< -o $@

util.o: util.c
	$(CC) $(O_FLAGS) $< -o $@

executor/cpu/load_elf.o: executor/cpu/load_elf.c
	$(CC) $(O_FLAGS) $< -o $@

executor/cpu/exec_elf.o: executor/cpu/exec_elf.c
	$(CC) $(O_FLAGS) $< -o $@

executor/cpu/modrm.o: executor/cpu/modrm.c
	$(CC) $(O_FLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(OBJS)
	rm $(PROJ_NAME).so