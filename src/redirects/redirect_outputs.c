/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_outputs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 23:39:39 by zhlim             #+#    #+#             */
/*   Updated: 2024/02/24 00:15:18 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/redirects/redirect_outputs.h"

int		redirect_outputs(int *save, char *file_name, int toAppend)
{
	int options;
	int file;

	if (toAppend)
		options = O_RDWR | O_CREAT | O_APPEND;
	else
		options = O_RDWR | O_CREAT | O_TRUNC;
	*save = dup(STDOUT_FILENO);
	file = open(file_name, options, 0644);
	if (file < 0)
	{
		perror("failed to open file");
		return file;
	}
	dup2(file, STDOUT_FILENO);
	return (file);
}

void	restore_outputs(int *save, int file)
{
	close(file);
	dup2(*save, STDOUT_FILENO);
}
