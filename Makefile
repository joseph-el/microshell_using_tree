# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/22 11:22:58 by yoel-idr          #+#    #+#              #
#    Updated: 2023/03/22 11:56:52 by yoel-idr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME           := microshell

SRCS_STACK 	   := stack_executor.c stack_utils.c
SRCS_PARSER    := parser.c microshell.c
SRCS_TRAVERSAL := traversal_executor.c

all	: $(NAME)
		@echo "microshell [OK]"

$(NAME) : $(SRCS_PARSER) $(SRCS_STACK) $(SRCS_TRAVERSAL)
			@cc -Wall -Wextra -Werror $^ -o $@
clean :
		@echo "clean [OK]"
		@rm -rf $(NAME)