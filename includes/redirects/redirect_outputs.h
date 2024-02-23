/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_outputs.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 23:39:54 by zhlim             #+#    #+#             */
/*   Updated: 2024/02/24 00:04:59 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_INPUTS_H
# define REDIRECT_INPUTS_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

int		redirect_outputs(int *save, char *file_name, int toAppend);
void	restore_outputs(int *save, int file);

#endif