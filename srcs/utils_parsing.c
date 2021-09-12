/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:03:58 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/07 13:20:15 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(t_data *data, char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
	{
		free_null((void **)&data);
		exit_strerror();
	}
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

t_var	*init_var_lst(t_data *data)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
	{
		ft_free_arr(data->env);
		exit_strerror();
	}
	var->prev = NULL;
	var->next = NULL;
	var->name = malloc(2);
	if (!var->name)
	{
		ft_free_arr(data->env);
		free_null((void **)&data);
		exit_strerror();
	}
	var->name[0] = '?';
	var->name[1] = '\0';
	var->val = ft_itoa(0);
	return (var);
}

ssize_t	ft_write(int fd, const void *buf, size_t nbyte)
{
	ssize_t	ret;

	ret = 0;
	if (!buf)
		return (ret);
	ret = write(fd, buf, nbyte);
	if (ret == ERROR)
		exit_strerror();
	return (ret);
}

void	ws_fd(size_t nb, int fd)
{
	size_t	i;

	i = 0;
	while (i < nb)
	{
		ft_putchar_fd(' ', fd);
		i++;
	}
}

char	*new_alloc(char *str, size_t size, size_t pos)
{
	char	*new;
	size_t	i;

	i = 0;
	new = malloc(size + 1);
	if (!new)
		return (NULL);
	new = (char *)ft_memcpy(new, str, pos);
	new[size] = '\0';
	free_null((void **)&str);
	return (new);
}
