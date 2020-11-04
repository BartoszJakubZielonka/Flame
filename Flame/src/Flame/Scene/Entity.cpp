#include "flpch.h"
#include "Entity.h"

namespace flame {

	Entity::Entity(entt::entity handle, Scene* scene): m_EntityHandle(handle), m_Scene(scene)
	{
	}

}