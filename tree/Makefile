GCC = gcc
GCCFLAGS = -g -finline-functions -Wall -Winline -pipe

PROJECT_1 = bitree
PROJECT_2 = binary-tree
PROJECT_3 = search-tree

OBJS_1 = bitree.o
OBJS_2 = binary-tree.o
OBJS_3 = search-tree.o

all : $(PROJECT_1) $(PROJECT_2) $(PROJECT_3)
	@echo "Start compile all"
	rm -f *.o
	@echo "complete"

$(PROJECT_1): $(OBJS_1)
	@echo "start compile $(PROJECT_1)"
	$(GCC) -g -o $@ $^

$(PROJECT_2): $(OBJS_2)
	@echo "start compile $(PROJECT_2)"
	$(GCC) -g -o $@ $^

$(PROJECT_3): $(OBJS_3)
	@echo "start compile $(PROJECT_3)"
	$(GCC) -g -o $@ $^

%.o : %.c
	$(GCC) $(GCCFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(PROJECT_1) $(PROJECT_2) $(OBJS_1) $(OBJS_2)
