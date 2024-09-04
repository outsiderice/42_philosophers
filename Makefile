# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/19 18:04:18 by amagnell          #+#    #+#              #
#    Updated: 2024/09/04 19:39:38 by amagnell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#      TARGET       #
NAME 		= philo

#      HEADER       #
INC		= inc/philo.h \
		  inc/parse.h

#      FILES        #
SRC_DIR 	= src
SRCS 		=	src/main.c \
				src/init.c \
		  		src/parsing.c \
		  		src/philo.c \
		  		src/routine.c \
				src/philo_utils.c \
				src/utils.c

#    OBJS & DEPS    #
BUILD_DIR	= .build
OBJS 		= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS		= $(OBJS:%.o=%.d)

#        CC         #
CC		= cc
CFLAGS		= -Wall -Wextra -Werror #-fsanitize=thread
CPPFLAGS	= $(addprefix -I, $(INC)) -MMD -MP

#      COMMANDS     #
RM		= rm -rf
DIR_DUP		= mkdir -p $(@D)
MAKEFLAGS	+= --no-print-directory

#       RULES       #
all: $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INC) Makefile
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info Created $@)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	$(info Created $@)

-include $(DEPS)

clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean flcean re
.SILENT:
