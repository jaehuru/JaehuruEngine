#pragma once

#include "Common/CommonInclude.h"
#include "Component/huruComponent.h"


namespace huru::object
{
	void Destroy(GameObject* gameObject);
}

namespace huru
{
	class GameObject : public Entity
	{
	public:
		friend void object::Destroy(GameObject* obj);

		enum class eState
		{
			Active,
			Paused,
			Dead,
			End
		};

		GameObject();
		~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			comp->SetOwner(this);
			comp->Initialize();

			mComponents[(UINT)comp->GetType()] = comp;
			
			return comp;
		}

		template <typename T>
		T* GetComponent()
		{
			T* component = nullptr;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component)
					break;
			}
			return component;
		}

		void AddChild(GameObject* child)
		{
			if (child == nullptr) return;
			child->mParent = this;
			mChildren.push_back(child);
		}

		template<typename T>
		T* FindChildOfType()
		{
			for (GameObject* child : mChildren)
			{
				if (child == nullptr) 
					continue;

				T* typedChild = dynamic_cast<T*>(child);
				if (typedChild != nullptr)
					return typedChild;
			}
			return nullptr;
		}

		eState GetState() { return mState; }
		void SetActive(bool power)
		{
			if (power == true)
				mState = eState::Active;
			if (power == false)
				mState = eState::Paused;
		}
		bool IsActive() { return mState == eState::Active; }
		bool IsDead() { return mState == eState::Dead; }
		void SetLayerType(eLayerType layerType) { mLayerType = layerType; }
		eLayerType GetLayerType() { return mLayerType; }
		const vector<GameObject*>& GetChildren() const { return mChildren; }

	private:
		void	initializeTransform();
		void	death() { mState = eState::Dead; }
		void	RemoveChild(GameObject* child)
		{
			mChildren.erase(
				remove(mChildren.begin(), mChildren.end(), child),
				mChildren.end());
			child->mParent = nullptr;
		}

	private:
		eState						mState;
		vector<Component*>			mComponents;
		eLayerType					mLayerType;

		GameObject*					mParent;
		vector<GameObject*>			mChildren;
	};
}

