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
};
