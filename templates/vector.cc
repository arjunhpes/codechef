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
