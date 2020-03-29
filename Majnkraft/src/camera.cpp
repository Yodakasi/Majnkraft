#include "camera.h"

#include <iostream>
//delete pls

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) 
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY)
{
    cameraMoved = true;
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}


void Camera::updateCameraVectors()
{
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // Update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::ProcessKeyboard(int direction, float deltaTime) {
    cameraMoved = true;
    float velocity = MovementSpeed * deltaTime;
    float x=Position.x, y=Position.z;
    if (x < 0) {
        x -= 4;
    }
    if (y < 0) {
        y -= 4;
    }
    //std::cout << (int)x/4 << " " << (int)y/4 << " " << Position.x << " " << Position.z << std::endl;
    if (direction == 0)
        Position += Front * velocity;
    else if (direction == 1)
        Position -= Front * velocity;
    else if (direction == 2)
        Position -= Right * velocity;
    else if (direction == 3)
        Position += Right * velocity;
    else if (direction == 4)
        Position += Up * velocity;
    else if (direction == 5)
        Position -= Up * velocity;
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

glm::vec2 Camera::get2dPos() {
    float x = Position.x, y = Position.z;
    if (x < 0) {
        x -= 4;
    }
    if (y < 0) {
        y -= 4;
    }
    return glm::vec2((int)x/4, (int)y/4);
}

bool Camera::getCameraMoved() {
    if (cameraMoved) {
        cameraMoved = false;
        return true;
    }
    return false;
}
