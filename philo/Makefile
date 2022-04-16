# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/08 14:17:22 by juhur             #+#    #+#              #
#    Updated: 2022/04/16 14:37:22 by juhur            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = ./src
SRCS = $(addprefix $(SRC_DIR)/, \
	main.c \
	init.c \
	philo.c \
	util.c \
	monitor.c \
	simulation.c \
)

INC_DIR = ./include
HEADER = $(INC_DIR)/philo.h

OBJS = $(SRCS:.c=.o)

all : $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -I./$(INC_DIR) -c $< -o $@

$(NAME) : $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -o $@