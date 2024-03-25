/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:15:21 by zhlim             #+#    #+#             */
/*   Updated: 2024/03/26 00:36:38 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/signals/signals.h"

void	signal_handler_int(int sig)
{
	(void)sig;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void	signal_handler_quit(int sig)
{
	(void)sig;
	return ;
}

int		term_echo_off(void)
{
    struct termios	term;

    if (tcgetattr(STDIN_FILENO, &term) == -1) 
		return 1;
    term.c_lflag &= ~ECHOCTL;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1) 
        return 1;
	return 0;
}

void	register_signals(void)
{
	if (term_echo_off() == 1)
		perror("failed to config terminal");
	signal(SIGINT, signal_handler_int);
	signal(SIGQUIT, signal_handler_quit);
}