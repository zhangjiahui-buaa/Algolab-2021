#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "CGAL/Delaunay_triangulation_2.h"
#include "iostream"
#include "vector"

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 Point;
void testcase(int n){
    std::vector<Point> pts;
    for(int i=0; i<n; i++){
        int x,y;std::cin >> x >> y;
        pts.emplace_back(Point_2(x,y));
    }
    Triangulation t;
    t.insert(pts.begin(), pts.end());

    int m;std::cin >> m;
    for(int i=0; i<m; i++){
        int x,y;std::cin >> x >> y;
        std::cout << CGAL::squared_distance(t.nearest_vertex(Point(x,y))->point(), Point(x,y)) << "\n";
    }
}

int main(){
    int n;std::cin >> n;
    while(n!=0){
        testcase(n);
        std::cin >> n;
    }
}