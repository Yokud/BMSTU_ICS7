INC_PATH := ./inc/
OBJ_PATH := ./out/
SRC_PATH := ./src/
FUNCTESTS_PATH := ./func_tests/
UNITTESTS_PATH := ./unit_tests/
CINC_PATH_KEY := -I$(INC_PATH)

CC := gcc
CFLAGS = -std=c99 $(CINC_PATH_KEY) -Wall -Wpedantic -Wextra -Werror -ggdb
LFLAGS = --coverage

SRCS := $(SRC_PATH)main.c $(SRC_PATH)data_structure.c
OBJS := $(addprefix $(OBJ_PATH), $(notdir $(SRCS:.c=.o)))

.PHONY : run clean func cppcheck
.NOTPARALLEL : build app.exe

build : app.exe

app.exe : $(OBJS)
	$(CC) $(LFLAGS) -o $@ $(OBJS)
	
$(OBJ_PATH)%.o : $(SRC_PATH)%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $@
	
$(OBJ_PATH)%.d : $(SRC_PATH)%.c | $(OBJ_PATH)
	$(CC) -MM $(CINC_PATH_KEY) $< > $@
	
include $(addprefix $(OBJ_PATH), $(notdir $(SRCS:.c=.d)))

$(OBJ_PATH) :
	mkdir -p $(OBJ_PATH)
	
func : app.exe | $(OBJ_PATH)
	@echo
	cd $(FUNCTESTS_PATH) && cmd //C all_test.cmd
	@echo
	gcov -n $(OBJS)
	
cppcheck : $(SRCS)
	@echo
	cppcheck $(SRC_PATH) $(UNITTESTS_PATH)
	@echo
	rm -fv $(OBJ_PATH)*.d

run : app.exe
	drmemory -lib_blacklist "*" -batch -prefix_style 2 -logdir $(OBJ_PATH) -- ./app.exe
	
clean : 
	rm -fv *.exe
	rm -fv $(OBJ_PATH)*.d
	rm -fv $(OBJ_PATH)*.o
	rm -fv $(OBJ_PATH)*.gcno
	rm -fv $(OBJ_PATH)*.gcda
	rm -fv $(OBJ_PATH)*.temp
	rm -rf $(OBJ_PATH)DrMemory*
	rm -rf $(OBJ_PATH)dynamorio
	rm -rf $(OBJ_PATH)symcache
	rm -rf $(OBJ_PATH)resfile.*

