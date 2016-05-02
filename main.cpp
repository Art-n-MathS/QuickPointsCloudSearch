#include <iostream>
#include "GridSearch.h"

#include <vector>

std::vector<Vec2> cloud;

int main(int /*argc*/, char **/*argv*/)
{
   for(unsigned int x=0; x<10; ++x)
   {
      for(unsigned int y=0; y<10; ++y)
      {
          cloud.push_back(Vec2(x,y));
      }
   }

   std::cout << "All the points of the point cloud are: \n";
   for(unsigned int i= 0; i<cloud.size(); ++i)
   {
       std::cout << "(" << cloud[i].m_x << "," << cloud[i].m_y << ") ";
   }
   std::cout << "\n";

   GridSearch grid(cloud,4);

   Vec2 point = grid.getCloserPoint(Vec2(0.0f,0.2f));
   std::cout <<"The closest point to (0,0.2) is (" << point.m_x << "," << point.m_y << ")\n";
   point = grid.getCloserPoint(Vec2(5.2f,5.9f));
   std::cout << "The closest point to (5.2,5.9) is (" << point.m_x << "," << point.m_y << ")\n";

   return 0;
}
