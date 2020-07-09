#include <stdio.h>
#include <iostream>
#include <math.h>



void Gauss_Elemination(const int *matrix,const int *rhs, const int n, float* sol);




int main(){
      int n;

      printf("정사각행렬의 크기를 입력해주세요 : ");
      scanf("%d", &n);

      int mat[n][n], i[n];

      for (int row = 0; row < n; row++){
            for (int col = 0; col < n; col++){
                  printf("%d행 %d열 입력 : ", row+1, col+1);
                  scanf("%d", &mat[row][col]);
            }
            printf("%d행의 인수를 입력해주세요 : ", row+1);
            scanf("%d", &i[row]);
      }
      
      float solution[n];
      
      Gauss_Elemination((int*)mat,i,n, solution);
      
      std::cout << "=== Print Solution ===" << std::endl;
      for (int i = 0; i < n; i++)
      {
            if (isnan(solution[i])){
                  std::cout << "can't solve" << std::endl;
                  break;
            }
            else if (isinf(solution[i])){
                  std::cout << "can't solve" << std::endl;
                  break;
            }
            else std::cout << "x_" << i+1 << " = " << solution[i] << std::endl;
      }

      return 0;
}




void Gauss_Elemination(const int *matrix,const int *rhs, const int n, float* sol){
      
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
                  }

                  i[row] -= i[num]*temp;
            }
      }

      for (int col = n-1; col >= 0; col--){
            for (int row = col-1; row >= 0; row--){
                  temp = M[row][col]/M[col][col];
                  i[row] -= i[col]*temp;
            }
      }

      for (int num = 0; num < n; num++)
            sol[num] = i[num]/M[num][num];
}