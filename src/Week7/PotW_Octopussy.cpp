///4
#include "iostream"
#include "vector"
#include "algorithm"
struct b_type{
    int idx;
    int time;
    bool is_de;
};

int de(int index, std::vector<b_type>& bombs){
    if(bombs[index].is_de)
        return 0;
    int result =  1 + (2*index+1 < bombs.size() ? de(2*index+1, bombs) : 0) + (2*index+2 < bombs.size() ? de(2*index+2, bombs) : 0);
    bombs[index].is_de = true;
    return result;
}

void testcase() {
    int n;std::cin >> n;
    std::vector<b_type> bombs;
    std::vector<b_type> tmp;
    for(int i=0; i<n; i++){
        int t;std::cin >> t;
        bombs.push_back({i, t, false});
        tmp.push_back({i,t,false});
    }
    std::sort(tmp.begin(), tmp.end(), [](b_type& b1, b_type& b2){
        return b1.time < b2.time;
    });
    int cur_time = 0;
    for(int i=0; i<n; i++){
        int idx = tmp[i].idx;
        if(bombs[idx].is_de)
            continue;
        else{
            int cost = de(idx, bombs);
            if(cost  > bombs[idx].time - cur_time){
                std::cout << "no\n";
                return;
            }else{
                cur_time += cost;
            }
        }
    }
    std::cout << "yes\n";
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}