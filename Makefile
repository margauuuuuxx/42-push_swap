NAME		= push_swap
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I includes

SRCS 		=	srcs/main.c \
				srcs/algo.c \
				srcs/common/named_operations/named_operations.c srcs/common/named_operations/named_operations2.c srcs/common/named_operations/operations.c srcs/common/compress.c srcs/common/final_rotate.c \
				srcs/large/alone.c srcs/large/chunk.c srcs/large/cost_utils.c srcs/large/cost.c srcs/large/sort_large_stack.c srcs/large/sort_large_utils.c srcs/large/sort_large_utils2.c \
				srcs/lis/lis_utils.c srcs/lis/lis.c \
				srcs/medium/insertion.c srcs/medium/sort_medium_stack.c \
				srcs/parsing/parsing_utils.c srcs/parsing/parsing.c \
				srcs/small/small_sort.c \
				srcs/utils/split.c srcs/utils/stack_utils.c srcs/utils/utils.c

# Test configuration
TEST_DIR	= tests
# SUPPRESS WILDCARD
TEST_SRCS	= $(wildcard $(TEST_DIR)/test_*.c) 
TEST_BINS	= $(TEST_SRCS:$(TEST_DIR)/%.c=$(TEST_DIR)/%)
TEST_OBJS	= $(filter-out $(OBJDIR)/srcs/main.o, $(OBJS))

OBJDIR 		= objects
OBJS		= $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo -e "Compiling push_swap..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo -e "\033[32mDone!\033[0m"

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