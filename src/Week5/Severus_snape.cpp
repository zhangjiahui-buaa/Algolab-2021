///4
#include "iostream"
#include "vector"
#include "algorithm"
#include "climits"
struct A_type{
    int power;
    int happy;
};
struct B_type{
    int wit;
};
typedef std::vector<long> VI;
typedef std::vector<VI> VVI;
typedef std::vector<VVI> VVVI;
long max_p(int i, int j, int h, std::vector<A_type>& pas, VVVI& memo){
    if(memo[i][j][h] == -1){
        if(j==0 ){
            if(h==0) memo[i][j][h] = 0;
            else memo[i][j][h] = -2; // not possible
        }
        else{
            long r1 = -2;
            if(i-1 >= j){
                //update r1
                r1 = max_p(i-1, j, h, pas, memo);
            }
            long r2 = -2;
            if(i-1 >= j-1){
                //update r2
                r2 = max_p(i-1, j-1, std::max(0,h-pas[i-1].happy), pas, memo) == -2 ? -2 : pas[i-1].power + max_p(i-1,j-1,std::max(0,h-pas[i-1].happy), pas, memo);
            }
            memo[i][j][h] = std::max(r1,r2);
        }
    }
    return memo[i][j][h];
}
void testcase(){
    int n,m;std::cin >> n >> m;
    long a,b; std::cin >> a >> b;
    long P,H,W; std::cin >> P >> H >> W;
    std::vector<A_type> pas(n);
    std::vector<B_type> pbs(m);
    for(int i=0; i<n; i++){
        int p,h; std::cin >> p >> h;
        pas[i] = {p,h};
    }
    for(int i=0; i<m; i++){
        int w; std::cin >> w;
        pbs[i] = {w};
    }
    std::sort(pbs.begin(), pbs.end(), [](B_type& b1, B_type& b2){
        return b1.wit > b2.wit;
    });
    int result = INT_MAX;
    VVVI memo(n+1, VVI(n+1, VI(H+1, -1)));
    for(int i=0; i<=n; i++){
        long result_p = max_p(n, i, H, pas, memo);
        long required_w = W + i * a;
        long cur_w = 0;
        int num_b = 0;
        while(num_b < m && cur_w < required_w)
            cur_w += pbs[num_b++].wit;
        if(cur_w < required_w) continue;
        long required_p = P + num_b * b;
        if(result_p >=0 && result_p >= required_p){
            result = std::min(result, num_b + i);
        }
    }
    if(result == INT_MAX)
        std::cout << "-1\n";
    else
        std::cout << result << "\n";

}
int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}