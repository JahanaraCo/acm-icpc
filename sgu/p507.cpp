/*
In the name of ALLAH
Complexity : 
O(n + m*lg(m)*lg(n))
every leaf can insert to a new set lg(n) times, because every time size of it's set become
at least double and size of a set always is smaller than n.
*/
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 1000 * 10 * 5 + 100;
const int INF = 2147483647;
vector<int> adj[MAXN];
int value[MAXN];
int ans[MAXN], best;

set<int>* merge(set<int>* a, set<int>* b){
  bool change = false;
  if((*a).size() < (*b).size())
    swap(a, b), change = true;
  for(set<int>::iterator it = (*b).begin(); it!=(*b).end(); ++it){
    set<int>::iterator itt = (*a).lower_bound(*it);
    if(itt!=(*a).end())
      best = min(best, abs((*it) - (*itt)));
    if(itt!=(*a).begin()){
      --itt;
      best = min(best, abs((*it) - (*itt)));
    }
    (*a).insert(*it);
  }
  return a;
}

set<int>* dfs(int u){
  set<int>* res; 
  if(adj[u].size()==0){
    res = new set<int>;
    (*res).insert(value[u]);
    return res;
  }
  for(int i=0;i<adj[u].size();i++){
    int v = adj[u][i];
    if(i==0)
      res = dfs(v);
    else {
      best = INF;
      res = merge(res, dfs(v));
      ans[u] = min(ans[u], best);
    }
    ans[u] = min(ans[u], ans[v]);
  }
  return res;
}

int main(){
  ios::sync_with_stdio(false);
  for(int i=0;i<MAXN;i++)
    ans[i] = INF;
  int n, m;
  cin>>n>>m;
  for(int i=2;i<=n;i++){
    int par;
    cin>>par;
    adj[par].push_back(i);
  }
  for(int i=n-m+1;i<=n;i++)
    cin>>value[i];
  dfs(1);
  for(int i=1;i<=n-m;i++)
    cout<<ans[i]<<' ';
  cout<<endl;
  return 0;
}
