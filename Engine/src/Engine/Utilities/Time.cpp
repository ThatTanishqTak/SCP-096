#include "Engine/Utilities/Time.h"

namespace Engine
{
	namespace Utilities
	{
		Uint64 Time::s_Frequency = 0;
		Uint64 Time::s_StartCounter = 0;
		Uint64 Time::s_LastCounter = 0;
		Uint64 Time::s_CurrentCounter = 0;

		float Time::s_DeltaTime = 0.0f;
		float Time::s_TimeSinceStartup = 0.0f;

		void Time::Initialize()
		{
			s_Frequency = SDL_GetPerformanceFrequency();

			s_StartCounter = SDL_GetPerformanceCounter();
			s_LastCounter = s_StartCounter;
			s_CurrentCounter = s_StartCounter;

			s_DeltaTime = 0.0f;
			s_TimeSinceStartup = 0.0f;
		}

		void Time::Update()
		{
			s_CurrentCounter = SDL_GetPerformanceCounter();

			s_DeltaTime = static_cast<float>(s_CurrentCounter - s_LastCounter) / static_cast<float>(s_Frequency);
			s_TimeSinceStartup = static_cast<float>(s_CurrentCounter - s_StartCounter) / static_cast<float>(s_Frequency);
			s_LastCounter = s_CurrentCounter;
		}
	}
}