#pragma once

#include "vector.h"

namespace num
{
    template<std::floating_point T>
    class specmat;

    template<std::floating_point T>
    bool operator==(const specmat<T> &lhs, const specmat<T> &rhs);
    template<std::floating_point T>
    bool operator!=(const specmat<T> &lhs, const specmat<T> &rhs);

    template<std::floating_point T>
    specmat<T> operator-(const specmat<T> &mat);
    template<std::floating_point T>
    specmat<T> operator+(const specmat<T> &lhs, const specmat<T> &rhs);
    template<std::floating_point T>
    specmat<T> operator-(const specmat<T> &lhs, const specmat<T> &rhs);

    template<std::floating_point T>
    specmat<T> operator*(const specmat<T> &mat, const T &scalar);
    template<std::floating_point T>
    specmat<T> operator*(const T &scalar, const specmat<T> &mat);
    template<std::floating_point T>
    vector<T> operator*(const specmat<T> &mat, const vector<T> &vec);

    template<std::floating_point T>
    std::ostream &operator<<(std::ostream &out, const specmat<T> &mat);
    template<std::floating_point T>
    std::istream &operator>>(std::istream &in, specmat<T> &mat);
}

namespace num
{
    template<std::floating_point T>
    class specmat
    {
    public:
        vector<T> a, b, c, p, q;

        specmat(std::size_t size = 1, const T &value = 0);
        specmat(const vector<T> &a,
                const vector<T> &b,
                const vector<T> &c,
                const vector<T> &p,
                const vector<T> &q);
        specmat(std::size_t size, const T &min, const T &max);
        specmat(std::size_t size,
                const T &min_a, const T &max_a,
                const T &min_b, const T &max_b,
                const T &min_c, const T &max_c,
                const T &min_p, const T &max_p,
                const T &min_q, const T &max_q);

        specmat(const specmat &other);
        specmat &operator=(const specmat &other);

        std::size_t size() const;

        /*friend bool operator==<T>(const specmat &lhs, const specmat &rhs);
        friend bool operator!=<T>(const specmat &lhs, const specmat &rhs);*/

        friend specmat operator-<T>(const specmat &mat);
        friend specmat operator+<T>(const specmat &lhs, const specmat &rhs);
        friend specmat operator-<T>(const specmat &lhs, const specmat &rhs);

        friend specmat operator*<T>(const specmat<T> &mat, const T &scalar);
        friend vector<T> operator*<T>(const specmat<T> &mat, const vector<T> &vec);

        friend std::ostream &operator<<<T>(std::ostream &out, const specmat &mat);
        friend std::istream &operator>><T>(std::istream &in, specmat &mat);
    };
}

namespace num
{
    template<std::floating_point T>
    specmat<T>::specmat(std::size_t size, const T &value)
            : a(size - 2, value, 2),
              b(size - 2, value, 2),
              c(size - 2, value, 2),
              p(size, value),
              q(size, value)
              {}

    template<std::floating_point T>
    specmat<T>::specmat(const vector<T> &a,
                        const vector<T> &b,
                        const vector<T> &c,
                        const vector<T> &p,
                        const vector<T> &q)
            : a(a, 2), b(b, 2), c(c, 2), p(p), q(q) {}

    template<std::floating_point T>
    specmat<T>::specmat(std::size_t size, const T &min, const T &max)
            : a(size - 2, min, max, 2),
              b(size - 2, min, max, 2),
              c(size - 2, min, max, 2),
              p(size, min, max),
              q(size, min, max)
    {}

    template<std::floating_point T>
    specmat<T>::specmat(std::size_t size,
                        const T &min_a, const T &max_a,
                        const T &min_b, const T &max_b,
                        const T &min_c, const T &max_c,
                        const T &min_p, const T &max_p,
                        const T &min_q, const T &max_q)
            : a(size - 2, min_a, max_a, 2),
              b(size - 2, min_b, max_b, 2),
              c(size - 2, min_c, max_c, 2),
              p(size, min_p, max_p),
              q(size, min_q, max_q)

    {}

    template<std::floating_point T>
    specmat<T>::specmat(const specmat &other)
            : a(other.a), b(other.b), c(other.c), p(other.p), q(other.q) {}

    template<std::floating_point T>
    specmat<T> &specmat<T>::operator=(const specmat<T> &other)
    {
        a = other.a;
        b = other.b;
        c = other.c;
        p = other.p;
        q = other.q;
        return *this;
    }

    template<std::floating_point T>
    std::size_t specmat<T>::size() const
    {
        return p.size();
    }

    /*template<std::floating_point T>
    bool operator==(const specmat<T> &lhs, const specmat<T> &rhs)
    {
        return lhs.a == rhs.a && lhs.b == rhs.b && lhs.c == rhs.c && lhs.p == rhs.p && lhs.q == rhs.q;
    }

    template<std::floating_point T>
    bool operator!=(const specmat<T> &lhs, const specmat<T> &rhs)
    {
        return !(lhs == rhs);
    }*/

    template<std::floating_point T>
    specmat<T> operator-(const specmat<T> &mat)
    {
        return specmat<T>(-mat.a, -mat.b, -mat.c, -mat.p, -mat.q);
    }

    template<std::floating_point T>
    specmat<T> operator+(const specmat<T> &lhs, const specmat<T> &rhs)
    {
        return specmat<T>(lhs.a + rhs.a, lhs.b + rhs.b, lhs.c + rhs.c, lhs.p + rhs.p, lhs.q + rhs.q);
    }

    template<std::floating_point T>
    specmat<T> operator-(const specmat<T> &lhs, const specmat<T> &rhs)
    {
        return specmat<T>(lhs.a - rhs.a, lhs.b - rhs.b, lhs.c - rhs.c, lhs.p - rhs.p, lhs.q - rhs.q);
    }

    template<std::floating_point T>
    specmat<T> operator*(const specmat<T> &mat, const T &scalar)
    {
        return specmat<T>(mat.a * scalar, mat.b * scalar, mat.c * scalar, mat.p * scalar, mat.q * scalar);
    }

    template<std::floating_point T>
    specmat<T> operator*(const T &scalar, const specmat<T> &mat)
    {
        return mat * scalar;
    }

    template<std::floating_point T>
    vector<T> operator*(const specmat<T> &mat, const vector<T> &vec)
    {
        int n = mat.size();
        vector<T> res(n);
        res[1] = mat.p * vec;
        for (int i = 2; i < n; i++)
            res[i] = mat.a[i] * vec[i - 1] + mat.b[i] * vec[i] + mat.c[i] * vec[i + 1];
        res[n] = mat.q * vec;
        return res;
    }

    template<std::floating_point T>
    std::ostream &operator<<(std::ostream &out, const specmat<T> &mat)
    {
        int n = mat.size();
        int places = format<T>(out);
        out << mat.p;
        for (int i = 2; i <= n - 1; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (j == i + 1)
                    out << std::setw(places) << mat.c[i];
                else if (j == i)
                    out << std::setw(places) << mat.b[i];
                else if (j == i - 1)
                    out << std::setw(places) << mat.a[i];
                else
                    out << std::setw(places) << 0;
            }
            out << std::endl;
        }
        out << mat.q;
        return out;
    }

    template<std::floating_point T>
    std::istream &operator>>(std::istream &in, specmat<T> &mat)
    {
        return in >> mat.a >> mat.b >> mat.c >> mat.p >> mat.q;
    }
}
