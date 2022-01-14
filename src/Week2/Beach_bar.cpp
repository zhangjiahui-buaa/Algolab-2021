///2
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

void push_position(int start, int val, VI& position){
  if(val % 2==0){
    if (std::find(position.begin(), position.end(), start + val/2) == position.end())
    position.push_back(start + val/2);
  }
  else{
      if (std::find(position.begin(), position.end(), start + std::ceil((double)val/2)-1) == position.end())
      position.push_back(start + std::ceil((double)val/2)-1);
      if (std::find(position.begin(), position.end(), start + std::ceil((double)val/2)) == position.end())
      position.push_back(start + std::ceil((double)val/2));
  }
}

void testcase(){
  int n; std::cin >> n;
  VI parasol(n,0);
  for(int i=0;i<n;i++){
    std::cin >> parasol[i];
  }
  std::sort(parasol.begin(), parasol.end());
  int i=0,j=0,val=parasol[j] - parasol[i];
  int cur_count = 0; int max_count = -1;
  VI position;
  int mini_dis = -1, cur_dis = -1;;
  while(true){
    if(val <= 200){
      cur_count = j-i+1;
      
      if(cur_count == max_count){
        cur_dis = std::ceil((double)val/2);
        if(cur_dis < mini_dis){
          position.clear();
          push_position(parasol[i], val, position);
          mini_dis = cur_dis;
        }
        if(cur_dis == mini_dis){
          push_position(parasol[i], val, position);
        }
      }
      
      if(cur_count > max_count){
        mini_dis = std::ceil((double)val/2);
        position.clear();
        push_position(parasol[i], val, position);
        max_count = cur_count;
      }
      
      if(j == n-1){
        break;
      }
      j++;
      val = parasol[j] - parasol[i];
    }
    else{
      i++;
      val = parasol[j] - parasol[i];
    }
  }
  std::cout << max_count << " " << mini_dis << "\n";
  for(auto it = position.begin(); it!=position.end(); it++){
    std::cout << *it << " ";
  }
  std::cout << "\n";
  
}


int main(){
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i=0; i< t;i++){
    testcase();
  }
}