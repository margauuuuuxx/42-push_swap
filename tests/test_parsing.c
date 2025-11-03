/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
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

void test_valid_input(void)
{
    TEST_START("Valid Input Parsing");
    
    t_stack a, b;
    char *args[] = {"push_swap", "42", "3", "-7"};
    
    bool result = parse(&a, &b, 4, args);
    
    ASSERT_TRUE(result, "Valid integers parse successfully");
    ASSERT_EQ(a.top, 2, "Correct number of elements");
    ASSERT_EQ(a.values[0], -7, "First element correct");
    ASSERT_EQ(a.values[1], 3, "Second element correct");
    ASSERT_EQ(a.values[2], 42, "Third element correct");
    
    free(a.values);
    free(b.values);
}

void test_negative_numbers(void)
{
    TEST_START("Negative Numbers Parsing");
    
    t_stack a, b;
    char *args[] = {"push_swap", "-42", "-100", "-1"};
    
    bool result = parse(&a, &b, 4, args);
    
    ASSERT_TRUE(result, "Negative integers parse successfully");
    ASSERT_EQ(a.values[0], -1, "Negative value correct");
    ASSERT_EQ(a.values[2], -42, "Multiple negatives handled");
    
    free(a.values);
    free(b.values);
}

void test_positive_sign(void)
{
    TEST_START("Positive Sign (+) Parsing");
    
    t_stack a, b;
    char *args[] = {"push_swap", "+42", "+100"};
    
    bool result = parse(&a, &b, 3, args);
    
    ASSERT_TRUE(result, "Positive sign handled");
    ASSERT_EQ(a.values[1], 42, "Value with + sign correct");
    
    free(a.values);
    free(b.values);
}

void test_invalid_characters(void)
{
    TEST_START("Invalid Characters Detection");
    
    t_stack a, b;
    
    char *args1[] = {"push_swap", "42", "abc"};
    bool result1 = parse(&a, &b, 3, args1);
    ASSERT_TRUE(!result1, "Rejects letters");
    
    char *args2[] = {"push_swap", "42", "12.5"};
    bool result2 = parse(&a, &b, 3, args2);
    ASSERT_TRUE(!result2, "Rejects decimal points");
    
    char *args3[] = {"push_swap", "42", "12a"};
    bool result3 = parse(&a, &b, 3, args3);
    ASSERT_TRUE(!result3, "Rejects mixed alphanumeric");
}

void test_sign_errors(void)
{
    TEST_START("Sign Position Errors");
    
    t_stack a, b;
    
    char *args1[] = {"push_swap", "++42"};
    bool result1 = parse(&a, &b, 2, args1);
    ASSERT_TRUE(!result1, "Rejects double plus");
    
    char *args2[] = {"push_swap", "--42"};
    bool result2 = parse(&a, &b, 2, args2);
    ASSERT_TRUE(!result2, "Rejects double minus");
    
    char *args3[] = {"push_swap", "4+2"};
    bool result3 = parse(&a, &b, 2, args3);
    ASSERT_TRUE(!result3, "Rejects sign in middle");
}

void test_single_string_input(void)
{
    TEST_START("Single String Input (with spaces)");
    
    t_stack a, b;
    char *args[] = {"push_swap", "42 3 -7 100"};
    
    bool result = parse(&a, &b, 2, args);
    
    ASSERT_TRUE(result, "Space-separated string parses");
    ASSERT_EQ(a.top, 3, "Correct number of elements");
    ASSERT_EQ(a.values[0], 100, "Elements in correct order");
    
    free(a.values);
    free(b.values);
}

void test_empty_string(void)
{
    TEST_START("Empty String Handling");
    
    t_stack a, b;
    char *args[] = {"push_swap", ""};
    
    bool result = parse(&a, &b, 2, args);
    
    ASSERT_TRUE(!result, "Empty string rejected");
}

void test_zero(void)
{
    TEST_START("Zero Value");
    
    t_stack a, b;
    char *args[] = {"push_swap", "0", "1", "-1"};
    
    bool result = parse(&a, &b, 4, args);
    
    ASSERT_TRUE(result, "Zero parsed successfully");
    ASSERT_EQ(a.values[2], 0, "Zero value correct");
    
    free(a.values);
    free(b.values);
}

void test_int_limits(void)
{
    TEST_START("INT_MIN and INT_MAX");
    
    t_stack a, b;
    char *args[] = {"push_swap", "-2147483648", "2147483647"};
    
    bool result = parse(&a, &b, 3, args);
    
    ASSERT_TRUE(result, "INT limits parse successfully");
    ASSERT_TRUE(a.values[1] == -2147483648, "INT_MIN correct");
    ASSERT_TRUE(a.values[0] == 2147483647, "INT_MAX correct");
    
    free(a.values);
    free(b.values);
}

int main(void)
{
    printf(YELLOW "\n╔═══════════════════════════════════╗\n" RESET);
    printf(YELLOW "║   PARSING UNIT TESTS              ║\n" RESET);
    printf(YELLOW "╚═══════════════════════════════════╝\n" RESET);
    
    test_valid_input();
    test_negative_numbers();
    test_positive_sign();
    test_invalid_characters();
    test_sign_errors();
    test_single_string_input();
    test_empty_string();
    test_zero();
    test_int_limits();
    
    TEST_SUMMARY();
    
    return (g_stats.failed > 0) ? 1 : 0;
}
