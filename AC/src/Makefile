GCC = gcc
GCCFLAGS = -g -finline-functions -Wall -Winline -pipe

LIBDIR = \
		-levent

TARGET = acsmx
SERVER = acmf

OBJS1 = entry.o acsmx.o
OBJS2 = acmf.o acsmx.o util.o

all: $(TARGET) $(SERVER)
	rm -f *.o

$(TARGET): $(OBJS1)
	$(GCC) -g -o $@ $^ $(LIBDIR)

$(SERVER): $(OBJS2)
	$(GCC) -g -o $@ $^ $(LIBDIR)

$.o: %c
	$(GCC) $(GCCFLAGS) -c $< -o $@

.PHONY: clean
clean :
	rm -rf $(TARGET) $(SERVER) $(OBJS1) $(OBJS2)

.PHONY: cleanobj
cleanobj:
	rm -rf $(OBJS1) $(OBJS2)
