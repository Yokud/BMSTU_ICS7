DLL_PATH := ./dll/
OBJ_PATH := ./out/
CINC_PATH_KEY := -I$(DLL_PATH)

CC := gcc
CFLAGS = -std=c99 $(CINC_PATH_KEY) -Wall -Wpedantic -Wextra -Werror -ggdb
LFLAGS = -O0


.PHONY : clean

SRCS := $(DLL_PATH)arr_lib.c
OBJS := $(addprefix $(OBJ_PATH), $(notdir $(SRCS:.c=.o)))
LIB_NAME := $(DLL_PATH)arr_lib.dll


lib : $(OBJS) | $(OBJ_PATH)
	$(CC) -shared $^ -Wl,--subsystem,windows -o $(LIB_NAME)
	
	
$(OBJ_PATH)%.o : $(DLL_PATH)%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) $(LFLAGS) -D EXPORTS -c $< -o $@
	
	
$(OBJ_PATH)%.d : $(DLL_PATH)%.c | $(OBJ_PATH)
	$(CC) -MM $(CINC_PATH_KEY) $< > $@

include $(addprefix $(OBJ_PATH), $(notdir $(SRCS:.c=.d)))


$(OBJ_PATH) :
	mkdir -p $(OBJ_PATH)

$(DLL_PATH) :
	mkdir -p $(DLL_PATH)

	
clean : 
	rm -fv *.exe
	rm -fv $(OBJ_PATH)*.d
	rm -fv $(OBJ_PATH)*.o
	rm -fv $(LIB_NAME)
	rm -rf ./py/__pycache__