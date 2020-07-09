#include <iostream>
#include <stdio.h>


enum class SolverType : int
{
      exit_program  = 0,
      GaussElim     = 1,
      Jacobi        = 2,
      GaussSeidel   = 3,
      GaussElim_inv = 9
};

class MatSolver
{
private:
      SolverType solType;
      int input_row, input_col, n = 0;


      void G_E_solve(const double matrix[], const double vector[])
      {
            double M[input_row][input_col], b[input_row], temp;

            for (int row = 0; row < n; row++)
            {
                  for (int col = 0; col < n; col++)
                  {
                        M[row][col] = *(matrix + n*row + col);
                  }
                  b[row] = *(vector + row);
            }

      
            for (int row = 0; row < input_row; row++)
            {

                  temp = M[row][row];

                  for (int col = 0; col < input_col; col++)
                  {
                        M[row][col] = M[row][col]/temp;
                        IM[row][col] = IM[row][col]/temp;
                  }
                  
                  for (int row2 = 0; row2 < input_row; row2++)
                  {
                        temp = M[row2][row];
                        for (int col = 0; col < n; col++){
                              if(row2 != row){
                                    M[row2][col] -= temp*M[row][col];
                                    IM[row2][col] -= temp*IM[row][col];
                              }
                        }
                  }
            }

            std::cout << "===== print inverse matrix =====" << std::endl;

            for (int row = 0; row < n; row++)
            {
                  for (int col = 0; col < n; col++){
                        std::cout << IM[row][col] << " ";
                  }
                  std::cout << std::endl;
            }

            std::cout << "====== end inverse matrix ======" << std::endl;
      }





      void G_E_invmat(const double matrix[])
      {     
            double M[n][n], IM[n][n] = {0,} , temp;

            for (int row = 0; row < n; row++)
            {
                  for (int col = 0; col < n; col++)
                  {
                        M[row][col] = *(matrix + n*row + col);
                  }
                  IM[row][row] = 1;
            }

      
            for (int row = 0; row < n; row++)
            {

                  temp = M[row][row];

                  for (int col = 0; col < n; col++)
                  {
                        M[row][col] = M[row][col]/temp;
                        IM[row][col] = IM[row][col]/temp;
                  }
                  
                  for (int row2 = 0; row2 < n; row2++)
                  {
                        temp = M[row2][row];
                        for (int col = 0; col < n; col++){
                              if(row2 != row){
                                    M[row2][col] -= temp*M[row][col];
                                    IM[row2][col] -= temp*IM[row][col];
                              }
                        }
                  }
            }

            std::cout << "===== print inverse matrix =====" << std::endl;

            for (int row = 0; row < n; row++)
            {
                  for (int col = 0; col < n; col++){
                        std::cout << IM[row][col] << " ";
                  }
                  std::cout << std::endl;
            }

            std::cout << "====== end inverse matrix ======" << std::endl;
      }

public:
      MatSolver(const int& select_solver, const int& _input_row,const int& _input_col, const double matrix[], const double vector[])
      {
            solType = static_cast<SolverType>(select_solver);
            input_row = _input_row;
            input_col = _input_col;

            if (input_row == input_col)
                  n = input_row;

            switch(solType)
            {
                  case SolverType::GaussElim:

                        break;
                  case SolverType::Jacobi:

                        break;
                  case SolverType::GaussSeidel:

                        break;
                  case SolverType::GaussElim_inv:
                        if (n == 0)
                        {
                              std::cout << "wrong matrix" << std::endl;
                              exit(1);
                        }
                        else
                        {
                              G_E_invmat(matrix);
                        }
                        break;
            }
      };

};

class Matrix
{
private:
      int rows;
      int cols;
      

public:
      double* data;
      Matrix(const int& _rows, const int& _cols)
      {
            rows = _rows;
            cols = _cols;

            data = new double[rows*cols];

            for (int i = 0; i < rows*cols; i++)
                  data[i] = 0.0;
      }

      void setElement(const int& m,const int& n,const double& value)
      {
            data[m*rows + n] = value;
      }

      void initMatrix()
      {
            for (int i = 0; i < rows; i++)
            {
                  for (int j = 0; j < cols; j++)
                  {
                        printf("%d행 %d열 입력 : ", i+1, j+1);
                        scanf("%lf", data + rows*i + j);
                  }
            }
      }

      ~Matrix()
      {
            delete[] data;
      }
};

class B_Vactor
{
private:
      int numbers;

public:
      double* b_elements;
      B_Vactor(const int& _numbers)
      {
            numbers = _numbers;

            b_elements = new double[numbers];

            for (int i = 0; i < numbers; i++)
                  b_elements[i] = 0.0;
      }

      void setElement(const int& n, const double& value)
      {
            b_elements[n] = value;
      }

      void initVactor()
      {
            for (int i = 0; i < numbers; i++)
            {
                  printf("b 벡터의 %d행 요소 입력 : ", i+1);
                  scanf("%lf", b_elements + i);
            }
      }

      ~B_Vactor()
      {
            delete[] b_elements;
      }
};

int main()
{
      int select_solver, input_row, input_col;

      printf("행렬의 가로크기를 입력해주세요 : ");
      scanf("%d", &input_col);
      printf("행렬의 세로크기를 입력해주세요 : ");
      scanf("%d", &input_row);

      Matrix myMat(input_row,input_col);

      myMat.initMatrix();

      B_Vactor b_Vactor(input_row);

      b_Vactor.initVactor();

      while(1)
      {
            std::cout << "\nPlaese select solver type."          << std::endl
                      << "1 == Gauss Elimination solve"          << std::endl
                      << "2 == Jacobi solve"                     << std::endl 
                      << "3 == Gauss Seidel solve"               << std::endl
                      << "9 == Gauss Elimination inverse matrix" << std::endl
                      << "0 == Exit the program"                 << std::endl;
            scanf("%d", &select_solver);

            if (select_solver == 0)
                  break;
            else
                  MatSolver matSolver(select_solver, input_row, input_col, myMat.data);
      }

      return 0;
}