#include "GridSearch.h"

#include <math.h>
#include <iostream>

//-----------------------------------------------------------------------------
GridSearch::GridSearch(
        const std::vector<Vec2> &i_pointsCloud,
        const unsigned short i_samplingRate
        ):m_points(i_pointsCloud)
{
   // Loop through all the points and find the minimum and max
    if(i_pointsCloud.size()<1)
    {
       std::cout << "Warning: Points cloud too small\n";
       m_min.m_x = 0.0f; m_min.m_y = 0.0f;
       m_max.m_y = 0.1f; m_max.m_y = 0.1f;
       return;
    }
    m_min.m_x = m_points[0].m_x;
    m_min.m_y = m_points[0].m_y;
    m_max.m_x = m_points[0].m_x;
    m_max.m_y = m_points[0].m_y;
    for(unsigned int i=1; i<m_points.size(); ++i)
    {
       if (m_min.m_x>m_points[i].m_x)
       {
          m_min.m_x=m_points[i].m_x;
       } else if (m_max.m_x<m_points[i].m_x)
       {
          m_max.m_x=m_points[i].m_x;
       }
       if (m_min.m_y>m_points[i].m_y)
       {
          m_min.m_y=m_points[i].m_y;
       } else if (m_max.m_y<m_points[i].m_y)
       {
          m_max.m_x=m_points[i].m_y;
       }
    }
    float rate = (m_max.m_x-m_min.m_x)/(m_max.m_y-m_min.m_y);
    float numOfSquares = m_points.size() / i_samplingRate;
    m_nY = sqrt(numOfSquares/rate);
    m_nX = ceil(numOfSquares/m_nY);

    for (unsigned int i=0; i<m_points.size(); ++i)
    {
        unsigned int sqX = double((m_points[i].m_x-m_min.m_x)/
                                  (m_max.m_x-m_min.m_x))*m_nX;
        unsigned int sqY = double((m_points[i].m_y-m_min.m_y)/
                                  (m_max.m_y-m_min.m_y))*m_nY;
        m_map.emplace(getKeyOfSquare(sqX,sqY),i);
    }

}


//-----------------------------------------------------------------------------
unsigned int GridSearch::getKeyOfSquare(
        const unsigned int i_x,
        const unsigned int i_y
        )
{
   return i_x + i_y * m_nX;
}

//-----------------------------------------------------------------------------
Vec2 GridSearch::getCloserPoint(const Vec2 i_point)
{
    const unsigned int x = float((i_point.m_x-m_min.m_x)/
                                 (m_max.m_x-m_min.m_x)*(float)m_nX);
    const unsigned int y = float((i_point.m_y-m_min.m_y)/
                                 (m_max.m_y-m_min.m_y)*(float)m_nY);

    unsigned int closestPointIndex = 0;
    float minDis = sqrt(pow(m_points[0].m_x-i_point.m_x,2.0)+
                        pow(m_points[0].m_y-i_point.m_y,2.0));
    auto itsElements = m_map.equal_range(getKeyOfSquare(x,y));
    for (auto it = itsElements.first; it != itsElements.second; ++it)
    {
       const float distance = sqrt(pow(m_points[it->second].m_x-i_point.m_x,2.0)+
                                   pow(m_points[it->second].m_y-i_point.m_y,2.0));
       if(distance<minDis)
       {
          closestPointIndex = it->second;
          minDis = distance;
       }
    }
    return m_points[closestPointIndex];
}


//-----------------------------------------------------------------------------
GridSearch::~GridSearch()
{
}
