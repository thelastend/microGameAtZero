//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/

#include "vector2.h"


/**
 * @brief added with the passed vector2
 * 
 * @param v vector2 to add
 */
void vector2::operator+(const vector2& v)
{
    x = x+v.x;
    y = y+v.y;

}


/**
 * @brief subtract with the passed vector2
 * 
 * @param v vector2 to subtract
 */
void vector2::operator-(const vector2& v)
{
    x = x-v.x;
    y = y-v.y;

}


/**
 * @brief This function compares if the passed vector2 is equal
 * 
 * @param v vector2 to compare
 * @return true is equal
 * @return false is not equal
 */
bool vector2::operator==(const vector2& v)
{
    if((x == v.x) && (y == v.y))
        return true;
    else
        return false;
}


/**
 * @brief This function added the passed int16_t value to x and y.
 * 
 * @param s int16_t value to add
 */
void vector2::operator+(int16_t s)
{
    x = x+s;
    y = y+s;
}


/**
 * @brief This function subtract the passed int16_t value to x and y.
 * 
 * @param s int16_t value to subtract
 */
void vector2::operator-(int16_t s)
{
    x = x-s;
    y = y-s;
}


/**
 * @brief This function multiplies  the passed int16_t value to x and y.
 * 
 * @param v vector2 to multiplies 
 */
void vector2::operator*(int16_t s)
{
    x = x*s;
    y = y*s;
}


/**
 * @brief This function divide the passed int16_t value to x and y.
 * 
 * @param v vector2 to divide
 */
void vector2::operator/(int16_t s)
{
    x = x/s;
    y = y/s;
}


/**
 * @brief This function set the values to the passed vector2.
 * 
 * @param v vector2 to which is set
 */
void vector2::set(const vector2& v)
{
    x = v.x;
    y = v.y;
}


/**
 * @brief This function set x and y to the passed x and y value.
 * 
 * @param _x  new x value
 * @param _y  new y value
 */
void vector2::set(int16_t _x,int16_t _y)
{
    x = _x;
    y = _y;
}
