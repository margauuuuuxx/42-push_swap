# Push Swap - Efficient Stack Sorting Algorithm

A highly optimized sorting algorithm that sorts a stack using only two stacks and a limited set of operations, achieving excellent performance with minimal moves.

## 📊 Performance Metrics

- **100 numbers:** ~659 operations average (Target: 700) ✅
- **500 numbers:** ~5910 operations average (Target: 5500) 📈

## 🎯 Project Overview

Push Swap is a sorting algorithm project that challenges you to sort data on a stack with a limited set of instructions, using the lowest possible number of operations. The program manipulates two stacks (A and B) using specific operations to sort integers in ascending order.

## 📐 Core Concepts

### 1. Coordinate Normalization (Compression)

Before sorting, all input values are normalized to their index positions (0 to n-1). This simplification allows the algorithm to work with predictable ranges regardless of the actual input values.

**Example:**
```
Input:  [42, -5, 100, 7]
Indices: [2,  0,   3,  1]  (compressed coordinates)
```

This transformation:
- Makes the algorithm independent of input value ranges
- Simplifies chunk calculations
- Enables efficient LIS computation

**Implementation:** `compress.c`

### 2. Longest Increasing Subsequence (LIS)

The LIS algorithm identifies elements that are already in correct relative order. These elements should **not** be moved, as they form the optimal backbone of the final sorted sequence.

**Example:**
```
Stack: [4, 1, 5, 2, 6, 3, 7]
LIS:   [1, 2, 3, 7]  ← Keep these in place!
Move:  [4, 5, 6]     ← Only move these to B
```

**Benefits:**
- Reduces the number of elements to move
- Preserves optimal ordering
- Significantly decreases total operations

**Algorithm:** O(n log n) dynamic programming approach using binary search

**Implementation:** `lis.c`

### 3. Chunking Heuristic

For large stacks (>20 elements), the algorithm divides non-LIS elements into **chunks** - contiguous ranges of indices that are processed together.

**Chunk Strategy:**
```
Size <= 100:  5 chunks
Size <= 500:  9 chunks
Size >  500: 20 chunks
```

**Why Chunking Works:**
- Reduces search time for elements to push
- Balances between too many small chunks (overhead) and too few large chunks (poor distribution)
- Allows for strategic pre-rotation of stack B

**Implementation:** `chunk.c`

### 4. Cost-Based Insertion

When pushing elements back from B to A, the algorithm calculates the "cost" of each move:

```
Cost = rotations_in_A + rotations_in_B + 1 (push operation)
```

**Optimizations:**
- Same-direction rotations can be combined (rr/rrr)
- Algorithm always chooses the cheapest move
- Considers both forward and reverse rotation costs

**Implementation:** `cost.c`

## 🔄 Algorithm Workflow

