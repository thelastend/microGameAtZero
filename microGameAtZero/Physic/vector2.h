#ifndef _VECTOR2_MICROGAMEATZERO_
#define _VECTOR2_MICROGAMEATZERO_


#include <stdint.h>
#include <stddef.h>
#include <cmath>


/**
 * @brief vector2 class
 * 
 */
class vector2{

public:
    int16_t x,y;

    vector2():x(0),y(0){}
    vector2(int16_t x,int16_t y):x(x),y(y){}
    void operator+(const vector2& v);
    void operator-(const vector2& v);
    bool operator==(const vector2& v);
    void operator+(int16_t s);
    void operator-(int16_t s);
    void operator*(int16_t s);
    void operator/(int16_t s);
    void set(const vector2& v);
    void set(int16_t _x =0,int16_t _y = 0);

};

#endif