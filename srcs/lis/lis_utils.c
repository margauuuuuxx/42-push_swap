#include "../../includes/push_swap.h"

t_lis	*init_lis(int size)
{
	int		i;
	t_lis	*lis;

	i = 0;
	lis = malloc(sizeof(t_lis));
	lis->lens = malloc(size * sizeof(int));
	lis->prev = malloc(size * sizeof(int));
	lis->tail = malloc(size * sizeof(int));
	if (!lis || !lis->lens || !lis->prev || !lis->tail)
		return (NULL);
	while (i < size)
	{
		lis->lens[i] = 0;
		i++;
	}
	lis->max_len = 0;
	return (lis);
}

void	get_non_lis_range(t_stack *a, int *min_idx, int *max_idx)
{
	int	i;
	int	first_found;

	*min_idx = a->capacity;
	*max_idx = -1;
	first_found = 0;
	i = 0;
	while (i <= a->top)
	{
		if (!a->in_lis[i])
		{
			if (a->indices[i] < *min_idx)
				*min_idx = a->indices[i];
			if (a->indices[i] > *max_idx)
				*max_idx = a->indices[i];
			first_found = 1;
		}
		i++;
	}
	if (!first_found)
	{
		*min_idx = 0;
		*max_idx = 0;
	}
}

void	free_lis(t_lis *lis)
{
	free(lis->lens);
	free(lis->prev);
	free(lis->tail);
	free(lis);
}

void	count_non_lis(t_stack *a)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (i <= a->top)
	{
		if (!a->in_lis[i])
			count++;
		i++;
	}
	a->not_in_lis = count;
}

int	lis_binary_search(int *tail, int len, int target)
{
	int	left;
	int	right;
	int	mid;

	left = 0;
	right = len;
	while (left < right)
	{
		mid = (left + right) / 2;
		if (tail[mid] < target)
			left = mid + 1;
		else
			right = mid;
	}
	return (left);
}
