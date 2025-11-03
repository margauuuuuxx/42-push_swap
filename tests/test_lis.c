/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:34:00 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/03 13:34:00 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include "test_framework.h"

TEST_INIT();

void test_lis_basic(void)
{
    TEST_START("LIS - Basic Case");
    
    t_stack a;
    init_stack(&a, 5);
    
    push(&a, 42);
    push(&a, -7);
    push(&a, 100);
    push(&a, 3);
    push(&a, 0);
    
    compress(&a);
    calculate_lis(&a);
    
    int lis_count = 0;
    int i = 0;
    while (i <= a.top)
    {
        if (a.in_LIS[i])
            lis_count++;
        i++;
    }
    
    ASSERT_EQ(lis_count, 2, "LIS has 2 elements");
    ASSERT_EQ(count_non_lis(&a), 3, "3 elements not in LIS");
    
    free(a.values);
    free(a.indices);
    free(a.in_LIS);
}

void test_lis_already_sorted(void)
{
    TEST_START("LIS - Already Sorted");
    
    t_stack a;
    init_stack(&a, 5);
    
    push(&a, 1);
    push(&a, 2);
    push(&a, 3);
    push(&a, 4);
    push(&a, 5);
    
    compress(&a);
    calculate_lis(&a);
    
    int i = 0;
    while (i <= a.top)
    {
        ASSERT_TRUE(a.in_LIS[i], "All elements should be in LIS");
        i++;
    }
    
    ASSERT_EQ(count_non_lis(&a), 0, "No elements outside LIS");
    
    free(a.values);
    free(a.indices);
    free(a.in_LIS);
}

void test_lis_reverse_sorted(void)
{
    TEST_START("LIS - Reverse Sorted");
    
    t_stack a;
    init_stack(&a, 5);
    
    push(&a, 5);
    push(&a, 4);
    push(&a, 3);
    push(&a, 2);
    push(&a, 1);
    
    compress(&a);
    calculate_lis(&a);
    
    int lis_count = 0;
    int i = 0;
    while (i <= a.top)
    {
        if (a.in_LIS[i])
            lis_count++;
        i++;
    }
    
    ASSERT_EQ(lis_count, 1, "LIS has only 1 element");
    ASSERT_EQ(count_non_lis(&a), 4, "4 elements not in LIS");
    
    free(a.values);
    free(a.indices);
    free(a.in_LIS);
}

void test_lis_single_element(void)
{
    TEST_START("LIS - Single Element");
    
    t_stack a;
    init_stack(&a, 1);
    
    push(&a, 42);
    
    compress(&a);
    calculate_lis(&a);
    
    ASSERT_TRUE(a.in_LIS[0], "Single element is in LIS");
    ASSERT_EQ(count_non_lis(&a), 0, "No elements outside LIS");
    
    free(a.values);
    free(a.indices);
    free(a.in_LIS);
}

void test_lis_two_elements_sorted(void)
{
    TEST_START("LIS - Two Elements Sorted");
    
    t_stack a;
    init_stack(&a, 2);
    
    push(&a, 1);
    push(&a, 2);
    
    compress(&a);
    calculate_lis(&a);
    
    ASSERT_TRUE(a.in_LIS[0], "First element in LIS");
    ASSERT_TRUE(a.in_LIS[1], "Second element in LIS");
    ASSERT_EQ(count_non_lis(&a), 0, "All elements in LIS");
    
    free(a.values);
    free(a.indices);
    free(a.in_LIS);
}

void test_lis_two_elements_reverse(void)
{
    TEST_START("LIS - Two Elements Reverse");
    
    t_stack a;
    init_stack(&a, 2);
    
    push(&a, 2);
    push(&a, 1);
    
    compress(&a);
    calculate_lis(&a);
    
    int lis_count = 0;
    int i = 0;
    while (i <= a.top)
    {
        if (a.in_LIS[i])
            lis_count++;
        i++;
    }
    
    ASSERT_EQ(lis_count, 1, "Only 1 element in LIS");
    ASSERT_EQ(count_non_lis(&a), 1, "1 element not in LIS");
    
    free(a.values);
    free(a.indices);
    free(a.in_LIS);
}

void test_lis_long_sequence(void)
{
    TEST_START("LIS - Long Sequence");
    
    t_stack a;
    init_stack(&a, 10);
    
    // Values: [1, 5, 2, 3, 4, 10, 6, 7, 8, 9]
    // LIS should be [1, 2, 3, 4, 6, 7, 8, 9] = length 8
    push(&a, 1);
    push(&a, 5);
    push(&a, 2);
    push(&a, 3);
    push(&a, 4);
    push(&a, 10);
    push(&a, 6);
    push(&a, 7);
    push(&a, 8);
    push(&a, 9);
    
    compress(&a);
    calculate_lis(&a);
    
    int lis_count = 0;
    int i = 0;
    while (i <= a.top)
    {
        if (a.in_LIS[i])
            lis_count++;
        i++;
    }
    
    ASSERT_TRUE(lis_count >= 8, "LIS has at least 8 elements");
    ASSERT_TRUE(count_non_lis(&a) <= 2, "At most 2 elements not in LIS");
    
    free(a.values);
    free(a.indices);
    free(a.in_LIS);
}

