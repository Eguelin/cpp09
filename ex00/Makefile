# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 18:33:10 by eguelin           #+#    #+#              #
#    Updated: 2023/12/13 18:36:59 by eguelin          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re
.SILENT:

# **************************************************************************** #
#                                   Variable                                   #
# **************************************************************************** #

NAME	= btc
OBJ_DIR	= .obj/
SRC_DIR	= src/
INC_DIR	= include/
CC		= c++
CFLAGS	= -Wall -Werror -Wextra -std=c++98
INC		= -I $(INC_DIR)
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

SRC_FILES	= main.cpp

UTILS_DIR	= utils/

UTILS_FILES	= dateToInt.cpp \
			  exeInput.cpp \
			  getData.cpp \
			  trim.cpp

SRC_FILES	+= $(addprefix $(UTILS_DIR), $(UTILS_FILES))

OBJ_FILES	= $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o))

DEP_FILES	= $(OBJ_FILES:.o=.d)

# **************************************************************************** #
#                                     Rules                                    #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(INC) $(OBJ_FILES) -o $(NAME)
	echo $(COMP_MSG)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)
	echo $(CLEAN_MSG)

fclean: clean
	$(RM) $(NAME)
	echo $(FULL_CLEAN_MSG)

re: fclean all

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)$(UTILS_DIR)

-include $(DEP_FILES)
