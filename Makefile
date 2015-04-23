# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/14 11:39:43 by ncoden            #+#    #+#              #
#    Updated: 2014/11/29 17:52:11 by ncoden           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
CCLIB = -Llibft -lft
CCFLAGS = -Wall -Werror -Wextra
SRCDIR = src
OBJDIR = obj
INCDIR = includes libft/includes

SRC = 	main.c\
		options.c\
		dirs.c\
		sort.c\
		recurs.c\
		print.c\
		print_rights.c\
		print_about.c\
		maxs.c\
		functions.c

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
INCS = $(addprefix -I , $(INCDIR))

all: $(NAME)
$(NAME): build $(OBJS)
		@make -C libft
		@gcc $(CCLIB) -o $(NAME) $(OBJS)
build:
		@mkdir -p $(OBJDIR)
clean:
		@make -C libft clean
		@rm -f $(OBJS)
fclean: clean
		@make -C libft fclean
		@rm -f $(NAME)
re: fclean all

dev : all
		@./$(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
		@gcc -c $(CCFLAGS) $(INCS) -o $@ $<
