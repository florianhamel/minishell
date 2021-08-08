/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_navigation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:51:47 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/08 11:48:00 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// get_history une seule fois
// quand UP_KEY est pressed:
// - tout est dépendant de la liste récupérée
// - si un modification avait été apportée à la ligne, celle-ci est sauvegardée
// - si l'élément en cours n'appartenait pas à la liste, ce dernier y est ajouté

// quand NL_KEY est pressed:
// ajoute la commande entrée dans le fichier
// ajoute un élément à la liste contenant la commande

void	go_up(t_read *data)
{
	if (data->current->next)
	{
		if (data->str)
			replace_alloc(data->str, data->current);
		wipe_and_replace(data, data->current->next);
		data->current = data->current->next;
	}
	else
	{
		cursor_right(1);
		cursor_left(1);
	}
	return ;
}

void	go_down(t_read *data)
{
	if (data->current->prev)
	{
		if (data->str)
			replace_alloc(data->str, data->current);
		wipe_and_replace(data, data->current->prev);
		data->current = data->current->prev;
	}
	else
	{
		cursor_right(1);
		cursor_left(1);
	}
}

void	history_navigation(t_read *data)
{
	if (data->c == UP_KEY)
		go_up(data);
	else if (data->c == DOWN_KEY)
		go_down(data);
}
