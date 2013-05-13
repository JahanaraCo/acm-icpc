// In the name of GOD
// Algorithm : binary serach on maximum number of people that can reach parking, check greedy for fixed value

#include <iostream>
using namespace std;

const int MAXN = 100 + 5;
int A[MAXN], tmp[MAXN];
long long S[MAXN];
int N;
long long C, P, T;

long long check(long long ted){ // find minimum time required 
  int top = 1;
  for(int i=1;i<=N;i++){
    tmp[i] = A[i];
    S[i] = S[i - 1] + A[i];
    if(S[i] < ted)
      top = i + 1;
  }
  
	long long res = 0; 
	long long cur = 0;
	for(int i=top;i>=1;i--){
    long long need = ted - (S[i-1] + cur);
    if(need <= 0)
      continue;

    long long p = (need / C) + ((need % C == 0) ? 0 : 1);
    cur += need;
    res += 2 * i * P * p;
    long long over = C - (need % C);
    if(over != C){
      int pos = i - 1;
      while(pos > 0 and over > 0){
        if(tmp[pos] <= over){
	        over -= tmp[pos];
          cur += tmp[pos];
      	  tmp[pos] = 0;
      	  pos--;
        }
        else{
      	  S[pos] -= over;
      	  tmp[pos] -= over;
      	  cur += over;
      	  over = 0;
      	}
      }
    }
  }
  return res;
}

int main(){
  cin>>N>>C>>P>>T;
  long long beg, end;
  beg = end = 0;
  for(int i=1;i<=N;i++)
    cin>>A[i], end += A[i];

  while(beg < end - 1){
    long long mid = (beg + end) / 2;
    if(check(mid) <= T)
      beg = mid;
    else
      end = mid - 1;
  }
  if(beg == end - 1)
    if(check(end) <= T)
      beg = end;  
  cout<<beg<<endl;

  return 0;
}
