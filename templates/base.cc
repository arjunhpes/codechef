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

void SolveTestCase() { cout << "Hello World"; }

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
