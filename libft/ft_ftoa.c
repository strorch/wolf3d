/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 14:28:34 by mstorcha          #+#    #+#             */
/*   Updated: 2018/06/02 14:28:36 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char			*ft_strjoinfree(char *s1, char *s2)
// {
// 	char		*new;
// 	size_t		len1;
// 	size_t		len2;

// 	if (s1 == NULL || s2 == NULL)
// 		return (NULL);
// 	len1 = ft_strlen(s1);
// 	len2 = ft_strlen(s2);
// 	if (!(new = ft_strnew(len1 + len2)))
// 		return (NULL);
// 	ft_strcat(new, s1);
// 	ft_strcat(new, s2);
// 	ft_strdel(&s1);
// 	ft_strdel(&s2);
// 	return (new);
// }

// char			*ft_strjoinlit(char *s1, const char *s2)
// {
// 	char		*new;
// 	size_t		len1;
// 	size_t		len2;

// 	if (s1 == NULL || s2 == NULL)
// 		return (NULL);
// 	len1 = ft_strlen(s1);
// 	len2 = ft_strlen(s2);
// 	if (!(new = ft_strnew(len1 + len2)))
// 		return (NULL);
// 	ft_strcat(new, s1);
// 	ft_strcat(new, s2);
// 	ft_strdel(&s1);
// 	return (new);
// }
// char			*ft_ftoa(float num)
// {
// 	int			whole;
// 	int			fract;
// 	char		*str;

// 	str = ft_strnew(1);
// 	whole = (int)num;
// 	fract = (num - whole) * 100;
// 	if (fract < 0 && whole >= 0)
// 		str = ft_strcpy(str, "-");
// 	if (fract < 0)
// 		fract *= -1;
// 	str = ft_strjoinfree(str, ft_itoa(whole));
// 	str = ft_strjoinlit(str, ".");
// 	str = ft_strjoinfree(str, ft_itoa(fract));
// 	return (str);
// }

char	*ft_dtoa(double d, int p, char *delimeter)
{
	char *str1;
	char *str2;
	char *res;
	char *buf;
	char sign[2];

	sign[0] = ' ';
	sign[1] = '\0';
	if (d < 0)
	{
		sign[0] = '-';
		d = -d;
	}
	str1 = ft_itoa((int)d);
	buf = ft_strjoin(str1, delimeter);
	str2 = ft_itoa((int)((d - (int)d) * 10 * p));
	res = ft_strjoin(buf, str2);
	free(str1);
	str1 = res;
	res = ft_strjoin(sign, res);
	ft_strdel(&str1);
	ft_strdel(&buf);
	ft_strdel(&str2);
	return (res);
}