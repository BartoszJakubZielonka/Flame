#pragma once

#include <string>
#include "Flame/Core/Core.h"

namespace flame
{
	class Texture
	{
	public:
		Texture() = default;
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(std::string_view path);
	};
}