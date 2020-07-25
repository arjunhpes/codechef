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

#include <algorithm>
#include <bits/stdc++.h>
#include <iostream>
#include <vector>

#ifdef UHATEME // Defined in Xcode Artichtecture for local development.

enum InputType { STDOUT, FILE_IO, FILE_INPUT };

#define CURRENT_INPUT_TYPE STDOUT
#include "uhateme.h"
#endif

using namespace std;

// Template used by Ritesh Singla (alias=uahteme) for competitive programming.
// TEMPLATE START
namespace {

// Constants
#define endl '\n'

// Loops
#define rep(i, j, n) for (int i = (j); i < (n); i++)
#define repv(i, j, n) for (int i = (n)-1; i >= (j); i--)
#define set2(ar, i, j, v)                                                      \
    rep(a, 0, i) {                                                             \
        rep(b, 0, j) { ar[a][b] = v; }                                         \
    }
#define set1(ar, i, v)                                                         \
    rep(a, 0, i) { ar[a] = v; }

// Data Types
#define int64 long long int
#define ll long long int
#define vi vector<int>

// Short aliases
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()

// Speeds up cin/cout. Do not use in cin/cout and scanf/printf
// when using UseFastIO
inline void UseFastIO(bool use_fast_io) {
    if (use_fast_io) {
        cin.tie(0);
        cout.tie(0);
        cin.sync_with_stdio(0);
        cout.sync_with_stdio(0);
    }
}

#ifdef UHATEME
inline void SetInputType(InputType input_type) {
    if (input_type == STDOUT) {
        return;
    }
    if (input_type == FILE_IO) {
        freopen(GetInputFileName(), "r", stdin);
        freopen(GetOutputFileName(), "w", stdout);
        return;
    }
    if (input_type == FILE_INPUT) {
        freopen(GetInputFileName(), "r", stdin);
        return;
    }
    cerr << "Unable to setup the input type. Please handle the error. Found "
            "input type = "
         << input_type;
    abort();
}
#endif

} // namespace
// TEMPLATE END

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

void Solve() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
#ifdef UHATEME
        if (CURRENT_INPUT_TYPE == FILE_IO) {
            cerr << "Starting Test Case #" << i << endl;
        }
#endif
        cout << "Case #" << i << ": ";
        SolveTestCase();
#ifdef UHATEME
        if (CURRENT_INPUT_TYPE == FILE_IO) {
            cerr << "Completed Test Case #" << i << endl;
            cout.flush();
            cerr.flush();
        }
#endif
        cout << endl;
    }
}

int main() {
    UseFastIO(true);
#ifdef UHATEME
    SetInputType(CURRENT_INPUT_TYPE);
#endif
    Solve();
}
