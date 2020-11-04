#pragma once

#include "entt.hpp"

#include "Flame/Core/Timestep.h"

namespace flame
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene() = default;

		Entity CreateEntity(const std::string& name = std::string());

		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;

		friend class Entity;
	};
}