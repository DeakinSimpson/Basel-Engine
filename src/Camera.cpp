//
// Created by deakin on 11/11/26.
//

#include "../include/Camera.hpp"

/**
 * This function takes in the how much the mouse has moved and and updates
 * the offset based on sensitivity before calling UpdateVectors to update
 * the cameras facing directions.
 *
 * @param xOffset How far the mouse moved in x since last frame
 * @param yOffset How far the mouse moved in y since last frame
 * @param constrainPitch To lock the camera from going to far up or down
 */
void Camera::ProcessMouseMovement(float xOffset, float yOffset,
    const bool constrainPitch)
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

/**
 * Updates the cameras cameraFront_ vector based on the current pitch and yaw
 */
void Camera::UpdateVectors()
{
    // calculate a new cameraFront_ vector based on new pitch and yaw
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    newFront.y = sin(glm::radians(pitch_));
    newFront.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    cameraFront_ = glm::normalize(newFront);
}
