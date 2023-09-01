# Compiler and flags
CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = 

# Directories
OBJDIR = obj
SRCDIR = src
INCLUDEDIR = include
EXAMPLEDIR = examples

# Output names
LIBNAME = $(OBJDIR)/libmem_pool.a
TESTBIN = test_driver

# Sources and objects
LIBSRCS = $(SRCDIR)/mem_pool.c
LIBOBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(LIBSRCS))
TESTSRCS = $(EXAMPLEDIR)/test.c
TESTOBJS = $(TESTSRCS:.c=.o)

all: directories $(LIBNAME) $(TESTBIN)

# Create the object directory
directories: $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compile the library
$(LIBNAME): $(LIBOBJS)
	ar rcs $@ $(LIBOBJS)

# Compile the test driver
$(TESTBIN): $(TESTOBJS) $(LIBNAME)
	$(CC) $(LDFLAGS) -o $@ $(TESTOBJS) -L$(OBJDIR) -lmem_pool

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXAMPLEDIR)/%.o: $(EXAMPLEDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean directories

clean:
	rm -rf $(OBJDIR) $(TESTOBJS) $(TESTBIN)