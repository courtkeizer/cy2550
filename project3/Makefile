# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Iinclude -g

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Sources and objects
SRCS = $(shell find $(SRCDIR) -name "*.cpp")   # Change file extension to .cpp
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))   # Change file extension to .cpp

# Targets
TARGET = $(BINDIR)/xkcdpwgen

all: $(TARGET)

$(OBJDIR) $(BINDIR):
	mkdir -p $@

$(TARGET): $(OBJS) | $(BINDIR)
	$(CXX) -o $@ $^   # Change the compiler from $(CC) to $(CXX)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)   # Change file extension to .cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<   # Change the compiler from $(CC) to $(CXX)

clean:
#	rm -rf $(OBJDIR)/* $(BINDIR)/*

.PHONY: all clean
