//
// Created by deakin on 11/12/26.
//

#pragma once
#include "Square.hpp"

class Cube
{
    std::array<Square, 6> cubeFaces_;

public:
    void Render(const std::array<bool, 6> facesToRender);
};

