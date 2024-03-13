class Solution {
 public:
  string dfs(string& s, int& i) {
    string ans;
    while (i < s.length()) {
      while (isalpha(s[i])) {
        ans.push_back(s[i]);
        i++;
      }
      if (s[i] == ']') return ans;
      int num = 0;
      while (isdigit(s[i])) {
        num = num * 10 + s[i] - '0';
        i++;
      }
      i++;
      string t = dfs(s, i);
      for (int i = 0; i < num; i++) {
        ans += t;
      }
      i++;
    }
    return ans;
  }
  string decodeString(string s) {
    int i = 0;
    string ans;
    while (i < s.length()) {
      while (isalpha(s[i])) {
        ans.push_back(s[i]);
        i++;
      }
      if (i == s.length()) break;
      int num = 0;
      while (isdigit(s[i])) {
        num = num * 10 + s[i] - '0';
        i++;
      }
      i++;
      string t = dfs(s, i);
      for (int i = 0; i < num; i++) {
        ans += t;
      }
      i++;
    }
    return ans;
  }
};
// 递归

class Solution {
 public:
  string getDigits(string& s, size_t& ptr) {
    string ret = "";
    while (isdigit(s[ptr])) {
      ret.push_back(s[ptr++]);
    }
    return ret;
  }

  string getString(vector<string>& v) {
    string ret;
    for (const auto& s : v) {
      ret += s;
    }
    return ret;
  }

  string decodeString(string s) {
    vector<string> stk;
    size_t ptr = 0;

    while (ptr < s.size()) {
      char cur = s[ptr];
      if (isdigit(cur)) {
        // 获取一个数字并进栈
        string digits = getDigits(s, ptr);
        stk.push_back(digits);
      } else if (isalpha(cur) || cur == '[') {
        // 获取一个字母并进栈
        stk.push_back(string(1, s[ptr++]));
      } else {
        ++ptr;
        vector<string> sub;
        while (stk.back() != "[") {
          sub.push_back(stk.back());
          stk.pop_back();
        }
        reverse(sub.begin(), sub.end());
        // 左括号出栈
        stk.pop_back();
        // 此时栈顶为当前 sub 对应的字符串应该出现的次数
        int repTime = stoi(stk.back());
        stk.pop_back();
        string t, o = getString(sub);
        // 构造字符串
        while (repTime--) t += o;
        // 将构造好的字符串入栈
        stk.push_back(t);
      }
    }

    return getString(stk);
  }
};
// 栈