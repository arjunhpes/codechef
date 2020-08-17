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

int n, k;
int f[10000];
int dpp[10000];
/*
 returns minimum inefficiency for having seating arrangement for people [i ....
 N -1]
 */
int dp(int i) {
  //  Trace(i, dpp[i]);
  if (i >= n) {
    return 0;
  }
  if (dpp[i] != -1) {
    return dpp[i];
  }
  //  Trace(i);
  int family_count[100];
  set1(family_count, 100, 0);
  int people_fighting = 0;

  int ans = 1e9;
  for (int j = i; j < n; j++) {
    // [i ... j] [j+1 .. n]
    family_count[f[j] - 1]++;
    int val = family_count[f[j] - 1];
    if (val == 2) {
      people_fighting += 2;
    } else if (val > 2) {
      people_fighting++;
    }
    ans = min(ans, people_fighting + k + dp(j + 1));
  }
  Trace(i, ans);
  dpp[i] = ans;
  return ans;
}
void SolveTestCase() {
  cin >> n >> k;
  set1(dpp, n, -1);
  //  Trace(n, k);
  rep(i, 0, n) { cin >> f[i]; }
  cout << dp(0);
  /*
   inefficiency = k * no of table + no of guests...
   cost = k + n

   */
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
  UseFastIO(true);
#ifdef UHATEME
  SetInputType(CURRENT_INPUT_TYPE, GenerateInput, Solve);
#endif
  Solve(MAIN);
}
