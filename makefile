# Compiler
CC = clang++

# Flags
CFLAGS = -c -Wall -std=c++14 -I src/ -I src/entities -I src/helpers
LDLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -framework CoreFoundation

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Executables
APP_NAME = breakout
EXEC := $(addprefix $(BINDIR)/, $(APP_NAME))

# Package
APP_PKG=$(APP_NAME).app
CONTENTS_DIR=$(APP_PKG)/Contents
RSC_DIR=$(CONTENTS_DIR)/resources
EXEC_DIR=$(CONTENTS_DIR)/MacOS

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
	rm -rf $(APP_PKG) $(BINDIR) $(OBJDIR)

package: $(EXEC)
	@[[ -d $(APP_PKG) ]] || mkdir $(APP_PKG)
	@[[ -d $(CONTENTS_DIR) ]] || mkdir $(CONTENTS_DIR)
	@[[ -d $(RSC_DIR) ]] || mkdir $(RSC_DIR)
	@[[ -d $(EXEC_DIR) ]] || mkdir $(EXEC_DIR)
	cp $(EXEC) $(EXEC_DIR)
	rsync -av ./resources $(CONTENTS_DIR)

print_vars:
	@echo SOURCES = $(SOURCES)
	@echo OBJECTS = $(OBJECTS)
	@echo HEADERS = $(HEADERS)
	@echo EXEC = $(EXEC)

run: $(EXEC)
	@./$(EXEC)

.PHONY: clean test run print_vars
