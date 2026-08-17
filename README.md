# Problem Setting

A collection of original competitive programming problems with official solutions, editorials, test generators, validators, and test cases.

## Repository Structure

```text
problem-setting/
│
├── README.md
│
├── problem-001/
│   ├── statement.md
│   ├── editorial.md
│   ├── solution.cpp
│   ├── brute.cpp
│   ├── generator.cpp
│   ├── validator.cpp
│   └── tests/
│       ├── 01.in
│       ├── 01.out
│       ├── 02.in
│       ├── 02.out
│       └── ...
│
├── problem-002/
│   └── ...
│
└── ...
```

## Files

### `statement.md`

Contains the complete problem statement.

This includes:

- Problem description
- Input format
- Output format
- Constraints
- Examples
- Notes and clarifications

If you want to solve a problem, **start with this file**.

---

### `editorial.md`

Contains the official explanation of the intended solution.

This includes:

- Key observations
- Approach
- Algorithm
- Correctness proof
- Time complexity
- Space complexity
- Implementation details

Try solving the problem yourself before reading the editorial.

---

### `solution.cpp`

The official optimized C++ solution.

This is the reference implementation of the intended solution.

It can be used to:

- Verify your own solution
- Understand the intended approach
- Check the required complexity
- Generate expected outputs

---

### `brute.cpp`

A simple and slow but reliable solution.

The brute-force solution is primarily used for testing.

It should be easy to understand and independently verify.

For small test cases, the brute solution and the official solution can be run together and their outputs compared.

---

### `generator.cpp`

Generates test cases automatically.

A generator can produce:

- Random cases
- Small cases
- Edge cases
- Boundary cases
- Maximum-size cases
- Adversarial cases

This is useful for stress testing the official solution.

---

### `validator.cpp`

Checks whether a test case is a valid input according to the problem constraints.

For example, if the problem has:

```text
1 <= N <= 200000
1 <= Ai <= 1000000000
```

the validator ensures that generated or manually created inputs satisfy these constraints.

The validator checks **input validity**, not whether a solution is correct.

---

### `tests/`

Contains prepared test cases and their expected outputs.

```text
tests/
├── 01.in
├── 01.out
├── 02.in
├── 02.out
└── ...
```

Each `.in` file contains an input and the corresponding `.out` file contains the expected output.

Tests should cover:

- Sample cases
- Minimum cases
- Maximum cases
- Edge cases
- Special cases
- Random cases
- Adversarial cases

## How to Solve a Problem

If you are solving a problem, you only need to start with:

```text
statement.md
```

### Step 1 — Read the Statement

Understand:

- What is being asked?
- What are the constraints?
- What is the input format?
- What is the output format?

Try to solve the problem without looking at the other files.

### Step 2 — Implement Your Solution

Write your own solution in C++.

```cpp
// your solution
```

Test it against the examples provided in `statement.md`.

### Step 3 — Test Your Solution

Use the test cases in:

```text
tests/
```

Run your solution against the `.in` files and compare your output with the corresponding `.out` files.

### Step 4 — Compare With the Official Solution

After solving the problem, compare your approach with:

```text
solution.cpp
```

Check:

- Correctness
- Time complexity
- Space complexity
- Implementation details

### Step 5 — Read the Editorial

If you were stuck or want to understand the intended solution, read:

```text
editorial.md
```

The editorial explains the reasoning and algorithm behind the official solution.

## Testing Workflow

The problem-setting testing workflow is:

```text
                  generator.cpp
                       │
                       ▼
                   Test Case
                       │
                       ▼
                  validator.cpp
                       │
                  Valid Input?
                   /       \
                 No         Yes
                 │           │
                 ▼           ▼
               Reject    Run Solutions
                           /       \
                          ▼         ▼
                     brute.cpp  solution.cpp
                          │         │
                          └────┬────┘
                               ▼
                         Compare Outputs
                           /       \
                        Match    Mismatch
                          │          │
                          ▼          ▼
                        Pass     Investigate
```

## Stress Testing

A typical stress-testing process is:

```text
Generate random test
        │
        ▼
Validate input
        │
        ▼
 ┌──────┴──────┐
 ▼             ▼
brute.cpp   solution.cpp
 │             │
 └──────┬──────┘
        ▼
 Compare outputs
        │
   ┌────┴────┐
   ▼         ▼
 Same     Different
   │         │
   ▼         ▼
 Pass      Bug found
```

The brute solution provides an independently computed answer for small cases.

If `brute.cpp` and `solution.cpp` produce different outputs, the test should be investigated before publishing the problem.

## Problem Setter Workflow

The recommended workflow for creating a new problem is:

```text
Problem Idea
     │
     ▼
Write statement.md
     │
     ▼
Write brute.cpp
     │
     ▼
Write solution.cpp
     │
     ▼
Write generator.cpp
     │
     ▼
Write validator.cpp
     │
     ▼
Stress Test
     │
     ▼
Create Curated Tests
     │
     ▼
Write editorial.md
     │
     ▼
Publish
```

## Important Principle

A problem solver should be able to solve the problem using **only `statement.md`**.

The other files exist for testing, verification, and post-solve reference.

```text
                  SOLVER
                    │
                    ▼
              statement.md
                    │
                    ▼
              Your Solution
                    │
                    ▼
                Tests
                    │
                    ▼
                 AC / WA


                  SETTER
                    │
        ┌───────────┼───────────┐
        ▼           ▼           ▼
    brute.cpp   generator.cpp  validator.cpp
        │           │           │
        └───────────┼───────────┘
                    ▼
               solution.cpp
                    │
                    ▼
              Stress Testing
                    │
                    ▼
              editorial.md
```

## Goal

The goal of this repository is to maintain a collection of original, well-tested competitive programming problems with:

- Clear problem statements
- Correct and efficient solutions
- Reliable test generation
- Input validation
- Stress testing
- Detailed editorials

Each problem should be independently solvable, testable, and reproducible.
