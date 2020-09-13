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
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

enum SolveType { BRUTE, MAIN };

/*
////////////////////////////////////////////////////////////////////////////////
//
// TEMPLATE START
//
// Template used by Ritesh Singla (alias=uhateme) for competitive programming.
//
////////////////////////////////////////////////////////////////////////////////
*/

#ifdef UHATEME  // Defined in Xcode Artichtecture for local development.

enum InputType { STDOUT, STDOUT_DBG, FILE_IO, FILE_INPUT, GENERATED_INPUT };
#define CURRENT_INPUT_TYPE FILE_INPUT
#include "uhateme.h"

int TEST_CASE = -1;
#else
#include <bits/stdc++.h>
#define Trace(...)
#endif

namespace {

// Constants
#define endl '\n'

// Loops
#define rep(i, j, n) for (int i = (int)(j); i < (int)(n); i++)
#define repv(i, j, n) for (int i = (int)(n)-1; i >= (int)(j); i--)
#define set2(ar, i, j, v)          \
  rep(a, 0, i) {                   \
    rep(b, 0, j) { ar[a][b] = v; } \
  }
#define set1(ar, i, v) \
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

}  // namespace

void GenerateInput() {}

// Use global vector to pass on the answers if needed.
vector<int> brute_ans;
void SolveBruteTestCase() {
  // Pushback answer using index |TEST_CASE|. This can be accessed via
  // |SolveTestCase|
}

/*
////////////////////////////////////////////////////////////////////////////////
//
// TEMPLATE END
//
// Template used by Ritesh Singla (alias=uhateme) for competitive programming.
//
////////////////////////////////////////////////////////////////////////////////
*/

int v[10];
bool inf[10];
int pos[10];
int n;
const int OFFSET = 120;

int TryFor(int infected) {
  rep(i, 0, n) {
    inf[i] = 0;
    pos[i] = i + 1;
  }
  inf[infected] = 1;

  // {time, pos }
  vector<pair<pair<int, int>, pair<int, int>>> simulation;

  rep(i, 0, n) {
    rep(j, i + 1, n) {
      //      pos[i] - pos[j]  =  v[j] * t - + v[i] * t

      if (v[j] == v[i]) {
        // no direct interaction
      } else {
        int t = (OFFSET * (pos[i] - pos[j])) / (v[j] - v[i]);
        if (t < 0) {
          // no direct interaction
        } else {
          // interacted at .. t/OFFSET
          int interaction_pos = (OFFSET * pos[i]) + v[i] * t;
          simulation.push_back(mp(mp(t, interaction_pos), mp(i, j)));
          //          Trace(t * 1.0 / OFFSET, i , j);
        }
      }
    }
  }

  if (simulation.size() == 0) {
    return 1;
  }
  sort(simulation.begin(), simulation.end());

  for (int start = 0; start < simulation.size();) {
    int end = start;
    while (end + 1 < simulation.size() &&
           simulation[start].first.first == simulation[end + 1].first.first &&
           simulation[start].first.second == simulation[end + 1].first.second) {
      end++;
    }
    //    Trace("time = ", simulation[start].first.first * 1.0 / OFFSET,
    //    infected);
    // [start .. end]
    bool any_infected = false;
    for (int j = start; j <= end; j++) {
      int u = simulation[j].second.first;
      int v = simulation[j].second.second;
      if (inf[u]) {
        //        Trace("Already infected == ", u);
        any_infected = true;
      }
      if (inf[v]) {
        //        Trace("Already infected == ", v);
        any_infected = true;
      }
    }
    if (any_infected) {
      for (int j = start; j <= end; j++) {
        int u = simulation[j].second.first;
        int v = simulation[j].second.second;
        //        Trace("Got infected == ", u);
        //        Trace("Got infected == ", v);
        inf[u] = true;
        inf[v] = true;
      }
    }
    start = end + 1;
  }
  int ans = 0;
  rep(i, 0, n) { ans += (inf[i]); }
  return ans;
}

void SolveTestCase() {
  cin >> n;
  rep(i, 0, n) { cin >> v[i]; }
  int best = n;
  int worst = 1;

  rep(i, 0, n) {
    // is is infected
    int cand = TryFor(i);

    best = min(best, cand);
    worst = max(worst, cand);
  }
  cout << best << " " << worst;
}

void Solve(SolveType solve_type) {
  int t;
  cin >> t;
  for (int tc = 1; tc <= t; tc++) {
//    cout << "Case #" << tc << ": ";
#ifdef UHATEME
    SolveTestCaseDriver(solve_type, SolveBruteTestCase, SolveTestCase,
                        TEST_CASE, tc);
#else
    SolveTestCase();
#endif
    cout << endl;
  }
}

int main() {
  //  SetupFactorials(100003);
  UseFastIO(true);
#ifdef UHATEME
  SetInputType(CURRENT_INPUT_TYPE, GenerateInput, Solve);
#endif
  Solve(MAIN);
}
