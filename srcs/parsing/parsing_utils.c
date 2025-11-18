#include "../../includes/push_swap.h"

size_t	split_len(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static bool	no_duplicates(t_stack *s)
{
	int	i;
	int	j;

	i = 0;
	while (i < s->top)
	{
		j = i + 1;
		while (j <= s->top)
		{
			if (s->values[i] == s->values[j])
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

static void	fill_stack(char **str, t_stack *s, size_t len)
{
	int	i;

	i = (int)len - 1;
	while (i >= 0)
	{
		push_element(s, ft_atoi(str[i]));
		i--;
	}
}

bool	is_valid(char **str, t_stack *s, size_t len)
{
	if (!validate_all_strings(str, len))
		return (false);
	fill_stack(str, s, len);
	return (no_duplicates(s));
}
