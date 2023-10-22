/**
 * Author: Lee Zongyu
 * Description: ans store the occurrence in dict. 
    Build to be called after all insert.
    Dfs is dp that store total Number of occurences, 
    if want one occurence, can set dp[u] = val as visited.
 */
class AC {
public:

int tot = 0;
struct Node{
    int next[26], ans, link, p;
    char pch;
    Node(int p):p(p){
        link = 0 , ans = 0;
        memset(next, 0,sizeof next);
    };
};
vector<Node> tr;

vector<int> dp;

AC(){
    tr.emplace_back(0);
}
// Trie
void insert(string s) {
    int u = 0;
    for (int i = 0; i < s.size(); i++) {
        if (!tr[u].next[s[i] - 'a']) 
            tr[u].next[s[i] - 'a'] = ++tot, tr.emplace_back(u);  
        u = tr[u].next[s[i] - 'a'];                      
    }
    tr[u].ans++;                                    
}

queue<int> q;
void build() {
    for (int i = 0; i < 26; i++)
        if (tr[0].next[i]) q.push(tr[0].next[i]);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            if (tr[u].next[i]) {
                tr[tr[u].next[i]].link = tr[tr[u].link].next[i];
                q.push(tr[u].next[i]);
            } 
            else tr[u].next[i] = tr[tr[u].link].next[i];
        }
    }
    dp.assign(tot+1,-1);
}

int dfs(int u){
    if(dp[u] != -1) return dp[u];
    if(u == 0) return dp[u] = 0;
    return dp[u] = dfs(tr[u].link) + tr[u].ans;
}

int query(string t) {
    int u = 0, res = 0;
    for (int i = 0; i < t.size(); i++) {
        u = tr[u].next[t[i] - 'a'];
        res += dfs(u);
    }
    return res;
}
};
int main(){
    string dict[] = {"i","in","tin", "sting"};
    AC ac;
    for(int i = 0; i < 4; i++)
        ac.insert(dict[i]);
    ac.build();
    cout << ac.query("stingin") << "\n";
// Debug
for(int i = 0; i <= ac.tot; i++){
    cout << i << " th Node - ";
    for(int k = 0; k < 26; k++) 
        if(ac.tr[i].next[k] != 0) 
        cout << (char)('a' + k)  << ":" << ac.tr[i].next[k] << " ";
    cout << "Suffix: " << ac.tr[i].link;
    cout << "\n";
} 
}