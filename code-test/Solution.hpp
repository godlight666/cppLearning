#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        int index=1,end = n*n;
        vector<vector<int>> res(n, vector<int>(n));
        for (int l=0;l<(n)/2;l++){
            for (int j=0+l;j<n-l-1;j++){    
                res[l][j] = index;
                index++;
                
            }
            
            for (int i=0+l;i<n-l-1;i++){
                res[i][n-1-l] = index;
                index++;
                
            }
            for (int j=n-1-l;j>l;j--){
                res[n-1-l][j] = index;
                index++;
                
            }
            for (int i=n-1-l;i>l;i--){
                res[i][l] = index;
                index++;
                
            }
        }
        if (n%2){
            res[n/2][n/2] = end;
        }
        
        return res;
    }
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string,vector<string>> map;
        for (string str:strs){
            string key = str;
            sort(key.begin(),key.end());
            map[key].emplace_back(str);
        }
        vector<vector<string>> res;
        for (unordered_map<string,vector<string>>::iterator it = map.begin();it!=map.end();it++){
            res.emplace_back(it->second);
        }
    }
    bool backspaceCompare(string s, string t) {
        int i=s.size()-1,j=t.size()-1;
        int back1=0,back2=0;
        while(i>=0||j>=0){
            if(i>=0&&s[i]=='#'){
                ++back1;
                --i;
                continue;
            }
            if (back1>0){
                --back1;
                --i;
                continue;
            }
            if(j>=0&&t[j]=='#'){
                --j;
                ++back2;
                continue;
            }
            if (back2>0){
                --back2;
                --j;
                continue;
            }
            if (i<0||j<0){
                return false;
            }
            if (s[i]!=t[j]){
                return false;
            }
            --i;
            --j;
        }
        cout<<i<<" "<<j<<endl;
        return i<0&&j<0;
    }
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        vector<int> pre;
        for (int i=0;i<numRows;++i){
            vector<int> temp(i+1);
            temp[0] = 1;
            temp[i] = 1;
            if (i>0){
                pre = res[i-1];
            }
            for(int j=1;j<i-1;++j){
                temp[j] = pre[j-1]+pre[j];
            }
            res.emplace_back(temp);
        }
        return res;
    }
};
