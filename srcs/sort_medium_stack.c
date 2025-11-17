#include "../includes/push_swap.h"

void smart_rotate_to_top(t_stack *s, int pos, t_algo *algo, char c)
{
    int cost_fwd = s->top - pos;
    int cost_bwd = pos + 1;
    
    if (pos == s->top)
        return;
    if (cost_fwd <= cost_bwd)
        while (cost_fwd-- > 0)
            (c == 'a') ? ra(algo) : rb(algo);
    else
        while (cost_bwd-- > 0)
            (c == 'a') ? rra(algo) : rrb(algo);
}

static int get_chunk_size(int size)
{
    if (size <= 16)
        return (size);
    if (size <= 100)
        return (17);
    if (size <= 500)
        return (37);
    return (50);
}

void sort_medium_stack(t_algo *algo)
{
    int size = algo->a->top + 1;
    int chunk_sz = get_chunk_size(size);
    int pushed = 0;
    int chunk_max = chunk_sz;
    int i;
    
    while (algo->a->top > 2 && pushed < size - 3)
    {
        i = algo->a->top;
        int found = 0;
        while (i >= 0)
        {
            if (algo->a->indices[i] < chunk_max)
            {
                smart_rotate_to_top(algo->a, i, algo, 'a');
                pb(algo);
                pushed++;
                found = 1;
                break;
            }
            i--;
        }
        if (!found)
            chunk_max += chunk_sz;
    }
    
    if (algo->a->top == 2)
        sort_three(algo);
    
    while (algo->b->top >= 0)
    {
        int max_p = 0, max_v = algo->b->indices[0];
        i = 1;
        while (i <= algo->b->top)
        {
            if (algo->b->indices[i] > max_v)
            {
                max_v = algo->b->indices[i];
                max_p = i;
            }
            i++;
        }
        smart_rotate_to_top(algo->b, max_p, algo, 'b');
        pa(algo);
    }
    
    final_rotate_to_min(algo);
}
