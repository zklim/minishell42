/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:15:49 by zhlim             #+#    #+#             */
/*   Updated: 2024/02/23 23:58:45 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <termios.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>

extern int	sig_int;

void		register_signals(void);

#endif