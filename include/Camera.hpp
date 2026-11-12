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
    /**
     *
     * @return The vector of the direction that is right of the facing direction
     */
    [[nodiscard]] glm::vec3 GetRight() const
    {
        return glm::normalize(glm::cross(cameraFront_, cameraUp_));
    }

    /**
     *
     * @return returns the cameras current view matrix
     */
    [[nodiscard]] glm::mat4 GetView() const
    {
        return glm::lookAt(cameraPos_, cameraPos_ + cameraFront_, cameraUp_);
    }

    /**
     *
     * @param deltaTime The time that has passed since the last frame
     * @return the speed based on the camera speed and the time since last frame
     */
    [[nodiscard]] float GetSpeed(const float deltaTime) const
    {
        return cameraSpeed_ * deltaTime;
    }

    /**
     * This function moves the camera towards the facing direction
     *
     * @param deltaTime Elapsed time since last frame
     */
    void MoveForward(const float deltaTime)
    {
        cameraPos_ += GetSpeed(deltaTime) * cameraFront_;
    }

    /**
     * Moves camera left of the facing direction
     *
     * @param deltaTime Elapsed time since last frame
     */
    void MoveLeft(const float deltaTime)
    {
        cameraPos_ -= GetRight() * GetSpeed(deltaTime);
    }

    /**
     * Moves camera right of the cameras facing direction
     *
     * @param deltaTime Elapsed time since last frame
     */
    void MoveRight(const float deltaTime)
    {
        cameraPos_ += GetRight() * GetSpeed(deltaTime);
    }

    /**
     * Moves camera back from the camera facing direction
     *
     * @param deltaTime Elapsed time since last frame
     */
    void MoveBack(const float deltaTime)
    {
        cameraPos_ -= GetSpeed(deltaTime) * cameraFront_;
    }

    void ProcessMouseMovement(float xOffset, float yOffset,
        const bool constrainPitch = true);

private:
    void UpdateVectors();
};
