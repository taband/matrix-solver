#pragma once

/*   ===== DECLARATION =====   */

template <typename T> class vecT;
template <typename T> class matT;

typedef vecT<double> vec;
typedef matT<double> mat;



/*   ===== DEFINITION =====   */

/*   === full vector ===   */

template <typename T>
class vecT	
{
public:
	int size;
	T *entry;

public:
	vecT() { size = 0; entry = NULL; }
	~vecT() { if (entry != NULL) delete[] entry; entry = NULL; }
	vecT(int n);
	vecT(const vecT<T>& x);
	void make(int n);

	T& operator[](int n) const { return entry[n]; }

	void print(void);

	vecT<T>& operator =(const vecT<T>& x);
	vecT<T>& operator +=(const vecT<T>& x);
	vecT<T>& operator -=(const vecT<T>& x);
	vecT<T>& operator *=(int a);
	vecT<T>& operator *=(double a);

	//vecT<T> operator +(const vecT<T>& x);
	//vecT<T> operator -(const vecT<T>& x);

	//double operator,(const vecT<T>& x);

	void zeros(void);
	double l2(void);
	double lmax(void);
};

template <typename T>	vecT<T>::vecT(int n)
{
	if (entry != NULL)
	{
		delete[] entry;
		entry = NULL;
	}

	size = n;
	entry = new T[size];

	for (int i = 0; i < size; i++)
		entry[i] = 0.;
}

template <typename T>	vecT<T>::vecT(const vecT<T>& x)
{
	size = x.size;
	entry = new T[size];
	for (int i = 0; i < size; i++) entry[i] = x.entry[i];
}

template <typename T>	inline void vecT<T>::make(int n)
{
	if (entry != NULL)
	{
		delete[] entry;
		entry = NULL;
	}

	size = n;
	entry = new T[size];

	for (int i = 0; i < size; i++)
		entry[i] = (T)0.;
}

template <typename T>	inline void vecT<T>::print(void)
{
	if (size == 0 || entry == NULL)
	{
		printf("Error: Empty vector");
		return;
	}
		
	if (typeid(T) != typeid(int) && typeid(T) != typeid(double) && typeid(T) != typeid(char))
	{
		sprintf(__message, "Error: Invalid type of vector");
		print_error();
	}

	// Print a vector only when T == int, double, or char
	printf("Print a vector: \n");
	for (int i = 0; i < size; i++)
		if (typeid(T) == typeid(double))
			printf("%3d: %12.8f\n", i, entry[i]);
		else if (typeid(T) == typeid(int))
			printf("%3d: %3d\n", i, entry[i]);
		else if (typeid(T) == typeid(char))
			printf("%3d: %c\n", i, entry[i]);
}

template <typename T>	inline vecT<T>& vecT<T>::operator =(const vecT<T>& x)
{
	if (size != x.size)
	{
		if (entry != NULL)
		{
			delete[] entry;
			entry = NULL;
		}

		size = x.size;
		entry = new T[size];
	}
	
	for (int i = 0; i < x.size; i++) entry[i] = x.entry[i];

	return *this;
}

template <typename T>	inline vecT<T>& vecT<T>::operator +=(const vecT<T>& x)
{
	if (size != x.size)
	{
		if (entry != NULL)
		{
			delete[] entry;
			entry = NULL;
		}

		size = x.size;
		entry = new T[size];
	}

	for (int i = 0; i < x.size; i++) entry[i] += x.entry[i];

	return *this;
}

template <typename T>	inline vecT<T>& vecT<T>::operator -=(const vecT<T>& x)
{
	if (size != x.size)
	{
		if (entry != NULL)
			delete[] entry; entry = NULL;

		size = x.size;
		entry = new T[size];
	}

	for (int i = 0; i < x.size; i++) entry[i] -= x.entry[i];

	return *this;
}

template <typename T>	inline vecT<T>& vecT<T>::operator *=(int a)
{
	for (int i = 0; i < size; i++)
		entry[i] *= (T)a;

	return *this;
}

template <typename T>	inline vecT<T>& vecT<T>::operator *=(double a)
{
	for (int i = 0; i < size; i++)
		this->entry[i] *= (T)a;

	return *this;
}

