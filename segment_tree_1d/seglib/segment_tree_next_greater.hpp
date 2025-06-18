#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

namespace seglib {

class SegmentTreeNextGreater {
private:
    int n;
    vector<vector<int>> tree;
    vector<int> a;

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = {a[l]};
            return;
        }
        int mid = (l + r) / 2;
        build(2 * node, l, mid);
        build(2 * node + 1, mid + 1, r);
        merge(tree[2 * node].begin(), tree[2 * node].end(),
              tree[2 * node + 1].begin(), tree[2 * node + 1].end(),
              back_inserter(tree[node]));
    }

    bool query(int node, int l, int r, int ql, int qr, int x) {
        if (r < ql || l > qr) return false;
        if (ql <= l && r <= qr) {
            auto it = lower_bound(tree[node].begin(), tree[node].end(), x);
            return it != tree[node].end();
        }
        int mid = (l + r) / 2;
        return query(2 * node, l, mid, ql, qr, x) ||
               query(2 * node + 1, mid + 1, r, ql, qr, x);
    }


    int query_value(int node, int l, int r, int ql, int qr, int x) {
    if (r < ql || l > qr) return -1;
    if (ql <= l && r <= qr) {
        auto it = lower_bound(tree[node].begin(), tree[node].end(), x);
        return (it != tree[node].end()) ? *it : -1;
    }
    int mid = (l + r) / 2;
    int left = query_value(2 * node, l, mid, ql, qr, x);
    int right = query_value(2 * node + 1, mid + 1, r, ql, qr, x);

    if (left != -1 && right != -1) return min(left, right);
    return (left != -1) ? left : right;
}


    void update(int node, int l, int r, int idx, int oldVal, int newVal) {
        auto it = lower_bound(tree[node].begin(), tree[node].end(), oldVal);
        if (it != tree[node].end() && *it == oldVal) {
            tree[node].erase(it);
        }
        tree[node].insert(lower_bound(tree[node].begin(), tree[node].end(), newVal), newVal);

        if (l == r) return;

        int mid = (l + r) / 2;
        if (idx <= mid)
            update(2 * node, l, mid, idx, oldVal, newVal);
        else
            update(2 * node + 1, mid + 1, r, idx, oldVal, newVal);
    }

public:
    SegmentTreeNextGreater(vector<int>& input) {
        a = input;
        n = a.size();
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }

    // Add or set value based on isAdd flag
    void point_update(int idx, int val, bool isAdd) {
        int oldVal = a[idx];
        if (isAdd) {
            a[idx] += val;
        } else {
            a[idx] = val;
        }
        update(1, 0, n - 1, idx, oldVal, a[idx]);
    }

   int range_query(int l, int r, int x) {
    return query_value(1, 0, n - 1, l, r, x);
}

    void display(int node = 1, int l = 0, int r = -1) {
        if (r == -1) r = n - 1;
        cout << "Node [" << l << ", " << r << "]: ";
        for (int val : tree[node]) cout << val << " ";
        cout << '\n';
        if (l == r) return;
        int mid = (l + r) / 2;
        display(2 * node, l, mid);
        display(2 * node + 1, mid + 1, r);
    }
};

} 
