#include "Game/GameLayer.h"

namespace Game
{
	GameLayer::GameLayer() : Layer("GameLayer")
	{

	}

	void GameLayer::OnUpdate(float deltaTime)
	{
		static_cast<void>(deltaTime);
	}

	void GameLayer::OnRender()
	{

	}
}