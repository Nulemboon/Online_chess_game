CC := g++
CFLAGS := -g
INCLUDE_DIRS := -I/usr/local/include
LIB_DIRS := -L/usr/local/lib
LIBS := -l:bcrypt.a -lsqlite3

SRCS := server.cpp database/database.cpp message/message.cpp 
OBJS := $(SRCS:.cpp=.o)
TARGET := server

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $(LIB_DIRS) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
