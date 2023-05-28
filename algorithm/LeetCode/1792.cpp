class Solution {
public:
    struct Ratio {
        int pass, total;
        bool operator < (const Ratio& oth) const {
            return (long long) (oth.total + 1) * oth.total * (total - pass) < (long long) (total + 1) * total * (oth.total - oth.pass);
        }
    };

    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        priority_queue<Ratio> q;
        for (auto &c : classes) {
            q.push({c[0], c[1]});
        }

        for (int i = 0; i < extraStudents; i++) {
            auto [pass, total] = q.top();
            q.pop();
            q.push({pass + 1, total + 1});
        }

        double res = 0;
        for (int i = 0; i < classes.size(); i++) {
            auto [pass, total] = q.top();
            q.pop();
            res += 1.0 * pass / total;
        }
        return res / classes.size();
    }
};
//对STL库用的不熟啊~，priority_queue是自动维护排序的队列默认从大到小，结构体Ratio重写了小于运算符，让以通过率变化量从大到小排序（公式推导看官方题解了）。
//24行，这是 C++ 17 引入的结构化绑定（Structured Binding）语法，可以将一个复合类型（如pair，tuple，结构体等）的成员分别绑定到不同的变量中，方便直接访问和使用。
//auto [pass, total] = q.top() 的意思是将结构体 Ratio 中的 pass 和 total 成员分别绑定到变量 pass 和 total 中。这样，我们就可以直接使用 pass 和 total 变量来访问 Ratio 对象的 pass 和 total 成员。

class Solution {
public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        priority_queue<tuple<double, int, int>> q;
        
        auto diff = [](int x, int y) -> double {
            return (double)(x + 1) / (y + 1) - (double)x / y;
        };
        
        double ans = 0.;
        for (const auto& c: classes) {
            int x = c[0], y = c[1];
            ans += (double)x / y;
            q.emplace(diff(x, y), x, y);
        }
        for (int _ = 0; _ < extraStudents; ++_) {
            auto [d, x, y] = q.top();
            q.pop();
            ans += d;
            q.emplace(diff(x + 1, y + 1), x + 1, y + 1);
        }
        return ans / classes.size();
    }
};

//用tuple模板第一个值储存每个对象的通过率变化量，priority_queue默认比较第一个值，就不用重载运算符了。