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
#include <set>
#include <map>
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
#define CURRENT_INPUT_TYPE STDOUT
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

int64 n;

// stores {s, e} key values representing that we can make [s, e) range (s
// inclusive, e exclusive) last element added to create this range is stored in
// track[s]
map<int64, int64> f;
map<int64, int64> track;

int64 GetCand(int64 i) { return i * i * i * i; }

// prints ',' separated elements to be picked up as my share.
int64 PrintDetailed(int64 ans, bool is_first) {
  if (ans <= 1) {
    if (ans == 1) {
      if (!is_first) {
        cout << ',';
      }
      cout << "1";
      return 1;
    }
    if (ans == 0) {
      return 0;
    }
    abort();
  }

  auto itr = f.upper_bound(ans);
  itr--;  // <= target.
  int64 tt = track[itr->first];
  if (!is_first) {
    cout << ',';
  }
  cout << tt;
  int64 cc = GetCand(tt);
  return cc + PrintDetailed(ans - cc, false);
}

void AddRange(int64 s, int64 e, int64 base) {
  auto itr = f.upper_bound(s);
  itr--;  // becomes <=s.
  if (itr->second >= s) {
    if (e <= itr->second) {
      // entire range already present
      return;
    } else {
      if (itr->first != s) {
        // shorten the range to s).
        itr->second = s;
        itr++;
      } else {
        track.erase(track.find(itr->first));
        itr = f.erase(itr);
      }
    }
  } else {
    itr++;
  }
  // itr->first > s.
  while (itr != f.end() && itr->first <= e) {
    if (itr->second > e) {
      // shorten this one.
      int64 start = e;
      int64 prev_start = itr->first;
      int64 end = itr->second;
      int64 prev_track = track[prev_start];
      track.erase(track.find(prev_start));
      f.erase(f.find(prev_start));
      track[start] = prev_track;
      f[start] = end;
      break;
    }
    track.erase(track.find(itr->first));
    itr = f.erase(itr);
  }
  f[s] = e;
  track[s] = base;
}

void SolveTestCase() {
  int64 sum = 0;

  f[0] = 1;
  int64 last_continuous_0_or_1 = 0;
  // For k == 4, cycle_length = 32. Thus, we need to take 32 continuous elements
  // with answer as 0/1. Using this, we can keep on adding any number of cycles,
  // if needed.
  for (int64 i = 1; last_continuous_0_or_1 < 32; i++) {
    int64 cand = GetCand(i);
    sum += cand;
    vector<pair<int64, int64>> temp;
    for (auto x : f) {
      temp.push_back(mp(cand + x.first, cand + x.second));
    }
    for (auto x : temp) {
      AddRange(x.first, x.second, i);
    }
    int64 target = sum / 2;
    auto itr = f.upper_bound(target);
    itr--;
    int64 ans = itr->second - 1;
    if (itr->second > target) {
      ans = target;
    }
    cout << "ar[1][" << i << "]={";
    int64 pd = PrintDetailed(ans, true);
    if (pd != ans) {
      abort();
    }
    cout << "}; // " << sum - 2 * ans << "\n";
    if (ans == 0 || ans == 1) {
      last_continuous_0_or_1++;
    } else {
      last_continuous_0_or_1 = 0;
    }
  }
  /*

   1, 0, 0, 1 repeating.
   S (odd) -> 1.
   S (even) -> 0.
   S (even) -> 0.
   S (odd) -> 1.

   For k == 1,
   consecutive terms diff = 1. Thus, cycle_length = 4.
   a     , a - 3
   a - 1 , a - 2
   1001

   For k == 2,
   consecutive terms diff = 2a - 1. Cycle_length = 8.
   a^2       , (a - 3)^2    a - 5    a- 6
   (a - 1)^2 , (a - 2)^2    a - 4   a- 7
   10010110

   For k == 3 -> 16
   1001011001101001

   For k == 4 -> 32
   1001011001101001
   */
}

void Solve(SolveType solve_type) {
  //  set1(sieve_4, MAXN, -1);
  int t = 1;
  //  cin >> t;
  for (int tc = 1; tc <= t; tc++) {
//    cout << "Case #" << tc << ": ";
#ifdef UHATEME
    //    n = tc;
    //    cout << n << endl;
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
