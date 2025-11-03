/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sorting.c                                     :+:      :+:    :+:   */
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

void merge_sort(int *arr, int *temp, int left, int right);

void test_merge_sort_basic(void)
{
    TEST_START("Merge Sort - Basic");
    
    int arr[] = {5, 2, 8, 1, 9};
    int temp[5];
    int expected[] = {1, 2, 5, 8, 9};
    
    merge_sort(arr, temp, 0, 4);
    
    ASSERT_ARRAY_EQ(arr, expected, 5, "Basic array sorted correctly");
}

void test_merge_sort_already_sorted(void)
{
    TEST_START("Merge Sort - Already Sorted");
    
    int arr[] = {1, 2, 3, 4, 5};
    int temp[5];
    int expected[] = {1, 2, 3, 4, 5};
    
    merge_sort(arr, temp, 0, 4);
    
    ASSERT_ARRAY_EQ(arr, expected, 5, "Already sorted array unchanged");
}

void test_merge_sort_reverse(void)
{
    TEST_START("Merge Sort - Reverse Sorted");
    
    int arr[] = {5, 4, 3, 2, 1};
    int temp[5];
    int expected[] = {1, 2, 3, 4, 5};
    
    merge_sort(arr, temp, 0, 4);
    
    ASSERT_ARRAY_EQ(arr, expected, 5, "Reverse sorted array corrected");
}

void test_merge_sort_duplicates(void)
{
    TEST_START("Merge Sort - With Duplicates");
    
    int arr[] = {5, 2, 8, 2, 5};
    int temp[5];
    int expected[] = {2, 2, 5, 5, 8};
    
    merge_sort(arr, temp, 0, 4);
    
    ASSERT_ARRAY_EQ(arr, expected, 5, "Duplicates handled correctly");
}

void test_merge_sort_negatives(void)
{
    TEST_START("Merge Sort - Negative Numbers");
    
    int arr[] = {-5, 2, -8, 1, -1};
    int temp[5];
    int expected[] = {-8, -5, -1, 1, 2};
    
    merge_sort(arr, temp, 0, 4);
    
    ASSERT_ARRAY_EQ(arr, expected, 5, "Negative numbers sorted correctly");
}

void test_merge_sort_single(void)
{
    TEST_START("Merge Sort - Single Element");
    
    int arr[] = {42};
    int temp[1];
    int expected[] = {42};
    
    merge_sort(arr, temp, 0, 0);
    
    ASSERT_ARRAY_EQ(arr, expected, 1, "Single element unchanged");
}

void test_merge_sort_two_elements(void)
{
    TEST_START("Merge Sort - Two Elements");
    
    int arr[] = {2, 1};
    int temp[2];
    int expected[] = {1, 2};
    
    merge_sort(arr, temp, 0, 1);
    
    ASSERT_ARRAY_EQ(arr, expected, 2, "Two elements sorted");
}

void test_merge_sort_large(void)
{
    TEST_START("Merge Sort - Large Dataset (100 elements)");
    
    int arr[100];
    int temp[100];
    int i = 0;
    
    while (i < 100)
    {
        arr[i] = 99 - i;
        i++;
    }
    
    merge_sort(arr, temp, 0, 99);
    
    ASSERT_EQ(arr[0], 0, "First element is 0");
    ASSERT_EQ(arr[99], 99, "Last element is 99");
    ASSERT_EQ(arr[50], 50, "Middle element is 50");
    
    bool sorted = true;
    i = 0;
    while (i < 99)
    {
        if (arr[i] > arr[i + 1])
            sorted = false;
        i++;
    }
    ASSERT_TRUE(sorted, "Array is fully sorted");
}

int main(void)
{
    printf(YELLOW "\n╔═══════════════════════════════════╗\n" RESET);
    printf(YELLOW "║   SORTING ALGORITHM UNIT TESTS    ║\n" RESET);
    printf(YELLOW "╚═══════════════════════════════════╝\n" RESET);
    
    test_merge_sort_basic();
    test_merge_sort_already_sorted();
    test_merge_sort_reverse();
    test_merge_sort_duplicates();
    test_merge_sort_negatives();
    test_merge_sort_single();
    test_merge_sort_two_elements();
    test_merge_sort_large();
    
    TEST_SUMMARY();
    
    return (g_stats.failed > 0) ? 1 : 0;
}
