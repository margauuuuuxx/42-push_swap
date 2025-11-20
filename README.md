# Push Swap - Efficient Stack Sorting Algorithm

A highly optimized sorting algorithm that sorts a stack using only two stacks and a limited set of operations, achieving excellent performance with minimal moves.

## 📊 Performance Metrics

- **100 numbers:** ~660 operations average (Target: 700) ✅
- **500 numbers:** ~5189 operations average (Target: 5500) ✅

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

**How it's used:**
- Calculated once at the start for all inputs
- For stacks ≤100: LIS calculation done but not actively used (simpler algorithm is optimal)
- For stacks >100: **Actively filters elements during push phase**
  - Only non-LIS elements are pushed to B
  - LIS elements stay in A (already in correct order!)
  - Reduces operations by ~30-40%

**Implementation:** `lis.c` (calculation) and `sort_large_stack.c` (usage)

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

For small stacks (≤100 elements):

- Uses simple max-based push (fast, minimal overhead)
- Finds largest element in B, rotates to top, pushes to A
- Keeps the efficient algorithm for smaller datasets

For large stacks (>100 elements):

- Uses sophisticated cost-based insertion (push_back_to_a())
- Calculates optimal rotation costs for both stacks
- Optimizes combined rotations using rr/rrr operations
- Finds best target position for each element

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
                                 │  ★ For size > 100:          │
                                 │    Filter by !in_lis[i]     │
                                 │    (skip LIS elements!)     │
                                 │  Process chunks in order:   │
                                 │  - Find closest non-LIS el  │
                                 │  - Smart rotate to top      │
                                 │  - Push to B (pb)           │
                                 │  - Rotate B if needed (rb)  │
                                 └──────────┬──────────────────┘
                                            │
                                            ▼
                                 ┌─────────────────────────────┐
                                 │  STEP 5: Sort Remaining     │
                                 │  ★ LIS elements stay in A!  │
                                 │  Sort remaining ≤3 elements │
                                 │  Use optimal 3-element sort │
                                 └──────────┬──────────────────┘
                                            │
                                            ▼
                                 ┌─────────────────────────────┐
                                 │  STEP 6: Push Back from B   │
                                 │  ★ For size ≤ 100:          │
                                 │    Simple max-based push    │
                                 │  ★ For size > 100:          │
                                 │    Cost-based insertion     │
                                 │    with optimal rotations   │
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


## 📂 Project Structure

