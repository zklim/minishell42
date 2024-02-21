/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:12:08 by cocheong          #+#    #+#             */
/*   Updated: 2024/02/16 15:12:08 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	v_lstclear(t_vlst **head)
{
	t_vlst	*temp;
	t_vlst	*next_node;

	if (!head)
		return ;
	temp = *head;
	while (temp != NULL)
	{
		next_node = temp->next;
		free(temp->var_name);
		free(temp->var_value);
		free(temp);
		temp = next_node;
	}
	*head = NULL;
}

void	destroy(t_data *data)
{
	rl_clear_history();
	if (data->envp_vlst)
		v_lstclear(&data->envp_vlst);
	if (data->head)
		p_lstclear(data->head);
}
