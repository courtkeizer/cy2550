# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Iinclude -g

# Directories
SRCDIR = .
OBJDIR =
BINDIR =

# Sources and objects
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

# Targets
TARGET = xkcdpwgen

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(TARGET) $(OBJS)

.PHONY: all clean
