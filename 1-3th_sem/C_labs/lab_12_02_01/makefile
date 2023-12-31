INC_PATH := ./inc/
OBJ_PATH := ./out/
SRC_PATH := ./src/
FUNCTESTS_PATH := ./func_tests/
UNITTESTS_PATH := ./unit_tests/


CC := gcc
CFLAGS = -std=c99 $(CINC_PATH_KEY) -Wall -Wpedantic -Wextra -Werror -ggdb
LFLAGS = -O0

SRCS := $(SRC_PATH)main.c $(SRC_PATH)compare.c $(SRC_PATH)dyn_arrs.c
OBJS := $(addprefix $(OBJ_PATH), $(notdir $(SRCS:.c=.o)))

UNIT_SRCS := $(UNITTESTS_PATH)check_main.c $(UNITTESTS_PATH)check_unit_tests.c $(SRC_PATH)compare.c $(SRC_PATH)dyn_arrs.c
UNIT_OBJS := $(addprefix $(OBJ_PATH), $(notdir $(UNIT_SRCS:.c=.o)))

.PHONY : clean func unit check
.NOTPARALLEL : static dyn_link dyn_load static_unit dyn_link_unit dyn_load_unit func unit


STAT_LIB_PATH := ./lib_stat/
STAT_LIB_SRCS := $(STAT_LIB_PATH)sort_and_filter.c $(STAT_LIB_PATH)get_and_write_data.c
STAT_LIB_OBJS := $(addprefix $(OBJ_PATH)stat_, $(notdir $(STAT_LIB_SRCS:.c=.o)))
STAT_LIB := $(STAT_LIB_PATH)libio_and_proc_data.a


DYN_LINK_LIB_PATH := ./lib_dyn_link/
DYN_LIB_SRC := $(DYN_LINK_LIB_PATH)sort_and_filter.c $(DYN_LINK_LIB_PATH)get_and_write_data.c
DYN_LIB_OBJS := $(addprefix $(OBJ_PATH)dyn_link_, $(notdir $(DYN_LIB_SRC:.c=.o)))
DYN_LIB := io_and_proc_data.dll

DYN_LOAD_LIB_PATH := ./lib_dyn_load/
DYN_LOAD_SRCS := $(DYN_LOAD_LIB_PATH)dyn_load_main.c $(SRC_PATH)compare.c $(SRC_PATH)dyn_arrs.c
DYN_LOAD_OBJS := $(addprefix $(OBJ_PATH), $(notdir $(DYN_LOAD_SRCS:.c=.o)))

CINC_PATH_KEY := -I$(INC_PATH) -I$(STAT_LIB_PATH) -I$(DYN_LINK_LIB_PATH)


static : $(OBJ_PATH)static.lastbuildstate $(STAT_LIB) $(OBJS) | $(OBJ_PATH)
	$(CC) $(LFLAGS) $(OBJS) $(STAT_LIB) -o app.exe
	
$(STAT_LIB) : $(STAT_LIB_OBJS)
	ar rc $@ $^
	ranlib $@
	
static_unit : $(OBJ_PATH)static.lastbuildstate $(STAT_LIB) $(UNIT_OBJS) | $(OBJ_PATH)
	$(CC) $(LFLAGS) $(UNIT_OBJS) $(STAT_LIB) -lcheck -o unit_tests.exe



dyn_link : $(OBJ_PATH)dyn_link.lastbuildstate $(DYN_LIB) $(OBJS) | $(OBJ_PATH)
	$(CC) $(LFLAGS) $(OBJS) -L. -l$(notdir $(basename $(DYN_LIB))) -o app.exe
	
$(DYN_LIB) : $(DYN_LIB_OBJS)
	$(CC) -shared $^ -Wl,--subsystem,windows -o $@

dyn_link_unit : $(OBJ_PATH)dyn_link.lastbuildstate $(DYN_LIB) $(UNIT_OBJS) | $(OBJ_PATH)
	$(CC) $(LFLAGS) $(UNIT_OBJS) -L. -l$(notdir $(basename $(DYN_LIB))) -lcheck -o unit_tests.exe


dyn_load : CFLAGS = -std=c99 $(CINC_PATH_KEY) -Wall -Wpedantic -Werror -ggdb
dyn_load : $(OBJ_PATH)dyn_load.lastbuildstate $(DYN_LIB) $(DYN_LOAD_OBJS) | $(OBJ_PATH)
	$(CC) $(LFLAGS) $(DYN_LOAD_OBJS) -o app.exe


$(OBJ_PATH)static.lastbuildstate : $(OBJ_PATH)
	rm -fv *.exe
	rm -fv $(OBJ_PATH)*.o
	rm -fv $(OBJ_PATH)*.gcno
	rm -fv $(OBJ_PATH)*.gcda
	rm -fv $(OBJ_PATH)dyn_link.lastbuildstate
	rm -fv $(OBJ_PATH)dyn_load.lastbuildstate
	touch $(OBJ_PATH)static.lastbuildstate

