NAME = philo_bonus
CC = gcc

FLAGS =

DIR_LIBFT = ../libft/libft/
LIBFT = ../libft/libft/libft.a

HEADER = ./philosopher.h

PHILO_BONUS_SRC = philosopher.c init.c monitor.c actions.c service1.c service2.c

SOURCES_LIBFT = $(addprefix $(DIR_LIBFT), $(LIBFT))

all: $(NAME)

$(NAME): $(LIBFT) $(PHILO_BONUS_SRC) $(HEADER)
	@$(CC) $(FLAGS) -pthread $(PHILO_BONUS_SRC) $(LIBFT) -o $(NAME) -g
	@echo "PHILO is ready to use"

$(LIBFT):
	$(MAKE) -C $(DIR_LIBFT)

clean:
	$(MAKE) clean -C $(DIR_LIBFT)

fclean:
	$(MAKE) fclean -C $(DIR_LIBFT)
	@rm -f $(NAME)

re: fclean all

.PHONY : all re fclean clean
