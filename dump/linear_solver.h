#pragma once
// This header file consists of numerical methods for solving a matrix equation Ax = b.

class LINEAR_SOLVER
{
public:
	// :: Gaussian Elimination Method without Pivotting ::
	// All the diagonal entries of A must be non-zero.
	static void GE(const mat& A, vec& x, const vec& b, int ifprint = 1)
	{
		if (A.row != A.col || A.col != b.size || b.size != x.size)
		{
			sprintf(__message, "Error: Incorrect size of matrix and vectors in Gaussian elimination process");
			print_error();
		}

		for (int i = 0; i < A.row; i++)
			if (A[i][i] == 0.)
			{
				sprintf(__message, "Error: Matrix in Gaussian elimination process has a zero diagonal element.");
				print_error();
			}

		int N = A.row;

		mat A_temp(A);
		vec b_temp(b);
		
		double m;

		// to check the execution time for GE
		clock_t t = clock();

		if (ifprint == 1)
			printf("Executing Gaussian Elimination Method Process...       ");

		for (int k = 0; k < N - 1; k++)
		{
			for (int i = k + 1; i < N; i++)
			{
				m = A_temp[i][k] / A_temp[k][k];
				for (int j = k + 1; j < N; j++)
					A_temp[i][j] -= m*A_temp[k][j];
				b_temp[i] -= m*b_temp[k];
			}

			if (ifprint == 1)
				printf("\b\b\b\b\b\b%5.1f%%", 100.*((double)k) / ((double)(N - 2)));
		}

		x[N - 1] = b_temp[N - 1] / A_temp[N - 1][N - 1];
		for (int i = N - 2; i > -1; i--)
		{
			x[i] = b_temp[i];
			for (int j = N - 1; j > i; j--)
				x[i] -= A_temp[i][j] * x[j];

			x[i] /= A_temp[i][i];
		}

		t = clock() - t;

		if (ifprint == 1)
			printf("\nGaussian Elimination Method Process Complete (execution time: %f seconds)\n", ((double)t) / CLOCKS_PER_SEC);
	}

	static void GE(const smat& A, vec& x, const vec& b, int ifprint = 1)
	{
		if (A.row != A.col || A.col != b.size || b.size != x.size)
		{
			sprintf(__message, "Error: Incorrect size of matrix and vectors in Gaussian elimination process");
			print_error();
		}

		for (int i = 0; i < A.row; i++)
			if (A[i].find_index(i) == NULL)
			{
				sprintf(__message, "Error: Matrix in Gaussian elimination process has a zero diagonal element");
				print_error();
			}

		// to check the execution time for GE
		clock_t t = clock();

		if (ifprint == 1)
			printf("Executing Gaussian Elimination Method Process...       ");

		int N = A.row; int i, j, k;

		smat A_temp; A_temp = A;
		vec b_temp; b_temp = b;

		double m;
		Node* node;

		for (k = 0; k < N - 1; k++)
		{
			for (i = k + 1; i < N; i++)
			{
				if (A_temp[i].find_index(k) != NULL)
				{
					m = A_temp[i][k] / A_temp[k][k];

					b_temp[i] -= m*b_temp[k];

					node = A_temp[k].entry;

					while (node != NULL)
					{
						j = node->index;

						if (j > k)
							A_temp[i][j] -= m*node->data;

						node = node->next;

						if (node == NULL)
							break;
					}
				}
			}

			if (ifprint == 1)
				printf("\b\b\b\b\b\b%5.1f%%", 50.*((double)k + 1.) / ((double)(N - 1)));
		}

		x[N - 1] = b_temp[N - 1] / A_temp[N - 1][N - 1];
		
		for (i = N - 2; i > -1; i--)
		{
			x[i] = b_temp[i];

			node = A_temp[i].entry;

			while (node != NULL)
			{
				j = node->index;

				if (j > i && j < N)
					x[i] -= node->data * x[j];

				node = node->next;

				if (node == NULL)
					break;
			}

			x[i] /= A_temp[i][i];

			if (ifprint == 1)
				printf("\b\b\b\b\b\b%5.1f%%", 100. - 50.*((double)i) / ((double)(N - 2)));
		}

		t = clock() - t;

		if (ifprint == 1)
			printf("\nGaussian Elimination Method Process Complete (execution time: %f seconds)\n", ((double)t) / CLOCKS_PER_SEC);

	}


