# COLORS
MAGENTA = \033[35;1m
YELLOW  = \033[33;1m
GREEN   = \033[32;1m
WHITE   = \033[37;1m
RESET   = \033[0m
GRAY 	= \033[0;90m
BLUE    = \033[34;1m
CYAN    = \033[37;1m
BOLD	= \033[1m
RED		= \033[31;1m

#---------- BASE ----------#

# FILES 
CFILES = philo.c check_argv.c error.c routine.c routine_utils.c actions.c\

ORDER_CFILES = 

# DIRECTORIES 
SRC_DIR = src/
ORDER_SRC_DIR = src/order_cmd/
OBJ_DIR = objs/

# OBJECTS
OFILES = $(addprefix $(OBJ_DIR), $(CFILES:.c=.o))
ORDER_OFILES = $(addprefix $(OBJ_DIR)order_cmd/, $(ORDER_CFILES:.c=.o))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@ mkdir -p $(OBJ_DIR)
	@ echo "$(BLUE)Compiling File: $(RESET)$(notdir $<)"
	@ $(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)order_cmd/%.o: $(ORDER_SRC_DIR)%.c
	@ mkdir -p $(OBJ_DIR)/order_cmd/
	@ $(CC) $(CFLAGS) -c $< -o $@

#---------- BONUS ----------#

# FILES 
BONUS_CFILES = \

BONUS_ORDER_CFILES = 

# DIRECTORIES
BONUS_SRC_DIR = bonus/
BONUS_ORDER_SRC_DIR = bonus/order_cmd/
BONUS_OBJ_DIR = bonus/objs/

# OBJECTS
BONUS_OFILES = $(addprefix $(BONUS_OBJ_DIR), $(BONUS_CFILES:.c=.o))
BONUS_ORDER_OFILES = $(addprefix $(BONUS_OBJ_DIR)order_cmd/, $(BONUS_ORDER_CFILES:.c=.o))

$(BONUS_OBJ_DIR)%.o: $(BONUS_SRC_DIR)%.c
	@mkdir -p $(BONUS_OBJ_DIR)
	@echo "$(CYAN)Compiling File: $(RESET)$(notdir $<)"
	@ $(CC) $(CFLAGS) -c $< -o $@

$(BONUS_OBJ_DIR)order_cmd/%.o: $(BONUS_ORDER_SRC_DIR)%.c
	@mkdir -p $(BONUS_OBJ_DIR)/order_cmd/
	@ $(CC) $(CFLAGS) -c $< -o $@


#---------- FLAGS & COMPILATION ----------#

CC = clang
NAME = philo
BONUS_NAME = checker_bonus
CFLAGS = -Wall -Werror -Wextra -pthread -fsanitize=thread -g

all: $(NAME)
$(NAME): compiling $(OFILES) $(ORDER_OFILES)
	@ echo
	@ $(CC) $(CFLAGS) $(OFILES) $(ORDER_OFILES) -o $(NAME)
	@ echo "$(YELLOW)Compilation finished!$(RESET)"

bonus: all $(BONUS_NAME)
$(BONUS_NAME): $(BONUS_OFILES) $(BONUS_ORDER_OFILES)
	@ $(CC) $(CFLAGS) $(BONUS_OFILES) $(BONUS_ORDER_OFILES) -o $(BONUS_NAME)

#---------- CLEAN ----------#

clean:
	@ echo "$(RED)Cleaning Project ... $(RESET)"
	@ rm -f $(OFILES) $(ORDER_OFILES) $(BONUS_OFILES) $(BONUS_ORDER_OFILES)
	@ rm -rf $(OBJ_DIR)order_cmd/ $(OBJ_DIR) $(BONUS_OBJ_DIR)order_cmd/ $(BONUS_OBJ_DIR)
	@ echo "$(YELLOW)Project Cleaned!\n $(RESET)"

fclean: clean
	@ rm -f $(NAME) $(BONUS_NAME)

re: fclean all

compiling:
	@ echo "$(MAGENTA)Compiling Project: $(RESET)"

.PHONY: all clean fclean re bonus
