# Range-Query-Engine


The primary objective of this project is to deeply understand and implement one of the most powerful and versatile data structures in computer science — Segment Tree.

This project focuses on building a comprehensive understanding of Segment Trees, starting from their basic implementation to more advanced variants.
It includes:

1. Basic Segment Trees for common operations like sum, min, max, etc.

2. Lazy Segment Trees for efficient range updates.

3. Two practical applications:

3.1. Maximum Subarray Sum using Kadane’s logic via Segment Trees

3.2. Finding the Next Greater Element in a range

4. To take it further, the project also includes an implementation of 2D Segment Trees for performing range queries over matrices.



---

##  Features

### 1. Basic Segment Tree
Supports point updates and range queries for:
- Sum
- Maximum
- Minimum
- GCD
- XOR
- OR
- AND
- Product

 **Time Complexity:**
- Build: `O(n)`
- Point Update: `O(log n)`
- Range Query: `O(log n)`

---

### 2. Lazy Segment Tree (Range Updates)
Optimized for range updates and range queries using lazy propagation. Supports:
- **Set** operation on a range
- **Add** operation on a range (for additive types)

 **Time Complexity:**
- Build: `O(n)`
- Range Update: `O(log n)`
- Range Query: `O(log n)`

---

### 3. Kadane's Segment Tree (Max Subarray Sum in Range)
A specialized segment tree where each node stores:
- Total sum of the range
- Maximum prefix sum
- Maximum suffix sum
- Maximum subarray sum

Useful for:
- Queries of the maximum subarray sum in a given range

 **Time Complexity:**
- Build: `O(n)`
- Point Update: `O(log n)`
- Range Query: `O(log n)`

---

###  4. Next Greater Value in Range
Allows finding the **smallest number ≥ x** in a subrange `[l, r]` of an array.

 Implementation:
- Each node stores a sorted list (merge sort tree)
- Binary search is used to answer range queries

 **Time Complexity:**
- Build: `O(n log n)`
- Point Update: `O(log² n)`
- Range Query: `O(log n)`

---

### 2D Segment Tree (Grid Queries)
Extends segment trees to two dimensions to support:
- Minimum
- Maximum
- Sum

 Applications:
- Range queries over 2D matrices (like maps, images, game grids)

 **Time Complexity:**
- Build: `O(n * m * log n * log m)`
- Query: `O(log n * log m)`
- Update: `O(log n * log m)`

---

## 📁 File Structure

```bash(for 1-d segment tree)
seglib/
├── segment_tree_basic.hpp       # Basic segment tree operations
├── segment_tree_lazy.hpp        # Lazy propagation for range updates
├── segment_tree_kadane.hpp      # Kadane’s algorithm via segment tree
├── segment_tree_next_greater.hpp # Query for next greater value in a range
└── seglib.h                     # Master header to include all
