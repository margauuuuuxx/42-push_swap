/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_framework.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:10:00 by marlonco          #+#    #+#             */
/*   Updated: 2025/11/03 11:10:00 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>
#include <stdbool.h>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

typedef struct s_test_stats {
    int total;
    int passed;
    int failed;
} t_test_stats;

extern t_test_stats g_stats;

#define TEST_INIT() \
    t_test_stats g_stats = {0, 0, 0}

#define TEST_START(name) \
    printf(BLUE "\n▶ Running: %s\n" RESET, name)

#define ASSERT_EQ(actual, expected, msg) \
    do { \
        g_stats.total++; \
        if ((actual) == (expected)) { \
            printf(GREEN "  ✓ " RESET "%s\n", msg); \
            g_stats.passed++; \
        } else { \
            printf(RED "  ✗ " RESET "%s\n", msg); \
            printf(RED "    Expected: %d, Got: %d\n" RESET, (expected), (actual)); \
            g_stats.failed++; \
        } \
    } while(0)

#define ASSERT_TRUE(condition, msg) \
    do { \
        g_stats.total++; \
        if (condition) { \
            printf(GREEN "  ✓ " RESET "%s\n", msg); \
            g_stats.passed++; \
        } else { \
            printf(RED "  ✗ " RESET "%s\n", msg); \
            g_stats.failed++; \
        } \
    } while(0)

#define ASSERT_ARRAY_EQ(actual, expected, size, msg) \
    do { \
        g_stats.total++; \
        bool match = true; \
        for (int i = 0; i < size; i++) { \
            if ((actual)[i] != (expected)[i]) { \
                match = false; \
                break; \
            } \
        } \
        if (match) { \
            printf(GREEN "  ✓ " RESET "%s\n", msg); \
            g_stats.passed++; \
        } else { \
            printf(RED "  ✗ " RESET "%s\n", msg); \
            printf(RED "    Arrays don't match\n" RESET); \
            g_stats.failed++; \
        } \
    } while(0)

#define TEST_SUMMARY() \
    do { \
        printf("\n" YELLOW "═══════════════════════════════\n" RESET); \
        printf(YELLOW "   TEST SUMMARY\n" RESET); \
        printf(YELLOW "═══════════════════════════════\n" RESET); \
        printf("  Total:  %d\n", g_stats.total); \
        printf(GREEN "  Passed: %d\n" RESET, g_stats.passed); \
        printf(RED "  Failed: %d\n" RESET, g_stats.failed); \
        if (g_stats.failed == 0) \
            printf(GREEN "\n  ✓ All tests passed!\n\n" RESET); \
        else \
            printf(RED "\n  ✗ Some tests failed!\n\n" RESET); \
    } while(0)

#endif
