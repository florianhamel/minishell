/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 09:52:23 by fhamel            #+#    #+#             */
/*   Updated: 2021/05/13 12:32:45 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*
**	input: echo par1 par2 ... parn
**	output: par1 par2 ... parn
**	
**	input: echo "blabla
**	> blabla"yoyo
**	output : blablablabla
**	com: the yoyo is not taken into account
**
**	input: echo $nonexistentvar | cat -e
**	output: $
**	com: if the var doesn't exist, it echoes nothing but don't error
*/

int	ft_echo(char **params, char **env)
{
	char	**tab;
	execve();
}