# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 18:33:10 by eguelin           #+#    #+#              #
#    Updated: 2024/01/21 19:07:46 by eguelin          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re
.SILENT:

# **************************************************************************** #
#                                   Variable                                   #
# **************************************************************************** #

NAME	= PmergeMe
OBJ_DIR	= .obj/
SRC_DIR	= src/
CLS_DIR	= class/
CC		= c++
CFLAGS	= -Wall -Werror -Wextra -std=c++98
INC		= -I $(CLS_DIR)
RM		= rm -fr

# **************************************************************************** #
#                                    Colors                                    #
# **************************************************************************** #

BLACK	= \033[30m
RED		= \033[31m
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m
PURPLE	= \033[35m
CYAN	= \033[36m
WHITE	= \033[37m
DEFAULT	= \033[0m

# **************************************************************************** #
#                                    Message                                   #
# **************************************************************************** #

COMP_MSG		= "$(GREEN)Compilation $(NAME) $(DEFAULT)done on $(YELLOW)$(shell date +'%Y-%m-%d %H:%M:%S')$(DEFAULT)"
CLEAN_MSG		= "$(RED)Cleaning $(NAME) $(DEFAULT)done on $(YELLOW)$(shell date +'%Y-%m-%d %H:%M:%S')$(DEFAULT)"
FULL_CLEAN_MSG	= "$(PURPLE)Full cleaning $(NAME) $(DEFAULT)done on $(YELLOW)$(shell date +'%Y-%m-%d %H:%M:%S')$(DEFAULT)"

# **************************************************************************** #
#                                    Sources                                   #
# **************************************************************************** #

CLS_FILES	= PmergeMe.cpp

ALL_FILES	= $(addprefix $(CLS_DIR), $(CLS_FILES))

SRC_FILES	= main.cpp

ALL_FILES	+= $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_FILES	= $(addprefix $(OBJ_DIR), $(ALL_FILES:.cpp=.o))

DEP_FILES	= $(OBJ_FILES:.o=.d)

ALL_OBJ_DIR	= $(sort $(dir $(OBJ_FILES)))

# **************************************************************************** #
#                                     Rules                                    #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(INC) $(OBJ_FILES) -o $(NAME)
	echo $(COMP_MSG)

$(OBJ_DIR)%.o: %.cpp | $(ALL_OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)
	echo $(CLEAN_MSG)

fclean: clean
	$(RM) $(NAME)
	echo $(FULL_CLEAN_MSG)

re: fclean all

$(ALL_OBJ_DIR):
	mkdir -p $@

-include $(DEP_FILES)