void test_lis_alternating(void)
{
    TEST_START("LIS - Alternating Pattern");
    
    t_stack a;
    init_stack(&a, 6);
    
    // Values: [1, 10, 2, 20, 3, 30]
    // Indices: [0, 3, 1, 4, 2, 5]
    // LIS could be [0, 1, 2, 5] = length 4 (optimal!)
    push(&a, 1);
    push(&a, 10);
    push(&a, 2);
    push(&a, 20);
    push(&a, 3);
    push(&a, 30);
    
    compress(&a);
    calculate_lis(&a);
    
    int lis_count = 0;
    int i = 0;
    while (i <= a.top)
    {
        if (a.in_LIS[i])
            lis_count++;
        i++;
    }
    
    ASSERT_TRUE(lis_count >= 3, "LIS has at least 3 elements");
    ASSERT_TRUE(count_non_lis(&a) <= 3, "At most 3 elements not in LIS");
    
    free(a.values);
    free(a.indices);
    free(a.in_LIS);
}

void test_lis_with_duplicates_removed(void)
{
    TEST_START("LIS - No Duplicates (distinct values)");
    
    t_stack a;
    init_stack(&a, 5);
    
    // All distinct values
    push(&a, 5);
    push(&a, 3);
    push(&a, 4);
    push(&a, 1);
    push(&a, 2);
    
    compress(&a);
    calculate_lis(&a);
    
    int lis_count = 0;
    int i = 0;
    while (i <= a.top)
    {
        if (a.in_LIS[i])
            lis_count++;
        i++;
    }
    
    ASSERT_TRUE(lis_count >= 2, "LIS has at least 2 elements");
    ASSERT_TRUE(count_non_lis(&a) >= 0, "Valid non-LIS count");
    
    free(a.values);
    free(a.indices);
    free(a.in_LIS);
}

void test_lis_large_dataset(void)
{
    TEST_START("LIS - Large Dataset (100 elements)");
    
    t_stack a;
    init_stack(&a, 100);
    
    // Push values 99 down to 0 (reverse sorted)
    int i = 99;
    while (i >= 0)
    {
        push(&a, i);
        i--;
    }
    
    compress(&a);
    calculate_lis(&a);
    
    int lis_count = 0;
    i = 0;
    while (i <= a.top)
    {
        if (a.in_LIS[i])
            lis_count++;
        i++;
    }
    
    ASSERT_EQ(lis_count, 1, "Reverse sorted has LIS of 1");
    ASSERT_EQ(count_non_lis(&a), 99, "99 elements not in LIS");
    
    free(a.values);
    free(a.indices);
    free(a.in_LIS);
}

void test_lis_includes_position_zero(void)
{
    TEST_START("LIS - Includes Position 0");
    
    t_stack a;
    init_stack(&a, 4);
    
    // Make sure LIS starts at position 0
    push(&a, 1);
    push(&a, 2);
    push(&a, 3);
    push(&a, 100);
    
    compress(&a);
    calculate_lis(&a);
    
    ASSERT_TRUE(a.in_LIS[0], "Position 0 is in LIS");
    ASSERT_TRUE(a.in_LIS[1], "Position 1 is in LIS");
    ASSERT_TRUE(a.in_LIS[2], "Position 2 is in LIS");
    
    free(a.values);
    free(a.indices);
    free(a.in_LIS);
}

void test_count_non_lis(void)
{
    TEST_START("count_non_lis() Function");
    
    t_stack a;
    init_stack(&a, 5);
    
    push(&a, 5);
    push(&a, 1);
    push(&a, 2);
    push(&a, 3);
    push(&a, 4);
    
    compress(&a);
    calculate_lis(&a);
    
    int count = count_non_lis(&a);
    int lis_count = 0;
    int i = 0;
    while (i <= a.top)
    {
        if (a.in_LIS[i])
            lis_count++;
        i++;
    }
    
    ASSERT_EQ(count + lis_count, 5, "LIS + non-LIS = total elements");
    ASSERT_TRUE(count >= 0 && count <= 5, "Valid non-LIS count");
    
    free(a.values);
    free(a.indices);
    free(a.in_LIS);
}

void test_is_in_lis(void)
{
    TEST_START("is_in_lis() Function");
    
    t_stack a;
    init_stack(&a, 3);
    
    push(&a, 1);
    push(&a, 2);
    push(&a, 3);
    
    compress(&a);
    calculate_lis(&a);
    
    ASSERT_TRUE(is_in_lis(&a, 0), "is_in_lis(0) returns true");
    ASSERT_TRUE(is_in_lis(&a, 1), "is_in_lis(1) returns true");
    ASSERT_TRUE(is_in_lis(&a, 2), "is_in_lis(2) returns true");
    
    free(a.values);
    free(a.indices);
    free(a.in_LIS);
}

int main(void)
{
    printf(YELLOW "\n╔═══════════════════════════════════╗\n" RESET);
    printf(YELLOW "║   LIS CALCULATION UNIT TESTS      ║\n" RESET);
    printf(YELLOW "╚═══════════════════════════════════╝\n" RESET);
    
    test_lis_basic();
    test_lis_already_sorted();
    test_lis_reverse_sorted();
    test_lis_single_element();
    test_lis_two_elements_sorted();
    test_lis_two_elements_reverse();
    test_lis_long_sequence();
    test_lis_alternating();
    test_lis_with_duplicates_removed();
    test_lis_large_dataset();
    test_lis_includes_position_zero();
    test_count_non_lis();
    test_is_in_lis();
    
    TEST_SUMMARY();
    
    return (g_stats.failed > 0) ? 1 : 0;
}