template <typename T>	inline void vecT<T>::zeros(void)
{
	if (size > 0)
		for (int i = 0; i < size; i++)
			entry[i] = (T)0.;
	else;
}

template <typename T>	inline double vecT<T>::l2(void)
{
	if (size == 0)
		return 0.;

	double norm = 0.;

	for (int i = 0; i < size; i++)
		norm += entry[i] * entry[i];

	return sqrt(norm);
}

template <typename T>	inline double vecT<T>::lmax(void)
{
	if (size == 0)
		return 0.;

	double norm = 0.;

	for (int i = 0; i < size; i++)
		if (entry[i] > norm)
			norm = entry[i];

	return norm;
}

/* === elementary(?) functions of vectors === */
template <typename T>	inline vecT<T> operator*(int a, const vecT<T>& x)
{
	vec result = x;
	result *= (T)a;
	return result;
}

template <typename T>	inline vecT<T> operator*(double a, const vecT<T>& x)
{
	vec result = x;
	result *= (T)a;
	return result;
}

template <typename T>	inline vecT<T> operator+(const vecT<T>& x, const vecT<T>& y)
{
	if (x.size != y.size)
	{
		sprintf(__message, "Error: Two vectors in + operation have different size.");
		print_error();
	}

	vecT<T> result = x;
	result += y;
	return result;
}

template <typename T>	inline vecT<T> operator-(const vecT<T>& x, const vecT<T>& y)
{
	if (x.size != y.size)
	{
		sprintf(__message, "Error: Two vectors in - operation have different size.");
		print_error();
	}

	vecT<T> result = x;
	result -= y;
	return result;
}

template <typename T>	inline double operator,(const vecT<T>& x, const vecT<T>& y)
{
	if (x.size != y.size)
	{
		sprintf(__message, "Error: Two vectors in an inner product have different size.");
		print_error();
	}

	double result = 0.;

	for (int i = 0; i < x.size; i++) result += x[i] * y[i];

	return result;
}




/* === full matrix === */

template <typename T>
class matT
{
public:
	int row; int col;
	vecT<T> *row_vec;

public:
	matT() { row = 0; col = 0; row_vec = NULL; }
	~matT();
	matT(int m, int n);
	matT(const matT<T>& A);
	void make(int m, int n);

	void print(void) const;

	vecT<T>& operator[](int i) const { return row_vec[i]; }
	matT<T>& operator=(const matT<T>& A);
	matT<T>& operator+=(const matT<T>& A);
	matT<T>& operator-=(const matT<T>& A);
	matT<T>& operator*=(int a);
	matT<T>& operator*=(double a);

	void transpose(const matT<T>& A);

	vecT<T> row_vector(int i) const;
	vecT<T> col_vector(int j) const;

	void zeros(void);
	double l2(void);
	double lmax(void);
};

template <typename T>	matT<T>::~matT()
{
	if (row_vec != NULL)
	{
		for (int i = 0; i < row; i++)
			row_vec[i].~vecT();

		delete[] row_vec;
	}
	row_vec = NULL;
}

template <typename T>	matT<T>::matT(int m, int n)
{
	if (row_vec != NULL)
	{
		for (int i = 0; i < row; i++)
			row_vec[i].~vecT();

		delete[] row_vec;
		row_vec = NULL;
	}
	
	row = m; col = n;

	row_vec = new vecT<T>[row];

	for (int i = 0; i < row; i++)
	{
		row_vec[i].size = col;
		row_vec[i].entry = new T[col];
		for (int j = 0; j < col; j++)
			row_vec[i].entry[j] = (T)0.;
	}
}

template <typename T>	matT<T>::matT(const matT<T>& A)
{
	if (A.row_vec == NULL)
	{
		row = 0; col = 0; row_vec = NULL;
	}
	else
	{
		row = A.row; col = A.col; row_vec = new vecT<T>[row];

		for (int i = 0; i < row; i++)
		{
			row_vec[i].size = col;
			row_vec[i].entry = new T[col];
			for (int j = 0; j < col; j++)
				row_vec[i][j] = A.row_vec[i][j];
		}
			
	}
}

