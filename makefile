CC     = g++
NEWDIR = mkdir
SRCDIR = src
BINDIR = bin
RM     = rm -rf
TARGET = $(BINDIR)/drone
HEADER = $(wildcard $(SRCDIR)/*.hpp)
RUNFLG = 
IGNORE = >>run.l 2>&1
EFLAGS = -lpthread -lwiringPi
CFLAGS = -Wall -Werror -I $(SRCDIR)/ -std=c++11
OBJECT = $(BINDIR)/main.o

.phony: all
all: build 

.phony: build
build: installdirs $(TARGET) $(TESTS)

.phony: installdirs
installdirs: $(BINDIR)

$(BINDIR):
	$(NEWDIR) $@

$(TARGET): $(OBJECT)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ $(EFLAGS)

$(BINDIR)/main.o: $(SRCDIR)/main.cpp $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ $(EFLAGS)

.phony: clean
clean:
	$(RM) $(BINDIR)
