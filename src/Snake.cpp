#include "Snake.h"

#include <GLFW/glfw3.h>

#include <iostream>

#include "Input.h"

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

    std::cout << (int)direction << "\n";
}