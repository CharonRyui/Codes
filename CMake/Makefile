CC = gcc
CFLAGS = -Wall -g
TARGET = main
OBJS = hello.o master.o
all: $(TARGET)
$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(TARGET) $(OBJS)
.PHONY: all clean