#include "Globals.h"
#include <glm/glm.hpp>

s_globals globals;
s_Avatar Avatar;

void avatarMoveForward()
{
	Avatar.posX += Avatar.movementSpeed * cos(glm::radians(Avatar.yaw));
	Avatar.posZ += Avatar.movementSpeed * sin(glm::radians(Avatar.yaw));
}

void avatarMoveBackward()
{
	Avatar.posX -= Avatar.movementSpeed * cos(glm::radians(Avatar.yaw));
	Avatar.posZ -= Avatar.movementSpeed * sin(glm::radians(Avatar.yaw));
}

void avatarMoveLeft()
{
	Avatar.posX += Avatar.movementSpeed * sin(glm::radians(Avatar.yaw));
	Avatar.posZ -= Avatar.movementSpeed * cos(glm::radians(Avatar.yaw));
}

void avatarMoveRight()
{
	Avatar.posX -= Avatar.movementSpeed * sin(glm::radians(Avatar.yaw));
	Avatar.posZ += Avatar.movementSpeed * cos(glm::radians(Avatar.yaw));
}

void avatarMoveUp()
{
	Avatar.posY += Avatar.movementSpeed;
}

void avatarMoveDown()
{
	Avatar.posY -= Avatar.movementSpeed;
}