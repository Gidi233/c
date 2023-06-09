class Solution {
public:
    unordered_map<int,vector<int>> map1;
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