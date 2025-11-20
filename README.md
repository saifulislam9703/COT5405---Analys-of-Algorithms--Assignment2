# COT5405 - Analysis of Algorithms: Assignment 2

This repository contains the solutions for **Assignment 2** of COT5405 - Analysis of Algorithms. The assignment focuses on designing, implementing, and analyzing **Dynamic Programming (DP) algorithms** for two distinct problems:

1. **Weighted Approximate Common Substring**  
2. **Largest Zero Submatrix**

---

## Repository Structure

assignment2-dp/
│
├─ DP1.cpp # Implementation of Weighted Approximate Common Substring
├─ DP2.cpp # Implementation of Largest Zero Submatrix
├─ helper.h # Helper functions for random data generation, matrix printing
├─ DP1.exe # Compiled executable for DP1 (optional)
├─ DP2.exe # Compiled executable for DP2 (optional)
└─ README.md

---

## Problem 1: Weighted Approximate Common Substring

- **Description:** Given two strings `S` and `T`, find a contiguous substring present in both strings with the maximum score. Score is defined as the sum of weights for character matches minus a penalty for mismatches.
- **Algorithm:** Dynamic Programming using a 2D DP table to compute maximum substring scores.
- **Complexity:**  
  - Time: `O(n * m)`  
  - Space: `O(n * m)` (can be optimized to `O(min(n,m))`)

### How to Run
- **Problem 1**
```bash
g++ -std=c++17 -O2 DP1.cpp -o DP1.exe
./DP1.exe
```

- **Problem 2**
  ```bash
  g++ -std=c++17 -O2 DP2.cpp -o DP2.exe
  ./DP2.exe
```

