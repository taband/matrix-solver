#pragma once

/*
In this header file, sparse matrices and their elementary functions are defined.
However, the sparse matrix 'smat' has fewer functions than the ordinary matrix 'mat'.
*/

/*   ===== DECLARATION =====   */

class Node;
class Linked_List;
class svec;
class smat;



/*   ===== DEFINITION =====   */

/* === Node === */
class Node
{
public:
	int index;
	double data;
	Node* next;

public:

	Node() { this->index = 0; this->data = 0.; this->next = NULL; }
	void make(int index, double data);
	Node(int index, double data) { this->make(index, data); }
	~Node() {}
};

inline void Node::make(int index, double data)
{
	this->index = index;
	this->data = data;
	this->next = NULL;
}

/* ===== other elementary(?) functions of Nodes ===== */
inline void swap_node(Node* node1, Node* node2) // swap their index and data.
{
	double temp_data;
	int temp_index;

	if (node1 != NULL && node2 != NULL)
	{
		temp_data = node1->data;
		temp_index = node1->index;

		node1->data = node2->data;
		node1->index = node2->index;

		node2->data = temp_data;
		node2->index = temp_index;
	}
}





/* === Linked List === */
class Linked_List
{
public:
	Node *head;

public:
	Linked_List() { head = NULL; }
	~Linked_List();
	void add_node(int index, double data);
	void delete_node(int index);
	Node* find_index(int index);
	void print(void);
};

Linked_List::~Linked_List()
{
	if (this != NULL)
	{
		Node* temp;

		if (this->head != NULL)
			temp = head->next;
		else
			temp = NULL;

		delete this->head;

		this->head = NULL;

		while (temp != NULL)
		{
			this->head = temp;
			temp = temp->next;
			delete head;

			if (temp == NULL)
				break;
		}
	}
}

inline void Linked_List::add_node(int index, double data)
{
	Node* temp = new Node(index, data);

	temp->next = head;
	head = temp;
}

inline void Linked_List::delete_node(int index)
{
	Node* temp = head;
	Node* temp_pre = NULL;

	while (temp != NULL)
	{
		if (temp == NULL)
			break;

		if (temp->index == index)
		{
			if (temp == head)
				head = temp->next;
			else
				temp_pre->next = temp->next;

			delete temp;
			break;
		}

		temp_pre = temp;
		temp = temp->next;
	}
}

inline Node* Linked_List::find_index(int index)
{
	if (this == NULL)
		return NULL;

	Node* temp = this->head;

	while (temp != NULL)
	{
		if (temp == NULL)
			break;

		if (temp->index == index)
			break;

		temp = temp->next;
	}

	return temp;
}

inline void Linked_List::print(void)
{
	Node* temp = head;

	printf("Print a linked list : \n");

	while (temp != NULL)
	{
		printf("index: %3d, col: %3d, data: %10.6f\n", temp->index, temp->data);

		if (temp->next == NULL)
			break;

		temp = temp->next;
	}

	printf("end\n");
}



/* === Sparse Vector === */

class svec // the structure of sparse vector is a linked list.
{
public:
	int size;
	Node* entry; // head of linked list

public:
	svec() { size = 0; entry = NULL; }
	~svec();
	void delete_vector(void);
	void make(int size);

	Node* find_index(int i); // find a node whose index is i.
	void add_node(int index, double data); // add a node with index and data.
	void delete_node(int index); // delete a node with index.

	void print(void);

	double& operator[](int n);

	svec(const svec& x);

	svec& operator=(const svec& x);
	svec& operator+=(const svec& x);
	svec& operator-=(const svec& x);
	svec& operator*=(int a);
	svec& operator*=(double a);

	double operator,(const vec& x);

	void sparse(const vec& x);
	void remove_zero(void);

	double l2(void);
	double lmax(void);
};

inline svec::~svec()
{
	if (this != NULL)
	{
		Node* temp;

		if (this->entry != NULL)
			temp = entry->next;
		else
			temp = NULL;

		delete this->entry;

		this->entry = NULL;

		while (temp != NULL)
		{
			this->entry = temp;
			temp = temp->next;
			delete entry;

			if (temp == NULL)
				break;
		}
	}
}

inline void svec::delete_vector(void)
{
	if (this != NULL)
	{
		Node* temp;

		if (this->entry != NULL)
			temp = entry->next;
		else
			temp = NULL;

		delete this->entry;
		this->entry = NULL;

		while (temp != NULL)
		{
			this->entry = temp;
			temp = temp->next;

			delete this->entry;
			this->entry = NULL;

			if (temp == NULL)
				break;
		}
	}
}

inline void svec::make(int n)
{
	if (this->entry != NULL)
		this->delete_vector();

	this->size = n;
	entry = NULL;
}

