# Push_Swap Unit Tests

## 📁 Test Structure

```
tests/
├── test_framework.h          # Testing macros and utilities
├── test_normalization.c      # Tests for coordinate compression
├── test_parsing.c            # Tests for input parsing
├── test_sorting.c            # Tests for merge sort algorithm
├── test_stack_ops.c          # Tests for stack operations
├── run_all_tests.sh          # Script to run all tests
└── README.md                 # This file
```

## 🚀 Running Tests

### Run All Tests
```bash
make test
```

### Compile Tests Only
```bash
make tests
```

### Run Individual Test
```bash
./tests/test_normalization
./tests/test_parsing
./tests/test_sorting
./tests/test_stack_ops
```

### Clean Test Binaries
```bash
make fclean
```

## 📊 Test Coverage

### test_normalization.c
- ✓ Basic normalization (arbitrary values → indices)
- ✓ Already sorted arrays
- ✓ Reverse sorted arrays
- ✓ Edge cases (single element, INT_MIN/MAX)
- ✓ Negative numbers
- ✓ Large datasets (100 elements)

### test_parsing.c
- ✓ Valid integer input
- ✓ Negative numbers
- ✓ Positive sign (+) handling
- ✓ Invalid characters detection
- ✓ Sign position errors (++, --, middle signs)
- ✓ Single string input with spaces
- ✓ Empty string handling
- ✓ Zero value
- ✓ INT_MIN and INT_MAX limits

### test_sorting.c
- ✓ Basic merge sort
- ✓ Already sorted arrays
- ✓ Reverse sorted arrays
- ✓ Arrays with duplicates
- ✓ Negative numbers
- ✓ Single element
- ✓ Two elements
- ✓ Large dataset (100 elements)

### test_stack_ops.c
- ✓ Push and pop operations
- ✓ Stack top function
- ✓ Stack overflow protection
- ✓ Stack underflow protection
- ✓ Multiple operations
- ✓ Stack capacity

## 🎯 Understanding Test Output

### Successful Test
```
▶ Running: Basic Normalization
  ✓ Values normalized correctly
  ✓ 42 maps to index 3
  ✓ -7 maps to index 0 (smallest)
```

### Failed Test
```
▶ Running: Basic Normalization
  ✗ Values normalized correctly
    Expected: 3, Got: 2
```

### Final Summary
```
═══════════════════════════════
   TEST SUMMARY
═══════════════════════════════
  Total:  25
  Passed: 25
  Failed: 0

  ✓ All tests passed!
```

## 🔧 Adding New Tests

1. Create a new test file: `tests/test_myfeature.c`
2. Include the framework: `#include "test_framework.h"`
3. Initialize test stats: `TEST_INIT();`
4. Write test functions:
```c
void test_my_feature(void)
{
    TEST_START("My Feature Test");
    
    // Your test code
    int result = my_function(42);
    
    ASSERT_EQ(result, 42, "Function returns correct value");
}
```
5. Add to main():
```c
int main(void)
{
    test_my_feature();
    TEST_SUMMARY();
    return (g_stats.failed > 0) ? 1 : 0;
}
```

## 📝 Available Assert Macros

```c
ASSERT_EQ(actual, expected, "message")         // Compare two integers
ASSERT_TRUE(condition, "message")              // Check boolean condition
ASSERT_ARRAY_EQ(arr1, arr2, size, "message")  // Compare two arrays
```

## 🐛 Debugging Failed Tests

1. Run the specific test file individually
2. Check the error message for expected vs actual values
3. Add printf debugging in your source code
4. Use DEBUG_MODE flag for verbose output

## 📈 Test Metrics

- **Total Test Cases**: ~50+
- **Code Coverage**: Core functions (parsing, sorting, normalization, stack ops)
- **Edge Cases**: INT_MIN/MAX, empty input, single elements
- **Performance**: Tests up to 100 elements

## 🎓 Best Practices

1. Run tests after every code change
2. Keep tests simple and focused
3. Test edge cases thoroughly
4. Use descriptive test names
5. Clean up resources (free malloc'd memory)

## 🔍 Continuous Integration

To integrate with CI/CD:
```bash
#!/bin/bash
make test
if [ $? -eq 0 ]; then
    echo "✓ Tests passed - ready to deploy"
else
    echo "✗ Tests failed - fix before merging"
    exit 1
fi
```

---

**Happy Testing! 🧪**
