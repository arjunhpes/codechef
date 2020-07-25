
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

#define CURRENT_INPUT_TYPE FILE_INPUT
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

// This data structure maintains the minimum cost that can be achieved with a
// given budget. It stores a map with Key-Value pairs (i,j) s.t.
//      if we have atleast budget |i|, the associated cost is |j|.
//      for any 2 pairs (i1,j1) and (i2,j2), i1 != i2.
//      for any 2 pairs (i1,j1) and (i2,j2), if(i1 < i2) then j1 > j2.
class BudgetCostMap {
  public:
#define CostType int64
#define BudgetType int
#define INFINITY_COST LONG_LONG_MAX
    void Clear() { budget_map_.clear(); }

    // Amortized O(logn)
    void Insert(BudgetType budget, CostType cost) {
        auto itr = budget_map_.lower_bound(budget);
        bool need_to_balance_by_itr = false;

        if (itr != budget_map_.end() && itr->first == budget) {
            // The exact key is present.
            if (itr->second <= cost) {
                return;
            }
            itr->second = cost;
            // keep on removing excessive costs which are in front.
            itr++;
            need_to_balance_by_itr = true;
        } else if (itr == budget_map_.begin()) {
            // itr->first > budget or empty map.
            auto itr_inserted_pair = budget_map_.insert({budget, cost});
            itr = itr_inserted_pair.first;
            itr++;
            need_to_balance_by_itr = true;
        } else if (itr == budget_map_.end()) {
            itr--;
            if (itr->second <= cost) {
                return;
            }
            budget_map_[budget] = cost;
        } else {
            // itr != budget_map_.begin() && itr != budget_map_.end() &&
            // itr->first != budget
            itr--;
            if (itr->second <= cost) {
                return;
            }
            auto itr_inserted_pair = budget_map_.insert({budget, cost});
            itr = itr_inserted_pair.first;
            itr++;
            need_to_balance_by_itr = true;
        }
        if (need_to_balance_by_itr) {
            while (itr != budget_map_.end() && itr->second >= cost) {
                itr = budget_map_.erase(itr);
            }
        }
    }

    // O(logn)
    CostType Query(BudgetType budget) {
        auto itr = budget_map_.upper_bound(budget);
        if (itr == budget_map_.begin()) {
            return INFINITY_COST;
        }
        itr--;
        return itr->second;
    }

#ifdef UHATEME
    void DebugString() {
        for (const auto &pair : budget_map_) {
            cout << pair.first << " -> " << pair.second << endl;
        }
        cout << endl;
    }
#endif

  private:
    map<BudgetType, CostType> budget_map_;

#undef CostType
#undef BudgetType
#undef INFINITY_COST
} budget_map;

void SolveTestCase() {
    budget_map.Clear();
    budget_map.Insert(1000, 10000);
    budget_map.DebugString();
    budget_map.Insert(1010, 5000);
    budget_map.DebugString();
    budget_map.Insert(1020, 100);
    budget_map.DebugString();
    budget_map.Insert(1000, 10000000000);
    budget_map.DebugString();
    budget_map.Insert(1000, 10000000000);
    budget_map.DebugString();
    cout << "999 == " << budget_map.Query(999) << endl;
    cout << "1000 == " << budget_map.Query(1000) << endl;
    cout << "1001 == " << budget_map.Query(1001) << endl;
    cout << "1009 == " << budget_map.Query(1009) << endl;
    cout << "1010 == " << budget_map.Query(1010) << endl;
    cout << "1011 == " << budget_map.Query(1011) << endl;
    cout << "1019 == " << budget_map.Query(1019) << endl;
    cout << "1020 == " << budget_map.Query(1020) << endl;
    cout << "1021 == " << budget_map.Query(1021) << endl;
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
