class Solution {
 public:
  string longestCommonPrefix(vector<string>& strs) {
    int min_ = INT_MAX;
    char c;
    for (auto a : strs) {
      min_ = min(min_, (int)a.size());
    }
    int size = strs.size();
    string ans;
    for (int i = 0; i < min_; i++) {
      for (int j = 0; j < size; j++) {
        if (j == 0)
          c = strs[j][i];
        else if (strs[j][i] != c)
          return ans;
      }
      ans.push_back(c);
    }
    return ans;
  }
};
// 纵向扫描

class Solution {
 public:
  string longestCommonPrefix(vector<string>& strs) {
    if (!strs.size()) {
      return "";
    } else {
      return longestCommonPrefix(strs, 0, strs.size() - 1);
    }
  }

  string longestCommonPrefix(const vector<string>& strs, int start, int end) {
    if (start == end) {
      return strs[start];
    } else {
      int mid = (start + end) / 2;
      string lcpLeft = longestCommonPrefix(strs, start, mid);
      string lcpRight = longestCommonPrefix(strs, mid + 1, end);
      return commonPrefix(lcpLeft, lcpRight);
    }
  }

  string commonPrefix(const string& lcpLeft, const string& lcpRight) {
    int minLength = min(lcpLeft.size(), lcpRight.size());
    for (int i = 0; i < minLength; ++i) {
      if (lcpLeft[i] != lcpRight[i]) {
        return lcpLeft.substr(0, i);
      }
    }
    return lcpLeft.substr(0, minLength);
  }
};
// 分治

class Solution {
 public:
  string longestCommonPrefix(vector<string>& strs) {
    if (!strs.size()) {
      return "";
    }
    int minLength = min_element(strs.begin(), strs.end(),
                                [](const string& s, const string& t) {
                                  return s.size() < t.size();
                                })
                        ->size();
    int low = 0, high = minLength;
    while (low < high) {
      int mid = (high - low + 1) / 2 + low;
      if (isCommonPrefix(strs, mid)) {
        low = mid;
      } else {
        high = mid - 1;
      }
    }
    return strs[0].substr(0, low);
  }

  bool isCommonPrefix(const vector<string>& strs, int length) {
    string str0 = strs[0].substr(0, length);
    int count = strs.size();
    for (int i = 1; i < count; ++i) {
      string str = strs[i];
      for (int j = 0; j < length; ++j) {
        if (str0[j] != str[j]) {
          return false;
        }
      }
    }
    return true;
  }
};
// 二分 不同就往左找 用横向扫描