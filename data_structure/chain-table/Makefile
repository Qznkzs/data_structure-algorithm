#编译器
CC = gcc

#编译选项
CFLAGS = -Wall -Wextra -g -I.

#目标执行文件
TARGET = chain-table-app

#源文件和目标文件
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
HEADERS = $(wildcard *.h)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -c $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all

run: $(TARGET)
	./$(TARGET)