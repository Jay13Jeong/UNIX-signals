/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjeong <jjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 03:42:34 by jjeong            #+#    #+#             */
/*   Updated: 2021/12/06 20:09:20 by jjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && *s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			break ;
		n--;
		s1++;
		s2++;
	}
	return ((*(unsigned char *)s1 - *(unsigned char *)s2) * (n > 0));
}
