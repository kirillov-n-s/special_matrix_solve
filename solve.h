#pragma once

#include "specmat.h"

namespace num
{
    template<std::floating_point T>
    vector<T> solve(specmat<T> mat, vector<T> vec);
}

namespace num
{
    template<std::floating_point T>
    vector<T> solve(specmat<T> mat, vector<T> vec)
    {
        //aliases
        auto& a = mat.a;
        auto& b = mat.b;
        auto& c = mat.c;
        auto& p = mat.p;
        auto& q = mat.q;
        auto& f = vec;

        //variables & result
        std::size_t n = mat.size(), k = 1, l = n;
        vector<T> x(n), r(n - 2, 0, 2);
        T R;

        //step 3
        r[k + 1] = a[k + 1];
        for (std::size_t i = k + 1; i < l - 1; i++)
        {
            R = 1 / b[i];
            b[i] = 1;
            r[i] *= R;
            c[i] *= R;
            f[i] *= R;

            R = a[i + 1];
            a[i + 1] = 0;
            r[i + 1] = -R * r[i];
            b[i + 1] -= R * c[i];
            f[i + 1] -= R * f[i];

            R = p[i];
            p[i] = 0;
            p[k]     -= R * r[i];
            p[i + 1] -= R * c[i];
            f[k]     -= R * f[i];

            R = q[i];
            q[i] = 0;
            q[k]     -= R * r[i];
            q[i + 1] -= R * c[i];
            f[l]     -= R * f[i];
        }

        //step 3 last iteration
        //because vectors a,b,c in special matrices are of size n - 2, they cannot be indexed [l - 1]
        //that design choice saves us from the need to check if a,b,c correlate with p,q in edge cases
        R = 1 / b[l - 1];
        b[l - 1] = 1;
        r[l - 1] *= R;
        c[l - 1] *= R;
        f[l - 1] *= R;

        R = p[l - 1];
        p[l - 1] = 0;
        p[k] -= R * r[l - 1];
        p[l] -= R * c[l - 1];
        f[k] -= R * f[l - 1];

        R = q[l - 1];
        q[l - 1] = 0;
        q[k] -= R * r[l - 1];
        q[l] -= R * c[l - 1];
        f[l] -= R * f[l - 1];

        //step 4
        R = 1 / p[k];
        p[k] = 1;
        p[l] *= R;
        f[k] *= R;

        R = q[k];
        q[k] = 0;
        q[l] -= R * p[l];
        f[l] -= R * f[k];

        R = 1 / q[l];
        q[l] = 1;
        f[l] *= R;

        R = p[l];
        p[l] = 0;
        f[k] -= f[l] * R;

        //step 5
        for (std::size_t i = k + 1; i <= l - 1; i++)
            f[i] -= r[i] * f[k];

        //step 6
        x[l] = f[l];
        for (std::size_t i = l - 1; i > k; i--)
            x[i] = f[i] - c[i] * x[i + 1];
        x[k] = f[k];

        return x;
    }
}
