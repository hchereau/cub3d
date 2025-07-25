/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:28:38 by hchereau          #+#    #+#             */
/*   Updated: 2024/10/02 17:24:53 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_word_len(const char *s, char c)
{
	size_t	word_len;

	word_len = 0;
	while (s[word_len] != '\0' && s[word_len] != c)
		++word_len;
	return (word_len);
}

static char	*get_next_words(const char **s, char c)
{
	size_t	word_len;
	char	*word;

	while (**s == c)
		++(*s);
	word_len = get_word_len(*s, c);
	word = (char *)malloc((word_len + 1) * sizeof(char));
	if (word != NULL)
		ft_strlcpy(word, *s, word_len + 1);
	*s += word_len;
	return (word);
}

size_t	count_words(const char *s, char c)
{
	size_t	size_split;
	bool	is_word;

	size_split = 0;
	is_word = false;
	while (*s != '\0')
	{
		if (*s == c)
		{
			if (is_word == true)
			{
				++size_split;
				is_word = false;
			}
		}
		else
			is_word = true;
		++s;
	}
	return (size_split + (is_word == true));
}

void	free_strs(char **strs)
{
	size_t	incre;

	if (strs == NULL)
		return ;
	incre = 0;
	while (strs[incre] != NULL)
	{
		free(strs[incre]);
		++incre;
	}
	free(strs);
}

char	**ft_split(const char *s, char c)
{
	size_t	size_split;
	size_t	i;
	char	**split;

	if (s == NULL)
		return (NULL);
	size_split = count_words(s, c);
	split = (char **)malloc((size_split + 1) * sizeof(char *));
	if (split != NULL)
	{
		i = 0;
		split[size_split] = NULL;
		while (i < size_split)
		{
			split[i] = get_next_words(&s, c);
			if (split[i] == NULL)
			{
				free_strs(split);
				split = NULL;
				break ;
			}
			++i;
		}
	}
	return (split);
}
