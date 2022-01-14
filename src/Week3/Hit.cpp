///1
#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "iostream"
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
void testcase(int n){
    long x,y,a,b;std::cin >> x >> y >> a >> b;
    K::Ray_2 ray(K::Point_2(x,y), K::Point_2(a,b));
    bool hit=false;
    for(int i=0; i<n; i++){
        long r,s,t,u;std::cin >> r >> s >> t >> u;
        if(hit)
          continue;
        K::Segment_2 seg(K::Point_2(r,s), K::Point_2(t,u));
        if(CGAL::do_intersect(ray, seg)){
            hit=true;
        }
    }
    std::cout << (hit ? "yes\n": "no\n"); 
    
}
int main(){
    std::ios_base::sync_with_stdio(false);
    int n;std::cin >> n;
    while(n!=0){
        testcase(n);
        std::cin >> n;
    }
}