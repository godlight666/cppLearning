#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <set>
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
        return res;
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
    struct Address{
    public:
        string local;
        string domain;
        Address() = default;
        Address(string l,string d):local(l),domain(d){};
        bool operator< (const struct Address& addr) const{
            if (local<addr.local){
                return true;
            }else if (local==addr.local){
                return domain<addr.domain;
            }else{
                return false;
            }
        }
        
    };
    int numUniqueEmails(vector<string>& emails) {
        set<Address> set;
        for(auto& email:emails){
            parseEmail(email,set);
        }
        return set.size();
    }
    void parseEmail(const string& email,set<Address>& set){
        string local;
        string domain;
        int i=0;
        char ch = email[i++];
        while(ch != '@'){
            if (ch == '.'){
                ch = email[i++];
                continue;
            }else if (ch == '+'){
                while(ch!='@'){
                    ch = email[i++];
                }
            }else{
                local.push_back(ch);
                ch = email[i++];
            }
        }
        domain = email.substr(i);
        Address temp(local,domain);
        set.insert(temp);
    }
};
