CC=gcc
CFLAGS=-DCONFIG_SYS_VALGRIND -ansi -Werror -Wall -pedantic-errors
APP=brackets

OBJS=brackets.o

all: $(APP)

help:
	@echo "\033[1mbuild $(APP) - analyize bracket correctness in a text\033[0m"
	@echo "targets:"
	@echo "  \033[1m[all]\033[0m:    build \033[1m$(APP)\033[0m"
	@echo "  \033[1mclean\033[0m:    remove all object files"
	@echo "  \033[1mcleanall\033[0m: do \033[1mclean\033[0m and remove tags file and \033[1m$(APP)\033[0m"
	@echo ""
	@echo "  command line options:"
	@echo "      \033[1mDEBUG=y\033[0m: build debug version"

ifeq ($(DEBUG),y)
  CFLAGS+=-g -DDEBUG
endif

%.o: %.c
	$(CC) -o $@ $(CFLAGS) -c $<

$(APP): $(OBJS)

clean:
	@echo "removing object files"
	@rm -rf *.o

cleanall: clean
	@echo "removing tag file"
	@rm -rf tags
	@echo "removing $(APP)"
	@rm -f $(APP)