template <typename T>	inline void matT<T>::make(int m, int n)
{
	if (row_vec != NULL)
	{
		for (int i = 0; i < row; i++)
			row_vec[i].~vecT();

		delete[] row_vec;
		row_vec = NULL;
	}

	row = m; col = n;

	row_vec = new vecT<T>[row];

	for (int i = 0; i < row; i++)
	{
		row_vec[i].size = col;
		row_vec[i].entry = new T[col];
		for (int j = 0; j < col; j++)
			row_vec[i].entry[j] = (T)0.;
	}
}

template <typename T>	inline void matT<T>::print(void) const
{
	if (row_vec == NULL)
	{
		printf("Empty matrix\n");
		return;
	}
	
	if (typeid(T) != typeid(int) && typeid(T) != typeid(double) && typeid(T) != typeid(char))
	{
		sprintf(__message, "Invalid type of matrix.");
		print_error();
	}

	// print a matrix only when T = int, double, or char
	printf("Print a matrix: \n");
	for (int i = 0; i < row; i++)
	{
		printf("row %3d: ", i);
		for (int j = 0; j < col; j++)
			if (typeid(T) == typeid(double))
				printf("%8.5f ", row_vec[i][j]);
			else if (typeid(T) == typeid(int))
				printf("%3d ", row_vec[i][j]);
			else if (typeid(T) == typeid(char))
				printf("%c ", row_vec[i][j]);

		printf("\n");
	}
}

template <typename T>	inline matT<T>& matT<T>::operator=(const matT<T>& A)
{
	if (this->row != A.row || this->col != A.col)
	{
		if (row_vec != NULL)
		{
			for (int i = 0; i < row; i++)
				row_vec[i].~vecT();

			delete[]row_vec;
			row_vec = NULL;
		}

		row = A.row; col = A.col;
		row_vec = new vecT<T>[row];

		for (int i = 0; i < row; i++)
		{
			row_vec[i].make(col);
		}
	}
	

	for (int i = 0; i < row; i++)
	{
		row_vec[i] = A.row_vec[i];
	}

	return *this;
}

template <typename T>	inline matT<T>& matT<T>::operator+=(const matT<T>& A)
{
	if (this->row != A.row || this->col != A.col)
	{
		if (row_vec != NULL)
		{
			for (int i = 0; i < row; i++)
				row_vec[i].~vecT();

			delete[]row_vec;
			row_vec = NULL;
		}

		row = A.row; col = A.col;
		row_vec = new vecT<T>[row];

		for (int i = 0; i < row; i++)
		{
			row_vec[i].make(col);
		}
	}


	for (int i = 0; i < row; i++)
	{
		row_vec[i] += A.row_vec[i];
	}

	return *this;
}

template <typename T>	inline matT<T>& matT<T>::operator-=(const matT<T>& A)
{
	if (this->row != A.row || this->col != A.col)
	{
		if (row_vec != NULL)
		{
			for (int i = 0; i < row; i++)
				row_vec[i].~vecT();

			delete[]row_vec;
			row_vec = NULL;
		}

		row = A.row; col = A.col;
		row_vec = new vecT<T>[row];

		for (int i = 0; i < row; i++)
		{
			row_vec[i].make(col);
		}
	}


	for (int i = 0; i < row; i++)
	{
		row_vec[i] -= A.row_vec[i];
	}

	return *this;
}

template <typename T>	inline matT<T>& matT<T>::operator*=(int a)
{
	if(row > 0 && col > 0 && row_vec != NULL)
		for (int i = 0; i < row; i++)
			row_vec[i] *= (T)a;

	return *this;
}

template <typename T>	inline matT<T>& matT<T>::operator*=(double a)
{
	if (row > 0 && col > 0 && row_vec != NULL)
		for (int i = 0; i < row; i++)
			row_vec[i] *= (T)a;

	return *this;
}

template <typename T>	inline void matT<T>::transpose(const matT<T>& A)
{
	if (A.row_vec == NULL)
	{
		sprintf(__message, "Error (Empty matrix)");
		print_error();
	}

	if (row != A.col || col != A.row)
	{
		this->~matT();
		this->make(A.col, A.row);
	}

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			row_vec[i][j] = A[j][i];
}