```
┌─────────────────────────────────────────────────────────────┐
│                     START: Parse Input                       │
│                   Stack A: [unsorted numbers]                │
│                   Stack B: [empty]                           │
└────────────────────────────┬────────────────────────────────┘
                             │
                             ▼
┌─────────────────────────────────────────────────────────────┐
│              STEP 1: Coordinate Normalization                │
│   Transform values to indices: [4,67,3,87,23] → [1,3,0,4,2] │
└────────────────────────────┬────────────────────────────────┘
                             │
                             ▼
┌─────────────────────────────────────────────────────────────┐
│           STEP 2: Calculate LIS (Keep in Place)             │
│   Identify longest increasing subsequence to preserve        │
│   Example: [1,3,0,4,2] → LIS: [1,3,4] (keep these)         │
└────────────────────────────┬────────────────────────────────┘
                             │
                             ▼
                    ┌────────┴────────┐
                    │  Size Check     │
                    └────┬─────┬──────┘
                         │     │
              Size ≤ 5   │     │   Size > 5
                         │     │
                    ┌────▼─┐   └──────┐
                    │Small │          │
                    │Sort  │          │
                    └──────┘          ▼
                                 ┌─────────────────────────────┐
                                 │  STEP 3: Create Chunks      │
                                 │  Divide non-LIS elements    │
                                 │  into manageable ranges     │
                                 └──────────┬──────────────────┘
                                            │
                                            ▼
                                 ┌─────────────────────────────┐
                                 │  STEP 4: Push to B          │
                                 │  Process chunks in order:   │
                                 │  - Find closest element     │
                                 │  - Smart rotate to top      │
                                 │  - Push to B (pb)           │
                                 │  - Rotate B if needed (rb)  │
                                 └──────────┬──────────────────┘
                                            │
                                            ▼
                                 ┌─────────────────────────────┐
                                 │  STEP 5: Sort Remaining 3   │
                                 │  Use optimal 3-element sort │
                                 │  in Stack A                 │
                                 └──────────┬──────────────────┘
                                            │
                                            ▼
                                 ┌─────────────────────────────┐
                                 │  STEP 6: Push Back from B   │
                                 │  While B is not empty:      │
                                 │  1. Find max element in B   │
                                 │  2. Calculate rotation cost │
                                 │  3. Rotate to top           │
                                 │  4. Push to A (pa)          │
                                 └──────────┬──────────────────┘
                                            │
                                            ▼
                                 ┌─────────────────────────────┐
                                 │  STEP 7: Final Rotation     │
                                 │  Rotate A to place minimum  │
                                 │  element at the top         │
                                 └──────────┬──────────────────┘
                                            │
                                            ▼
                             ┌──────────────────────────────┐
                             │    DONE: Stack A is sorted   │
                             │  [smallest → largest, top→bot]│
                             └──────────────────────────────┘
```

## 🛠️ Available Operations

| Operation | Description |
|-----------|-------------|
| `sa` | Swap first 2 elements of stack A |
| `sb` | Swap first 2 elements of stack B |
| `ss` | `sa` and `sb` simultaneously |
| `pa` | Push top element from B to A |
| `pb` | Push top element from A to B |
| `ra` | Rotate stack A up (first → last) |
| `rb` | Rotate stack B up |
| `rr` | `ra` and `rb` simultaneously |
| `rra` | Rotate stack A down (last → first) |
| `rrb` | Rotate stack B down |
| `rrr` | `rra` and `rrb` simultaneously |

## 🚀 Compilation

```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Recompile from scratch
```

## 📝 Usage

### Basic Usage
```bash
./push_swap [numbers]
```

**Examples:**
```bash
# Simple test
./push_swap 4 67 3 87 23

# Using quotes
./push_swap "4 67 3 87 23"

# Large random test
./push_swap $(shuf -i 1-1000 -n 100 | tr '\n' ' ')
```

### Output
The program outputs the sequence of operations needed to sort the stack:
```bash
$ ./push_swap 3 2 1
sa
rra
```

## 🧪 Testing

### Using the Checker

The `checker_linux` validates that your operations correctly sort the stack:

```bash
# Basic check
ARG="4 67 3 87 23"
./push_swap $ARG | ./testers/checker_linux $ARG
# Output: OK (if sorted correctly) or KO (if not)
```

### Count Operations
```bash
# Count number of operations
ARG="4 67 3 87 23"
./push_swap $ARG | wc -l
```

### Comprehensive Testing

**Test 100 random numbers (50 iterations):**
```bash
for i in {1..50}; do
    ARG=$(shuf -i 1-1000 -n 100 | tr '\n' ' ')
    OPS=$(./push_swap $ARG | wc -l)
    CHECK=$(./push_swap $ARG | ./testers/checker_linux $ARG)
    echo "Test $i: $OPS operations - $CHECK"
done
```

**Test 500 random numbers (20 iterations):**
```bash
for i in {1..20}; do
    ARG=$(shuf -i 1-5000 -n 500 | tr '\n' ' ')
    OPS=$(./push_swap $ARG | wc -l)
    CHECK=$(./push_swap $ARG | ./testers/checker_linux $ARG)
    echo "Test $i: $OPS operations - $CHECK"
done
```

**Calculate average operations:**
```bash
# For 100 numbers
for i in {1..50}; do
    ARG=$(shuf -i 1-1000 -n 100 | tr '\n' ' ')
    ./push_swap $ARG | wc -l
done | awk '{sum+=$1; count++} END {print "Average:", sum/count}'

# For 500 numbers
for i in {1..50}; do
    ARG=$(shuf -i 1-5000 -n 500 | tr '\n' ' ')
    ./push_swap $ARG | wc -l
done | awk '{sum+=$1; count++} END {print "Average:", sum/count}'
```

