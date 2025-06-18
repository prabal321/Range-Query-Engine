#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> segTree2D;
int seg_type;
int R, C;

int compute_gcd(int a, int b) {
    return b == 0 ? a : compute_gcd(b, a % b);
}

bool is_additive() {
    return seg_type == 0 || seg_type == 4 || seg_type == 5 || seg_type == 6;
}

int merge(int a, int b) {
    switch(seg_type) {
        case 0: return a + b;
        case 1: return max(a, b);
        case 2: return min(a, b);
        case 3: return compute_gcd(a, b);
        case 4: return a ^ b;
        case 5: return a | b;
        case 6: return a & b;
        case 7: return a * b;
        default: return 0;
    }
}

int identity() {
    switch(seg_type) {
        case 0: return 0;
        case 1: return INT_MIN;
        case 2: return INT_MAX;
        case 3: return 0;
        case 4: case 5: return 0;
        case 6: return ~0;
        case 7: return 1;
        default: return 0;
    }
}

void build_y(vector<vector<int>>& matrix, int node_x, int start_x, int end_x, int node_y, int start_y, int end_y) {
    if (start_y == end_y) {
        if (start_x == end_x) {
            segTree2D[node_x][node_y] = matrix[start_x][start_y];
        } else {
            segTree2D[node_x][node_y] = merge(segTree2D[2 * node_x][node_y], segTree2D[2 * node_x + 1][node_y]);
        }
    } else {
        int mid_y = (start_y + end_y) / 2;
        build_y(matrix, node_x, start_x, end_x, 2 * node_y, start_y, mid_y);
        build_y(matrix, node_x, start_x, end_x, 2 * node_y + 1, mid_y + 1, end_y);
        segTree2D[node_x][node_y] = merge(segTree2D[node_x][2 * node_y], segTree2D[node_x][2 * node_y + 1]);
    }
}

void build_x(vector<vector<int>>& matrix, int node_x, int start_x, int end_x) {
    if (start_x != end_x) {
        int mid_x = (start_x + end_x) / 2;
        build_x(matrix, 2 * node_x, start_x, mid_x);
        build_x(matrix, 2 * node_x + 1, mid_x + 1, end_x);
    }
    build_y(matrix, node_x, start_x, end_x, 1, 0, C - 1);
}

void update_y(int node_x, int start_x, int end_x, int node_y, int start_y, int end_y, int x, int y, int val, bool is_add) {
    if (start_y == end_y) {
        if (start_x == end_x) {
            if (is_add) {
                segTree2D[node_x][node_y] += val;
            } else {
                segTree2D[node_x][node_y] = val;
            }
        } else {
            segTree2D[node_x][node_y] = merge(segTree2D[2 * node_x][node_y], segTree2D[2 * node_x + 1][node_y]);
        }
    } else {
        int mid_y = (start_y + end_y) / 2;
        if (y <= mid_y) {
            update_y(node_x, start_x, end_x, 2 * node_y, start_y, mid_y, x, y, val, is_add);
        } else {
            update_y(node_x, start_x, end_x, 2 * node_y + 1, mid_y + 1, end_y, x, y, val, is_add);
        }
        segTree2D[node_x][node_y] = merge(segTree2D[node_x][2 * node_y], segTree2D[node_x][2 * node_y + 1]);
    }
}

void update_x(int node_x, int start_x, int end_x, int x, int y, int val, bool is_add) {
    if (start_x != end_x) {
        int mid_x = (start_x + end_x) / 2;
        if (x <= mid_x) {
            update_x(2 * node_x, start_x, mid_x, x, y, val, is_add);
        } else {
            update_x(2 * node_x + 1, mid_x + 1, end_x, x, y, val, is_add);
        }
    }
    update_y(node_x, start_x, end_x, 1, 0, C - 1, x, y, val, is_add);
}

int query_y(int node_x, int node_y, int start_y, int end_y, int y1, int y2) {
    if (y2 < start_y || end_y < y1) return identity();
    if (y1 <= start_y && end_y <= y2) return segTree2D[node_x][node_y];
    int mid_y = (start_y + end_y) / 2;
    return merge(query_y(node_x, 2 * node_y, start_y, mid_y, y1, y2),
                 query_y(node_x, 2 * node_y + 1, mid_y + 1, end_y, y1, y2));
}

int query_x(int node_x, int start_x, int end_x, int x1, int x2, int y1, int y2) {
    if (x2 < start_x || end_x < x1) return identity();
    if (x1 <= start_x && end_x <= x2) return query_y(node_x, 1, 0, C - 1, y1, y2);
    int mid_x = (start_x + end_x) / 2;
    return merge(query_x(2 * node_x, start_x, mid_x, x1, x2, y1, y2),
                 query_x(2 * node_x + 1, mid_x + 1, end_x, x1, x2, y1, y2));
}

void display_segment_tree() {
    cout << "\nFinal 2D Segment Tree Structure:\n";
    cout << "--------------------------------\n";
    for (int i = 1; i < 4 * R; i++) {
        if (segTree2D[i][1] == identity()) continue;
        cout << "Row Node " << i << " [";
        for (int j = 1; j < 4 * C; j++) {
            if (segTree2D[i][j] != identity()) {
                cout << segTree2D[i][j];
                if (j < 4 * C - 1 && segTree2D[i][j + 1] != identity()) cout << " ";
            }
        }
        cout << "]\n";
    }
    cout << "--------------------------------\n";
}

int main() {
    cout << "Enter number of rows and columns: ";
    cin >> R >> C;

    vector<vector<int>> matrix(R, vector<int>(C));
    cout << "Enter the matrix (" << R << " x " << C << "):\n";
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cin >> matrix[i][j];
        }
    }

    cout << "\nChoose Segment Tree Type:\n";
    cout << "0: Sum\n1: Max\n2: Min\n3: GCD\n4: XOR\n5: OR\n6: AND\n7: Product\n";
    cin >> seg_type;

    segTree2D.assign(4 * R, vector<int>(4 * C, identity()));
    build_x(matrix, 1, 0, R - 1);

    int q;
    cout << "Enter number of queries: ";
    cin >> q;

    cout << "\nQuery Format:\n";
    cout << "+ x y val\n";
    cout << "? x1 x2 y1 y2\n";

    if (is_additive()) {
        cout << "Two kinds of point update queries can be made:\n";
        cout << "1: Set value at a given index\n";
        cout << "2: Add to value at index\n";
    } else {
        cout << "Only set update is available (non-additive operation).\n";
    }

    while (q--) {
        char ch;
        cin >> ch;
        if (ch == '+') {
            int x, y, val;
            cin >> x >> y >> val;
            if (is_additive()) {
                int choice;
                cin >> choice;
                if (choice == 1) {
                    int current = query_x(1, 0, R - 1, x, x, y, y);
                    update_x(1, 0, R - 1, x, y, val - current, true);
                } else if (choice == 2) {
                    update_x(1, 0, R - 1, x, y, val, true);
                } else {
                    cout << "Invalid choice. Skipping update.\n";
                }
            } else {
                update_x(1, 0, R - 1, x, y, val, false);
            }
        } else if (ch == '?') {
            int x1, x2, y1, y2;
            cin >> x1 >> x2 >> y1 >> y2;
            cout << query_x(1, 0, R - 1, x1, x2, y1, y2) << "\n";
        }
    }

    display_segment_tree();
    return 0;
}
