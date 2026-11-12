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

    // TODO: PULL THESE FROM CONFIG
    float cameraSpeed_ { 10.0f };
    float mouseSensitivity_ { 0.1f };
    float fov_ { 45.0f };

    /**
     * yaw and pitch are kept as the current running pointing direction, then
     * the vectors are updated each to match the yaw and the pitch.
     *
     * This is because mouse movement can essentially be converted into yaw and
     * pitch for up-down, left-right
     */
    float yaw_ { -90.0f };
    float pitch_ { 0.0f };

public:
    [[nodiscard]] glm::vec3 GetDirection() const
    {
        return glm::normalize(cameraPos_ - cameraTarget_);
    }
    [[nodiscard]] glm::vec3 GetRight() const
    {
        return glm::normalize(glm::cross(cameraFront_, cameraUp_));
    }
    [[nodiscard]] glm::mat4 GetView() const
    {
        return glm::lookAt(cameraPos_, cameraPos_ + cameraFront_, cameraUp_);
    }
    [[nodiscard]] float GetSpeed(const float deltaTime) const
    {
        return cameraSpeed_ * deltaTime;
    }

    void MoveForward(const float deltaTime)
    {
        cameraPos_ += GetSpeed(deltaTime) * cameraFront_;
    }

    void MoveLeft(const float deltaTime)
    {
        cameraPos_ -= GetRight() *
            GetSpeed(deltaTime);
    }

    void MoveRight(const float deltaTime)
    {
        cameraPos_ += GetRight() *
            GetSpeed(deltaTime);
    }

    void MoveBack(const float deltaTime)
    {
        cameraPos_ -= GetSpeed(deltaTime) * cameraFront_;
    }

    void ProcessMouseMovement(float xOffset, float yOffset,
        const bool constrainPitch = true)
    {
        // increase the offset based on the mouse sensitivity
        xOffset *= mouseSensitivity_;
        yOffset *= mouseSensitivity_;

        // update camera yaw and pitch based on the offset
        yaw_ += xOffset;
        pitch_ += yOffset;

        // if pitch is constrained stop camera from looking too far up or down
        if (constrainPitch)
        {
            if (pitch_ > 89.0f) { pitch_ = 89.0f; }
            if (pitch_ < -89.0f) { pitch_ = -89.0f; }
        }

        // update the camera vectors to match the pitch and yaw
        UpdateVectors();
    }
private:

    void UpdateVectors()
    {
        // calculate a new cameraFront_ vector based on new pitch and yaw
        glm::vec3 newFront;
        newFront.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
        newFront.y = sin(glm::radians(pitch_));
        newFront.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
        cameraFront_ = glm::normalize(newFront);
    }
};
