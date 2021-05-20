#pragma once
#include <iostream>
#include <cassert>
#include <iomanip>
using namespace std;

template <typename T>
class matrix
{
private:
	T** mtr;
	int rows = 0;
	int cols = 0;
public:
	class Iterator;

	matrix(int r, int c);
	matrix(const matrix<T>& matr);
	matrix(matrix<T>&& matr);
	explicit matrix(initializer_list<initializer_list<T>> lst);
	~matrix();

	template <typename _T>
	friend ostream& operator <<(ostream& os, const matrix<_T>& matr);
	template <typename _T>
	friend istream& operator >>(istream& in, matrix<_T>& matr);
	template <typename _T>
	friend matrix<_T> operator+ (const matrix<_T>& m1, const matrix<_T>& m2);
	template <typename _T>
	friend matrix<_T> operator- (const matrix<_T>& m1, const matrix<_T>& m2);
	template <typename _T>
	friend matrix<_T> operator* (const matrix<_T>& m1, const matrix<_T>& m2);
	template <typename _T>
	friend matrix<_T> operator+ (const matrix<_T>& matr, double num);
	template <typename _T>
	friend matrix<_T> operator- (const matrix<_T>& matr, double num);
	template <typename _T>
	friend matrix<_T> operator* (const matrix<_T>& matr, double num);
	template <typename _T>
	friend matrix<_T> operator/ (const matrix<_T>& matr, double num);

	void operator= (const matrix<T>& matr);
	void operator+= (const matrix<T>& matr);
	void operator-= (const matrix<T>& matr);
	T& operator() (size_t i, size_t j);

	void set_elem(size_t i, size_t j, const T& elem);
	T& get_elem(size_t i, size_t j);
	bool is_square();
	bool is_angle();
	T& find_max();
	T& find_min();
	size_t get_rows() const;
	size_t get_columns() const;

	Iterator iterator_begin()
	{
		return Iterator(*this);
	}
	Iterator iterator_end() 
	{
		return Iterator(*this, rows * cols);
	}
};

template <typename T>
class matrix<T>::Iterator
{
private:
	T** now;
	T* first_elem;
	T* current = nullptr;
	int count = 0;
	int rows;
	int cols;
	void add_matrix(matrix<T> container_obj);
public:
	Iterator(matrix<T> container_obj);
	Iterator(matrix<T> container_obj, int _n);
	Iterator next();
	Iterator& operator++();
	T& operator* ();
	T value();
	bool is_end();
	bool operator== (Iterator b);
	bool operator!= (Iterator b);
	
};

template <typename T>
void matrix<T>::Iterator::add_matrix(matrix<T> container_obj)
{
	rows = container_obj.rows;
	cols = container_obj.cols;
	now = new T * [rows];
	T* v = new T[rows * cols];
	for (int i = 0; i < rows; i++)
	{
		now[i] = v + i * cols;
		for (int j = 0; j < cols; j++)
			now[i][j] = container_obj.mtr[i][j];
	}
	first_elem = *now;
}

template <typename T>
matrix<T>::Iterator::Iterator(matrix<T> container_obj)
{
	add_matrix(container_obj);
}

template <typename T>
matrix<T>::Iterator::Iterator(matrix<T> container_obj, int _n)
{
	add_matrix(container_obj);
	*now += _n;
	count += _n;
}

template <typename T>
typename matrix<T>::Iterator matrix<T>::Iterator::next()
{
	*now += 1; 
	count += 1;
	return *this;
}

template <typename T>
typename matrix<T>::Iterator& matrix<T>::Iterator::operator++()
{
	*now += 1; 
	return *this;
}

template <typename T>
T& matrix<T>::Iterator::operator*()
{
	return **now;
}

template <typename T>
T matrix<T>::Iterator::value()
{
	return **now;
}

template <typename T>
bool matrix<T>::Iterator::is_end()
{
	return *now == first_elem + cols * rows;
}

template <typename T>
bool matrix<T>::Iterator::operator==(Iterator b)
{
	current = first_elem + b.count;
	return *now == current;
}
template <typename T>
bool matrix<T>::Iterator::operator!=(Iterator b)
{
	current = first_elem + b.count;
	return *now != current;
}

