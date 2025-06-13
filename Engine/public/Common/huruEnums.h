#pragma once

#include <type_traits>

namespace huru::utils
{
	template<typename T>
	constexpr huru::enums::eLayerType ToEngineLayerType(T layerEnum)
	{
		static_assert(std::is_enum_v<T>, "Must be enum type.");
		return static_cast<enums::eLayerType>(layerEnum);
	}
}

namespace huru::enums
{
	enum class eComponentType
	{
		Transform,
		TileMapRenderer,
		Collider,
		Rigidbody,
		Script,
		SpriteRenderer,
		Animator,
		Camera,
		AudioListener,
		AudioSource,
		End,
	};

	enum class eLayerType
	{
		None,
		Max = 16,
	};

	enum class eResourceType
	{
		Texture,
		AudioClip,
		Animation,
		Prefab,
		End,
	};

	enum class eColliderType
	{
		Circle2D,
		Rect2D,
		End,
	};

	enum class eUIType
	{
		Button,
		HUD,
		End,
	};
}