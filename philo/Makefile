CC = cc

CFLAGS = -Werror -Wextra -Wall -I Headers -g

SRCS = ./src/main.c ./src/utils.c

OBJS_DIR := objects

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

NAME = philo

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY:fclean all clean re