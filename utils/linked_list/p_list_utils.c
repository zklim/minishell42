/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_list_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:54:47 by cocheong          #+#    #+#             */
/*   Updated: 2024/02/16 15:54:47 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	p_lstclear(t_statement **head)
{
	t_statement	*temp;
	t_statement	*next_node;

	if (!head)
		return ;
	temp = *head;
	while (temp != NULL)
	{
		next_node = temp->next;
		free_matrix(temp->argv);
		free(temp);
		temp = next_node;
	}
	*head = NULL;
}

size_t	p_lstsize(t_statement *head)
{
	t_statement	*temp;
	size_t		size;

	temp = head;
	size = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		size += 1;
	}
	return (size);
}

t_statement	*p_new_node(int argc)
{
	t_statement	*new_node;

	new_node = malloc(sizeof(t_statement));
	new_node->argc = argc;
	new_node->argv = malloc((argc + 1) * sizeof(char *));
	new_node->operator = NONE;
	new_node->next = NULL;
	return (new_node);
}