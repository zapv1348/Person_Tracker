#this project is currently just for tracking a single individual and giving you an estimate (aka guess)
#of how far away they are
# Makefile
# Creator: Zachary Vogel
# 2/5/2018

#==================================================
# Common Configuration Section
#==================================================

# initialize directory paths
OBJDIR = ./obj
SRCDIR = ./src
ASMDIR = ./asm
INCDIR = ./inc

# set default architecture
ARCH := x86

# toolchain
CC := g++
LD := g++
SIZE = size
OBJDUMP = objdump

# define flags
CFLAGS = -c -std=c++17 -Wall -Wextra -g -O2 -I$(INCDIR)
LDFLAGS = -I$(INCDIR) 
SFLAGS = -S -O2 -Wall -Wextra -I$(INCDIR)

#==================================================
# File Lists
#==================================================
# .c file dependencies (header files)
DEPS := $(shell find $(INCDIR) -name '*.hpp')

# .c files themselves
SRCS := $(shell find $(SRCDIR) -name '*.cpp')

# .o file list
OBJS := $(addprefix $(OBJDIR)/,$(SRCS:%.cpp=%.o))

# .S/.asm file list
SMS := $(addprefix $(ASMDIR)/,$(SRCS:%.cpp=%.S))


# .elf file list
elf := person_tracker


#==================================================
# Specific Build Targets
#==================================================
all: person_tracker


.PHONY: asm-file
asm-file: $(SMS)

.PHONY: compile-all
compile-all: $(OBJS)

.PHONY: build
build: $(OBJS)
	$(CC) $(LDFLAGS) -o ./person_tracker $^
	$(OBJDUMP) -f person_tracker
	$(SIZE) ./person_tracker

.PHONY: clean
clean:
	rm -f person_tracker  
	rm -rf obj
	rm -rf asm

#==================================================
# Implicit Targets
#==================================================
$(OBJDIR)/%.o: %.cpp $(DEPS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $<

person_tracker: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(ASMDIR)/%.S: %.cpp $(DEPS)
	@mkdir -p $(@D)
	$(CC) $(SFLAGS) $< -o $@

