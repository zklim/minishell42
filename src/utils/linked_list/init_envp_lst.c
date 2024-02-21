/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:47:24 by cocheong          #+#    #+#             */
/*   Updated: 2024/02/16 16:47:24 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	init_oldpwd(t_vlst **head)
{
	char	*temp;

	unset_var("OLDPWD", head);
	temp = ft_strjoin("OLDPWD=", getenv("HOME"));
	save_user_vars(temp, head, true);
	free(temp);
}

t_vlst	*init_envp_lst(char **envp)
{
	t_vlst	*head;
	t_vlst	*temp;
	char	**line;
	size_t	i;

	line = split_envp(envp[0]);
	head = v_new_node(line[0], line[1], true);
	free(line);
	i = 1;
	temp = head;
	while (envp[i])
	{
		line = split_envp(envp[i]);
		temp->next = v_new_node(line[0], line[1], true);
		free(line);
		temp = temp->next;
		i += 1;
	}
	init_oldpwd(&head);
	return (head);
}
