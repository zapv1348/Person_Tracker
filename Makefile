#this project is currently just for tracking a single individual and giving you an estimate (aka guess)
#of how far away they are
# Makefile
# Creator: Zachary Vogel
# 2/5/2018

#==================================================
# Common Configuration Section
#==================================================

UNAME := $(shell uname -s)

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
ifeq ($(UNAME), Darwin)
CFLAGS = -c -std=c++14 -Wall -Wextra -g -DDARWIN -O2 -I$(INCDIR) $(shell pkg-config --cflags  opencv)
endif
ifeq ($(UNAME), Linux)
CFLAGS = -c -std=c++17 -Wall -Wextra -g -DLINUX -O2 -I$(INCDIR) $(shell pkg-config --cflags --libs opencv)
endif
LDFLAGS = -I$(INCDIR) $(shell pkg-config --cflags --libs opencv)
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
	rm -rf training_data

#==================================================
# Implicit Targets
#==================================================
$(OBJDIR)/%.o: %.cpp $(DEPS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $<

person_tracker: $(OBJS)
	@mkdir -p training_data
	$(CC) $(LDFLAGS) -o $@ $^

$(ASMDIR)/%.S: %.cpp $(DEPS)
	@mkdir -p $(@D)
	$(CC) $(SFLAGS) $< -o $@