inline Node* svec::find_index(int i)
{
	if (this == NULL)
		return NULL;

	Node* temp = this->entry;

	while (temp != NULL)
	{
		if (temp->index == i)
			break;

		temp = temp->next;

		if (temp == NULL)
			break;
	}

	return temp;
}

inline void svec::add_node(int index, double data)
{
	Node* temp = new Node(index, data);

	temp->next = this->entry;
	this->entry = temp;
}

inline void svec::delete_node(int index)
{
	Node* temp = this->entry;
	Node* temp_pre = NULL;

	while (temp != NULL)
	{
		if (temp->index == index)
		{
			if (temp == this->entry)
				this->entry = temp->next;
			else
				temp_pre->next = temp->next;

			delete temp;
			break;
		}

		temp_pre = temp;
		temp = temp->next;

		if (temp == NULL)
			break;
	}
}

inline void svec::print(void)
{
	if (size == 0 || this->entry == NULL)
	{
		printf("Empty sparse vector\n");
		return;
	}

	Node* temp;

	printf("Print a sparse vector: \n");

	for (int i = 0; i < size; i++)
	{
		printf("%3d: ", i);

		temp = this->find_index(i);

		if (temp == NULL)
			printf(" 0.0     \n");
		else
			printf("%8.5f\n", temp->data);
	}

	printf("end print\n\n");
}

inline double& svec::operator[](int n)
{
	if (n >= size)
	{
		sprintf(__message, "Error: Two matrices in + operation have different size.");
		print_error();
	}

	if (this->entry == NULL)
	{
		this->add_node(n, 0.);
		return this->entry->data;
	}

	Node* temp = this->find_index(n);

	if (temp == NULL)
	{
		this->add_node(n, 0.);
		return this->entry->data;
	}
	else
		return temp->data;
}

inline svec::svec(const svec& x)
{
	if (x.size == 0 || x.entry == NULL)
	{
		sprintf(__message, "Error (empty sparse vector)");
		print_error();
	}

	if (this->size != x.size)
		this->make(x.size);

	Node* temp = x.entry;

	while (temp != NULL)
	{
		if (temp->data != 0.)
			this->operator[](temp->index) = temp->data;

		temp = temp->next;

		if (temp == NULL)
			break;
	}
}

inline svec& svec::operator=(const svec& x)
{
	if (x.size == 0)
	{
		sprintf(__message, "Error (empty sparse vector)");
		print_error();
	}

	if (this->size != x.size)
		this->make(x.size);

	Node* temp = x.entry;

	while (temp != NULL)
	{
		if (temp->data != 0.)
			this->operator[](temp->index) = temp->data;

		temp = temp->next;

		if (temp == NULL)
			break;
	}

	return *this;
}

inline svec& svec::operator+=(const svec& x)
{
	if (x.size == 0)
	{
		sprintf(__message, "Error (empty sparse vector in гл operation)");
		print_error();
	}

	if (this->size != x.size)
		this->make(x.size);

	Node* temp = x.entry;

	while (temp != NULL)
	{
		if (temp->data != 0.)
			this->operator[](temp->index) += temp->data;

		temp = temp->next;

		if (temp == NULL)
			break;
	}

	return *this;
}

inline svec& svec::operator-=(const svec& x)
{
	if (x.size == 0)
	{
		sprintf(__message, "Error (empty sparse vector in - operation)");
		print_error();
	}

	if (this->size != x.size)
		this->make(x.size);

	Node* temp = x.entry;

	while (temp != NULL)
	{
		if (temp->data != 0.)
			this->operator[](temp->index) -= temp->data;

		temp = temp->next;

		if (temp == NULL)
			break;
	}

	return *this;
}

inline svec& svec::operator*=(int a)
{
	if (this->size == 0 || this->entry == NULL)
		return *this;

	Node* temp = this->entry;

	while (temp != NULL)
	{
		temp->data *= (double)a;

		temp = temp->next;

		if (temp == NULL)
			break;
	}

	return *this;
}

inline svec& svec::operator*=(double a)
{
	if (this->size == 0 || this->entry == NULL)
		return *this;

	Node* temp = this->entry;

	while (temp != NULL)
	{
		temp->data *= a;

		temp = temp->next;

		if (temp == NULL)
			break;
	}

	return *this;
}

inline double svec::operator,(const vec& x)
{
	if (size != x.size)
	{
		sprintf(__message, "Error (incorrect size of sparse vectors in an inner product)");
		print_error();
	}

	double result = 0.;

	Node* temp = this->entry;

	while (temp != NULL)
	{
		result += (temp->data)*x[temp->index];

		temp = temp->next;

		if (temp == NULL)
			break;
	}

	return result;
}