	// :: Conjugate Gradient Method ::
	// The matrix A must be symmetric positive definite.
	static void CG(const mat& A, vec& x, const vec& b, int ifprint = 1)
	{
		if (A.row != A.col || A.col != b.size || b.size != x.size)
		{
			sprintf(__message, "Error: Incorrect size of matrix and vectors in conjugate gradient method process");
			print_error();
		}

		int iter = 0; int N = A.row; double alpha, res, res_next;

		// to check the execution time for CG, start clock
		clock_t t = clock();

		if (ifprint == 1)
			printf("Executing Conjugate Gradient Method Process...\n");

		vec r(N), d(N), Ad(N);

		x.zeros();
		r = b; d = b; res = (r, r);

		if (ifprint == 1)
			printf("Iteration: %6d   Residual: %20.16f", iter, res);

		while (sqrt(res) > 1e-16)
		{
			Ad = A*d;
			alpha = res / (Ad, d);

			x += alpha*d; r -= alpha*(Ad);

			res_next = (r, r);

			d *= res_next / res;

			d += r;

			res = res_next;

			iter++;

			if (ifprint == 1)
			{
				for (int i = 0; i<70; i++)
					printf("\b");
				printf("Iteration: %6d   Residual: %20.16f", iter, sqrt(res));
			}
		}
		t = clock() - t; // stop clock

		if (ifprint == 1)
		{
			for (int i = 0; i<70; i++)
				printf("\b");
			printf("Iteration: %6d   Residual: %20.16f", iter, sqrt(res));
			printf("\nConjugate Gradient Method Process Complete (execution time: %f seconds)\n", ((double)t) / CLOCKS_PER_SEC);
		}
	}

	static void CG(const smat& A, vec& x, const vec& b, int ifprint = 1)
	{
		if (A.row != A.col || A.col != b.size || b.size != x.size)
		{
			sprintf(__message, "Error: Incorrect size of matrix and vectors in conjugate gradient method process");
			print_error();
		}

		int iter = 0; int i = 0; int N = A.row; double alpha, res, res_next;

		// to check the execution time for CG, start clock
		clock_t t = clock();

		if (ifprint == 1)
			printf("Executing Conjugate Gradient Method Process...\n");

		vec r, d, Ad; r.make(N); d.make(N); Ad.make(N);

		r = b; d = b; res = (r, r);

		if (ifprint == 1)
			printf("Iteration: %6d   Residual: %20.16f", iter, sqrt(res));

		while(sqrt(res) > 1e-16)
		{
			iter++;

			Ad = A*d;
			alpha = res / (Ad, d);

			x += alpha*d; r -= alpha*(Ad);

			res_next = (r, r);

			d *= res_next / res;

			d += r;

			res = res_next;

			if (ifprint == 1 && iter % 100 == 0)
			{
				for (i = 0; i<70; i++)
					printf("\b");
				printf("Iteration: %6d   Residual: %20.16f", iter, sqrt(res));
			}
		}
		t = clock() - t; // stop clock

		if (ifprint == 1)
		{
			for (i = 0; i<70; i++)
				printf("\b");
			printf("Iteration: %6d   Residual: %20.16f", iter, sqrt(res));
			printf("\nConjugate Gradient Method Process Complete (execution time: %f seconds)\n", ((double)t) / CLOCKS_PER_SEC);
		}
			
	}


	// :: Jacobi Method ::
	// The matrix A must be irreducibly diagonally dominant.
	static void JACOBI(const mat& A, vec& x, const vec& b, int iter, int ifprint = 1)
	{
		if (A.row != A.col || A.col != b.size || b.size != x.size)
		{
			sprintf(__message, "Error: Incorrect size of matrix and vectors in Jacobi method process");
			print_error();
		}
		
		for (int i = 0; i < A.row; i++)
			if (A[i][i] == 0.)
			{
				sprintf(__message, "Error: Matrix in Jacobi method process has a zero diagonal element.");
				print_error();
			}

		int N = A.row; double sigma, res;

		// to check the execution time for CG, start clock
		clock_t t = clock();

		if (ifprint == 1)
			printf("Executing Jacobi Method Process...\n");

		for (int k = 0; k < iter; k++)
		{
			for (int i = 0; i < N; i++)
			{
				sigma = 0.;
				for (int j = 0; j < N; j++)
					if (j != i)
						sigma += A[i][j] * x[j];

				x[i] = (b[i] - sigma) / A[i][i];
			}

			res = (b - A*x, b - A*x);

			if (ifprint == 1)
			{
				for (int i = 0; i<70; i++)
					printf("\b");
				printf("Iteration: %6d   Residual: %20.16f", k + 1, sqrt(res));
			}

		}

		t = clock() - t; // stop clock

		if (ifprint == 1)
			printf("\nJacobi Method Process Complete (execution time: %f seconds)\n", ((double)t) / CLOCKS_PER_SEC);
	}

