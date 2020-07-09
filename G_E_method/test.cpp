#include <iostream>


class Arraymake{
private:
      int n;
public:
      double* data;
      Arraymake(const int& _n)
      {
            n = _n;

            data = new double[n];
            for (int i = 0; i < n; i++)
                  data[i] = i+5;
      }
};

class MatSol
{
private:
      int n;


public:
      MatSol(int _n)
      {
            n = _n;
      }
      
      void PrintMat(const double data[])
      {
            for (int i = 0; i < n ; i++)
            {
                  std::cout << data[i] << std::endl;
            }
      }
      
};


int main(){
      int n;

      std::cin >> n;
      
      Arraymake myArr(n);

            
      MatSol pMat(n);

      pMat.PrintMat(myArr.data);
      
      
}