inline void svec::sparse(const vec& x)
{
	if (x.size == 0)
	{
		sprintf(__message, "Error (invalid input in sparse function)");
		print_error();
	}

	if (x.size != this->size)
		this->make(x.size);

	for (int i = 0; i < x.size; i++)
		if (x[i] != 0.)
			this->add_node(i, x[i]);
}

inline void svec::remove_zero(void)
{
	if (this->size == 0 || this->entry == NULL)
		return;

	Node* remove;
	Node* temp = this->entry;

	while (temp != NULL)
	{
		if (temp->data == 0.)
		{
			remove = temp;
			temp = temp->next;
			this->delete_node(remove->index);
		}
		else
			temp = temp->next;

		if (temp == NULL)
			break;
	}
}

inline double svec::l2(void)
{
	if (size == 0 || this->entry == NULL)
		return 0.;

	Node* temp = this->entry;

	double norm = 0.;

	while (temp != NULL)
	{
		if (temp->data != 0.)
			norm += temp->data;

		temp = temp->next;

		if (temp == NULL)
			break;
	}

	return norm;
}

inline double svec::lmax(void)
{
	if (size == 0 || this->entry == NULL)
		return 0.;

	Node* temp = this->entry;

	double norm = 0.;

	while (temp != NULL)
	{
		if (abs(temp->data) > norm)
			norm = abs(temp->data);

		temp = temp->next;

		if (temp == NULL)
			break;
	}

	return norm;
}





/* === Sparse Matrix === */

class smat
{
public:
	int row;
	int col;
	svec* row_vec;

public:
	smat() { row = 0; col = 0; row_vec = NULL; }
	~smat();
	void make(int row, int col);
	void print(void);

	svec& operator[](int m) const { return row_vec[m]; };

	smat& operator=(const smat& A);
	smat& operator+=(const smat& A);
	smat& operator-=(const smat& A);
	smat& operator*=(int a);
	smat& operator*=(double a);

	vec operator*(const vec& x);

	void sparse(const mat& A);
	void sparse_diag(const mat& A);
	void sparse_diag(const smat& A);
	void sparse_lower(const smat& A);
	void sparse_upper(const smat& A);
	void sparse_str_lower(const smat& A);
	void sparse_str_upper(const smat& A);
	void transpose(const smat& A);
	void remove_zero(void);

};

inline smat::~smat()
{
	if (row_vec != NULL)
	{
		delete[] row_vec;
		row_vec = NULL;
	}
}

inline void smat::make(int row, int col)
{
	if (this->row != row || this->col != col)
	{
		this->~smat();

		this->row = row; this->col = col;
		row_vec = new svec[row];

		for (int i = 0; i < row; i++)
			row_vec[i].make(col);
	}
}

inline void smat::print(void)
{
	if (this->row == 0 || this->col == 0 || this->row_vec == NULL)
	{
		printf("Empty Sparse Matrix.\n");
		return;
	}

	Node* temp;

	printf("Print a sparse matrix:\n");

	for (int i = 0; i < row; i++)
	{
		printf("row %3d: ", i);

		for (int j = 0; j < col; j++)
		{
			temp = this->row_vec[i].find_index(j);

			if (temp == NULL)
				printf(" 0.0  ");
			else
				printf("%5.2f ", temp->data);
		}
		printf("\n");
	}

	printf("end print\n");
}

inline smat& smat::operator=(const smat& A)
{
	if (this->row != A.row || this->col != A.col)
		this->make(A.row, A.col);

	for (int i = 0; i < row; i++)
		this->row_vec[i] = A.row_vec[i];

	return *this;
}

inline smat& smat::operator+=(const smat& A)
{
	if (this->row != A.row || this->col != A.col)
		this->make(A.row, A.col);

	for (int i = 0; i < row; i++)
		row_vec[i] += A.row_vec[i];

	return *this;
}

inline smat& smat::operator-=(const smat& A)
{
	if (this->row != A.row || this->col != A.col)
		this->make(A.row, A.col);

	for (int i = 0; i < row; i++)
		row_vec[i] -= A.row_vec[i];

	return *this;
}

inline smat& smat::operator*=(int a)
{
	if (row > 0 && col > 0 && this->row_vec != NULL)
		for (int i = 0; i < row; i++)
			this->row_vec[i] *= (double)a;

	return *this;
}

inline smat& smat::operator*=(double a)
{
	if (row > 0 && col > 0 && this->row_vec != NULL)
		for (int i = 0; i < row; i++)
			row_vec[i] *= a;

	return *this;
}

