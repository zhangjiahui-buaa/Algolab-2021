#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "CGAL/Delaunay_triangulation_2.h"
#include "CGAL/Triangulation_face_base_with_info_2.h"
#include "iostream"
#include "vector"
#include "queue"
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_face_base_with_info_2<long, K> Fb;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef K::Point_2 Point;
struct item{
    long dis;
    Triangulation::Face_handle v;
};
void pre(Triangulation&t){
    auto cmp = [](item&o1, item&o2){return o1.dis < o2.dis;};
    std::priority_queue<item, std::vector<item>, decltype(cmp)> pq(cmp);
    for(Triangulation::Face_handle it = t.all_faces_begin(); it!=t.all_faces_end(); it++){
        if(t.is_infinite(it)){
            pq.push({LONG_MAX, it});
        }
        it->info() = -1;
    }
    while(!pq.empty()){
        auto top = qp.top();
        pq.pop();
        auto handle = top.v;
        long dis = top.dis;
        if(handle->info!=-1)
            continue;
        handle->info() = dis;

        for(int i=0; i<3; i++){
            auto nei = handle->neighbor(i);
            if(nei->info()==-1 && !t.is_infinite(nei)){
                Point p1 = handle->vertex((i+1)%3).point();
                Point p2 = handle->vertex((i+2)%3).point();
                pq.push({std::min(dis, (long)CGAL::squared_distance(p1,p2)), nei});
            }
        }
    }
}
void testcase(int n){
    std::vector<Point> pts;
    for(int i=0; i<n; i++){
        int x,y;std::cin >> x >> y;
        pts.emplace_back(Point(x,y));
    }
    Triangulation t;
    t.insert(pts.begin(), pts.end());
    pre(t);
    int m;std::cin >> m;
    for(int i=0; i<m; i++){
        int x,y;
        long d;
        std::cin >> x >> y >> d;
        Point pt(x,y);
        if(CGAL::squared_distance(t.nearest_vertex(pt).point(), pt) < d){
            std::cout << "n";
            continue;
        }
        Triangulation::Face_handle f = t.locate(pt);
        if(f->info()>=4*d){
            std::cout << "y";
        }else{
            std::cout << "n";
        }
    }
    std::cout << "\n";
}

int main(){
    int n;std::cin >> n;
    while(n!=0){
        testcase(n);
        std::cin >> n;
    }
}