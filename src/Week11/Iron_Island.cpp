#include "iostream"
#include "vector"
#include "unordered_map"
typedef std::vector<int> VI;
typedef std::vector<VI> VVI;
void testcase() {
    int n,k,w;std::cin >> n >> k >> w;
    VI irlands(n,0);
    for(int i=0; i<n; i++)
        std::cin >> irlands[i];
    VVI pipes(w);
    int max_single = 0;
    for(int i=0; i<w; i++){
        int l;std::cin >> l;
        for(int j=0; j<l; j++){
            int r;std::cin >> r;
            pipes[i].push_back(r);
        }
        int max_num = 0, left = 0, right = left+1;
        int sum = irlands[pipes[i][left]];
        while(left<l && right<=l){
            if(sum==k){
                max_num = std::max(max_num, right- left);
                sum -= irlands[pipes[i][left++]];
                if(left==right){
                    if(right < l)
                        sum += irlands[pipes[i][right++]];
                    else break;
                }
            }else if(sum < k){
                if(right < l)
                    sum += irlands[pipes[i][right++]];
                else break;
            }else{
                sum -= irlands[pipes[i][left++]];
                if(left==right){
                    if(right < l)
                        sum += irlands[pipes[i][right++]];
                    else break;
                }
            }
        }
        max_single = std::max(max_single, max_num);
    }

    std::unordered_map<int,int> prev_pipes;
    int max_double = 0;
    for(int i=0; i<w; i++){
        int cur = 0;
        int left;
        for(int j=1; j<pipes[i].size(); j++){
            cur += irlands[pipes[i][j]];
            left = k - cur;
            if(prev_pipes.find(left)!=prev_pipes.end()){
                max_double = std::max(max_double, j + prev_pipes[left]);
            } 
        }   
        cur = 0;
        for(int j=0; j<pipes[i].size(); j++){
            cur += irlands[pipes[i][j]];
            if(prev_pipes.find(cur)!=prev_pipes.end()){
                prev_pipes[cur] = std::max(j + 1, prev_pipes[cur]);
            }else{
                prev_pipes[cur] = j + 1;
            }
        }
    }
    std::cout << std::max(max_single, max_double) << "\n";
    return;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}