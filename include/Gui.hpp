//
// Created by deakin on 11/12/26.
//

#ifndef BASEL_ENGINE_GUI_HPP
#define BASEL_ENGINE_GUI_HPP
#include "Window.hpp"


class Gui
{
public:
    Gui(Window& window);
    ~Gui();

    void StartFrame();
    void EndFrame();
};


#endif //BASEL_ENGINE_GUI_HPP
