#include <vector>
#include <iostream>

#define FORI(n) for (unsigned i = 0; i < n; ++i)
#define FORJ(n) for (unsigned j = 0; j < n; ++j)

template<class Type> Type powbin(Type a, int n);

template <typename T>
std::vector<T> operator-(const std::vector<T>& a, const std::vector<T>& b)
{
    std::vector<T> c(a.size());
    FORI(a.size())
        c[i] = a[i] - b[i];
    return c;
}

template <typename T>
std::vector<T> operator*(const std::vector<T>& a, T b)
{
    std::vector<T> c(a.size());
    FORI(a.size())
        c[i] = a[i] * b;
    return c;
}

template <typename T> class Matrix
{
public:
    std::vector<std::vector<T> > a;
    unsigned n;
    unsigned m;

    Matrix(std::vector<std::vector<T> >& rhs);
    Matrix(unsigned n, unsigned m, const T& initial);
    Matrix(const Matrix<T>& rhs);
    virtual ~Matrix();

    Matrix<T>& operator=(const Matrix<T>& rhs);

    Matrix<T> operator+(const Matrix<T>& rhs);
    Matrix<T>& operator+=(const Matrix<T>& rhs);
    Matrix<T> operator-(const Matrix<T>& rhs);
    Matrix<T>& operator-=(const Matrix<T>& rhs);
    Matrix<T> operator*(const Matrix<T>& rhs);
    Matrix<T>& operator*=(const Matrix<T>& rhs);
    Matrix<T> operator^(int i);
    Matrix<T> transpose();
    Matrix<T> invert();

    Matrix<T> operator+(const T& rhs);
    Matrix<T> operator-(const T& rhs);
    Matrix<T> operator*(const T& rhs);
    Matrix<T> operator/(const T& rhs);
    Matrix<T> operator!();

    std::vector<T>& operator[](int i);
    std::vector<T> operator*(const std::vector<T>& rhs);
    T det();
};

template<typename T>
T Matrix<T>::det()
{
    if (n == 2)
        return a[0][0] * a[1][1] - a[0][1] * a[1][0];
    if (n == 3)
        return a[0][0] * a[1][1] * a[2][2] +
               a[0][1] * a[1][2] * a[2][0] +
               a[0][2] * a[1][0] * a[2][1] - 
               a[0][2] * a[1][1] * a[2][0] -
               a[0][1] * a[1][0] * a[2][2] -
               a[0][0] * a[1][2] * a[2][1];
    return 0;
}

template<typename T>
std::vector<T>& Matrix<T>::operator[](int i)
{
    return a[i];
}


template<typename T>
Matrix<T> Matrix<T>::transpose()
{
    Matrix<T> b(m, n, 0);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            b.a[j][i] = a[i][j];
    return b;
}

template<typename T>
Matrix<T> Matrix<T>::invert()
{
    Matrix<T> b(n, n, 0);
    for (int i = 0; i < n; i++)
        b.a[i][i] = 1;
    for (int i = 0; i < n; i++)
    {
        b.a[i] = b.a[i] * (1 / a[i][i]);
        a[i] = a[i] * (1 / a[i][i]);
        for (int j = i + 1; j < n; ++j)
            b.a[j] = b.a[j] - b.a[i] * a[j][i],
            a[j] = a[j] - a[i] * a[j][i];
    }
    for (int i = n - 1; i >= 0; --i)
    {
        b.a[i] = b.a[i] * (1 / a[i][i]);
        a[i] = a[i] * (1 / a[i][i]);
        for (int j = i - 1; j >= 0; --j)
            b.a[j] = b.a[j] - b.a[i] * a[j][i],
            a[j] = a[j] - a[i] * a[j][i];
    }
    return b;
}

template<typename T>
std::vector<T> operator*(const std::vector<T>& a, const Matrix<T>& rhs)
{
    std::vector<T> result(rhs.m, (T) 0);
    for (int i = 0; i < rhs.m; ++i)
        for (int j = 0; j < a.size(); ++j)
            result[i] += a[j] * rhs.a[j][i];
    return result;
}

