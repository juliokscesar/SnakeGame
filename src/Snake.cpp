#include "Snake.h"

#include <GLFW/glfw3.h>

#include <iostream>

#include "Input.h"

#define MIN_X -2.8
#define MIN_Y -2.9

void Snake::Update(float deltaTime)
{
    Entity::Update(deltaTime);

    if (Input::GetKey(GLFW_KEY_UP) == KeyEvent::PRESS)
        direction = MovementDirection::UP;
    if (Input::GetKey(GLFW_KEY_DOWN) == KeyEvent::PRESS)
        direction = MovementDirection::DOWN;
    if (Input::GetKey(GLFW_KEY_RIGHT) == KeyEvent::PRESS)
        direction = MovementDirection::RIGHT;
    if (Input::GetKey(GLFW_KEY_LEFT) == KeyEvent::PRESS)
        direction = MovementDirection::LEFT;
    
    if (Input::GetKey(GLFW_KEY_SPACE) == KeyEvent::PRESS)
        direction = MovementDirection::STOP;

    switch (direction)
    {
    case MovementDirection::UP:
        this->Transform.Position.y += velocity * deltaTime;
        break;
    
    case MovementDirection::DOWN:
        this->Transform.Position.y -= velocity * deltaTime;
        break;

    case MovementDirection::LEFT:
        this->Transform.Position.x -= velocity * deltaTime;
        break;

    case MovementDirection::RIGHT:
        this->Transform.Position.x += velocity * deltaTime;
        break;

    case MovementDirection::STOP:
        break;

    default:
        return;
    }

    if (Transform.Position.x < -4.44f || Transform.Position.x > 4.44f)
        Transform.Position.x *= -1;
    if (Transform.Position.y < -4.58f || Transform.Position.y > 4.58f)
        Transform.Position.y *= -1;
}