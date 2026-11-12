//
// Created by deakin on 11/12/26.
//

#pragma once
#include "Square.hpp"

class Cube
{
    struct CubeFaces
    {
        Square top;
        Square bottom;
        Square xp;
        Square xn;
        Square yp;
        Square yn;
    };

    CubeFaces cubeFaces_;
};

