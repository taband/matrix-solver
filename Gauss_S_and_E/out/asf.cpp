#include <iostream>
using namespace std;

// Struct 
class Point 
{
private:
      double xCoord;
      double yCoord;

public:
      void add(Point& p)
      {
            xCoord += p.xCoord;
            yCoord += p.yCoord;
      }

      Point(double _x, double _y) {
            xCoord = _x;
            yCoord = _y;
      }

      void printConsole()
      {
            cout << "x coordinate :" << xCoord << endl;
            cout << "y coordinate :" << yCoord << endl;
      }
};

int main()
{
      Point p1(3.0, 4.0);
      Point p2(2.0, 1.0);

      p1.add(p2);

      p1.printConsole();
      p2.printConsole();

      return 0;
}













