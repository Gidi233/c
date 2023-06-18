class Solution {
public:
    unordered_set<int> A,B;
    int flag=1;
    bool search(vector<vector<int>>& graph,int num,char ch){
        if(ch=='a'){
            if(B.find(num)!=B.end()) return 0;
            if(A.find(num)!=A.end()) return 1;
            A.emplace(num);
            for(int i:graph[num]){
                if(A.find(i)!=A.end()) return 0;
                if(B.find(i)!=B.end()) continue;
                B.emplace(i);
                if(!search(graph,i,'b')) return false;
                //不能直接return search(graph,i,'b');如果为1的话要进行下一个循环
            }
        }
        if(ch=='b'){
            if(A.find(num)!=A.end()) return 0;
            if(B.find(num)!=B.end()) return 1;
            B.emplace(num);
            for(int i:graph[num]){
                if(B.find(i)!=B.end()) return 0;
                if(A.find(i)!=A.end()) continue;
                A.emplace(i);
                if(!search(graph,i,'a')) {
                    return false;
                }
                //return search(graph,i,'a');
            }
        }
        printf("1\n");
        return 1;//就算用不到也要加？？？
    }

    bool isBipartite(vector<vector<int>>& graph) {
        return search(graph,0,'a');
    }
};

//递归，分别加入两个哈希set（代表A、B）,再加入的时候在另一个set里搜一遍，搜到了返回false，没搜到就加入set