//
// Created by deakin on 11/11/26.
//

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// this only applies if the "up" direction is +y
static glm::vec3 GetUp() { return glm::vec3(0.0f, 1.0f, 0.0f); }

class Camera
{
    glm::vec3 cameraPos_ { glm::vec3(0.0f, 0.0f, 3.0f) };
    glm::vec3 cameraTarget_ { glm::vec3(0.0f, 0.0f, 0.0f) };

public:
    [[nodiscard]] glm::vec3 GetDirection()
        { return glm::normalize(cameraPos_ - cameraTarget_); }
    [[nodiscard]] glm::vec3 GetRight()
        { return glm::normalize(glm::cross(GetUp(), GetDirection())); }
    [[nodiscard]] glm::vec3 GetUp()
        { return glm::cross(GetDirection(), GetRight()); }
};
