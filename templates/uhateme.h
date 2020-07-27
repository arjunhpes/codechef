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
#include <filesystem>

using namespace std;
namespace fs = std::__fs::filesystem;

inline const char *GetAbsoluteFileName(const string &file_name) {
    // FILE_IO_DIR is defined in Xcode Artichtecture for local development.
    string file_path(FILE_IO_DIR);
    file_path.append(file_name);
    return file_path.c_str();
}

inline void SetInputType(InputType input_type, void (*GenerateInput)(),
                         void (*Solve)(SolveType)) {
    if (input_type == STDOUT) {
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
        freopen(GetAbsoluteFileName("generated_input_brute.txt"), "w", stdout);
        GenerateInput();
        // Not sure why, but this new line character seems to be needed. Else,
        // input for number fo testcases during Solve(MAIN) causes issue.
        cout << endl;
        cout.flush();

        // Copy Brute Input to Main Input.
        fs::remove(GetAbsoluteFileName("generated_input_main.txt"));
        fs::copy(GetAbsoluteFileName("generated_input_brute.txt"),
                 GetAbsoluteFileName("generated_input_main.txt"));

        // Solve with Brute Solution.
        freopen(GetAbsoluteFileName("generated_input_brute.txt"), "r", stdin);
        freopen(GetAbsoluteFileName("output_brute.txt"), "w", stdout);
        Solve(BRUTE);

        // Update the File IO for Main Solution.
        freopen(GetAbsoluteFileName("generated_input_main.txt"), "r", stdin);
        freopen(GetAbsoluteFileName("output.txt"), "w", stdout);
        return;
    }
    cerr << "Unable to setup the input type. Please handle the error. Found "
            "input type = "
         << input_type;
    abort();
}

#endif /* uhateme_h */
