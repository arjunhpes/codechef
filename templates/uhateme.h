
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

#ifndef uhateme_h
#define uhateme_h

#include <bits/stdc++.h>
#include <chrono>
#include <filesystem>

using namespace std;
namespace fs = std::__fs::filesystem;
namespace chr = std::chrono;

inline void CHECK(bool condition, const string &error_msg) {
  if (!condition) {
    cerr << error_msg;
    abort();
  }
}

inline void CHECK_LT(int left, int right, const string &error_msg) {
  CHECK(left < right, error_msg);
}

inline void CHECK_LE(int left, int right, const string &error_msg) {
  CHECK(left <= right, error_msg);
}

inline void CHECK_GT(int left, int right, const string &error_msg) {
  CHECK(left > right, error_msg);
}

inline void CHECK_GE(int left, int right, const string &error_msg) {
  CHECK(left >= right, error_msg);
}

inline const char *GetAbsoluteFileName(const string &file_name) {
  // FILE_IO_DIR is defined in Xcode Artichtecture for local development.
  string file_path(FILE_IO_DIR);
  file_path.append(file_name);
  return file_path.c_str();
}

bool IsDebugMode() {
  return !(CURRENT_INPUT_TYPE == STDOUT || CURRENT_INPUT_TYPE == FILE_INPUT);
}

inline void SetInputType(InputType input_type, void (*GenerateInput)(),
                         void (*Solve)(SolveType)) {
  if (input_type == STDOUT) {
    return;
  }
  if (input_type == STDOUT_DBG) {
    return;
  }
  if (input_type == FILE_IO) {
    freopen(GetAbsoluteFileName("input.txt"), "r", stdin);
    freopen(GetAbsoluteFileName("output.txt"), "w", stdout);
    return;
  }
  if (input_type == FILE_INPUT) {
    freopen(GetAbsoluteFileName("input.txt"), "r", stdin);
    return;
  }
  if (input_type == GENERATED_INPUT) {
    // Generate Brute Input.
    if (IsDebugMode()) {
      cerr << "Generating the input..." << endl;
    }
    freopen(GetAbsoluteFileName("generated_input_brute.txt"), "w", stdout);
    GenerateInput();
    // Not sure why, but this new line character seems to be needed. Else,
    // input for number fo testcases during Solve(MAIN) causes issue.
    cout << endl;
    if (IsDebugMode()) {
      cerr << "Input Generated." << endl;
    }
    cout.flush();

    // Copy Brute Input to Main Input.
    if (IsDebugMode()) {
      cerr << "Copying generated_input_brute.txt..." << endl;
    }
    fs::remove(GetAbsoluteFileName("generated_input_main.txt"));
    fs::copy(GetAbsoluteFileName("generated_input_brute.txt"),
             GetAbsoluteFileName("generated_input_main.txt"));
    if (IsDebugMode()) {
      cerr << "File Copied." << endl;
    }

    // Solve with Brute Solution.
    if (IsDebugMode()) {
      cerr << "Running brute force solution..." << endl;
    }
    freopen(GetAbsoluteFileName("generated_input_brute.txt"), "r", stdin);
    freopen(GetAbsoluteFileName("output_brute.txt"), "w", stdout);
    Solve(BRUTE);
    if (IsDebugMode()) {
      cerr << "Brute Force solution ran successfully." << endl;
    }

    // Update the File IO for Main Solution.
    if (IsDebugMode()) {
      cerr << "Running main solution..." << endl;
    }
    freopen(GetAbsoluteFileName("generated_input_main.txt"), "r", stdin);
    freopen(GetAbsoluteFileName("output.txt"), "w", stdout);
    return;
  }
  cerr << "Unable to setup the input type. Please handle the error. Found "
            "input type = "
         << input_type;
  abort();
}

inline void SolveTestCaseDriver(SolveType solve_type,
                                std::function<void()> solve_brute_test_case,
                                std::function<void()> solve_test_case,
                                int &TEST_CASE, int tc) {
  TEST_CASE = tc;
  if (IsDebugMode()) {
    cerr << "\n  Starting Test Case #" << tc << endl;
  }
  auto start = chr::high_resolution_clock::now();

  if (solve_type == BRUTE) {
    solve_brute_test_case();
  } else {
    solve_test_case();
  }
  auto stop = chr::high_resolution_clock::now();

  if (IsDebugMode()) {
    auto duration = chr::duration_cast<chr::milliseconds>(stop - start);
    cerr << "\n  Completed Test Case #" << tc << " in "
         << duration.count() / 1000.0 << " seconds";
    cout.flush();
    cerr.flush();
  }
}

#endif /* uhateme_h */
