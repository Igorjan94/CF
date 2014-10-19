#include <vector>

#define FORI(n) for (unsigned i = 0; i < n; ++i)
#define FORJ(n) for (unsigned j = 0; j < n; ++j)

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
    Matrix<T> transpose();

    Matrix<T> operator+(const T& rhs);
    Matrix<T> operator-(const T& rhs);
    Matrix<T> operator*(const T& rhs);
    Matrix<T> operator/(const T& rhs);

    std::vector<T> operator*(const std::vector<T>& rhs);
};

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
    Matrix result(this);
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
    Matrix result(this);
    FORI(n)
        FORJ(m)
            result.a[i][j] += rhs;
    return result;
}


template<typename T>
Matrix<T> Matrix<T>::operator-(const T& rhs)
{
    Matrix result(this);
    FORI(n)
        FORJ(m)
            result.a[i][j] -= rhs;
    return result;
}


template<typename T>
Matrix<T> Matrix<T>::operator*(const T& rhs)
{
    Matrix result(this);
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
    printf("here\n");
    std::vector<T> result(this->n, (T) 0);
    FORI(this->n)
        FORJ(this->n)
            result[i] += a[i][j] * rhs[j];
    return result;
}

