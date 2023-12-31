CC:=gcc
INCPATH:=./inc/
SRCPATH:=./src/
OBJPATH:=./out/
CINCPATH:=-I$(INCPATH)
SRCS:=$(SRCPATH)alloc_strings.c $(SRCPATH)file_utils.c $(SRCPATH)hash_utils.c $(SRCPATH)trees.c $(SRCPATH)measuring.c $(SRCPATH)main.c
OBJS:=$(addprefix $(OBJPATH), $(notdir $(SRCS:.c=.o)))
CFLAGS:=-std=c99 --coverage -Wall -Werror -Wextra -Wpedantic -g3 $(CINCPATH)
LFLAGS:=--coverage
TRASH:=*.exe $(OBJPATH)*.d $(OBJPATH)*.o $(OBJPATH)*.gcno $(OBJPATH)*.gcda $(OBJPATH)*.out $(OBJPATH)*.lastbuildstate
 
.PHONY: clean debug release
.NOTPARALLEL: release debug app.exe

release: CFLAGS:=-std=c99 -I$(INCPATH)
release: LFLAGS:=-o0

release: $(OBJPATH) $(OBJPATH)release.lastbuildstate app.exe

debug: $(OBJPATH) $(OBJPATH)debug.lastbuildstate app.exe

memcheck: $(OBJPATH) $(OBJPATH)debug.lastbuildstate app.exe
	cppcheck $(SRCS)
	drmemory -lib_blacklist "*" -batch -prefix_style 2 -logdir $(OBJ_PATH) -- ./app.exe


vpath %.c $(UNITTESTPATH)
vpath %.c $(SRCPATH)

$(OBJPATH)release.lastbuildstate:
	rm -fv $(TRASH)
	touch $(OBJPATH)release.lastbuildstate
	
$(OBJPATH)debug.lastbuildstate:
	rm -fv $(TRASH)
	touch $(OBJPATH)debug.lastbuildstate
	
app.exe: $(OBJPATH) $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $@
	
$(OBJPATH)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJPATH)%.d : $(SRCPATH)%.c
	$(CC) -MM $(CINCPATH) $< > $@
	
	
include $(addprefix $(OBJPATH), $(notdir $(SRCS:.c=.d)))

$(OBJPATH):
	mkdir -p $(OBJPATH)
	
clean:
	rm -fv $(TRASH)