	static void JACOBI(const smat& A, vec& x, const vec& b, int iter, int ifprint = 1)
	{
		if (A.row != A.col || A.col != b.size || b.size != x.size)
		{
			sprintf(__message, "Error: Incorrect size of matrix and vectors in Jacobi method process");
			print_error();
		}

		for (int i = 0; i < A.row; i++)
			if (A[i].find_index(i) == NULL)
			{
				sprintf(__message, "Error: Matrix in Jacobi method process has a zero diagonal element");
				print_error();
			}

		int N = A.row; double res;

		// to check the execution time for CG, start clock
		clock_t t = clock();

		if (ifprint == 1)
			printf("Executing Jacobi Method Process...\n");

		smat sD, sA_minus_D; vec Ax;

		//vec x_next; x_next.make(x.size);

		sD.sparse_diag(A);
		sA_minus_D = A;
		sA_minus_D -= sD;

		for (int k = 0; k < iter; k++)
		{
			x = b - sA_minus_D*x;

			for (int i = 0; i < N; i++)
				x[i] /= A[i][i];

			Ax = A*x;

			res = (b - Ax, b - Ax);

			if (ifprint == 1)
			{
				for (int i = 0; i<70; i++)
					printf("\b");
				printf("Iteration: %6d   Residual: %20.16f", k + 1, sqrt(res));
			}

		}

		t = clock() - t; // stop clock

		if (ifprint == 1)
			printf("\nJacobi Method Process Complete (execution time: %f seconds)\n", ((double)t) / CLOCKS_PER_SEC);
	}


	// :: Gauss-Seidel Method ::
	// The matrix A must be irreducibly diagonally dominant.
	static void GAUSS_SEIDEL(const mat& A, vec& x, const vec& b, int iter, double epsilon = 1e-16, int ifprint = 1)
	{
		if (A.row != A.col || A.col != b.size || b.size != x.size)
		{
			sprintf(__message, "Error: Incorrect size of matrix and vectors in Gauss-Seidel method process");
			print_error();
		}

		for (int i = 0; i < A.row; i++)
			if (A[i][i] == 0.)
			{
				sprintf(__message, "Error: Matrix in Gaussian elimination process has a zero diagonal element.");
				print_error();
			}

		int N = A.row; double sigma, res = 100.; int k;

		// to check the execution time for CG, start clock
		clock_t t = clock();

		if (ifprint == 1)
			printf("Executing Gauss-Seidel Method Process...\n");

		vec Ax(N);

		while (sqrt(res) > epsilon && k < iter)
		{
			for (int i = 0; i < N; i++)
			{
				sigma = 0.;
				for (int j = 0; j < N; j++)
					sigma += A[i][j] * x[j];

				x[i] = (b[i] - sigma) / A[i][i];
			}

			Ax = A*x;

			res = (b - Ax, b - Ax);

			k++;

			if (ifprint == 1)
			{
				for (int i = 0; i < 70; i++)
					printf("\b");
				printf("Iteration: %6d   Residual: %20.16f", k, sqrt(res));
			}
		}

		t = clock() - t; // stop clock

		if (ifprint == 1)
			printf("\nGauss-Seidel Method Process Complete (execution time: %f seconds)\n", ((double)t) / CLOCKS_PER_SEC);
	}

	static void GAUSS_SEIDEL(const smat& A, vec& x, const vec& b, int iter, double epsilon = 1e-16, int ifprint = 1)
	{
		if (A.row != A.col || A.col != b.size || b.size != x.size)
		{
			sprintf(__message, "Error: Incorrect size of matrix and vectors in Gauss-Seidel method process");
			print_error();
		}

		for (int i = 0; i < A.row; i++)
			if (A[i].find_index(i) == NULL)
			{
				sprintf(__message, "Error: Matrix in Gaussian elimination process has a zero diagonal element");
				print_error();
			}

		int k = 0; int i, j; double res = 1.; double sigma;

		// to check the execution time for CG, start clock
		clock_t t = clock();

		if (ifprint == 1)
			printf("Executing Gauss-Seidel Method Process...\n");

		vec Ax(A.row);
		Node* node_temp;

		while(sqrt(res) > epsilon && k < iter)
		{
			for (i = 0; i < A.row; i++)
			{
				sigma = 0.;
				node_temp = A.row_vec[i].entry;

				while (node_temp != NULL)
				{
					j = node_temp->index;
					if (j != i)
						sigma += node_temp->data*x[j];

					node_temp = node_temp->next;

					if (node_temp == NULL)
						break;
				}

				node_temp = A.row_vec[i].find_index(i);

				x[i] = (b[i] - sigma) / node_temp->data;
			}

			Ax = A*x;

			res = (b - Ax, b - Ax);

			k++;

			if (ifprint == 1 && k % 10 == 0)
			{
				for (int i = 0; i < 70; i++)
					printf("\b");
				printf("Iteration: %6d   Residual: %20.16f", k, sqrt(res));
			}
		}

		t = clock() - t; // stop clock

		if (ifprint == 1)
			printf("\nGauss-Seidel Method Process Complete (execution time: %f seconds)\n", ((double)t) / CLOCKS_PER_SEC);
	}
};
