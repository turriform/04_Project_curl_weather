CC:= gcc

PROG:= prog

INCLUDE:= -I./include/ -I./third_party/cJSON/include

FLAGS:= -std=c11 -Wall -Wextra -Wpedantic

LIBS:= -lcurl

C_SRC:= $(wildcard ./src/*.c ./src/**/*.c)
C_JSON_SRC = ./third_party/cJSON/src/cJSON.c

TARGET:= ./bin/$(PROG)

ARGS:=Saint-Petersburg
all:
	$(CC) $(C_SRC) $(FLAGS) $(INCLUDE)  $(C_JSON_SRC) $(LIBS) -o $(TARGET) && $(TARGET) $(ARGS)

run:
	$(TARGET) $(ARGS)

val:
	valgrind -s --track-origins=yes $(TARGET) $(ARGS)

