#include <string>

#include "solve.h"

using real = double;

int main()
{
    //define table format

    std::string head_err = "MEAN RELATIVE ERROR",
                head_est = "MEAN PRECISION ESTIMATE",
                sep = " | ";

    std::size_t real_places = num::format<real>(std::cout, false),
                int_places  = std::log10(std::numeric_limits<std::size_t>::max()) + 1,
                width_err   = std::max(real_places, head_err.size()),
                width_est   = std::max(real_places, head_est.size());

    auto border = [&int_places, &width_err, &width_est](std::ostream& out)
    {
        out << std::setfill('_') << ' '
            << std::setw(int_places + 1) << "|"
            << std::setw(int_places + 3) << "|"
            << std::setw(width_err + 3) << "|"
            << std::setw(width_est + 1) << "_"
            //<< std::setfill(' ')
            << std::endl;
    };

    auto padding = [&int_places, &width_err, &sep](std::ostream& out)
    {
        out << std::setfill(' ')
            << std::setw(int_places + 3) << sep
            << std::setw(int_places + 3) << sep
            << std::setw(width_err + 3) << sep
            << std::endl;
    };

    padding(std::cout);
    std::cout << std::setw(int_places) << "SIZE" << sep
              << std::setw(int_places) << "LIMITS" << sep
              << std::setw(width_err) << head_err << sep
              << std::setw(width_est) << head_est
              << std::endl;
    border(std::cout);

    //actual method testing

    auto sizes  = { 10, 100, 1000, 10000, 100000, 1000000, 10000000 };
    auto limits = { 1, 10, 100, 1000 };
    std::size_t tests = 32;

    for (auto n : sizes)
    {
        padding(std::cout);
        for (auto m : limits)
        {
            real mean_err = 0,
                 mean_est = 0;

            for (int i = 0; i < tests; i++)
            {
                real r = m;

                num::spmatrix<real> A(n, -r, r);
                num::vector<real>  e_(n, 1.);
                num::vector<real>  x_(n, -r, r);

                auto fe = A * e_;
                auto fx = A * x_;

                auto e = num::solve(A, fe);
                auto x = num::solve(A, fx);

                mean_err += ((x - x_) / x_).norm();
                mean_est += ((e - e_) / e_).norm();
            }

            mean_err /= tests;
            mean_est /= tests;

            std::cout << std::setw(int_places) << std::to_string(n) << sep
                      << std::setw(int_places) << std::to_string(-m) + " .. " + std::to_string(m) << sep
                      << std::setw(width_err) << mean_err << sep
                      << std::setw(width_est) << mean_est
                      << std::endl;
        }
        border(std::cout);
    }
    std::cin.get();
}
