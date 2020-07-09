#include <stdio.h>
#include <iostream>
#include <math.h>



class Gausses{
      public:

      int n;
      int typecheck;

      void Initialize(){
            int mat[n][n], i[n];

            for (int row = 0; row < n; row++){
                  for (int col = 0; col < n; col++){
                        printf("%d행 %d열 입력 : ", row+1, col+1);
                        scanf("%d", &mat[row][col]);
                  }
                  printf("%d행의 인수를 입력해주세요 : ", row+1);
                  scanf("%d", &i[row]);
            }
            
            

            Gausses elemi = {};
            
            elemi.Gauss_Elemination((int*)mat,i,n);
            
            
      }

      void Gauss_Elemination(const int *matrix,const int *rhs, const int n){
            
            float M[n][n], IM[n][n] = {0,}, i[n], x[n], temp;

            for (int num = 0; num < n; num++){
                  IM[num][num] = 1;
            }

            for (int row = 0; row < n; row++){
                  for (int col = 0; col < n; col++){
                        M[row][col] = *(matrix + row*n + col);
                  }
                  i[row] = *(rhs + row);
            }
            

            for (int num = 0; num < n; num++){
                  for (int row = num+1; row < n; row++){
                        temp = M[row][num]/M[num][num];

                        for (int col = num; col < n; col++){
                              M[row][col] -= M[num][col]*temp;
                              IM[row][col] -= IM[num][col]*temp;
                        }
                        i[row] -= i[num]*temp;
                  }
            }

            for (int num = 0; num < n; num++){
                  for (int row = num+1; row < n; row++){
                        for (int col = num; col < n; col++){
                              M[row][col] = M[row][col] / M[num][col];
                              IM[row][col] = IM[row][col] / M[num][col];
                        }
                        
                  }
            }

            for (int row = 0; row < n; row++){
                  for (int col = 0; col < n; col++){
                        std::cout << IM[row][col] << " ";
                  }
                  std::cout << std::endl;
            }

            for (int num = n-1; num >= 0; num--){
                  for (int row = num-1; row >= 0; row--){
                        temp = M[row][num]/M[num][num];
                        
                        for (int col = num; col < n; col++){

                              M[row][col] -= M[num][col]*temp;
                              IM[row][col] -= IM[num][col]*temp;
                        }
                        i[row] -= i[num]*temp;
                  }
            }

            for (int row = 0; row < n; row++){
                  for (int col = 0; col < n; col++){
                        std::cout << IM[row][col] << " ";
                  }
                  std::cout << std::endl;
            }

            float sol[n];

            for (int num = 0; num < n; num++)
                  sol[num] = i[num]/M[num][num];

            std::cout << "=== Print Solution ===" << std::endl;
            for (int i = 0; i < n; i++)
            {
                  if (isnan(sol[i])){
                        std::cout << "can't solve" << std::endl;
                        break;
                  }
                  else if (isinf(sol[i])){
                        std::cout << "can't solve" << std::endl;
                        break;
                  }
                  else std::cout << "x_" << i+1 << " = " << sol[i] << std::endl;
            }
      }
};



int main(){
      int n;
      printf("정사각행렬의 크기를 입력해주세요 : ");
      scanf("%d", &n);
      Gausses init = {n};
      init.Initialize();
}