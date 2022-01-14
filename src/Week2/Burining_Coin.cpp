#include <iostream>
#include <vector>
#include <algorithm>

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

int f(int i, int j, VI& coins, VVI& memo){
  if(memo[i][j] != -1){return memo[i][j];}
  if(j==i+1){
    memo[i][j] = std::max(coins[i], coins[j]);
    return memo[i][j];
  }
  if(j==i){
    memo[i][j] = coins[i];
    return memo[i][j];
  }
  int val_i1 = coins[i] + f(i+2, j, coins, memo);
  int val_i2 = coins[i] + f(i+1, j-1, coins, memo);
  int val_j1 = coins[j] + f(i, j-2, coins, memo);
  int val_j2 = coins[j] + f(i+1, j-1, coins, memo);
  
  memo[i][j] = std::max(
    std::min(val_i1, val_i2),
    std::min(val_j1, val_j2)
    );
  return memo[i][j];
  
}

void testcase(){
  int n; std::cin >> n;
  VI coins(n,0);
  VVI memo(n, VI(n,-1));
  for(int i=0;i<n;++i){
    int v; std::cin >> v;
    coins[i] = v;
  }
  std::cout << f(0, n-1, coins, memo) << "\n";
}


int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i<t; i++){
    testcase();
  }
}