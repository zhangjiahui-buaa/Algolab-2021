#include "iostream"
#include "CGAL/QP_functions.h"
#include "CGAL/QP_models.h"
#include "CGAL/Gmpz.h"

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


long floor_to_long(CGAL::Quotient<ET>& x){
    double a = std::floor(CGAL::to_double(x));
    while(a>x) a--;
    while(a+1<=x) a++;
    return (long)a;
}
void testcase(int n,int m){
    std::vector<std::pair<int,int>> nutrients;
    for(int i=0; i<n; i++){
        int mini, maxi;std::cin >> mini >> maxi;
        nutrients.push_back(std::make_pair(mini, maxi));
    }
    std::vector<int> prices;
    std::vector<std::vector<int>> matrix(m);
    Program lp(CGAL::SMALLER, true, 0, false, 0);
    for(int i=0; i<m; i++){
        int p;std::cin >> p;
        lp.set_c(i, p);
        prices.push_back(p);
        for(int j=0;j<n;j++){
            int c;std::cin >> c;
            lp.set_a(i,j,c); 
            lp.set_a(i,n+j,-c);
        }
    }
    for(int j=0;j<n;j++){
        lp.set_b(j,nutrients[j].second);
        lp.set_b(j+n, -nutrients[j].first);
    }
    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_infeasible()) std::cout << "No such diet.\n";
    else
        std::cout << floor_to_long(s.objective_value())<<"\n";

}
int main(){
    int n,m;std::cin >> n >> m;
    while(n!=0 || m!=0){
        testcase(n,m);
        std::cin >> n >> m;
    }
}