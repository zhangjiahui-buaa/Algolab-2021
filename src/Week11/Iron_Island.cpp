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
        int max_num = 0, left = 0, right = 0;
        int sum = irlands[pipes[i][left]];
        while(right < l){
            if(sum == k){
                max_num = std::max(max_num, right - left + 1);
                sum -= irlands[pipes[i][left]];
                left++;
                if(left > right){
                    right++;
                    if(right == l) break;
                    sum += irlands[pipes[i][right]];
                }
            }else if(sum < k){
                right++;
                if(right == l) break;
                sum += irlands[pipes[i][right]];
            }else{
                sum -= irlands[pipes[i][left]];
                left++;
                if(left > right){
                    right++;
                    if(right == l) break;
                    sum += irlands[pipes[i][right]];
                }
            }
        }
        max_single = std::max(max_single, max_num);
    }

    std::unordered_map<int,int> prev_pipes;
    int max_double = 0;
    for(int i=0; i<w; i++){
        int cur_sum = 0;
        for(int j=1; j<pipes[i].size(); j++){
            cur_sum += irlands[pipes[i][j]];
            if(prev_pipes.find(k-cur_sum) != prev_pipes.end()){
                max_double = std::max(max_double, prev_pipes[k-cur_sum] + j);
            }
        }
        cur_sum = 0;
        for(int j=0; j<pipes[i].size(); j++){
            cur_sum += irlands[pipes[i][j]];
            prev_pipes[cur_sum] = std::max(prev_pipes[cur_sum], j + 1);
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