///4
#include "iostream"
#include "vector"
#include "set"
#include "cmath"
#include "map"
#include "algorithm"
typedef std::vector<std::map<std::pair<int,int>, int>> VM;
typedef std::vector<VM> VVM;
typedef std::vector<int> VI;
typedef std::vector<VI> VVI;
typedef std::vector<VVI> VVVI;
typedef std::vector<VVVI> VVVVI;


std::pair<int,int> cal_single(int status, int x, int m, int k){ // return new status and the number of distince fighter;
    int distinct = 0;
    int new_s = (status * 10 + x);
    int tmp = new_s;
    std::vector<int> help(k+1, 0);
    while(tmp!=0){
        help[tmp%10] = 1;
        tmp /= 10;
    }
    for(int i=0; i<k+1; i++){
        if(i !=0 && help[i]==1)
            distinct++;
    }
    return std::make_pair(new_s % (int)std::pow(10, m-1), distinct);
}

int dp(int start, int m, int len_dif, std::pair<int,int> s, VI& fighters, VVM& memo, int k){
    if(start == fighters.size()) return 0;
    if(memo[start][len_dif].find(s) == memo[start][len_dif].end()){
        double result = 0;
        // if place on the top
        auto p = cal_single(s.first, fighters[start], m, k);
        if(p.second * 1000 - std::pow(2, std::abs(len_dif + 1 - 11)) >= 0){
            result = std::max(result, p.second * 1000 - std::pow(2, std::abs(len_dif + 1 - 11))
                                      + dp(start+1, m, len_dif + 1, std::make_pair(p.first, s.second) , fighters, memo, k));
        }
        p = cal_single(s.second, fighters[start], m, k);
        if(p.second * 1000 - std::pow(2, std::abs(len_dif - 1 - 11)) >= 0){
            result = std::max(result, p.second * 1000 - std::pow(2, std::abs(len_dif - 1 - 11))
                                      + dp(start+1, m, len_dif - 1, std::make_pair(s.first, p.first), fighters, memo, k));
        }
        memo[start][len_dif][s] = (int)result;
    }
    return memo[start][len_dif][s];
}
void testcase() {
    int n,k,m;std::cin >> n >> k >> m;
    VI fighters(n);
    for(int i=0; i<n; i++){
        std::cin >> fighters[i];
        fighters[i]++;
    }
    VVM memo(n, VM(23));
    std::cout << dp(0, m, 11,std::make_pair(0,0),fighters, memo, k) << "\n";
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}