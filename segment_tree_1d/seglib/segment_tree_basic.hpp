#pragma once
#include <vector>
#include <climits>
#include <iostream>

namespace seglib {

class SegmentTreeBasic {
    std::vector<int> segTree;
    int n, type;

    int compute_gcd(int a, int b) {
        return b == 0 ? a : compute_gcd(b, a % b);
    }

    int merge(int a, int b) {
        if (type == 0) return a + b;
        if (type == 1) return std::max(a, b);
        if (type == 2) return std::min(a, b);
        if (type == 3) return compute_gcd(a, b);
        if (type == 4) return a ^ b;
        if (type == 5) return a | b;
        if (type == 6) return a & b;
        if (type == 7) return a * b;
        return 0;
    }

    int identity() {
        if (type == 0) return 0;
        if (type == 1) return INT_MIN;
        if (type == 2) return INT_MAX;
        if (type == 3) return 0;
        if (type == 4 || type == 5) return 0;
        if (type == 6) return -1;
        if (type == 7) return 1;
        return 0;
    }

    void build(std::vector<int> &arr, int node, int start, int end) {
        if (start == end) {
            segTree[node] = arr[start];
            return;
        }
        int mid = (start + end) / 2;
        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        segTree[node] = merge(segTree[2 * node], segTree[2 * node + 1]);
    }

    void update(int node, int start, int end, int idx, int val, bool isAdd) {
        if (start == end) {
            segTree[node] = isAdd ? segTree[node] + val : val;
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid) update(2 * node, start, mid, idx, val, isAdd);
        else update(2 * node + 1, mid + 1, end, idx, val, isAdd);
        segTree[node] = merge(segTree[2 * node], segTree[2 * node + 1]);
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return identity();
        if (l <= start && end <= r) return segTree[node];
        int mid = (start + end) / 2;
        return merge(
            query(2 * node, start, mid, l, r),
            query(2 * node + 1, mid + 1, end, l, r)
        );
    }

public:
    SegmentTreeBasic(std::vector<int> &arr, int t) : type(t), n(arr.size()) {
        segTree.assign(4 * n, identity());
        build(arr, 1, 0, n - 1);
    }

    void point_update(int idx, int val, bool isAdd = true) {
        update(1, 0, n - 1, idx, val, isAdd);
    }

    int range_query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    void display() {
        for (int i = 1; i < 4 * n; ++i) std::cout << segTree[i] << " ";
        std::cout << "\n";
    }
};

} 
