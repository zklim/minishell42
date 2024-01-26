/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:33:36 by zhlim             #+#    #+#             */
/*   Updated: 2024/01/26 17:47:19 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT2_H
# define EXPORT2_H

# include "../../../libft/libft.h"
# include "../../utils/build_shell.h"
# include "./env.h"

void	add_to_env(t_shell *shell, char *addition);

#endif