# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/12 21:38:43 by zhlim             #+#    #+#              #
#    Updated: 2024/02/21 03:36:36 by cocheong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS				= $(addprefix $(SRCSDIR)/, \
					$(addsuffix .c, \
					main \
						config_signal setup_shell \
						$(addprefix executions/, \
						execve binaries builtin executable pipes redirects\
							$(addprefix builtins/, \
							echo pwd cd export export2 env unset)) \
						$(addprefix utils/, \
						build_shell destroy is_all_digit_or_signals other_tools panic valid_input \
							$(addprefix linked_list/, \
							init_envp_lst p_list_utils v_list_utils v_list_utils2)) \
						$(addprefix expander/, \
						expander_utils expander) \
						$(addprefix parser/, \
						invalid_syntax parser parser_utils remove_quotes)))))


OBJS				= $(patsubst $(SRCSDIR)/%.c, $(OBJSDIR)/%.o, $(SRCS))

SRCSDIR				= src
OBJSDIR				= build
OBJSUBDIR			= $(addprefix $(OBJSDIR)/, executions)

CC					= gcc
CFLAGS				= -Wall -Werror -Wextra -g

RM					= rm -rf

INCLUDES			= -Iincludes -Ilibft -Ilibft/ft_printf/include/ -Ilibft/get_next_line

NAME				= minishell

LIBFT				= libft/libft.a
LIBFTFLAGS			= -Llibft/ -lft
LIBPRINTF			= libft/ft_printf/libftprintf.a
LIBPRINTFFLAGS		= -Llibft/ft_printf -lftprintf

$(OBJSDIR)/%.o:		$(SRCSDIR)/%.c | $(OBJSDIR)
					mkdir -p $(@D)
					$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all:				$(NAME) 

$(NAME):			$(OBJS)
					$(CC) $(CFLAGS) $^ $(LIBFTFLAGS) $(LIBPRINTFFLAGS) -o $@

$(OBJS):			$(LIBFT) $(LIBPRINTF)

$(OBJSDIR):		
					mkdir -p $(OBJSDIR)

$(LIBFT):		
					make bonus -C libft/

$(LIBPRINTF):	
					make -C libft/ft_printf/

clean:		
					$(RM) $(OBJSDIR)
					make clean -C libft/
					make clean -C libft/ft_printf/
				
fclean:				clean
					$(RM) $(NAME)
					make fclean -C libft/
					make fclean -C libft/ft_printf/

re:					fclean all

.PHONY:				all clean fclean re bonus