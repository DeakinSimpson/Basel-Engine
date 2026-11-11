//
// Created by deakin on 11/11/26.
//

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
    glm::vec3 cameraPos_ { glm::vec3(0.0f, 0.0f, 3.0f) };
    glm::vec3 cameraTarget_ { glm::vec3(0.0f, 0.0f, 0.0f) };

    glm::vec3 cameraFront_ = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp_    = glm::vec3(0.0f, 1.0f,  0.0f);

    static constexpr float cameraSpeed = 10.0f;


public:
    [[nodiscard]] glm::vec3 GetDirection()
        { return glm::normalize(cameraPos_ - cameraTarget_); }
    [[nodiscard]] glm::vec3 GetRight()
        { return glm::normalize(glm::cross(cameraUp_, GetDirection())); }
    [[nodiscard]] glm::mat4 GetView()
        { return glm::lookAt(cameraPos_, cameraPos_ + cameraFront_, cameraUp_); }
    [[nodiscard]] float GetSpeed(const float deltaTime) const
        { return cameraSpeed * deltaTime; }

    void MoveForward(const float deltaTime)
    {
        cameraPos_ += GetSpeed(deltaTime) * cameraFront_;
    }

    void MoveLeft(const float deltaTime)
    {
        cameraPos_ -= glm::normalize(glm::cross(cameraFront_, cameraUp_)) *
            GetSpeed(deltaTime);
    }

    void MoveRight(const float deltaTime)
    {
        cameraPos_ += glm::normalize(glm::cross(cameraFront_, cameraUp_)) *
            GetSpeed(deltaTime);
    }

    void MoveBack(const float deltaTime)
    {
        cameraPos_ -= GetSpeed(deltaTime) * cameraFront_;
    }
};