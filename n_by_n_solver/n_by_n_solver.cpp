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
      int input_size;

      void G_E_xVec_solve(const double matrix[],const double _b_Vector[])
      {
            double M[input_size][input_size], b_Vector[input_size], x_Vector[input_size], x[input_size], temp;

            for (int row = 0; row < input_size; row++)
            {
                  for (int col = 0; col < input_size; col++)
                  {
                        M[row][col] = *(matrix + row*input_size + col);
                  }
                  b_Vector[row] = *(_b_Vector + row);
            }

            for (int num = 0; num < input_size; num++)
            {
                  for (int row = num+1; row < input_size; row++)
                  {
                        temp = M[row][num]/M[num][num];

                        for (int col = num; col < input_size; col++)
                        {
                              M[row][col] -= M[num][col]*temp;
                        }

                        b_Vector[row] -= b_Vector[num]*temp;
                  }
            }

            for (int col = input_size-1; col >= 0; col--)
            {
                  for (int row = col-1; row >= 0; row--)
                  {
                        temp = M[row][col]/M[col][col];
                        b_Vector[row] -= b_Vector[col]*temp;
                  }
            }

            for (int num = 0; num < input_size; num++)
                  x_Vector[num] = b_Vector[num]/M[num][num];


            std::cout << "===== print x vector =====" << std::endl;

            for (int num = 0; num < input_size; num++)
            {
                  std::cout << "x_" << num << " = " << x_Vector[num] << std::endl;
            }

            std::cout << "====== end x vector ======" << std::endl;
      }



      void G_E_invmat(const double matrix[])
      {     
            double M[input_size][input_size], IM[input_size][input_size], temp;
            

            for (int row = 0; row < input_size; row++)
            {
                  for (int col = 0; col < input_size; col++)
                  {
                        M[row][col] = *(matrix + input_size*row + col);
                        IM[row][col] = 0;
                  }
                  IM[row][row] = 1;
            }

      
            for (int row = 0; row < input_size; row++)
            {

                  temp = M[row][row];

                  for (int col = 0; col < input_size; col++)
                  {
                        M[row][col] = M[row][col]/temp;
                        IM[row][col] = IM[row][col]/temp;
                  }
                  
                  for (int row2 = 0; row2 < input_size; row2++)
                  {
                        temp = M[row2][row];
                        for (int col = 0; col < input_size; col++){
                              if(row2 != row){
                                    M[row2][col] -= temp*M[row][col];
                                    IM[row2][col] -= temp*IM[row][col];
                              }
                        }
                  }
            }

            std::cout << "===== print inverse matrix =====" << std::endl;

            for (int row = 0; row < input_size; row++)
            {
                  for (int col = 0; col < input_size; col++){
                        std::cout << IM[row][col] << " ";
                  }
                  std::cout << std::endl;
            }

            std::cout << "====== end inverse matrix ======" << std::endl;
      }

public:
      MatSolver(const int& select_solver, const int& _input_size, const double matrix[], const double vector[])
      {
            solType = static_cast<SolverType>(select_solver);
            input_size = _input_size;

            
            switch(solType)
            {
                  case SolverType::GaussElim:
                        G_E_xVec_solve(matrix, vector);
                        break;
                  case SolverType::Jacobi:

                        break;
                  case SolverType::GaussSeidel:

                        break;
                  case SolverType::GaussElim_inv:
                        G_E_invmat(matrix);
                        break;
            }
      };

};

class Matrix
{
private:
      int input_size;

public:
      double* data;
      Matrix(const int& _input_size)
      {
            input_size = _input_size;

            data = new double[input_size*input_size];

            for (int i = 0; i < input_size*input_size; i++)
                  data[i] = 0.0;
      }

      void setElement(const int& m,const int& n,const double& value)
      {
            data[m*input_size + n] = value;
      }

      void initMatrix()
      {
            for (int i = 0; i < input_size; i++)
            {
                  for (int j = 0; j < input_size; j++)
                  {
                        printf("%d행 %d열 입력 : ", i+1, j+1);
                        scanf("%lf", data + input_size*i + j);
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
      int select_solver, mat_size;

      printf("정사각행렬의 변 크기를 입력해주세요 : ");
      scanf("%d", &mat_size);
      

      Matrix myMat(mat_size);

      myMat.initMatrix();

      B_Vactor b_Vactor(mat_size);

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
            {
                  std::cout << "Exit the program" << std::endl;
                  break;
            }
            else
                  MatSolver matSolver(select_solver, mat_size, myMat.data, b_Vactor.b_elements);
      }

      return 0;
}