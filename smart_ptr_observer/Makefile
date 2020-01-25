BIN=main

SRCDIR=src
OBJDIR=obj

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

CC=g++ -std=c++11
CPPFLAGS=
LDFLAGS=


# ensure that all required directories exist and build executable
.PHONY: build
build: directories executable

.PHONY: debug
debug: CPPFLAGS += -g -O0 -DDEBUG
debug: LDFLAGS += -g
debug: build

.PHONY: release
release: CPPFLAGS += -O2
release: build

.PHONY: all
all: debug release


$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CPPFLAGS) -c -o $@ $< 	


$(BIN): $(OBJS)
	$(CC) $(CPPFLAGS) $(LDFLAGS) $^ -o $@


executable: $(BIN)

.PHONY: clean
clean:
	@rm -rf $(OBJDIR) $(BIN)


.PHONY: directories
directories:
	@mkdir -p $(OBJDIR)

info:
	@echo "SRCDIR: $(SRCDIR)"
	@echo "OBJDIR: $(OBJDIR)"
	@echo "SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"
	@echo "BIN: $(BIN)"


