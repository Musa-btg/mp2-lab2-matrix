// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0 || sz > MAX_VECTOR_SIZE)
        throw length_error("Vector size should be greater than zero");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {

      sz = v.sz;
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept: sz(v.sz) {
      pMem = v.pMem;
      v.pMem = nullptr;
      v.sz = 0;     
  }
  ~TDynamicVector()
  {
      delete[] pMem;
      pMem = nullptr;
  }
  TDynamicVector& operator=(const TDynamicVector& v) 
  {

      if (this == &v)
          return *this;
      sz = v.sz;
      delete[] pMem;
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept 
  {
      if (this == &v)
          return *this;
      delete[] pMem;
      sz = v.sz;
      pMem = v.pMem;

      v.pMem = nullptr;
      v.sz = 0;

      return *this;
  }

  size_t size() const noexcept { 
      return sz;
  }

  // индексация
  T& operator[](size_t ind) {

      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {

      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  { 
      if (ind >= sz)
          throw out_of_range(" ");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz)
          throw out_of_range(" ");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz)
          return 0;
      for (size_t i = 0; i <sz; i++) {
          if (pMem[i] != v.pMem[i])
              return 0;
      }
      return 1;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++)
          tmp[i] = pMem[i] + val;
      return tmp;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] - val;
      return tmp;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] * val;
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw std::invalid_argument("Sizes must be equal for addition");
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] + v.pMem[i];
      return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw std::invalid_argument("Sizes must be equal for addition");
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] - v.pMem[i];
      return tmp;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz)
          return T();
      T ans = T();
      for (size_t i = 0; i < sz; i++)
          ans += pMem[i] * v.pMem[i];
      return ans;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (s > MAX_MATRIX_SIZE) 
            throw std::length_error("Matrix is too large");
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz) return false;
        for (size_t i = 0; i < sz; i++) {
            // Используем уже написанный operator== для вектора
            if (pMem[i] != m.pMem[i]) return false;
        }
        return true;
    }

    // матрично-скалярные операции (умножение всех элементов на число)
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            tmp.pMem[i] = pMem[i] * val; // Используем оператор * вектора на скаляр
        }
        return tmp;
    }

    // матрично-векторные операции (умножение матрицы на вектор-столбец)
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        // В идеале тут нужна проверка, что sz == v.size()
        TDynamicVector<T> result(sz);
        for (size_t i = 0; i < sz; i++) {
            // Скалярное произведение i-й строки матрицы на вектор v
            result[i] = pMem[i] * v;
        }
        return result;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        TDynamicMatrix tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            tmp.pMem[i] = pMem[i] + m.pMem[i]; // Сложение векторов (строк)
        }
        return tmp;
    }

    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        TDynamicMatrix tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            tmp.pMem[i] = pMem[i] - m.pMem[i]; // Вычитание векторов (строк)
        }
        return tmp;
    }


    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        TDynamicMatrix tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                T sum = T(); // Сумма для элемента [i][j]
                for (size_t k = 0; k < sz; k++) {
                    sum += pMem[i][k] * m.pMem[k][j]; // Классическое умножение матриц
                }
                tmp[i][j] = sum;
            }
        }
        return tmp;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++) {
            istr >> v.pMem[i]; // Используем оператор >> для вектора (читает строку)
        }
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++) {
            ostr << v.pMem[i] << "\n"; // Выводим строку и переходим на новую
        }
        return ostr;
    }
};
#endif
