/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_normalization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:10:00 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/03 11:10:00 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include "test_framework.h"

TEST_INIT();

void test_basic_normalization(void)
{
    TEST_START("Basic Normalization");
    
    t_stack a;
    init_stack(&a, 5);
    
    push(&a, 42);
    push(&a, -7);
    push(&a, 100);
    push(&a, 3);
    push(&a, 0);
    
    compress(&a);
    
    int expected[] = {3, 0, 4, 2, 1};
    
    ASSERT_ARRAY_EQ(a.indices, expected, 5, "Values normalized correctly");
    ASSERT_EQ(a.indices[0], 3, "42 maps to index 3");
    ASSERT_EQ(a.indices[1], 0, "-7 maps to index 0 (smallest)");
    ASSERT_EQ(a.indices[4], 1, "0 maps to index 1");
    
    free(a.values);
    free(a.indices);
}

void test_already_sorted(void)
{
    TEST_START("Already Sorted Array");
    
    t_stack a;
    init_stack(&a, 3);
    
    push(&a, 1);
    push(&a, 2);
    push(&a, 3);
    
    compress(&a);
    
    int expected[] = {0, 1, 2};
    ASSERT_ARRAY_EQ(a.indices, expected, 3, "Already sorted normalizes correctly");
    
    free(a.values);
    free(a.indices);
}

void test_reverse_sorted(void)
{
    TEST_START("Reverse Sorted Array");
    
    t_stack a;
    init_stack(&a, 3);
    
    push(&a, 3);
    push(&a, 2);
    push(&a, 1);
    
    compress(&a);
    
    int expected[] = {2, 1, 0};
    ASSERT_ARRAY_EQ(a.indices, expected, 3, "Reverse sorted normalizes correctly");
    
    free(a.values);
    free(a.indices);
}

void test_edge_cases(void)
{
    TEST_START("Edge Cases");
    
    t_stack a;
    
    init_stack(&a, 1);
    push(&a, 42);
    compress(&a);
    ASSERT_EQ(a.indices[0], 0, "Single element maps to 0");
    free(a.values);
    free(a.indices);
    
    init_stack(&a, 3);
    push(&a, -2147483648);
    push(&a, 0);
    push(&a, 2147483647);
    compress(&a);
    ASSERT_TRUE(a.indices[0] == 0, "INT_MIN maps to 0");
    ASSERT_TRUE(a.indices[2] == 2, "INT_MAX maps to 2");
    free(a.values);
    free(a.indices);
}

void test_negative_numbers(void)
{
    TEST_START("Negative Numbers");
    
    t_stack a;
    init_stack(&a, 4);
    
    push(&a, -25);
    push(&a, -50);
    push(&a, -100);
    push(&a, -1);
    
    compress(&a);
    
    ASSERT_EQ(a.indices[2], 0, "-100 is smallest (index 0)");
    ASSERT_EQ(a.indices[3], 3, "-1 is largest (index 3)");
    
    free(a.values);
    free(a.indices);
}

void test_large_dataset(void)
{
    TEST_START("Large Dataset (100 elements)");
    
    t_stack a;
    init_stack(&a, 100);
    
    int i = 99;
    while (i >= 0)
    {
        push(&a, i);
        i--;
    }
    
    compress(&a);
    
    ASSERT_EQ(a.indices[0], 99, "First element (99) maps to index 99");
    ASSERT_EQ(a.indices[99], 0, "Last element (0) maps to index 0");
    ASSERT_EQ(a.indices[50], 49, "Element at position 50 (value 49) maps to index 49");
    
    free(a.values);
    free(a.indices);
}

int main(void)
{
    printf(YELLOW "\n╔═══════════════════════════════════╗\n" RESET);
    printf(YELLOW "║   NORMALIZATION UNIT TESTS        ║\n" RESET);
    printf(YELLOW "╚═══════════════════════════════════╝\n" RESET);
    
    test_basic_normalization();
    test_already_sorted();
    test_reverse_sorted();
    test_edge_cases();
    test_negative_numbers();
    test_large_dataset();
    
    TEST_SUMMARY();
    
    return (g_stats.failed > 0) ? 1 : 0;
}
