#pragma once

namespace flame
{
	class Timestep
	{
	public:
		Timestep(float time = 0.0f);

		operator float() const;

		float GetSeconds() const;
		float GetMilliseconds() const;
	private:
		float m_Time;
	};
}