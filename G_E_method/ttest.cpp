#include <iostream>
#include <stdio.h>


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

      float M[n][n], IM[n][n] = {0,} , temp;

      
      for (int row = 0; row < n; row++){
            for (int col = 0; col < n; col++){
                  M[row][col] = mat[row][col];
            }
            IM[row][row] = 1;
      }
      

      for (int row = 0; row < n; row++){
            temp = M[row][row];
            for (int col = 0; col < n; col++){
                  M[row][col] = M[row][col]/temp;
                  IM[row][col] = IM[row][col]/temp;
            }
            i[row] = i[row]/temp;
            
            for (int row2 = 0; row2 < n; row2++){
                  temp = M[row2][row];
                  for (int col = 0; col < n; col++){
                        if(row2 != row){
                              M[row2][col] -= temp*M[row][col];
                              IM[row2][col] -= temp*IM[row][col];
                        }
                  }
            }
            
            
      }

      for (int row = 0; row < n; row++){
            for (int col = 0; col < n; col++){
                  std::cout << M[row][col] << " ";
            }
            std::cout << std::endl;
      }

      for (int row = 0; row < n; row++){
            for (int col = 0; col < n; col++){
                  std::cout << IM[row][col] << " ";
            }
            std::cout << std::endl;
      }

      for (int row = 0; row < n; row++){
            
            std::cout << i[row] << std::endl;
      }

}