template<typename T>
Matrix<T>::Matrix(std::vector<std::vector<T> >& rhs)
{
    this->n = rhs.size();
    this->m = rhs[0].size();
    this->a = rhs;
}

template<typename T>
Matrix<T>::Matrix(unsigned n, unsigned m, const T& initial)
{
    this->n = n;
    this->m = m;
    a.resize(n);
    FORI(n)
        a[i].resize(m, initial);
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& rhs)
{
    this->a = rhs.a;
    this->n = rhs.n;
    this->m = rhs.m;
}


template<typename T>
Matrix<T>::~Matrix() {}


template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs)
{
    if (&rhs == this)
        return *this;

    this->n = rhs.n;
    this->m = rhs.m;
    a.resize(this->n);
    FORI(this->n)
        a[i].resize(this->m);

    FORI(this->n)
        FORJ(this->m)
            a[i][j] = rhs.a[i][j];
    return *this;
}


template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& rhs)
{
    Matrix result(rhs);
    FORI(this->n)
        FORJ(this->m)
            result.a[i][j] += a[i][j];
    return result;
}


template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs)
{
    FORI(this->n)
        FORJ(this->m)
            a[i][j] += rhs.a[i][j];
    return *this;
}


template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& rhs)
{
    Matrix result(a);
    FORI(this->n)
        FORJ(this->m)
            result.a[i][j] -= rhs.a[i][j];
    return result;
}


template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& rhs)
{
    FORI(this->n)
        FORJ(this->m)
            a[i][j] -= rhs.a[i][j];
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const T& rhs)
{
    Matrix result(a);
    FORI(n)
        FORJ(m)
            result.a[i][j] += rhs;
    return result;
}


template<typename T>
Matrix<T> Matrix<T>::operator-(const T& rhs)
{
    Matrix result(a);
    FORI(n)
        FORJ(m)
            result.a[i][j] -= rhs;
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator/(const T& rhs)
{
    Matrix result(a);
    FORI(n)
        FORJ(m)
            result.a[i][j] /= rhs;
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T& rhs)
{
    Matrix result(a);
    FORI(n)
        FORJ(m)
            result.a[i][j] *= rhs;
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs)
{
    unsigned n = this->n;
    unsigned m = rhs.m;
    Matrix result(n, m, (T) 0);
    FORI(n)
        FORJ(m)
            for (unsigned k = 0; k < this->m; k++)
                result.a[i][j] += this->a[i][k] * rhs.a[k][j];
    return result;
}


template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& rhs)
{
    Matrix result = (*this) * rhs;
    (*this) = result;
    return *this;
}

template<typename T>
std::vector<T> Matrix<T>::operator*(const std::vector<T>& rhs)
{
    std::vector<T> result(this->n, (T) 0);
    FORI(this->n)
        FORJ(this->m)
            result[i] += a[i][j] * rhs[j];
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator!()
{
    Matrix<T> temp(a);
    temp = temp.transpose();
    return temp;
}

template<typename T>
Matrix<T> Matrix<T>::operator^(int i)
{
    Matrix<T> temp(a);
    if (i < 0)
        temp = temp.invert();
    i = abs(i);
    if (i > 0)
        temp = powbin(temp, i);
    return temp;
}

template<class Type>
Type powbin(Type a, int n)
{
    Type result = a;
    --n;
    while (n)
    {
        if (n & 1)
            result *= a;
        a *= a;
        n >>= 1;
    }
    return result;
}

/*

    ll t = clock();
    int n = 3;
    Matrix<double> a(n, n, 0.0);
    fori(n)
        forj(n)
            a[i][j] = rand() % 10;
    writeln(a);
    vi s({1, 2});
    fori(1000)
        forj(1000)
            writeln(s, "asdf", 1, 1.0, i + j);
    writeln("time=", clock() - t);
//time= 1576302
//time= 1731351
   */
