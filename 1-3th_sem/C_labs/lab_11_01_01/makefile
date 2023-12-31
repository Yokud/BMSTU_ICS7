INC_PATH := ./inc/
OBJ_PATH := ./out/
SRC_PATH := ./src/
FUNCTESTS_PATH := ./func_tests/
UNITTESTS_PATH := ./unit_tests/
CINC_PATH_KEY := -I$(INC_PATH)

CC := gcc
CFLAGS = -std=c99 $(CINC_PATH_KEY) -Wall -Wpedantic -Wextra -Werror -ggdb
LFLAGS = --coverage

SRCS := $(SRC_PATH)main.c $(SRC_PATH)my_snprintf.c
OBJS := $(addprefix $(OBJ_PATH), $(notdir $(SRCS:.c=.o)))

UNIT_SRCS := $(UNITTESTS_PATH)check_main.c $(UNITTESTS_PATH)check_unit_tests.c $(SRC_PATH)my_snprintf.c
UNIT_OBJS := $(addprefix $(OBJ_PATH), $(notdir $(UNIT_SRCS:.c=.o)))

.PHONY : clean func unit check
.NOTPARALLEL : release debug app.exe unit_tests.exe func unit

release : CFLAGS = -std=c99 $(CINC_PATH_KEY) -Wall -Wpedantic -Wextra -Werror
release : LFLAGS = -O0
release : $(OBJ_PATH)release.lastbuildstate app.exe | $(OBJ_PATH)

debug : $(OBJ_PATH)debug.lastbuildstate app.exe | $(OBJ_PATH)

app.exe : $(OBJS) | $(OBJ_PATH)
	$(CC) $(LFLAGS) -o $@ $(OBJS)
	
unit_tests.exe : $(UNIT_OBJS) | $(OBJ_PATH)
	$(CC) $(LFLAGS) $(UNIT_OBJS) -lcheck -o $@

$(OBJ_PATH)debug.lastbuildstate :
	rm -fv *.exe
	rm -fv $(OBJ_PATH)*.o
	rm -fv $(OBJ_PATH)*.gcno
	rm -fv $(OBJ_PATH)*.gcda
	rm -fv $(OBJ_PATH)release.lastbuildstate
	touch $(OBJ_PATH)debug.lastbuildstate

$(OBJ_PATH)release.lastbuildstate :
	rm -fv *.exe
	rm -fv $(OBJ_PATH)*.o
	rm -fv $(OBJ_PATH)*.gcno
	rm -fv $(OBJ_PATH)*.gcda
	rm -fv $(OBJ_PATH)debug.lastbuildstate
	touch $(OBJ_PATH)release.lastbuildstate
	
$(OBJ_PATH)%.o : $(SRC_PATH)%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $@
	
$(OBJ_PATH)%.o : $(UNITTESTS_PATH)%.c | $(OBJ_PATH)
	$(CC) $(LFLAGS) $(CFLAGS) -c $< -o $@
	
$(OBJ_PATH)%.d : $(SRC_PATH)%.c | $(OBJ_PATH)
	$(CC) -MM $(CINC_PATH_KEY) $< > $@
	
$(OBJ_PATH)%.d : $(UNITTESTS_PATH)%.c | $(OBJ_PATH)
	$(CC) -MM $(CINC_PATH_KEY) $< > $@
	
#include $(addprefix $(OBJ_PATH), $(notdir $(SRCS:.c=.d)))
include $(addprefix $(OBJ_PATH), $(notdir $(UNIT_SRCS:.c=.d)))
	
func : $(OBJ_PATH)debug.lastbuildstate app.exe | $(OBJ_PATH)
	@echo
	cd $(FUNCTESTS_PATH) && cmd //C all_test.cmd
	@echo
	gcov $(OBJS)
	
unit : $(OBJ_PATH)debug.lastbuildstate unit_tests.exe | $(OBJ_PATH)
	@echo
	drmemory -lib_blacklist "*" -batch -prefix_style 2 -logdir $(OBJ_PATH) -- ./unit_tests.exe

check : $(SRCS)
	@echo
	cppcheck $(SRC_PATH) $(UNITTESTS_PATH)
	@echo
	rm -fv $(OBJ_PATH)*.d
	
dirs : $(INC_PATH) $(OBJ_PATH) $(SRC_PATH) $(FUNCTESTS_PATH) $(UNITTESTS_PATH)

$(OBJ_PATH) :
	mkdir -p $(OBJ_PATH)

$(INC_PATH) :
	mkdir -p $(INC_PATH)

$(SRC_PATH) :
	mkdir -p $(SRC_PATH)
	
$(FUNCTESTS_PATH) :
	mkdir -p $(FUNCTESTS_PATH)
	
$(UNITTESTS_PATH) :
	mkdir -p $(UNITTESTS_PATH)
	
clean : 
	rm -fv *.exe
	rm -fv $(OBJ_PATH)*.d
	rm -fv $(OBJ_PATH)*.o
	rm -fv $(OBJ_PATH)*.gcno
	rm -fv $(OBJ_PATH)*.gcda
	rm -fv *.h.gcov
	rm -fv *.c.gcov
	rm -fv $(OBJ_PATH)*.lastbuildstate
	rm -fv $(OBJ_PATH)*.temp
	rm -rf $(OBJ_PATH)DrMemory*
	rm -rf $(OBJ_PATH)dynamorio
	rm -rf $(OBJ_PATH)symcache
	rm -rf $(OBJ_PATH)resfile.*