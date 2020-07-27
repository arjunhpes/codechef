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

// Alternative of std::vector. To be used when we need to a vector on stack
// instead of heap, i.e. with static size. Allows basic checks for better
// debugging.
template <typename T, size_t Size>
class Vector {
 public:
  // Vector size
  int size() { return cur_size_; }
  bool empty() { return cur_size_ == 0; }

  // Value access
  T &operator[](int index) {
#ifdef UHATEME
    CHECK_GE(index, 0, "Out of bounds vector access");
    CHECK_LT(index, cur_size_, "Out of bounds vector access");
#endif
    return arr_[index];
  }

  // Vector Helper Methods.
  void push_back(const T &element) {
#ifdef UHATEME
    CHECK_LT(cur_size_, Size, "Vector overflow");
#endif
    arr_[cur_size_++] = element;
  }

  void pop_back() {
#ifdef UHATEME
    if (cur_size_ == 0) {
      cerr << "Popping while size is already 0.";
      abort();
    }
#endif
    cur_size_--;
  }

  void clear() { cur_size_ = 0; }

#ifdef UHATEME
  void DebugString() {
    cerr << "Size = " << cur_size_ << ". Elements: {";
    rep(i, 0, cur_size_) { cerr << (i ? ", " : "") << arr_[i]; }
    cerr << '}' << endl;
  }
#endif

  // Pointers
  T *back() { return &arr_[cur_size_ - 1]; }
  T *begin() { return &arr_[0]; }
  T *end() { return &arr_[cur_size_]; }

 private:
  T arr_[Size];
  int cur_size_ = 0;
};

void SolveTestCase() {
  Vector<int, 100> vec;
#ifdef UHATEME
  vec.DebugString();
#endif
  vec.push_back(100);
#ifdef UHATEME
  vec.DebugString();
#endif
  vec.push_back(200);
#ifdef UHATEME
  vec.DebugString();
#endif
  vec[0] = 999;
#ifdef UHATEME
  vec.DebugString();
#endif
  for (auto &n : vec) {
    n += 100;
  }
#ifdef UHATEME
  vec.DebugString();
#endif
}
