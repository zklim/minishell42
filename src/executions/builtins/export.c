/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:09:07 by zhlim             #+#    #+#             */
/*   Updated: 2024/02/19 02:18:32 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executions/builtins/export.h"

static char	**create_subarrays(char **arr, int l, int r)
{
	int		i;
	char	**subarray;

	i = 0;
	subarray = (char **)malloc(sizeof(char *) * (r + 1));
	if (!subarray)
		return (NULL);
	while (i < r)
	{
		subarray[i] = arr[l + i];
		i++;
	}
	subarray[i] = NULL;
	return (subarray);
}

static void	merge(char **arr, int l, int m, int r)
{
	int		i;
	int		j;
	int		k;
	char	**left;
	char	**right;

	i = 0;
	j = 0;
	k = l;
	left = create_subarrays(arr, l, m - l + 1);
	right = create_subarrays(arr, m + 1, r - m);
	while (i < m - l + 1 && j < r - m)
	{
		if (right[j] == NULL || *left[i] <= *right[j])
			arr[k++] = left[i++];
		else
			arr[k++] = right[j++];
	}
	while (i < m - l + 1)
		arr[k++] = left[i++];
	while (j < r - m)
		arr[k++] = right[j++];
	free(left);
	free(right);
}

static void	merge_sort(char **arr, int l, int r)
{
	int	m;

	if (l < r)
	{
		m = l + (r - l) / 2;
		merge_sort(arr, l, m);
		merge_sort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}

static void	sort_and_print(char **env, int size)
{
	merge_sort(env, 0, size);
	print_export(env);
}

void	ft_export(t_data *shell, char *addition)
{
	if (addition == NULL)
		sort_and_print(shell->envp, ft_arrlen(shell->envp));
	else
		add_to_env(shell, addition);
}
