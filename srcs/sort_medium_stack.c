#include "../includes/push_swap.h"

void smart_rotate_to_top(t_stack *s, int pos, t_algo *algo, char c)
{
    int cf = s->top - pos;
    int cb = pos + 1;
    
    if (pos == s->top)
        return;
    if (cf <= cb)
        while (cf-- > 0)
            (c == 'a') ? ra(algo) : rb(algo);
    else
        while (cb-- > 0)
            (c == 'a') ? rra(algo) : rrb(algo);
}

static int get_chunks(int size)
{
    if (size <= 100)
        return (7);
    if (size <= 500)
        return (15);
    return (20);
}

void sort_medium_stack(t_algo *algo)
{
    int size = algo->a->top + 1;
    int chunks = get_chunks(size);
    int chunk_sz = size / chunks;
    int target = 0;
    int i, pos, best_cost, cost_top, cost_bot;
    int max_to_keep = size - 3;
    
    while (algo->b->top < size - 4)
    {
        best_cost = INT_MAX;
        pos = -1;
        i = 0;
        while (i <= algo->a->top)
        {
            if (algo->a->indices[i] < max_to_keep && 
                algo->a->indices[i] >= target && 
                algo->a->indices[i] < target + chunk_sz)
            {
                cost_top = algo->a->top - i;
                cost_bot = i + 1;
                if (cost_top < best_cost || cost_bot < best_cost)
                {
                    best_cost = (cost_top < cost_bot) ? cost_top : cost_bot;
                    pos = i;
                }
            }
            i++;
        }
        if (pos == -1)
        {
            target += chunk_sz;
            if (target >= max_to_keep)
                break;
            continue;
        }
        smart_rotate_to_top(algo->a, pos, algo, 'a');
        pb(algo);
        if (algo->b->top > 0 && algo->b->indices[algo->b->top] < target + chunk_sz / 2)
            rb(algo);
    }
    
    if (algo->a->top == 2)
        sort_three(algo);
    else if (algo->a->top > 2)
    {
        while (algo->a->top > 2)
            pb(algo);
        if (algo->a->top == 2)
            sort_three(algo);
    }
    
    while (algo->b->top >= 0)
    {
        int mx_p = 0, mx_v = algo->b->indices[0];
        i = 1;
        while (i <= algo->b->top)
        {
            if (algo->b->indices[i] > mx_v)
            {
                mx_v = algo->b->indices[i];
                mx_p = i;
            }
            i++;
        }
        smart_rotate_to_top(algo->b, mx_p, algo, 'b');
        pa(algo);
    }
    
    final_rotate_to_min(algo);
}