template <typename T>	inline vecT<T> matT<T>::row_vector(int i) const
{
	if (row == 0 || row_vec == NULL)
	{
		sprintf(__message, "Error (Empty matrix)");
		print_error();
	}
	else if (i >= row)
	{
		sprintf(__message, "Error (Incorrect row number)");
		print_error();
	}
	else
		return row_vec[i];
}

template <typename T>	inline vecT<T> matT<T>::col_vector(int j) const
{
	if (col == 0 || row_vec == NULL)
	{
		sprintf(__message, "Error (Empty matrix)");
		print_error();
	}
	else if (j >= col)
	{
		sprintf(__message, "Error (Incorrect column number)");
		print_error();
	}
	else
	{
		vecT<T> c(row);

		for (int i = 0; i < row; i++)
			c[i] = row_vec[i][j];

		return c;
	}
}

template <typename T>	void matT<T>::zeros(void)
{
	if (row != 0 && col != 0)
		for (int i = 0; i < row; i++)
			row_vec[i].zeros();
	else;
}

template <typename T>	inline double matT<T>::l2(void)
{
	if (row == 0 || col == 0)
		return 0.;

	double norm = 0.;

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			norm += this->row_vec[i][j] * this->row_vec[i][j];

	return sqrt(norm);
}

template <typename T>	inline double matT<T>::lmax(void)
{
	if (row == 0 || col == 0)
		return 0.;

	double norm = 0.;

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			if (abs(row_vec[i][j]) > norm)
				norm = abs(row_vec[i][j]);

	return norm;
}

/* === other elementary(?) functions of matrices === */
template <typename T>	inline matT<T> operator+(const matT<T>& A, const matT<T>& B)
{
	if (A.row != B.row || A.col != B.col)
	{
		sprintf(__message, "Error: Two matrices in + operation have different size.");
		print_error();
	}

	matT<T> result = A;
	result += B;
	return result;
}

template <typename T>	inline matT<T> operator-(const matT<T>& A, const matT<T>& B)
{
	if (A.row != B.row || A.col != B.col)
	{
		sprintf(__message, "Error: Two matrices in - operation have different size.");
		print_error();
	}

	matT<T> result = A;
	result -= B;
	return result;
}

template <typename T>	inline matT<T> operator*(const matT<T>& A, const matT<T>& B)
{
	if (A.col != B.row)
	{
		sprintf(__message, "Error: Two matrices in × operation have different size.");
		print_error();
	}

	matT<T> prod(A.row, B.col);

	for (int i = 0; i < A.row; i++)
		for (int j = 0; j < B.col; j++)
			for(int k = 0; k < A.col; k++)
				prod[i][j] += A[i][k]*B[k][j];

	return prod;
}

template <typename T>	inline matT<T> operator*(int a, const matT<T>& A)
{
	matT<T> result = A;

	result *= (T)a;

	return result;
}

template <typename T>	inline matT<T> operator*(double a, const matT<T>& A)
{
	matT<T> result = A;

	result *= (T)a;

	return result;
}

template <typename T>	inline vecT<T> operator*(const matT<T>& A, const vecT<T>& x)
{
	if (A.col != x.size)
	{
		sprintf(__message, "Error: A matrix and a vector in × operation have different size.");
		print_error();
	}

	vecT<T> prod(A.row);

	for (int i = 0; i < A.row; i++)
		prod[i] = (A[i], x);

	return prod;
}

double det(const mat& A) // incomplete...
{
	if (A.row != A.col || A.row == 0 || A.col == 0 || A.row_vec == NULL)
		return 0.;
	else
	{
		if (A.row == 2)
		{
			double det = A[0][0] * A[1][1] - A[1][0] * A[0][1];

			return det;
		}
		else
			return 0.;
	}
}

mat inverse(const mat& A) // incomplete...
{
	if (A.row != A.col || A.row == 0 || A.col == 0 || A.row_vec == NULL)
		return A;
	else
	{
		if (A.row == 2)
		{
			mat result(2, 2);

			double det = A[0][0] * A[1][1] - A[1][0] * A[0][1];

			if (det == 0)
				return A;

			result[0][0] = A[1][1] / det; result[1][1] = A[0][0] / det;
			result[1][0] = -A[1][0] / det; result[0][1] = -A[0][1] / det;

			return result;
		}
		else
			return A;
	}
}