### Interactive Testing

**Test with visualization (if you have a visualizer):**
```bash
# Generate random numbers and pipe to visualizer
./push_swap $(shuf -i 1-100 -n 100) | ./visualizer
```

**Debug mode (if enabled):**
```bash
# Compile with debug flags
make DEBUG_MODE=1

# Run with debug output
./push_swap "3 2 1"
```

## 📂 Project Structure

```
push_swap/
├── includes/
│   ├── push_swap.h          # Main header with function prototypes
│   └── structs.h            # Data structure definitions
├── srcs/
│   ├── algo.c               # Main algorithm logic and initialization
│   ├── chunk.c              # Chunk creation and management
│   ├── compress.c           # Coordinate normalization
│   ├── cost.c               # Cost calculation for optimal moves
│   ├── final_rotate.c       # Final rotation to sort position
│   ├── insertion.c          # Push-back insertion strategy
│   ├── lis.c                # Longest Increasing Subsequence
│   ├── main.c               # Entry point
│   ├── parsing.c            # Input validation and parsing
│   ├── small_sort.c         # Optimized sorting for ≤5 elements
│   ├── sort_medium_stack.c  # Medium-large stack sorting (>20)
│   ├── sort_small_stack.c   # Small stack sorting (6-20)
│   ├── named_operations/
│   │   ├── named_operations.c  # High-level operations (pa, pb, etc.)
│   │   └── operations.c        # Low-level stack operations
│   └── utils/
│       ├── split.c          # String splitting utility
│       ├── stack_utils.c    # Stack management functions
│       └── utils.c          # General utilities (atoi, strlen, etc.)
├── testers/
│   └── checker_linux        # Validation tool
├── Makefile
└── README.md
```

## 🎓 Algorithm Complexity

- **Time Complexity:** O(n²) worst case, O(n log n) average
- **Space Complexity:** O(n)
- **Operation Count:**
  - 2-3 elements: ≤3 operations
  - 5 elements: ≤12 operations
  - 100 elements: ~659 operations average
  - 500 elements: ~5910 operations average

## 🔍 Key Algorithm Insights

### Why LIS?
The LIS represents elements that don't need to move. By keeping these in place and only moving non-LIS elements, we minimize operations.

### Why Chunks?
Instead of finding any element to push, chunks create a strategic order:
1. Push smaller elements first
2. This naturally organizes B in descending order
3. Makes push-back phase more efficient

### Rotation Strategy in B
When pushing to B, we pre-rotate smaller elements:
```
If (pushed_element < chunk_midpoint):
    rb  # Rotate smaller elements to bottom
```
This separates larger elements (top) from smaller (bottom), optimizing later retrieval.

### Cost Optimization
The cost-based approach considers:
- **Combined rotations:** If both stacks rotate the same direction, combine with `rr`/`rrr`
- **Distance:** Choose closer rotation direction (forward vs reverse)
- **Total cost:** Always pick the cheapest element to push next

## 🐛 Error Handling

The program handles:
- ✅ Non-integer inputs
- ✅ Integers outside INT_MIN to INT_MAX range
- ✅ Duplicate values
- ✅ Empty input
- ✅ Already sorted stacks

All errors output `"Error\n"` to stderr and exit with status 1.

## 📚 Resources

- [Push Swap Visualizer](https://github.com/o-reo/push_swap_visualizer)
- [Algorithm Explanation](https://medium.com/@jamierobertdawson/push-swap-the-least-amount-of-moves-with-two-stacks-d1e76a71789a)
- [LIS Algorithm](https://en.wikipedia.org/wiki/Longest_increasing_subsequence)

## 👨‍💻 Author

**marlonco** - 42 School Project

---

**Note:** This implementation focuses on achieving optimal performance through strategic use of LIS, chunking, and cost-based insertion, resulting in operation counts that consistently meet or exceed competitive benchmarks.
