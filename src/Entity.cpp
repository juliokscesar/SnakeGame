#include "Entity.h"

#include <glm/gtc/matrix_transform.hpp>

void Entity::Update()
{
    ModelMatrix = glm::mat4(1.0f);

    // Apply Rotation
    if (Transform.Rotation.x)
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Transform.Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // x-axis (pitch)
    if (Transform.Rotation.y)
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Transform.Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // y-axis (yaw)
    if (Transform.Rotation.z)
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Transform.Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // z-axis (roll)

    // Apply Scale
    ModelMatrix = glm::scale(ModelMatrix, Transform.Scale);
    
    // Apply Translation
    ModelMatrix = glm::translate(ModelMatrix, Transform.Position);
}
