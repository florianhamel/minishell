/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 10:45:27 by fhamel            #+#    #+#             */
/*   Updated: 2019/10/22 15:37:27 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		if (!(substr = (char *)malloc(sizeof(char))))
			return (NULL);
		*substr = '\0';
		return (substr);
	}
	if (!(substr = ft_strdup(&s[start])))
		return (NULL);
	if (len < ft_strlen(substr))
		substr[len] = '\0';
	return (substr);
}
