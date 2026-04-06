#pragma once

#include <SDL3/SDL.h>

#include <cstdint>

namespace Engine
{
	namespace Utilities
	{
		class Time
		{
		public:
			static void Initialize();
			static void Update();

			static float GetDeltaTime() { return s_DeltaTime; }
			static float GetNow() { return s_TimeSinceStartup; }

		private:
			static std::uint64_t s_Frequency;
			static std::uint64_t s_StartCounter;
			static std::uint64_t s_LastCounter;
			static std::uint64_t s_CurrentCounter;

			static float s_DeltaTime;
			static float s_TimeSinceStartup;
		};
	}
}