/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:27:20 by cocheong          #+#    #+#             */
/*   Updated: 2024/01/15 16:27:20 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define QUOTES "\"\'"
# define OPERATOR "|><"
# include "minishell.h"

typedef enum s_token
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}	t_token;

typedef struct s_lexer
{
	char				*str;
	t_token				token;
	int					i;
	struct s_lexer		*next;
	struct s_lexer		*prev;
}	t_lexer;

typedef struct s_parser_tools
{
	t_lexer			*lexer_list;
	t_lexer			*redirections;
	int				num_redirections;
	struct s_tools	*tools;
}	t_parser_tools;

typedef struct s_tools
{
	char					*args;
	char					**path;
	char					**envp;
	struct s_simple_cmds	*simple_cmds;
	t_lexer					*lexer_list;
	char					*pwd;
	char					*oldpwd;
	int						pipes;
	int						*pid;
	bool					heredoc;
	bool					reset;
}	t_tools;

typedef struct s_simple_cmds
{
	char					**str;
	int						(*builtin)(t_tools *, struct s_simple_cmds *);
	int						num_redirections;
	char					*hd_file_name;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

#endif