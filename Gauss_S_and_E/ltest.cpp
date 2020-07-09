#include <iostream>
#include <stdio.h>


enum class SolverType
{
      GaussElim     = 1,
      Jacobi        = 2,
      GaussSeidel   = 3,
      GaussElim_inv = 9
};

class MatSolver
{
private:
      SolverType solType;
      int input_row, input_col;

public:
      int n;

      MatSolver(const int select_solver)
      {
            solType = static_cast<SolverType>(select_solver);

            int _input_row, _input_col;
      
            printf("행렬의 가로크기를 입력해주세요 : ");
            scanf("%d", &_input_col);
            printf("행렬의 세로크기를 입력해주세요 : ");
            scanf("%d", &_input_row);


            Matrix myMat(_input_row,_input_col);
            
            myMat.initMatrix();

            switch(solType)
            {
                  case SolverType::GaussElim:
                  
                        break;
                  case SolverType::Jacobi:

                        break;
                  case SolverType::GaussSeidel:

                        break;
                  case SolverType::GaussElim_inv:

                        break;
            }
      };


      void G_E_invmat(const int *matrix)
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

      

};

class Matrix
{
private:
      int rows;
      int cols;
      double* data;

public:
      Matrix(int _rows, int _cols)
      {
            rows = _rows;
            cols = _cols;

            data = new double[rows*cols];

            for (int i = 0; i < rows*cols; i++)
                  data[i] = 0.0;
      }

      void setElement(int m, int n, double value)
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


int main()
{
      int select_solver;
      
      std::cout << "Plaese select solver type."            << std::endl
                << "1 == Gauss Elimination solve"          << std::endl
                << "2 == Jacobi solve"                     << std::endl 
                << "3 == Gauss Seidel solve"               << std::endl
                << "9 == Gauss Elimination inverse matrix" << std::endl;
      scanf("%d", &select_solver);
      
      

      MatSolver matSolver(select_solver);

      

      return 0;
}