NAME		= push_swap
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -DDEBUG_MODE
INCLUDES	= -I includes -I printf/includes -I printf/libft

SRCS 		=	srcs/main.c \
				srcs/named_operations/named_operations.c srcs/named_operations/operations.c \
				srcs/utils/split.c srcs/utils/stack_utils.c srcs/utils/utils.c \
				srcs/algo.c srcs/chunk.c srcs/compress.c srcs/cost.c \
				srcs/final_rotate.c srcs/insertion.c srcs/lis.c \
				srcs/parsing.c srcs/small_sort.c srcs/sort_medium_stack.c srcs/sort_small_stack.c

# Test configuration
TEST_DIR	= tests
# SUPPRESS WILDCARD
TEST_SRCS	= $(wildcard $(TEST_DIR)/test_*.c) 
TEST_BINS	= $(TEST_SRCS:$(TEST_DIR)/%.c=$(TEST_DIR)/%)
TEST_OBJS	= $(filter-out $(OBJDIR)/srcs/main.o, $(OBJS))

# NAME_BONUS      = checker
# SRCS_BONUS      = srcs/checker/main_bonus.c \
#                   srcs/checker/reader_bonus.c
# OBJS_BONUS      = $(SRCS_BONUS:%.c=$(OBJDIR)/%.o)

OBJDIR 		= objects
OBJS		= $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo -e "Compiling push_swap..."
	@$(CC) $(CFLAGS) $(OBJS) $(PRINTF_LIB) -lm -o $(NAME)
	@echo -e "\033[32mDone!\033[0m"

# bonus: $(PRINTF_LIB) $(OBJS_BONUS) $(OBJS_COMMON)
# 	@echo -e "\033[32mCompiling checker... \033[0m"
# 	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(OBJS_COMMON) $(PRINTF_LIB) -o $(NAME_BONUS)
# 	@echo -e "\033[32mDone!\033[0m"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo -e "Cleaning objects..."
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(TEST_BINS)
	@echo -e "Full cleaning..."
	@echo -e "\033[32mDone!\033[0m"

re: fclean all

# Test targets
$(TEST_DIR)/%: $(TEST_DIR)/%.c $(TEST_OBJS)
	@echo -e "\033[34mCompiling test: $@\033[0m"
	@$(CC) $(CFLAGS) $(INCLUDES) $< $(TEST_OBJS) -o $@

tests: $(OBJS) $(TEST_BINS)
	@echo -e "\033[32mAll tests compiled!\033[0m"

test: tests
	@echo -e "\n\033[33mRunning all tests...\033[0m\n"
	@chmod +x $(TEST_DIR)/run_all_tests.sh
	@./$(TEST_DIR)/run_all_tests.sh

.PHONY: all clean fclean re tests test