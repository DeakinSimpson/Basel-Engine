//
// Created by deakin on 11/7/26.
//

#include "../include/Cube.hpp"

#include <iostream>
#include <ostream>

void Cube::Render()
{
    std::cout << "Cube::Render() Run" << std::endl;
    renderable_.Render();
}