inline vec smat::operator*(const vec& x)
{
	if (this->col != x.size)
	{
		sprintf(__message, "Error: Incorrect size of two matrices in б┐ operation");
		print_error();
	}

	vec prod(row);
	Node* temp;
	int j;

	for (int i = 0; i < row; i++)
	{
		if (this->row_vec[i].entry != NULL)
		{
			temp = this->row_vec[i].entry;

			while (temp != NULL)
			{
				j = temp->index;
				prod[i] += temp->data* x[j];

				temp = temp->next;

				if (temp == NULL)
					break;
			}
		}
	}

	return prod;
}

inline void smat::sparse(const mat& A)
{
	if (this->row != A.row || this->col != A.col)
		this->make(A.row, A.col);

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			if (A[i][j] != 0.)
				this->row_vec[i][j] = A[i][j];
}

inline void smat::sparse_diag(const mat& A)
{
	if (this->row != A.row || this->col != A.col)
		this->make(A.row, A.col);

	int M = (A.row < A.col) ? A.row : A.col;

	for (int i = 0; i < M; i++)
		if (A[i][i] != 0.)
			this->row_vec[i][i] = A[i][i];
}

inline void smat::sparse_diag(const smat& A)
{
	if (this->row != A.row || this->col != A.col)
		this->make(A.row, A.col);

	int M = (A.row < A.col) ? A.row : A.col;

	Node* temp;

	for (int i = 0; i < M; i++)
	{
		temp = A.row_vec[i].find_index(i);

		if (temp != NULL)
			row_vec[i][i] = temp->data;
	}

}

inline void smat::sparse_lower(const smat& A)
{
	if (this->row != A.row || this->col != A.col)
		this->make(A.row, A.col);

	Node* temp;

	int m;

	for (int i = 0; i < A.row; i++)
	{
		m = (A.col - 1 < i) ? A.col - 1 : i;
		for (int j = 0; j <= m; j++)
		{
			temp = A.row_vec[i].find_index(j);

			if (temp != NULL)
				row_vec[i][j] = temp->data;
		}
	}
}

inline void smat::sparse_upper(const smat& A)
{
	if (this->row != A.row || this->col != A.col)
		this->make(A.row, A.col);

	Node* temp;

	int m;

	for (int i = 0; i < A.row; i++)
	{
		m = (A.col - 1 < i) ? A.col - 1 : i;
		for (int j = A.col - 1; j >= m; j--)
		{
			temp = A.row_vec[i].find_index(j);

			if (temp != NULL)
				row_vec[i][j] = temp->data;
		}
	}
}

inline void smat::sparse_str_lower(const smat& A)
{
	if (this->row != A.row || this->col != A.col)
		this->make(A.row, A.col);

	Node* temp;

	int m;

	for (int i = 0; i < A.row; i++)
	{
		m = (A.col - 1 < i) ? A.col - 1 : i;
		for (int j = 0; j < m; j++)
		{
			temp = A.row_vec[i].find_index(j);

			if (temp != NULL)
				row_vec[i][j] = temp->data;
		}
	}
}

inline void smat::sparse_str_upper(const smat& A)
{
	if (this->row != A.row || this->col != A.col)
		this->make(A.row, A.col);

	Node* temp;

	int m;

	for (int i = 0; i < A.row; i++)
	{
		m = (A.col - 1 < i) ? A.col - 1 : i;
		for (int j = A.col - 1; j > m; j--)
		{
			temp = A.row_vec[i].find_index(j);

			if (temp != NULL)
				row_vec[i][j] = temp->data;
		}
	}
}

inline void smat::transpose(const smat& A)
{
	if (A.row == 0 || A.col == 0)
		return;

	this->make(A.col, A.row);

	Node* temp;

	for (int i = 0; i < A.row; i++)
	{
		temp = A.row_vec[i].entry;

		while (temp != NULL)
		{
			this->row_vec[temp->index][i] = temp->data;

			temp = temp->next;

			if (temp == NULL)
				break;
		}
	}
}

inline void smat::remove_zero(void)
{
	if (this->row == 0 || this->col == 0)
		return;

	for (int i = 0; i < this->row; i++)
		this->row_vec[i].remove_zero();
}

/* ===== other elementary(?) functions of sparse matrices ===== */
inline vec operator*(const smat& A, const vec& x)
{
	if (A.col != x.size)
	{
		sprintf(__message, "Error: Incorrect size of two matrices in б┐ operation");
		print_error();
	}

	vec prod(A.row);
	Node* node;
	int j;

	for (int i = 0; i < A.row; i++)
	{
		if (A[i].entry != NULL)
		{
			node = A[i].entry;

			while (node != NULL)
			{
				j = node->index;
				prod[i] += node->data* x[j];

				node = node->next;

				if (node == NULL)
					break;
			}
		}
	}

	return prod;
}