/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_c_to_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgontier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 23:17:32 by tgontier          #+#    #+#             */
/*   Updated: 2019/11/22 15:35:02 by tgontier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_c_to_str(char c)
{
	char	*s;

	s = ft_calloc(2, sizeof(char));
	s[0] = c;
	s[1] = '\0';
	return (s);
}
