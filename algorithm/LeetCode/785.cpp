class Solution {
public:
    unordered_set<int> A,B;
    // int flag=1;
    bool search(vector<vector<int>>& graph,int num,char ch){
        if(ch=='a'){
            if(B.find(num)!=B.end()) return 0;
            if(A.find(num)!=A.end()) return 1;
            A.emplace(num);
            for(int i:graph[num]){
                if(A.find(i)!=A.end()) return 0;
                if(B.find(i)!=B.end()) continue;
                //B.emplace(i);//递归后会自己加进去，不用在前一个加
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
                //A.emplace(i);
                if(!search(graph,i,'a')) {
                    return false;
                }
                //return search(graph,i,'a');
            }
        }
        //printf("1\n");
        return 1;//就算用不到也要加？？？//此处用得到
    }

    bool isBipartite(vector<vector<int>>& graph) {
        for(int i=0;i<graph.size();i++){
            if(A.find(i)==A.end()&&B.find(i)==B.end()){
                if(!search(graph,i,'a')) return false;
            }
        }
        return 1;
    }
};

//dfs
//递归，分别加入两个哈希set（代表A、B）,再加入的时候在另一个set里搜一遍，搜到了返回false，没搜到就加入set
//表达里用vector代替了我的两个unordered_set，给他三个状态，用color.assign(n, UNCOLORED);初始化。用一个bool判断，在每个循环的条件里判断。

class Solution {
private:
    static constexpr int UNCOLORED = 0;
    static constexpr int RED = 1;
    static constexpr int GREEN = 2;
    vector<int> color;

public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> color(n, UNCOLORED);
        for (int i = 0; i < n; ++i) {
            if (color[i] == UNCOLORED) {
                queue<int> q;
                q.push(i);
                color[i] = RED;
                while (!q.empty()) {
                    int node = q.front();
                    int cNei = (color[node] == RED ? GREEN : RED);
                    q.pop();
                    for (int neighbor: graph[node]) {
                        if (color[neighbor] == UNCOLORED) {
                            q.push(neighbor);
                            color[neighbor] = cNei;
                        }
                        else if (color[neighbor] != cNei) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }
};

//用bfs没什么区别，就是搜索的顺序变了。

class Solution {
public:
    vector<int> uf;
    int find(int x)
    {
        if(uf[x] != x)
            uf[x] = find(uf[x]);
        return uf[x];
    }

    void connected(int p, int q)
    {
        int rp = find(p);
        int rq = find(q);
        if(rp == rq)
            return;
        uf[rp] = uf[rq];
    }
    
    bool isBipartite(vector<vector<int>>& graph) {
        uf = vector<int>(graph.size());
        for(int i = 0; i < graph.size(); i++)
            uf[i] = i;
        for(int i = 0; i < graph.size(); i++)
        {
            for(int v : graph[i])
            {
                if(find(v) == find(i))
                    return false;
                connected(v, graph[i][0]);
            }
        }

        return true;
    }
};

//并查集
//先初始化，然后把一个节点的相邻节点归为一类,到最后会归为两类，如果发现相邻节点归为一类了就false。