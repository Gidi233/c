class Solution {
public:
    unordered_map<int,vector<int>> map1;//在数据范围给定情况下不用用map，vector就可以。（要先vector1.resize(numCourses);）
    int flags[5005]={0};//有没有找过

    int myfind(int i,unordered_set<int> flag){//可否完成所有
        if(flags[i]==1) return 1;
        auto iter=map1.find(i);
        if(iter!=map1.end()){//?按理说一定能找到的呀
            if(flag.find(iter->first)!=flag.end()) return 0;
            flag.emplace(iter->first);
            //int n=iter->secind.size();
            for(auto yuansu:iter->second){
                if(myfind(yuansu,flag)==0) return 0;
            }
            flags[i]=1;
        }
        return 1;
    }

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        
        for (const auto& prerequisite : prerequisites) {
            int key = prerequisite[0];
            int value = prerequisite[1];
            if (map1.count(key) == 0) {
                map1[key] = {value};
            } else {
                map1[key].push_back(value);//会有课有多个前提
            }
        }
        
        for(const auto& prerequisite : prerequisites){
            //if(map1.find(prerequisite[0])==map1.end())肯定能找到
            unordered_set<int> flag;
            if(myfind(prerequisite[0],flag)==0) return 0;
        }
        return 1;
    }
};

//自己不动脑子写的，当是练习用STL了

class Solution {
private:
    vector<vector<int>> edges;
    vector<int> visited;
    bool valid = true;

public:
    void dfs(int u) {
        visited[u] = 1;
        for (int v: edges[u]) {
            if (visited[v] == 0) {
                dfs(v);
                if (!valid) {
                    return;
                }
            }
            else if (visited[v] == 1) {
                valid = false;
                return;
            }
        }
        visited[u] = 2;
    }

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        visited.resize(numCourses);
        for (const auto& info: prerequisites) {
            edges[info[1]].push_back(info[0]);
        }
        for (int i = 0; i < numCourses && valid; ++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        return valid;
    }
};

//edges[info[1]].push_back(info[0]);从下往上（二维储存一维学了后能学的课）建图，visited 0、1、2表示未搜索、搜索中、已完成。用dfs如果在搜索中搜到搜索中的点就代表成环了，学一个课的前提是学自己，便不能学完所有课程。
//edges[info[0]].push_back(info[1])这样也行
//可以用栈存储排序结果

class Solution {
private:
    vector<vector<int>> edges;
    vector<int> indeg;

public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        indeg.resize(numCourses);
        for (const auto& info: prerequisites) {
            edges[info[1]].push_back(info[0]);
            ++indeg[info[0]];
        }

        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (indeg[i] == 0) {
                q.push(i);
            }
        }

        int visited = 0;
        while (!q.empty()) {
            ++visited;
            int u = q.front();
            q.pop();
            for (int v: edges[u]) {
                --indeg[v];
                if (indeg[v] == 0) {
                    q.push(v);
                }
            }
        }

        return visited == numCourses;
    }
};

//用bfs，建图（同时获得每个节点的入度）后，将入度为0的推入队列，然后弹出、visited++、给它的相邻接点的入度-1、同时将此时的相邻接点入度为0的推入队列。当队列为空时判断已访问节点数与课程数是否相等，不等则说明内部成环了，返回0。