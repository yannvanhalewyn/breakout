# Compiler
CC = clang++

# Flags
CFLAGS = -c -Wall -std=c++14 -I src/ -I src/entities
LDLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -framework CoreFoundation

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Executables
EXEC = breakout
EXEC := $(addprefix $(BINDIR)/, $(EXEC))

# Sources
SOURCES := $(shell find $(SRCDIR) -name '*.cpp')
HEADERS := $(shell find $(SRCDIR) -name '*.h')
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(EXEC): $(OBJECTS)
	@[ -d $(BINDIR) ] || (mkdir $(BINDIR) && echo "made $(BINDIR) dir")
	$(CC) $(LDLFLAGS) $^ -o $@

$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	@[ -d $(dir $@) ] || (mkdir -p $(dir $@) && echo "made dir $(dir $@)")
	$(CC) $(CFLAGS) $< -o $@

# Helpers
clean:
	rm -f $(EXEC) $(OBJECTS)

print_vars:
	@echo SOURCES = $(SOURCES)
	@echo OBJECTS = $(OBJECTS)
	@echo HEADERS = $(HEADERS)
	@echo EXEC = $(EXEC)

run: $(EXEC)
	@./$(EXEC)

.PHONY: clean test run print_vars
