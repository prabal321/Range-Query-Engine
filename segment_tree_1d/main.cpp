#include <iostream>
#include <vector>
#include "seglib/seglib.h"

using namespace std;
using namespace seglib;

bool is_additive(int type) {
    return type == 0 || type == 4 || type == 5 || type == 6;
}

int main() {
    cout << "Welcome to Segment Tree Tester!" << endl;
    cout << "Enter the size of the array: ";
    int n; cin >> n;

    vector<int> arr(n);
    cout << "Enter the array elements:\n";
    for (int i = 0; i < n; ++i) cin >> arr[i];

    cout << "\nChoose Segment Tree Type:\n";
    cout << "1: Basic Segment Tree\n";
    cout << "2: Lazy Segment Tree (Add/Set Range Updates)\n";
    cout << "3: Kadane Segment Tree (Max Subarray Sum in Range)\n";
    cout << "4: Next Greater Element in Range\n";
    cout << "Your choice: ";

    int choice; cin >> choice;

    if (choice == 1) {
        cout << "\nChoose Operation Type for Basic Segment Tree (array is 0-based indexed):\n";
        cout << "0: Sum\n1: Max\n2: Min\n3: GCD\n4: XOR\n5: OR\n6: AND\n7: Product\n";
        int type; cin >> type;

        SegmentTreeBasic st(arr, type);

        cout << "\nQuery Format:\n+ idx val (point update)\n? l r (range query)\n"<<endl;
        if (is_additive(type)) {
            cout << "Update Queries are of two types:\n1. Set the value at the index\n2. Increase the value at the index\n\n";
        } else {
            cout << "Only set type update queries are supported\n\n";
        }

        int q; cout << "Enter number of queries: "; cin >> q;

        while (q--) {
            char op; cin >> op;
            if (op == '+') {
                int idx, val; cin >> idx >> val;
                if (!is_additive(type)) {
                    st.point_update(idx, val, false);
                } else {
                    cout << "1: Set | 2: Add => ";
                    int t; cin >> t;
                    st.point_update(idx, val, t == 2);
                }
            } else if (op == '?') {
                int l, r; cin >> l >> r;
                cout << "Query result: " << st.range_query(l, r) << "\n";
            }
        }

    } else if (choice == 2) {
        cout << "\nChoose Operation Type for Lazy Segment Tree (array is 0-based indexed):\n";
        cout << "0: Sum\n1: Max\n2: Min\n";
        int type; cin >> type;
        bool isAdd = (type == 0); // only sum supports add

        SegmentTreeLazy st(arr, type);

        cout << "\nQuery Format:\n+ l r val (range update)\n? l r (range query)\n";

        if (isAdd) {
            cout << "Update Queries are of two types:\n1. Set the range to a value\n2. Add to all elements in range\n\n";
        } else {
            cout << "Only set type update queries are supported\n\n";
        }

        int q; cout << "Enter number of queries: "; cin >> q;

        while (q--) {
            char op; cin >> op;
            if (op == '+') {
                int l, r, val; cin >> l >> r >> val;
                if (isAdd) {
                    cout << "1: Set | 2: Add => ";
                    int t; cin >> t;
                    st.range_update(l, r, val, t == 2);
                } else {
                    st.range_update(l, r, val, false);
                }
            } else if (op == '?') {
                int l, r; cin >> l >> r;
                cout << "Query result: " << st.range_query(l, r) << "\n";
            }
        }

    } else if (choice == 3) {
        SegmentTreeKadane st(arr);

        cout << "\nQuery Format:\n+ idx val (point update and set to the given value)\n? l r (max subarray sum in range)\n (array is 0-based indexed)\n";
        int q; cout << "Enter number of queries: "; cin >> q;

        while (q--) {
            char op; cin >> op;
            if (op == '+') {
                int idx, val; cin >> idx >> val;
                st.point_update(idx, val);
            } else if (op == '?') {
                int l, r; cin >> l >> r;
                cout << "Max Subarray Sum: " << st.range_query(l, r) << "\n";
            }
        }

    } else if (choice == 4) {
    SegmentTreeNextGreater st(arr);

    cout << "\nQuery Format:\n+ idx val (point update)\n? l r x (find minimum value >= x in range)\n(array is 0-based indexed)\n";
    cout << "Update Queries are of two types:\n1. Set the value at the index\n2. Add to the current value at the index\n\n";

    int q; cout << "Enter number of queries: "; cin >> q;

    while (q--) {
        char op; cin >> op;
        if (op == '+') {
            int idx, val; cin >> idx >> val;
            cout << "1: Set | 2: Add => ";
            int t; cin >> t;
            st.point_update(idx, val, t == 2);
        } else if (op == '?') {
            int l, r, x; cin >> l >> r >> x;
            int result = st.range_query(l, r, x);
            cout << result << '\n';  
        } else if (op == 'd') {
            st.display();
        }
    }
}
 else {
        cout << "Invalid choice.\n";
    }

    cout << "\nProgram ended. Thank you!\n";
    return 0;
}
