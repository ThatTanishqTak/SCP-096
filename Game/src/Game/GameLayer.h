#include "Engine/Layer/Layer.h"

namespace Game
{
	class GameLayer : public Engine::Layer
	{
	public:
		GameLayer();
		~GameLayer() = default;

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
	};
}