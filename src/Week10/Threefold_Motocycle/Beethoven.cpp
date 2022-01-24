#include "CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h"
#include "CGAL/Delaunay_triangulation_2.h"
#include "vector"
#include "iostream"
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;

void testcase() {
    int n,m;
    long w;
    std::cin >> n >> m >> w;
    K::Line_2 l(1,0,-w);
    std::vector<K::Segment_2> segs;
    for(int i=0; i<n; i++){
        long y0, x1, y1; std::cin >> y0 >> x1 >> y1;
        K::Point_2 p0(0,y0);
        const auto inter = CGAL::intersection(K::Ray_2(p0, K::Point_2(x1,y1)),l);
        const K::Point_2* p1 = boost::get<K::Point_2>(&*inter);
        segs.push_back(K::Segment_2(p0,*p1));

    }
    std::vector<K::Point_2> pts;
    for(int i=0; i<m; i++){
        long x,y;std::cin >> x >> y;
        pts.push_back(K::Point_2(x,y));
    }
    Triangulation t;
    t.insert(pts.begin(), pts.end());

    K::FT res_r;
    for(int i=0; i<n; i++){
        res_r = std::max(res_r, CGAL::squared_distance(segs[i].source(), t.nearest_vertex(segs[i].source())->point()));
        res_r = std::max(res_r, CGAL::squared_distance(segs[i].target(), t.nearest_vertex(segs[i].target())->point()));
    }
    std::cout << std::ceil(CGAL::to_double(CGAL::sqrt(res_r))) << " ";
    for(auto e = t.finite_edges_begin(); e!=t.finite_edges_end(); e++){
        K::Point_2 p1 = e->first->vertex((e->second+1)%3)->point();
        CGAL::Object dual_e = t.dual(e);
        K::Ray_2 ray;
        K::Segment_2 seg;
        K::Line_2 line;
        if(CGAL::assign(ray, dual_e)){
            for(int i=0; i<n; i++){
                if(CGAL::do_intersect(ray, segs[i])){
                    const auto inter = CGAL::intersection(ray, segs[i]);
                    if(const K::Segment_2* s = boost::get<K::Segment_2>(&*inter)){
                        res_r = std::max(res_r, CGAL::squared_distance(s->source(), p1));
                    }else if(const K::Point_2* p = boost::get<K::Point_2>(&*inter)){
                        res_r = std::max(res_r, CGAL::squared_distance(*p, p1));
                    }
                }
            }
        }
        if(CGAL::assign(seg, dual_e)){
            for(int i=0; i<n; i++){
                if(CGAL::do_intersect(seg, segs[i])){
                    const auto inter = CGAL::intersection(seg, segs[i]);
                    if(const K::Segment_2* s = boost::get<K::Segment_2>(&*inter)){
                        res_r = std::max(res_r, CGAL::squared_distance(s->source(), p1));
                    }else if(const K::Point_2* p = boost::get<K::Point_2>(&*inter)){
                        res_r = std::max(res_r, CGAL::squared_distance(*p, p1));
                    }
                }
            }
        }
        if(CGAL::assign(line, dual_e)){
            for(int i=0; i<n; i++){
                if(CGAL::do_intersect(line, segs[i])){
                    const auto inter = CGAL::intersection(line, segs[i]);
                    if(const K::Segment_2* s = boost::get<K::Segment_2>(&*inter)){
                        res_r = std::max(res_r, CGAL::squared_distance(s->source(), p1));
                    }else if(const K::Point_2* p = boost::get<K::Point_2>(&*inter)){
                        res_r = std::max(res_r, CGAL::squared_distance(*p, p1));
                    }
                }
            }
        }
    }
    std::cout << std::ceil(CGAL::to_double(CGAL::sqrt(res_r))) << "\n";
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}