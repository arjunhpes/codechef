
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
#ifdef UHATEME
  budget_map.DebugString();
#endif
  budget_map.Insert(1010, 5000);
#ifdef UHATEME
  budget_map.DebugString();
#endif
  budget_map.Insert(1020, 100);
#ifdef UHATEME
  budget_map.DebugString();
#endif
  budget_map.Insert(1000, 10000000000);
#ifdef UHATEME
  budget_map.DebugString();
#endif
  budget_map.Insert(1000, 10000000000);
#ifdef UHATEME
  budget_map.DebugString();
#endif
  cout << "999 == " << budget_map.Query(999) << endl;    // LONG_LONG_MAX
  cout << "1000 == " << budget_map.Query(1000) << endl;  // 10000
  cout << "1001 == " << budget_map.Query(1001) << endl;  // 10000
  cout << "1009 == " << budget_map.Query(1009) << endl;  // 10000
  cout << "1010 == " << budget_map.Query(1010) << endl;  // 5000
  cout << "1011 == " << budget_map.Query(1011) << endl;  // 5000
  cout << "1019 == " << budget_map.Query(1019) << endl;  // 5000
  cout << "1020 == " << budget_map.Query(1020) << endl;  // 100
  cout << "1021 == " << budget_map.Query(1021) << endl;  // 100
}
