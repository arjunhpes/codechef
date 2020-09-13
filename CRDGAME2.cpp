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

#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>

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

const int NUM = 1e9 + 7;

const int MAXN = 100005;
vector<int> fact, factinv;

// Returns a^b %p
int PowMod(int64 a, int64 b, int64 p = NUM) {
  int64 ans = 1;
  while (b) {
    if (b & 1) {
      ans = (ans * a) % p;
    }
    a = (a * a) % p;
    b = b >> 1;
  }
  return (int)ans;
}

// (a^p-1 % p) = (1 % p) if a and p are co-prime.
// Thus, a^p-2 is the multiplicative inverse.
int MultiplicativeInverse(int64 a, int64 p = NUM) {
  return PowMod(a, p - 2, p);
}

int Multiply(int64 a, int64 b, int64 p = NUM) { return (int)((a * b) % p); }

int Divide(int64 n, int64 d, int64 p = NUM) {
  return (int)((n * MultiplicativeInverse(d)) % p);
}

int Add(int64 a, int64 b, int64 p = NUM) {
  int64 c = a + b;
  if (c >= p) {
    c -= p;
  }
  if (c < 0 || c >= p) {
    c = (a + b) % p;
  }
  return (int)c;
}

int Subtract(int64 a, int64 b, int64 p = NUM) {
  int64 c = a - b;
  if (c < 0) {
    c += p;
  }
  if (c < 0 || c >= p) {
    c = ((a % p) + p - (b % p)) % p;
  }
  return (int)c;
}

void SetupFactorials(int n) {
  fact.resize(n + 1);
  factinv.resize(n + 1);
  fact[0] = fact[1] = 1;
  factinv[0] = factinv[1] = 1;
  for (int i = 2; i <= n; i++) {
    fact[i] = Multiply(fact[i - 1], i);
    factinv[i] = MultiplicativeInverse(fact[i]);
  }
}

int Combinatrics(int64 a, int64 b) {
  if (b > a) {
    return 0;
  }
  return Multiply(fact[a], Multiply(factinv[a - b], factinv[b]));
}

void SolveTestCase() {
  int n;
  cin >> n;
  int max_count = 0;
  int max_element = -1;
  rep(i, 0, n) {
    int x;
    cin >> x;
    if (x > max_element) {
      max_element = x;
      max_count = 1;
    } else if (x == max_element) {
      max_count++;
    }
  }
  // max_count

  /*
   6,6,6,6 ->16 / 6 have issues

   max_count


   */

  // 2 ^ n
  ll ans = PowMod(2, n);
  if (max_count % 2 == 0) {
    //    (2 ^ n / (2 ^ max_count))*((2 ^ max_count) - C(max_count,max_count/2))
    int temp = PowMod(2, max_count);
    ans = Divide(ans, temp);
    ans = Multiply(ans, Subtract(temp, Combinatrics(max_count, max_count / 2)));
  }
  cout << ans;
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
  SetupFactorials(100003);
  UseFastIO(true);
#ifdef UHATEME
  SetInputType(CURRENT_INPUT_TYPE, GenerateInput, Solve);
#endif
  Solve(MAIN);
}
