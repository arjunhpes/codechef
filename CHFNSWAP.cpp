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

int64 n;
int EPS = 1e-9;

double Solve(double a, double b, double c) {
  // a*x*x + b*x + c = 0
  double d = b * b - 4 * a * c;
  if (d < 0) {
    return -1;  // Impossible
  }
  double m = (-b + sqrt(d)) / (2 * a);
  if (m + EPS < 1) {
    m = -1;
  } else if (m - EPS > n) {
    m = -1;
  }
  return m;
}

void SolveTestCase() {
  cin >> n;
  if (n <= 2) {
    cout << 0;
    return;
  }
  int64 sum = (n * n + n) / 2;
  if (sum & 1) {
    cout << 0;
    return;
  }

  int64 c1 = -sum;
  int64 ans = 0;

  double temp = Solve(1, 1, c1) + EPS;
  int64 m1 = (int64)(floor(temp));
  if (m1 > 0 && (m1 * m1 + m1 + c1) == 0) {
    ans += (m1 * (m1 - 1)) / 2;              // 13 * 7 = 91
    ans += ((n - m1) * ((n - m1) - 1)) / 2;  // = 15
  }
  //  cout << ans;

  // m * (m+1) + 2 - (n * (n+1))/2 <= 0
  temp = Solve(1, 1, 2 + c1) + EPS;
  int64 m2 = (int64)(floor(temp));

  // m * (m+1) + 2*(n-1) - (n * (n+1))/2 >= 0
  temp = Solve(1, 1, 2 * (n - 1) + c1) - EPS;
  int64 m3 = (int64)(ceil(temp));

  //  cout << " -- " << m2 << " " << m3 << " -- \n";

  for (int64 m = m3; m <= m2; m++) {
    int64 d = (n * n + n) / 4 - (m * m + m) / 2;
    int64 t2 = max(m + 1, 1 + d);
    int64 t1 = min(n, m + d);
//    Trace(d, t1, t2, ans);
    ans += t1 - t2 + 1;
  }
  Trace(n, ans, m1, m2, m3);
  cout << ans;

  /*
   1 2 3 4 5 6 7
   S = 28
   14

   1 ..... m ..... n


   x            y

   m * (m+1)/2 == n * (n+1)/4 => mC2 + (n-m)C2


   (m*m + m) - (n * n + n)/2 = 0;


   Say d =  (y-x)
   m * (m+1)/2 + d == n * (n+1)/4
   d >= 1
   d <= n-1

   d = n * (n+1)/4 - m * (m+1)/2

   For d >=1
   n * (n+1)/4 - m * (m+1)/2 >= 1
   m * (m+1)/2 + 1 - n * (n+1)/4 <= 0
   m * (m+1) + 2 - (n * (n+1))/2 <= 0

   For d <= n-1
   n * (n+1)/4 - m * (m+1)/2 <= (n-1)
   m * (m+1)/2 + (n-1) - n * (n+1)/4 >= 0
   m * (m+1) + 2*(n-1) - (n * (n+1))/2 >= 0






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
  //  SetupFactorials(100003);
  UseFastIO(true);
#ifdef UHATEME
  SetInputType(CURRENT_INPUT_TYPE, GenerateInput, Solve);
#endif
  Solve(MAIN);
}
