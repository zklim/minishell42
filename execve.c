/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:04:17 by zhlim             #+#    #+#             */
/*   Updated: 2024/01/12 20:21:16 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{	
	char *const	path = "/bin/ls";
	char *const	args[] = {path ,"-l", NULL};
	char *const	env[] = {NULL};

	if (execve(path, args, env) == -1)
	{
		perror(strerror(errno));
		exit(errno);
	}
	return 0;
}