//
// Created by deakin on 11/12/26.
//

#pragma once

#include "Window.hpp"

class Gui
{
    bool isVisible { false };
public:
    Gui(Window& window);
    ~Gui();

    void StartFrame();
    void EndFrame();
    void ToggleGui() { isVisible = !isVisible; }
    bool GetVisibility() const { return isVisible; }
};
