///1
#include <iostream>
#include <vector>
#include <algorithm>
typedef std::vector<int> VI;
void testcase(){
  int n; std::cin >> n;
  VI v;
  for(int i=0; i<n; i++){
    int h; std::cin >> h;
    v.push_back(h);
  }
  int fall = 0;
  for(int i=0; i< n; i++){
    if(fall==i+v[i]-1 && v[i]==1){
      break;
    }
    fall = std::max(fall, i+v[i]-1);
    fall = std::min(fall, n-1);

  }
  std::cout << fall + 1<< "\n";
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0;i < t;i++){
    testcase();
  }
