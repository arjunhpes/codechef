//
//  MIT License
//
//  Copyright (c) [2020] [Ritesh Singla]
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to
//  deal in the Software without restriction, including without limitation the
//  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
//  sell copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
//  IN THE SOFTWARE.
//

class SegmentTree {
  public:
#define NodeValue int64
#define SEG_TREE_COMPUTATION                                                   \
    int c1 = (cur << 1) + 1;                                                   \
    int c2 = (cur << 1) + 2;                                                   \
    int m = (s + e) >> 1;

    void Make(int _n) {
        n = _n;
        Make(0, 0, n - 1);
    }

    void Update(int S, int E, NodeValue val) { Update(0, 0, n - 1, S, E, val); }

    NodeValue Query(int S, int E) { return Query(0, 0, n - 1, S, E); }

  private:
    void Make(int cur, int s, int e) {
        if (s == e) {
            tree[cur] = LONG_LONG_MAX;
            return;
        }
        SEG_TREE_COMPUTATION
        Make(c1, s, m);
        Make(c2, m + 1, e);
        tree[cur] = LONG_LONG_MAX;
    }

    // [s, e] -> tree range. [S, E] -> range of interest.
    void Update(int cur, int s, int e, int S, int E, NodeValue val) {
        // node not of interest.
        if (s > E || e < S)
            return;
        // node completely inside interest range. Mark for laze update if
        // needed.
        if (s >= S && e <= E) {
            // This is just a palceholder. In reality, add lazy propagation for
            // min segtree.
            tree[cur] = val;
            return;
        }
        SEG_TREE_COMPUTATION
        Update(c1, s, m, S, E, val);
        Update(c2, m + 1, e, S, E, val);
        tree[cur] = min(tree[c1], tree[c2]);
    }

    NodeValue Query(int cur, int s, int e, int S, int E) {
        if (s > E || e < S) {
            return LONG_LONG_MAX;
        }

        if (s >= S && e <= E) {
            return tree[cur];
        }
        SEG_TREE_COMPUTATION
        NodeValue a = Query(c1, s, m, S, E);
        NodeValue b = Query(c2, m + 1, e, S, E);
        return min(a, b);
    }

    NodeValue tree[6 * 10000005];
    int n;

#undef SEG_TREE_COMPUTATION
#undef NodeValue
} tree;

void SolveTestCase() {
    tree.Make(100);
    rep(i, 0, 100) { tree.Update(i, i, i); }
    rep(i, 0, 100) { cout << tree.Query(i, i) << endl; }
    cout << tree.Query(28, 75) << endl;
}