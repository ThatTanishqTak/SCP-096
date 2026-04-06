#include "Engine/Layer/Layer.h"

namespace Game
{
	class GameLayer : public Engine::Layer
	{
	public:
		GameLayer() = default;
		~GameLayer() = default;

		void Update() override;
		void Render() override;
	};
}