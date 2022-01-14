#include "CGAL/Exact_predicates_exact_constructions_kernel.h"
typedef CGAL::Exact_predicates_exact_constructions_kernel K;


double floor_to_double(const K::FT& x) {
    double a = std::floor(CGAL::to_double(x));
    while (a > x) a -= 1;
    while (a+1 <= x) a += 1;
    return a;
}

void testcase(int n){
    long x,y,a,b;std::cin >> x >> y >> a >> b;
    K::Ray_2 ray(K::Point_2(x,y), K::Point_2(a,b));
    K::Segment_2 seg;
    K::Point_2 start(x,y);
    bool first_hit=false;
    std::vector<K::Segment_2> vs;

    for(int i=0; i<n; i++){
        long r,s,t,u;std::cin >> r >> s >> t >> u;
        vs.push_back(K::Segment_2(K::Point_2(r,s), K::Point_2(t,u)));
    }
    std::random_shuffle(vs.begin(), vs.end());
    for(int i=0; i<n; i++){
        K::Segment_2 tmp = vs[i];
        if(first_hit){
            if(CGAL::do_intersect(seg, tmp)){
                auto o = CGAL::intersection(seg, tmp);
                if(K::Point_2* op = boost::get<K::Point_2>(&*o)){
                    seg = K::Segment_2(start, *op);
                }else if(K::Segment_2* op = boost::get<K::Segment_2>(&*o)){
                    seg = CGAL::squared_distance(start, op->source()) <= CGAL::squared_distance(start, op->target()) ? 
                            K::Segment_2(start, op->source()) :
                            K::Segment_2(start, op->target());
                }
            }
        }else{
            if(CGAL::do_intersect(ray, tmp)){
                first_hit = true;
                auto o = CGAL::intersection(ray, tmp);
                if(K::Point_2* op = boost::get<K::Point_2>(&*o)){
                    seg = K::Segment_2(K::Point_2(x,y), *op);
                }else if(K::Segment_2* op = boost::get<K::Segment_2>(&*o)){
                    seg = CGAL::squared_distance(start, op->source()) <= CGAL::squared_distance(start, op->target()) ? 
                            K::Segment_2(start, op->source()) :
                            K::Segment_2(start, op->target());
                }
            }
        }
    }
    if(first_hit)
        std::cout << floor_to_double(seg.target().x()) << " " << floor_to_double(seg.target().y()) << "\n";
    else
        std::cout << "no\n";
}
int main(){
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
    std::ios_base::sync_with_stdio(false);
    int n;std::cin >> n;
    while(n!=0){
        testcase(n);
        std::cin >> n;
    }
}
