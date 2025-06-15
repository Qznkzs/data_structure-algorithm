# 编译器
CC = gcc

# 编译选项
CFLAGS = -Wall -Wextra -g -I.

# 目标可执行文件
TARGET = linear-table-app

# 源文件和目标文件
SRCS = linear-table_app.c linear-table.c
OBJS = $(SRCS:.c=.o)
HEADERS = $(wildcard *.h)

# 默认目标
all: $(TARGET)

# 生成可执行文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# 编译每个 .o 文件
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# 清理编译产物
clean:
	rm -f $(OBJS) $(TARGET)

# 重新构建
rebuild: clean all

# 运行程序
run: $(TARGET)
	./$(TARGET)