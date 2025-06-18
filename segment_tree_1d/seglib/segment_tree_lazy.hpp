#pragma once
#include <vector>
#include <climits>
#include <iostream>

namespace seglib {

class SegmentTreeLazy {
    std::vector<int> tree, lazy;
    int n, type;
    bool isAdd;

    int identity() {
        if (type == 0) return 0;
        if (type == 1) return INT_MIN;
        if (type == 2) return INT_MAX;
        return 0;
    }

    int merge(int a, int b) {
        if (type == 0) return a + b;
        if (type == 1) return std::max(a, b);
        if (type == 2) return std::min(a, b);
        return 0;
    }

    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            if (isAdd) {
                tree[node] += (end - start + 1) * lazy[node];
            } else {
                tree[node] = (end - start + 1) * lazy[node];
            }

            if (start != end) {
                if (isAdd) {
                    lazy[2 * node] += lazy[node];
                    lazy[2 * node + 1] += lazy[node];
                } else {
                    lazy[2 * node] = lazy[node];
                    lazy[2 * node + 1] = lazy[node];
                }
            }
            lazy[node] = 0;
        }
    }

    void build(std::vector<int> &arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = (start + end) / 2;
        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int start, int end, int l, int r, int val) {
        push(node, start, end);
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            lazy[node] = val;
            push(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        update(2 * node, start, mid, l, r, val);
        update(2 * node + 1, mid + 1, end, l, r, val);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    int query(int node, int start, int end, int l, int r) {
        push(node, start, end);
        if (r < start || end < l) return identity();
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        return merge(
            query(2 * node, start, mid, l, r),
            query(2 * node + 1, mid + 1, end, l, r)
        );
    }

public:
    SegmentTreeLazy(std::vector<int> &arr, int t, bool is_add = true) : n(arr.size()), type(t), isAdd(is_add) {
        tree.assign(4 * n, identity());
        lazy.assign(4 * n, 0);
        build(arr, 1, 0, n - 1);
    }

    void range_update(int l, int r, int val, bool add_op = false) {
        isAdd = add_op; 
        update(1, 0, n - 1, l, r, val);
    }

    int range_query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    void display() {
        for (int i = 1; i < 4 * n; ++i) std::cout << tree[i] << " ";
        std::cout << "\n";
    }
};

}