```
push_swap/
├── includes/
│   ├── push_swap.h          # Main header with function prototypes
│   └── structs.h            # Data structure definitions
├── srcs/
│   ├── algo.c               # Main algorithm logic and initialization
│   ├── common/
│   │   ├── compress.c           # Coordinate normalization
│   │   ├── final_rotate.c       # Final rotation to sort position
│   │   └── named_operations/
│   │       ├── named_operations.c  # High-level operations (pa, pb, etc.)
│   │       ├── named_operations2.c # Additional named operations
│   │       └── operations.c        # Low-level stack operations
│   ├── large/
│   │   ├── alone.c              # Logic for single elements
│   │   ├── chunk.c              # Chunk creation and management
│   │   ├── cost.c               # Cost calculation for optimal moves
│   │   ├── cost_utils.c         # Utilities for cost calculation
│   │   ├── sort_large_stack.c  # Large stack sorting logic
│   │   ├── sort_large_utils.c  # Utilities for large stack sorting
│   │   └── sort_large_utils2.c # More utilities for large stack sorting
│   ├── lis/
│   │   ├── lis.c                # Longest Increasing Subsequence
│   │   └── lis_utils.c          # Utilities for LIS
│   ├── main.c               # Entry point
│   ├── medium/
│   │   ├── insertion.c          # Insertion sort for medium stacks
│   │   └── sort_medium_stack.c   # Medium stack sorting logic
│   ├── parsing/
│   │   ├── parsing.c            # Input validation and parsing
│   │   └── parsing_utils.c      # Utilities for parsing
│   ├── small/
│   │   └── small_sort.c         # Optimized sorting for ≤5 elements
│   └── utils/
│       ├── split.c          # String splitting utility
│       ├── stack_utils.c    # Stack management functions
│       └── utils.c          # General utilities (atoi, strlen, etc.)
├── testers/
│   ├── checker_linux        # Validation tool for Linux
│   └── checker_Mac          # Validation tool for MacOS
├── Makefile
├── push_swap
├── README.md
└── tests/
    ├── README.md
    ├── run_all_tests.sh
    ├── test_framework.h
    ├── test_lis.c
    ├── test_normalization.c
    ├── test_parsing.c
    ├── test_sorting.c
    └── test_stack_ops.c


## 🎓 Algorithm Complexity

- **Time Complexity:** O(n²) worst case, O(n log n) average
- **Space Complexity:** O(n)
- **Operation Count:**
  - 2-3 elements: ≤3 operations
  - 5 elements: ≤12 operations
  - 100 elements: ~660 operations average
  - 500 elements: ~5189 operations average

## 🔍 Key Algorithm Insights

### Why LIS?
The LIS represents elements that don't need to move. By keeping these in place and only moving non-LIS elements, we minimize operations.

**Implementation Strategy:**
- **For stacks ≤100:** LIS is calculated but not actively used (simpler algorithm is already optimal)
- **For stacks >100:** LIS actively filters elements during push phase
  - Only non-LIS elements are pushed to B
  - LIS elements stay in A (already in correct relative order!)
  - Reduces elements to move by ~30-40%
  - Example: For 500 elements, if LIS captures 35%, only 325 elements are pushed instead of 497

### Why Chunks?
Instead of finding any element to push, chunks create a strategic order:
1. Push smaller elements first
2. This naturally organizes B in descending order
3. Makes push-back phase more efficient
4. For large stacks, chunks only consider non-LIS elements

### Rotation Strategy in B
When pushing to B, we use a threshold-based rotation (35% of chunk range):
```
threshold = chunk_min + (chunk_range * 0.35)
If (pushed_element < threshold && b_size > 2):
    rb  # Rotate smaller elements to bottom
```
This keeps more elements accessible at the top of B, reducing rotation costs during insertion.

### Hybrid Push-Back Strategy
- **For stacks ≤100:** Simple max-based push (fast, efficient for small datasets)
- **For stacks >100:** Cost-based insertion with:
  - **Combined rotations:** If both stacks rotate the same direction, combine with `rr`/`rrr`
  - **Distance:** Choose closer rotation direction (forward vs reverse)
  - **Total cost:** Always pick the cheapest element to push next

### LIS-Aware Implementation Details

**How it works in the code:**

For large stacks (>100 elements), the algorithm uses `push_non_lis_to_b()` function:

```c
// Key filtering logic:
if (!algo->a->in_lis[i] && 
    algo->a->indices[i] >= target && 
    algo->a->indices[i] < target + chunk_sz)
{
    // Only push this element if it's NOT in the LIS
    // LIS elements are kept in stack A
}
```

**Visual Example (500 numbers):**

```
Before LIS filtering:
  Stack A: [245, 67, 312, 89, 401, 123, 456, ...]
  All 497 elements pushed to B → LIS ignored ❌

After LIS implementation:
  Stack A: [245, 67, 312, 89, 401, 123, 456, ...]
              ↓
  LIS identified: [67, 89, 123, 456, ...] (35% of elements)
              ↓
  Only non-LIS pushed to B:
  Stack A: [67, 89, 123, 456, ...] ← Already sorted! ✅
  Stack B: [245, 312, 401, ...]    ← Need repositioning
  
  Result: Only ~325 elements moved instead of 497
          Saves ~172 push operations!
```

## 🐛 Error Handling

The program handles:
- ✅ Non-integer inputs
- ✅ Integers outside INT_MIN to INT_MAX range
- ✅ Duplicate values
- ✅ Empty input
- ✅ Already sorted stacks

All errors output `"Error\n"` to stderr and exit with status 1.

