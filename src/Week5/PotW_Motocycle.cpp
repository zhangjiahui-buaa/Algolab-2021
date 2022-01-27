///4
#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "stack"
#include "vector"
#include "algorithm"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
struct p_type{
    int idx;
    long start;
    long dirx;
    long diry;
    K::Ray_2 ray;
};
bool replace(p_type& pa, p_type& pb){
    K::Direction_2 d1 = pa.diry >= pa.start ? pa.ray.direction() : K::Ray_2(K::Point_2(0, pa.start), K::Point_2(pa.dirx, pa.diry+2*(pa.start-pa.diry))).direction();
    K::Direction_2 d2 = pb.diry >= pb.start ? pb.ray.direction() : K::Ray_2(K::Point_2(0, pb.start), K::Point_2(pb.dirx, pb.diry+2*(pb.start-pb.diry))).direction();
    return d2 <= d1;
}
void testcase() {
    int n;std::cin >> n;
    std::vector<p_type> people;
    for(int i=0; i<n; i++){
        long y0, x1, y1;std::cin >> y0 >> x1 >> y1;
        people.push_back({i,y0,x1,y1,K::Ray_2(K::Point_2(0,y0), K::Point_2(x1,y1))});
    }
    std::sort(people.begin(), people.end(), [](p_type& p1, p_type& p2){return p1.start > p2.start;});
    std::stack<p_type> s;
    for(int i=0; i<people.size(); i++){
        if(s.empty()) s.push(people[i]);
        else{
            if(CGAL::do_intersect(s.top().ray, people[i].ray)){
                bool die = false;
                while(!s.empty() && CGAL::do_intersect(s.top().ray, people[i].ray)){
                    if(replace(s.top(), people[i]))
                        s.pop();
                    else{
                        die = true;
                        break;
                    }
                }
                if(!die)
                    s.push(people[i]);
            }else{
                s.push(people[i]);
            }
        }
    }
    people.clear();
    while(!s.empty()){
        auto top = s.top();
        s.pop();
        people.push_back(top);
    }
    std::sort(people.begin(), people.end(), [](p_type& p1, p_type& p2){return p1.idx < p2.idx;});
    for(p_type& p : people)
        std::cout << p.idx << " ";
    std::cout << "\n";
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}