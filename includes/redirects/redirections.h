/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_outputs.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 23:39:54 by zhlim             #+#    #+#             */
/*   Updated: 2024/03/27 17:52:37 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

int		redirect_outputs(int *save, char *file_name, int toAppend);
void	restore_outputs(int *save, int file);
int		redirect_inputs(int *save, char *file_name);
void	restore_inputs(int *save, int file);

#endif