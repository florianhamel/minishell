/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_tmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:03:52 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/11 17:11:55 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_existence(t_data *data, char *arg)
{
	t_var	*current;
	char	*name;
	int		i;

	name = NULL;
	i = 0;
	while (arg[i] && arg[i] != '=')
		name = add_char(data, name, arg[i++]);
	current = data->var_lst;
	while (current)
	{
		if (!ft_strncmp(name, current->name, ft_strlen(name)))
		{
			free_null((void **)&name);
			return (1);
		}
	}
	free_null((void **)&name);
}

void	create_var(t_data *data, char *arg)
{
	t_var	*current;
	t_var	*var_def;
	int		i;

	var_def = malloc(sizeof(t_var));
	if (!var_def)
		exit_custom(data, NULL, AUTO);
	var_def->prev = NULL;
	var_def->next = NULL;
	var_def->name = NULL;
	var_def->val = NULL;
	i = 0;
	while (arg[i] && arg[i] != '=')
		var_def->name = add_char(data, var_def->name, arg[i++]);
	if (arg[i] == '=')
		i++;
	while (arg[i])
		var_def->val = add_char(data, var_def->val, arg[i++]);
	current = data->var_lst;
	while (current->next)
		current = current->next;
	var_def->prev = current;
	current->next = var_def;
	export_var(data, var_def->name);
}

void	export_var_def(t_data *data, char *arg)
{
	t_var	*current;
	t_var	*var_def;
	int		i;

	if (check_existence(data, arg))
		modify_var(data, arg);
	else
		create_var(data, arg);
}

void	add_var_env(t_data *data, char *var)
{
	char	**new_env;
	int		i;

	i = 0;
	while (data->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		exit_custom(data, NULL, AUTO);
	i = 0;
	while (data->env[i])
	{
		new_env[i] = ft_strdup(data->env[i]);
		i++;
	}
	new_env[i] = var;
	new_env[i + 1] = NULL;
	ft_free_arr(data->env);
	data->env = new_env;
}

void	export_var(t_data *data, char *name)
{
	char	*var;
	t_var	*current;

	var = NULL;
	current = data->var_lst;
	while (current)
	{
		if (!ft_strncmp(name, current->name, ft_strlen(name)))
		{
			var = concat_str(data, ft_strdup(current->name), ft_strdup("="));
			var = concat_str(data, var, ft_strdup(current->val));
		}
		current = current->next;
	}
	add_var_env(data, var);
}

void	export_var(t_data *data, char *arg)
{
	char	*name;
	int		i;

	name = NULL;
	i = 0;
	while (arg[i] && arg[i] != '=')
		name = add_char(data, name, arg[i++]);
}

int	ft_export(t_data *data, char **args)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	if (!args[1])
		only_export(data);
	else if (is_option(args[1]))
		error_option(args, "export", &status);
	i = 1;
	while (args[i])
	{
		if (is_valid_var(args[i]))
			export_var(data, args[i]);
		else
			error_identifier(args, &status);
		i++;
	}
	ft_free_arr(args);
	return (status);
}
