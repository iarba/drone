CC     = g++
NEWDIR = mkdir
SRCDIR = src
BINDIR = bin
RM     = rm -rf
TARGET = $(BINDIR)/drone
HEADER = $(wildcard $(SRCDIR)/*.hpp)
SOURCE = $(wildcard $(SRCDIR)/*.cpp)
OBJECT = $(patsubst %.cpp,%.o, $(patsubst $(SRCDIR)/%,$(BINDIR)/%, $(SOURCE)))
RUNFLG = 
IGNORE = >>run.l 2>&1
EFLAGS = -pthread -lwiringPi
CFLAGS = -Wall -Werror -I $(SRCDIR)/ -std=c++11

.PHONY: all
all: build 

.PHONY: build
build: installdirs $(TARGET)

.PHONY: installdirs
installdirs: $(BINDIR)

$(BINDIR):
	$(NEWDIR) $@

$(TARGET): $(OBJECT)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ $(EFLAGS)

$(BINDIR)/%.o: $(SRCDIR)/%.cpp $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ $(EFLAGS)

.PHONY: clean
clean:
	$(RM) $(BINDIR)