//Конструкторы, деструктор и методы класса matrix
template <typename T>
matrix<T>::matrix(int r, int c)
{
	assert(r != 0 && c != 0);
	this->rows = r;
	this->cols = c;
	T* v = new T[rows * cols];
	mtr = new T * [rows];
	for (int i = 0; i < rows; i++)
		mtr[i] = v + i * cols;
}

template<typename T>
matrix<T>::matrix(const matrix<T>& matr)
{
    assert(mart.rows != 0 && matr.cols != 0);
	rows = matr.rows;
	cols = matr.cols;
	this->mtr = new T * [rows];
	T* v = new T[rows * cols];
	for (int i = 0; i < rows; i++)
	{
		this->mtr[i] = v + i * cols;
		for (int j = 0; j < cols; j++)
			this->mtr[i][j] = matr.mtr[i][j];
	}
}

template<typename T>
matrix<T>::matrix(matrix<T>&& matr)
{
    assert(mart.rows != 0 && matr.cols != 0);
	rows = matr.rows;
	cols = matr.cols;
	mtr = new T * [rows];
	T* v = new T[rows * cols];
	for (int i = 0; i < rows; i++)
	{
		this->mtr[i] = v + i * cols;
		for (int j = 0; j < cols; j++)
			this->mtr[i][j] = matr.mtr[i][j];
	}
}

template <typename T>
matrix<T>::matrix(initializer_list<initializer_list<T>> lst)
{
	rows = lst.size();
	int max = 0;
	for (auto& list : lst)
		if (list.size() >= max)
			max = list.size();
	cols = max;
	T* v = new T[rows * cols];
	mtr = new T * [rows];
	for (int i = 0; i < rows; i++)
		mtr[i] = v + i * cols;

	int count1 = 0;
	int count2 = 0;
	for (auto& list : lst)
	{
		for (auto& element : list)
		{
			mtr[count1][count2] = element;
			++count2;
		}
		++count1;
		count2 = 0;
	}
}

template <typename T>
matrix<T>::~matrix()
{
	rows = 0;
	cols = 0;
	delete[] * mtr;
	delete[] mtr;
}

template <typename _T> 
ostream& operator <<(ostream& os, const matrix<_T>& matr)
{
	for (int i = 0; i < matr.rows; i++)
	{
		cout << "\n";
		for (int j = 0; j < matr.cols; j++)
			os << matr.mtr[i][j] << setw(5);
	}
	return os;
}

template <typename _T>
istream& operator >>(istream& in, matrix<_T>& matr)
{
	for (int i = 0; i < matr.rows; i++)
		for (int j = 0; j < matr.cols; j++)
			in >> matr.mtr[i][j];
	return in;
}

template <typename _T>
matrix<_T> operator+ (const matrix<_T>& m1, const matrix<_T>& m2)
{	
	assert(m1.rows == m2.rows);
	assert(m1.cols == m2.cols);
	matrix<_T> sum(m1.rows, m1.cols);
	for (int i = 0; i < m1.rows; i++)
		for (int j = 0; j < m1.cols; j++)
			sum.mtr[i][j] = m1.mtr[i][j] + m2.mtr[i][j];
	return sum;
}

template <typename _T>
matrix<_T> operator- (const matrix<_T>& m1, const matrix<_T>& m2)
{
	assert(m1.rows == m2.rows);
	assert(m1.cols == m2.cols);
	matrix<_T> dif(m1.rows, m1.cols);
	for (int i = 0; i < m1.rows; i++)
		for (int j = 0; j < m1.cols; j++)
			dif.mtr[i][j] = m1.mtr[i][j] - m2.mtr[i][j];
	return dif;
}

template <typename _T>
matrix<_T> operator* (const matrix<_T>& m1, const matrix<_T>& m2)
{
	assert(m1.rows == m2.cols);
	matrix<_T> mult(m1.rows, m2.cols);
	for (int i = 0; i < m1.rows; i++)
	{
		for (int j = 0; j < m2.cols; j++)
		{
			mult.mtr[i][j] = 0;
			for (int k = 0; k < m1.cols; k++)
				mult.mtr[i][j] += m1.mtr[i][k] * m2.mtr[k][j];
		}
	}
	return mult;
}

