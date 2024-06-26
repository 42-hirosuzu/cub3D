/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                               :+:      :+:    :+:s  */
/*                                                    +:+ +:+         +:+     */
/*   By: hrinka <hrinka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:26:18 by hrinka            #+#    #+#             */
/*   Updated: 2024/05/27 19:26:35 by hrinka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

size_t	cnt_chr_in_str(const char c, const char *str)
{
	size_t	i;
	size_t	cnt;

	if (!str)
		return (0);
	i = 0;
	cnt = 0;
	while (str[i])
		if (str[i++] == c)
			cnt++;
	return (cnt);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (dstsize)
	{
		while (src[i] && i + 1 < dstsize)
			dst[i++] = src[j++];
		dst[i] = '\0';
	}
	return (ft_strlen_gnl(src));
}

void	*ft_free(char **alloc1, char **alloc2)
{
	if (alloc1)
	{
		free(*alloc1);
		*alloc1 = NULL;
	}
	if (alloc2)
	{
		free(*alloc2);
		*alloc2 = NULL;
	}
	return (NULL);
}

char	*strjoin_and_free_dst(char *dst, char *src)
{
	size_t	dstlen;
	size_t	srclen;
	char	*joined_str;

	if (!dst)
	{
		dst = (char *)malloc(sizeof(char) * 1);
		if (!dst)
			return (NULL);
		dst[0] = '\0';
	}
	dstlen = ft_strlen_gnl(dst);
	srclen = ft_strlen_gnl(src);
	joined_str = (char *)malloc(sizeof(char) * (dstlen + srclen + 1));
	if (!joined_str)
		return (ft_free(&dst, NULL));
	ft_strlcpy(joined_str, dst, dstlen + 1);
	ft_strlcpy(&joined_str[dstlen], src, srclen + 1);
	ft_free(&dst, NULL);
	return (joined_str);
}
