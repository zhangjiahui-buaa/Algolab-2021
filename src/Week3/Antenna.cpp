#include "CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h"
#include "CGAL/Min_circle_2_traits_2.h"
#include "CGAL/Min_circle_2.h"

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> mCircle;
double ceil_to_double(K::FT& x){
    double a = std::ceil(CGAL::to_double(x));
    while(a<x) a++;
    while(a-1>=x) a--;
    return a;
}
void testcase(int n){
    std::vector<K::Point_2> pts;
    for(int i=0; i<n; i++){
        long x,y;std::cin >> x >> y;
        pts.push_back(K::Point_2(x,y));
    }
    mCircle c(pts.begin(), pts.end(), true);
    Traits::Circle C = c.circle();
    K::FT tmp = CGAL::sqrt(C.squared_radius());
    std::cout << ceil_to_double(tmp) << "\n";
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout << std::fixed << std::setprecision(0);
    int n;std::cin >> n;
    while(n!=0){
        testcase(n);
        std::cin >> n;
    }
}