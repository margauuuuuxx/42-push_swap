NAME		= push_swap
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -DDEBUG_MODE
INCLUDES	= -I includes -I printf/includes -I printf/libft

SRCS 		= 

OBJS		= $(SRCS:%.c=$(OBJDIR)/%.o)

# NAME_BONUS      = checker
# SRCS_BONUS      = srcs/checker/main_bonus.c \
#                   srcs/checker/reader_bonus.c
# OBJS_BONUS      = $(SRCS_BONUS:%.c=$(OBJDIR)/%.o)

OBJDIR 		= objects
OBJS		= $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(PRINTF_LIB) $(OBJS)
	@echo -e "\033[32mCompiling push_swap...\033[0m"
	@$(CC) $(CFLAGS) $(OBJS) $(PRINTF_LIB) -o $(NAME)
	@echo -e "\033[32mDone!\033[0m"

# bonus: $(PRINTF_LIB) $(OBJS_BONUS) $(OBJS_COMMON)
# 	@echo -e "\033[32mCompiling checker... \033[0m"
# 	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(OBJS_COMMON) $(PRINTF_LIB) -o $(NAME_BONUS)
# 	@echo -e "\033[32mDone!\033[0m"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo -e "\033[31mCleaning objects...\033[0m"
	@rm -rf $(OBJDIR)
# @rm -f $(NAME) $(NAME_BONUS)

fclean: clean
	@echo -e "\033[31mFull cleaning...\033[0m"
	@echo -e "\033[31mDone!\033[0m"

re: fclean all

.PHONY: all clean fclean re