#pragma once

namespace Engine
{
	class Layer
	{
	public:
		Layer() = default;
		~Layer() = default;

		virtual void Render() = 0;
		virtual void Update() = 0;
	};
}