#pragma once
#include <vector>
#include <algorithm>
using namespace std;

namespace seglib {

struct Node {
    long long total, prefix, suffix, max_sum;
};

class SegmentTreeKadane {
private:
    int n;
    vector<Node> tree;

    Node make_node(int val) {
        return {val, val, val, val};
    }

    Node merge(Node left, Node right) {
        Node res;
        res.total = left.total + right.total;
        res.prefix = max(left.prefix, left.total + right.prefix);
        res.suffix = max(right.suffix, right.total + left.suffix);
        res.max_sum = max({left.max_sum, right.max_sum, left.suffix + right.prefix});
        return res;
    }

    void build(vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = make_node(arr[start]);
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node, start, mid);
            build(arr, 2 * node + 1, mid + 1, end);
            tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
        }
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = make_node(val);
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid)
                update(2 * node, start, mid, idx, val);
            else
                update(2 * node + 1, mid + 1, end, idx, val);
            tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
        }
    }

    Node query(int node, int start, int end, int l, int r) {
        if (r < start || end < l)
            return make_node(-1e9); 
        if (l <= start && end <= r)
            return tree[node];
        int mid = (start + end) / 2;
        Node left = query(2 * node, start, mid, l, r);
        Node right = query(2 * node + 1, mid + 1, end, l, r);
        return merge(left, right);
    }

public:
    SegmentTreeKadane(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }

    void point_update(int idx, int val) {
        update(1, 0, n - 1, idx, val);
    }

    long long range_query(int l, int r) {
        return query(1, 0, n - 1, l, r).max_sum;
    }
};

} 
