class Solution {
public:
    string getSmallestString(int n, int k) {
        int z=k/26;
        if(z==n) return string (z,'z');
        int o=0;//z需要退一个的次数
        while(k%26+o*26+z<n){
            z--;
            o++;
        }
        string ans(n-z-1,'a');
        // for(int i=0;i<n-z-1;i++){
        //     ans+="a";//+=的是字符串
        // }

        // char a='a';
        // a+=k-(z*26+(n-z-1))-1;//减去a和z算出中间的字母
        ans.append(1,'a'+(k-(z*26+(n-z-1))-1));

        // for(int i=0;i<z;i++){
        //     ans+="z";
        // }
        ans.append(z,'z');
        return ans;
    }
};

//自己写的稀烂版本，先算出z的个数,然后+a，+中间的字母，+z(最开始是一个一个+=的)

class Solution {
public:
    string getSmallestString(int n, int k) {
        string ans;
        for (int i = 1; i <= n; i++) {
            int lower = max(1, k - (n - i) * 26);
            k -= lower;
            ans.push_back('a' + lower - 1);
        }
        return ans;
    }
};

//官答一个个计算出字母，一个个追加上去

class Solution {
public:
    string getSmallestString(int n, int k) {
        string s(n, 'a');
        k -= n;
        for(int i=n-1;i>=0 && k;i--){
            int t = min(25, k);
            s[i] += t;
            k -= t;
        }
        return s;
    }
};
//感觉这个更直观
//先构造n个a，从后往前，对k一次次减