template <typename _T>
matrix<_T> operator+ (const matrix<_T>& matr, double num)
{
	matrix<_T> sum(matr.rows, matr.cols);
	for (int i = 0; i < matr.rows; i++)
	{
		for (int j = 0; j < matr.cols; j++)
		{
			if (i == j)
				sum.mtr[i][j] = matr.mtr[i][j] + num;
			else
				sum.mtr[i][j] = matr.mtr[i][j];
		}
	}
	return sum;
}

template <typename _T>
matrix<_T> operator- (const matrix<_T>& matr, double num)
{
	matrix<_T> dif(matr.rows, matr.cols);
	for (int i = 0; i < matr.rows; i++)
	{
		for (int j = 0; j < matr.cols; j++)
		{
			if (i == j)
				dif.mtr[i][j] = matr.mtr[i][j] - num;
			else
				dif.mtr[i][j] = matr.mtr[i][j];
		}
	}
	return dif;
}

template <typename _T>
matrix<_T> operator* (const matrix<_T>& matr, double num)
{
	matrix<_T> mult(matr.rows, matr.cols);
	for (int i = 0; i < matr.rows; i++)
		for (int j = 0; j < matr.cols; j++)
			mult.mtr[i][j] = matr.mtr[i][j] * num;
	return mult;
}

template <typename _T>
matrix<_T> operator/ (const matrix<_T>& matr, double num)
{
	assert(num != 0);
	matrix<_T> div(matr.rows, matr.cols);
	for (int i = 0; i < matr.rows; i++)
		for (int j = 0; j < matr.cols; j++)
			div.mtr[i][j] = matr.mtr[i][j]/num;
	return div;
}

template<typename T>
void matrix<T>::operator=(const matrix<T>& matr)
{
	if (mtr != nullptr)
	{
		delete[] * mtr;
		delete[] mtr;
	}
	rows = matr.rows;
	cols = matr.cols;
	mtr = new T * [rows];
	T* v = new T[rows * cols];
	for (int i = 0; i < rows; i++)
	{
		mtr[i] = v + i * cols;
		for (int j = 0; j < cols; j++)
			mtr[i][j] = matr.mtr[i][j];
	}
}

template<typename T>
void matrix<T>::operator+=(const matrix<T>& matr)
{
	if (rows == matr.rows && cols == matr.cols)
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				mtr[i][j] += matr.mtr[i][j];
	}
	else
		cout << "\nНельзя складывать матрицы разной размерности\n";
}

template<typename T>
void matrix<T>::operator-=(const matrix<T>& matr)
{
	if (rows == matr.rows && cols == matr.cols)
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				mtr[i][j] -= matr.mtr[i][j];
	}
	else
		cout << "\nНельзя вычитать матрицы разной размерности\n";
}

template <typename T>
T& matrix<T>::operator()(size_t i, size_t j)
{
	return mtr[i][j];
}

template <typename T>
void matrix<T>::set_elem(size_t i, size_t j, const T& elem)
{
	this->mtr[i][j] = elem;
}

template <typename T>
T& matrix<T>::get_elem(size_t i, size_t j)
{
	return this->mtr[i][j];
}

template <typename T>
bool matrix<T>::is_square()
{
	return rows == cols;
}

template <typename T>
bool matrix<T>::is_angle()
{
	bool check = 1;
	if (is_square())
	{
		for (int i = 0; i < rows && check; i++)
			for (int j = 0; j < cols && check; j++)
				if (j < i && mtr[i][j] != 0)
					check = 0;
	}
	else
		check = 0;
	return check;
}

template <typename T>
T& matrix<T>::find_max()
{
	T max = mtr[0][0];
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (mtr[i][j] > max)
				max = mtr[i][j];
	return max;
}

template <typename T>
T& matrix<T>::find_min()
{
	T min = mtr[0][0];
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (mtr[i][j] < min)
				min = mtr[i][j];
	return min;
}

template <typename T>
size_t matrix<T>::get_rows() const
{
	return this->rows;
}

template <typename T>
size_t matrix<T>::get_columns() const
{
	return this->cols;
}