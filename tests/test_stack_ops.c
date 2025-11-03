/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack_ops.c                                   :+:      :+:    :+:   */
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

void test_push_pop(void)
{
    TEST_START("Push and Pop Operations");
    
    t_stack s;
    init_t_stack(&s, 5);
    
    ASSERT_EQ(s.top, -1, "Stack starts empty (top = -1)");
    
    push(&s, 42);
    ASSERT_EQ(s.top, 0, "After 1 push, top = 0");
    ASSERT_EQ(s.values[0], 42, "First value is 42");
    
    push(&s, 100);
    ASSERT_EQ(s.top, 1, "After 2 pushes, top = 1");
    ASSERT_EQ(s.values[1], 100, "Second value is 100");
    
    pop(&s);
    ASSERT_EQ(s.top, 0, "After pop, top = 0");
    ASSERT_EQ(s.values[0], 42, "Bottom value still 42");
    
    free(s.values);
}

void test_stack_top(void)
{
    TEST_START("Stack Top Function");
    
    t_stack s;
    init_t_stack(&s, 5);
    
    ASSERT_EQ(top(&s), -1, "Empty stack returns -1");
    
    push(&s, 42);
    ASSERT_EQ(top(&s), 42, "Top returns correct value");
    
    push(&s, 100);
    ASSERT_EQ(top(&s), 100, "Top returns latest value");
    
    pop(&s);
    ASSERT_EQ(top(&s), 42, "After pop, top returns previous value");
    
    free(s.values);
}

void test_stack_overflow(void)
{
    TEST_START("Stack Overflow Protection");
    
    t_stack s;
    init_t_stack(&s, 2);
    
    push(&s, 1);
    push(&s, 2);
    push(&s, 3);
    
    ASSERT_EQ(s.top, 1, "Stack doesn't overflow beyond capacity");
    ASSERT_EQ(s.values[0], 1, "First value preserved");
    ASSERT_EQ(s.values[1], 2, "Second value preserved");
    
    free(s.values);
}

void test_stack_underflow(void)
{
    TEST_START("Stack Underflow Protection");
    
    t_stack s;
    init_t_stack(&s, 5);
    
    pop(&s);
    ASSERT_EQ(s.top, -1, "Pop on empty stack keeps top at -1");
    
    push(&s, 42);
    pop(&s);
    pop(&s);
    ASSERT_EQ(s.top, -1, "Multiple pops don't go negative");
    
    free(s.values);
}

void test_multiple_operations(void)
{
    TEST_START("Multiple Push/Pop Operations");
    
    t_stack s;
    init_t_stack(&s, 10);
    
    int i = 0;
    while (i < 5)
    {
        push(&s, i);
        i++;
    }
    
    ASSERT_EQ(s.top, 4, "After 5 pushes, top = 4");
    ASSERT_EQ(top(&s), 4, "Top value is 4");
    
    i = 0;
    while (i < 3)
    {
        pop(&s);
        i++;
    }
    
    ASSERT_EQ(s.top, 1, "After 3 pops, top = 1");
    ASSERT_EQ(top(&s), 1, "Top value is 1");
    
    free(s.values);
}

void test_stack_capacity(void)
{
    TEST_START("Stack Capacity");
    
    t_stack s;
    init_t_stack(&s, 100);
    
    ASSERT_TRUE(s.capacity == 100, "Capacity set correctly");
    ASSERT_EQ(s.top, -1, "Stack initialized empty");
    
    free(s.values);
}

int main(void)
{
    printf(YELLOW "\n╔═══════════════════════════════════╗\n" RESET);
    printf(YELLOW "║   STACK OPERATIONS UNIT TESTS     ║\n" RESET);
    printf(YELLOW "╚═══════════════════════════════════╝\n" RESET);
    
    test_push_pop();
    test_stack_top();
    test_stack_overflow();
    test_stack_underflow();
    test_multiple_operations();
    test_stack_capacity();
    
    TEST_SUMMARY();
    
    return (g_stats.failed > 0) ? 1 : 0;
}