$(OBJ_PATH)dyn_link.lastbuildstate : $(OBJ_PATH)
	rm -fv *.exe
	rm -fv $(OBJ_PATH)*.o
	rm -fv $(OBJ_PATH)*.gcno
	rm -fv $(OBJ_PATH)*.gcda
	rm -fv $(OBJ_PATH)dyn_load.lastbuildstate
	rm -fv $(OBJ_PATH)static.lastbuildstate
	touch $(OBJ_PATH)dyn_link.lastbuildstate
	
$(OBJ_PATH)dyn_load.lastbuildstate : $(OBJ_PATH)
	rm -fv *.exe
	rm -fv $(OBJ_PATH)*.o
	rm -fv $(OBJ_PATH)*.gcno
	rm -fv $(OBJ_PATH)*.gcda
	rm -fv $(OBJ_PATH)dyn_link.lastbuildstate
	rm -fv $(OBJ_PATH)static.lastbuildstate
	touch $(OBJ_PATH)dyn_load.lastbuildstate
	
	
	
$(OBJ_PATH)%.o : $(SRC_PATH)%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $@
	
$(OBJ_PATH)%.o : $(UNITTESTS_PATH)%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $@
	
$(OBJ_PATH)stat_%.o : $(STAT_LIB_PATH)%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $@
	
$(OBJ_PATH)dyn_link_%.o : $(DYN_LINK_LIB_PATH)%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) $(LFLAGS) -D ARR_EXPORTS -c $< -o $@
	
$(OBJ_PATH)dyn_load_main.o : $(DYN_LOAD_LIB_PATH)dyn_load_main.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $@
	
	
	
$(OBJ_PATH)%.d : $(SRC_PATH)%.c | $(OBJ_PATH)
	$(CC) -MM $(CINC_PATH_KEY) $< > $@
	
$(OBJ_PATH)%.d : $(UNITTESTS_PATH)%.c | $(OBJ_PATH)
	$(CC) -MM $(CINC_PATH_KEY) $< > $@
	
$(OBJ_PATH)stat_%.d : $(STAT_LIB_PATH)%.c | $(OBJ_PATH)
	$(CC) -MM $(CINC_PATH_KEY) $< > $@
	
$(OBJ_PATH)dyn_link_%.d : $(DYN_LINK_LIB_PATH)%.c | $(OBJ_PATH)
	$(CC) -MM $(CINC_PATH_KEY) $< > $@	
	
$(OBJ_PATH)dyn_load_main.d : $(DYN_LOAD_LIB_PATH)dyn_load_main.c | $(OBJ_PATH)
	$(CC) -MM $(CINC_PATH_KEY) $< > $@
	
	
include $(addprefix $(OBJ_PATH), $(notdir $(SRCS:.c=.d)))
include $(addprefix $(OBJ_PATH), $(notdir $(UNIT_SRCS:.c=.d)))
include $(addprefix $(OBJ_PATH)stat_, $(notdir $(STAT_LIB_SRCS:.c=.d)))
include $(addprefix $(OBJ_PATH)dyn_link_, $(notdir $(DYN_LIB_SRC:.c=.d)))
include $(OBJ_PATH)dyn_load_main.d
	
	
	
func : app.exe | $(OBJ_PATH)
	@echo
	cd $(FUNCTESTS_PATH) && cmd //C all_test.cmd
	@echo
	#gcov $(OBJS)
	
unit : unit_tests.exe | $(OBJ_PATH)
	@echo
	drmemory -lib_blacklist "*" -batch -prefix_style 2 -logdir $(OBJ_PATH) -- ./unit_tests.exe

check : $(SRCS)
	@echo
	cppcheck $(SRC_PATH) $(UNITTESTS_PATH)
	@echo
	rm -fv $(OBJ_PATH)*.d
	
dirs : $(INC_PATH) $(OBJ_PATH) $(SRC_PATH) $(FUNCTESTS_PATH) $(UNITTESTS_PATH) $(LIB_PATH)

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
	
$(LIB_PATH) :
	mkdir -p $(LIB_PATH)
	
clean : 
	rm -fv *.exe
	rm -fv $(OBJ_PATH)*.d
	rm -fv $(OBJ_PATH)*.o
	rm -fv $(OBJ_PATH)*.gcno
	rm -fv $(OBJ_PATH)*.gcda
	rm -fv *.h.gcov
	rm -fv $(STAT_LIB)
	rm -fv $(DYN_LIB)
	rm -fv *.c.gcov
	rm -fv $(OBJ_PATH)*.lastbuildstate
	rm -fv $(OBJ_PATH)*.temp
	rm -rf $(OBJ_PATH)DrMemory*
	rm -rf $(OBJ_PATH)dynamorio
	rm -rf $(OBJ_PATH)symcache
	rm -rf $(OBJ_PATH)resfile.*