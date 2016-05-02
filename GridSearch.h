#ifndef GRIDSEARCH_H
#define GRIDSEARCH_H


//-------------------------------------------------------------------------
/// @file GridSearch.h
/// @author Milto Miltiadou
/// @version 2.0
/// @date 24/03/14
/// @class Grid
/// @brief this class is a Grid that allows easy and quick search of
/// point 2D clouds.
//-------------------------------------------------------------------------

#include <string>
#include <unordered_map>
#include <vector>

class Vec2
{
public:
    Vec2(){};
    Vec2(float i_x, float i_y):m_x(i_x),m_y(i_y){};
    float m_x;
    float m_y;
};



class GridSearch
{
public:
   //--------------------------------------------------------------------------
   /// @brief default constructor
   /// @param[in] i_pointsCloud the points cloud
   /// @param[in] i_samplingRate average of expected pixels per square
   //--------------------------------------------------------------------------
   GridSearch(
           const std::vector<Vec2> &i_pointsCloud,
           const unsigned short int i_samplingRate
           );
   //--------------------------------------------------------------------------
   /// @brief method that search the points cloud and returns the nearest point
   /// @param[in] i_point the point that we would like to find its closest one
   /// @returns the point that is closest to i_point
   //--------------------------------------------------------------------------
   Vec2 getCloserPoint(const Vec2 i_point);

   //--------------------------------------------------------------------------
   /// @brief default destructor
   //--------------------------------------------------------------------------
   ~GridSearch();

private:
   //--------------------------------------------------------------------------
   /// @brief method that takes the x,y position of a square and returns the
   /// key of the corresponding container in m_multiMap
   /// @param[in] i_x the x position of the square
   /// @param[in] i_y the y position of the square
   /// @returns the key of the corresponding container in m_multiMap
   //--------------------------------------------------------------------------
   unsigned int getKeyOfSquare(
           const unsigned int i_x,
           const unsigned int i_y
           );


   //--------------------------------------------------------------------------
   /// @brief the number of squares in the x-axis
   //--------------------------------------------------------------------------
   unsigned int m_nX;
   //--------------------------------------------------------------------------
   /// @brief the number of squares in the y-axis
   //--------------------------------------------------------------------------
   unsigned int m_nY;
   //--------------------------------------------------------------------------
   /// @brief the min values of the geo positions of the pixels
   //--------------------------------------------------------------------------
   Vec2 m_min;
   //--------------------------------------------------------------------------
   /// @brief the max values of the geo positions of the pixels
   //--------------------------------------------------------------------------
   Vec2 m_max;

   //--------------------------------------------------------------------------
   /// @brief the map used for the quick search,
   //--------------------------------------------------------------------------
   std::unordered_multimap<int, int> m_map;

   //--------------------------------------------------------------------------
   /// @brief the points
   //--------------------------------------------------------------------------
   std::vector <Vec2> m_points;

};

#endif // GRIDSEARCH_H
