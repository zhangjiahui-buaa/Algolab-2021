#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "CGAL/Delaunay_triangulation_2.h"
#include "CGAL/Triangulation_vertex_base_with_info_2.h"
#include "iostream"
#include "vector"
#include "climits"
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef CGAL::Triangulation_vertex_base_with_info_2<long, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;

int number(Triangulation& t, long time){
    long radius = 4*time*time*time*time + 4*time*time + 1;
    int result = 0;
    for(Triangulation::Vertex_iterator it = t.finite_vertices_begin(); it != t.finite_vertices_end(); it++){
        if(it->info() <= radius)
            result++;
    }
    return result;
}
int find_time(Triangulation&t, int die_number){
    int left = 0, right = 1024*8;
    while(left < right){
        int pivot = (left+right)/2;
        int num = number(t, pivot);
        if(num <= die_number)
            left = pivot+1;
        else 
            right = pivot;
    } 
    return left;
}
void testcase(int n){
    int l,b,r,top; std::cin >> l >> b >> r >> top;
    std::vector<Point> pts;
    for(int i=0; i<n; i++){
        int x,y;std::cin >> x >> y;
        pts.push_back(Point(x,y));
    }
    Triangulation t;
    t.insert(pts.begin(), pts.end());
    for(Triangulation::Vertex_iterator it = t.finite_vertices_begin(); it != t.finite_vertices_end(); it++){
        Point pt = it->point();
        it->info() = LONG_MAX;
        long x_dis = std::min(pt.x()-l, r-pt.x());
        long y_dis = std::min(pt.y()-b, top-pt.y());
        long dis = std::min(x_dis, y_dis);
        if(dis == 0){
            it->info() = 1;
        }else{
            it->info() = 4 * dis * dis;
            Triangulation::Edge_circulator c = t.incident_edges(it);
            if(!c.is_empty()){
                do{
                    if(!t.is_infinite(c)){
                        if(t.segment(c).squared_length() <= 1){
                            it->info() = 1;
                        }else{
                            it->info() = std::min(it->info(), (long)t.segment(c).squared_length());
                        }
                    }
                }while(++c != t.incident_edges(it));
            }
        }
    }
    std::cout << find_time(t,0) << " " << find_time(t, n/2) << " " << find_time(t, n-1) << "\n";
}

int main(){
    int n;std::cin >> n;
    while(n!=0){
        testcase(n);
        std::cin >> n;
    }
}