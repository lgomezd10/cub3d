#include "cub3d.h"

static char	*ft_subchr(char const *s, char *set)
{
	int		i;
	char	*str;

	i = 0;
	while (!ft_strrchr(set, s[i]) && s[i] != '\0')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str)
		ft_strlcpy(str, s, i + 1);
	return (str);
}

static size_t	ft_count_fragments(char const *s, char *set)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		while (s[i] && ft_strrchr(set, s[i]))
			i++;
		if (s[i] && !ft_strrchr(set, s[i]))
		{
			count++;
			i++;
			while (!ft_strrchr(set, s[i]) && s[i])
				i++;
		}
	}
	return (count);
}

char	**ft_split_set(char const *s, char *set)
{
	size_t	i;
	size_t	count;
	char	**split;

	i = 0;
	count = ft_count_fragments(s, set);
	split = (char **)malloc(sizeof(char *) * (count + 1));
	if (split)
	{
		split[count] = 0;
		i = 0;
		while (i < count)
		{
			while (ft_strrchr(set, *s))
				s++;
			split[i++] = ft_subchr(s, set);
			while (!ft_strrchr(set, *s))
				s++;
		}
	}
	return (split);
}

int ft_array_len(char **a)
{
	int count;
	while (a[count])
		count++;
	return (count);
}

char *ft_delete_set(char **str1, char *set)
{
	char *copy;
	char *str;
	int len;
	int i;
	int j;

	str = *str1;
	len = ft_strlen(str);
	copy = ft_calloc(sizeof(char), len + 1);
	copy[len] = '\0';
	if (copy)
	{
		i = 0;
		j = 0;
		while (i < len && str[i])
		{
			if (!ft_strrchr(set, str[i]))
				copy[j++] = str[i];
			i++;
		}
		free(*str1);
		*str1 = ft_strdup(copy);
		free(copy);
	}
	return (str);
}

int ft_is_nbr(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
