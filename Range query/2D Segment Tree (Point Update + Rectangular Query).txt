/////////////// 2D Segment Tree (Point Update + Rectangular Query) ///////////////
#pragma once
#include <vector>
#include <cassert>
using namespace std;

// ========== 2D Segment Tree (Point Update + Rectangular Query) ==========
// Generic template: customize Node, MergeFn, Identity

template<typename Node, class MergeFn>
class SegmentTree2D {
    int n, m;
    vector<vector<Node>> tree;
    MergeFn merge;
    Node ID;

public:
    // data: n x m matrix
    // _merge: function to combine two Nodes
    // _id: identity element for merge
    SegmentTree2D(const vector<vector<Node>>& data,
                  MergeFn _merge,
                  Node _id)
        : merge(_merge), ID(_id)
    {
        n = data.size();
        m = n ? data[0].size() : 0;
        tree.assign(4*n, vector<Node>(4*m, ID));
        if (n && m) build_x(data, 1, 0, n-1);
    }

    // Point update: combine val into cell (x,y)
    void update(int x, int y, const Node& val) {
        assert(0 <= x && x < n && 0 <= y && y < m);
        update_x(1, 0, n-1, x, y, val);
    }

    // Rectangular query: merge over [x1..x2] x [y1..y2]
    Node query(int x1, int y1, int x2, int y2) {
        assert(0 <= x1 && x1 <= x2 && x2 < n);
        assert(0 <= y1 && y1 <= y2 && y2 < m);
        return query_x(1, 0, n-1, x1, x2, y1, y2);
    }

private:
    void build_x(const vector<vector<Node>>& data, int vx, int lx, int rx) {
        if (lx == rx) {
            build_y(data, vx, lx, rx, 1, 0, m-1);
        } else {
            int mx = (lx + rx) >> 1;
            build_x(data, vx<<1,   lx,   mx);
            build_x(data, vx<<1|1, mx+1, rx);
            build_y(data, vx, lx, rx, 1, 0, m-1);
        }
    }
    void build_y(const vector<vector<Node>>& data,
                 int vx, int lx, int rx,
                 int vy, int ly, int ry) {
        if (ly == ry) {
            if (lx == rx)
                tree[vx][vy] = data[lx][ly];
            else
                tree[vx][vy] = merge(tree[vx<<1][vy], tree[vx<<1|1][vy]);
        } else {
            int my = (ly + ry) >> 1;
            build_y(data, vx, lx, rx, vy<<1,   ly,   my);
            build_y(data, vx, lx, rx, vy<<1|1, my+1, ry);
            tree[vx][vy] = merge(tree[vx][vy<<1], tree[vx][vy<<1|1]);
        }
    }
    void update_y(int vx, int lx, int rx,
                  int vy, int ly, int ry,
                  int x, int y, const Node& val) {
        if (ly == ry) {
            if (lx == rx)
                tree[vx][vy] = merge(tree[vx][vy], val);
            else
                tree[vx][vy] = merge(tree[vx<<1][vy], tree[vx<<1|1][vy]);
        } else {
            int my = (ly + ry) >> 1;
            if (y <= my)
                update_y(vx, lx, rx, vy<<1,   ly,   my, x, y, val);
            else
                update_y(vx, lx, rx, vy<<1|1, my+1, ry, x, y, val);
            tree[vx][vy] = merge(tree[vx][vy<<1], tree[vx][vy<<1|1]);
        }
    }
    void update_x(int vx, int lx, int rx,
                  int x, int y, const Node& val) {
        if (lx != rx) {
            int mx = (lx + rx) >> 1;
            if (x <= mx)
                update_x(vx<<1,   lx,   mx, x, y, val);
            else
                update_x(vx<<1|1, mx+1, rx, x, y, val);
        }
        update_y(vx, lx, rx, 1, 0, m-1, x, y, val);
    }
    Node query_y(int vx, int vy, int ly, int ry,
                 int y1, int y2) {
        if (y1 > ry || y2 < ly) return ID;
        if (y1 <= ly && ry <= y2) return tree[vx][vy];
        int my = (ly + ry) >> 1;
        return merge(
            query_y(vx, vy<<1,   ly,   my, y1, y2),
            query_y(vx, vy<<1|1, my+1, ry, y1, y2)
        );
    }
    Node query_x(int vx, int lx, int rx,
                 int x1, int x2, int y1, int y2) {
        if (x1 > rx || x2 < lx) return ID;
        if (x1 <= lx && rx <= x2)
            return query_y(vx, 1, 0, m-1, y1, y2);
        int mx = (lx + rx) >> 1;
        return merge(
            query_x(vx<<1,   lx,   mx, x1, x2, y1, y2),
            query_x(vx<<1|1, mx+1, rx, x1, x2, y1, y2)
        );
    }
};

// ==== CUSTOMIZATION (always before main) ====  
// 1) Node type
using Node = int;
// 2) Merge function
static auto merge_fn = [](Node a, Node b){ return a + b; };
// 3) Identity element
static const Node identity = 0;
// =======================================================

#include <iostream>
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // sample 3x4 matrix
    vector<vector<Node>> mat = {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12}
    };

    SegmentTree2D<Node, decltype(merge_fn)> seg2d(mat, merge_fn, identity);

    // update: add 10 to cell (1,2)
    seg2d.update(1,2,10);
    // query sum on rectangle [0..2] x [1..3]
    Node ans = seg2d.query(0,1,2,3);
    cout << "sum of submatrix = " << ans << '\n';

    return 0;
}
