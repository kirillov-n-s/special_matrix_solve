#include <fstream>
#include <string>

#include "solve.h"

using real = double;

int main()
{
    int n = 6;
    num::specmat<real> A(n);
    std::cin >> A;
    std::cin.ignore();
    num::vector<real> x(n, 1);
    auto f = A * x;
    auto x_sol = num::solve(A, f);
    std::cout << x << std::endl
              << x_sol << std::endl
              << x - x_sol;
    std::cin.get();
}
