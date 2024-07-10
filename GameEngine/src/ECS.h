#pragma once

#include <vector>
#include <set>
#include <unordered_map>
#include <deque>
#include <typeindex>
#include <memory>
#include <iostream>

#include "Logger.h"

#include "Component.h"
#include "Pool.h"
#include "Constants.h"

class Registry;

class Entity
{
private:
	size_t mId;
	Registry* mRegistry;

public:
	Entity() {}
	Entity(size_t id, Registry* registry)
	{
		this->mId = id;
		this->mRegistry = registry;
	}
	Entity(const Entity& entity)
	{
		this->mId = entity.mId;
		this->mRegistry = entity.mRegistry;
	}

	bool operator == (const Entity& rhs) const { return rhs.GetID() == mId; }
	bool operator != (const Entity& rhs) const { return rhs.mId != mId; }
	bool operator > (const Entity& rhs) const { return rhs.mId > mId; }
	bool operator < (const Entity& rhs) const { return rhs.mId < mId; }

	inline size_t GetID() const { return mId; }
	void Kill();
	void Tag(const std::string& tag);
	bool HasTag(const std::string& tag);
	void Group(const std::string& group);
	bool BelongsToGroup(const std::string& group);

	template <typename TComponent, typename ...TArgs> void AddComponent(TArgs&&... args);
	template <typename TComponent> void RemoveComponent();
	template <typename TComponent> bool HasComponent() const;
	template <typename TComponent> TComponent& GetComponent();
};

class System
{
protected:
	Signature mComponentSignature;
	std::vector<Entity> mEntities;
	Registry* mRegistry;

public:
	System() = default;
	~System() = default;

	void SetRegsitry(Registry* registry);
	void AddEntityToSystem(const Entity& entity);
	void RemoveEntity(const Entity& entity);
	std::vector<Entity>& GetSystemEntities();
	const Signature& GetComponentSignature() const;

	template <typename TComponent>
	void RequireComponent()
	{
		const auto componentId = Component<TComponent>::GetId();
		mComponentSignature.set(componentId);
	}
};

class Registry
{
private:
	size_t mNumEntities = 0;
	std::set<Entity> mEntitiesToBeAdded;
	std::set<Entity> mEntitiesToBeKilled;
	std::deque<size_t> mFreeIds;

	std::unordered_map<std::string, Entity> mEntityPerTag;
	std::unordered_map<size_t, std::string> mTagPerEntity;

	std::unordered_map<std::string, std::set<Entity>> mEntitiesPerGroup;
	std::unordered_map<size_t, std::string> mGroupPerEntity;

	std::vector<std::shared_ptr<IPool>> mComponentPools;
	std::vector<Signature> mEntityComponentSignatures;

	std::unordered_map<std::type_index, std::shared_ptr<System>> mSystems;

public:
	Registry() = default;

	void Update();
	void UpdateSystems();
	void DrawRenderSystems();

	Entity CreateEntity();
	void KillEntity(Entity entity);

	void TagEntity(Entity entity, const std::string& tag);
	bool EntityHasTag(Entity entity, const std::string& tag) const;
	Entity& GetEntityByTag(const std::string& tag);
	void RemoveEntityTag(Entity entity);

	void GroupEntity(Entity entity, const std::string& group);
	bool EntityBelongsToGroup(Entity entity, const std::string& group) const;
	std::vector<Entity> GetEntitiesByGroup(const std::string& group);
	void RemoveEntityGroup(Entity entity);

	template<typename TSystem, typename ...TArgs> void AddSystem(TArgs&& ...args);
	template<typename TSystem> void RemoveSystem();
	template<typename TSystem> bool HasSystem();
	template<typename TSystem> TSystem& GetSystem();

	template<typename TComponent, typename ...TArgs> void AddComponent(Entity entity, TArgs&& ...args);
	template<typename TComponent> void RemoveComponent(Entity entity);
	template<typename TComponent> bool HasComponent(Entity entity);
	template<typename TComponent> TComponent& GetComponent(Entity entity) const;

	void AddEntityToSytems(Entity entity);
	void RemoveEntityFromSystems(Entity entity);
};

template<typename TComponent, typename ...TArgs>
inline void Registry::AddComponent(Entity entity, TArgs && ...args)
{
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.GetID();

	if (componentId >= mComponentPools.size()) mComponentPools.resize(componentId + 1, nullptr);

	if (!mComponentPools[componentId])
	{
		std::shared_ptr<Pool<TComponent>> newComponentPool = std::make_shared<Pool<TComponent>>();
		mComponentPools[componentId] = newComponentPool;
	}

	std::shared_ptr<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>(mComponentPools[componentId]);

	TComponent newComponent(std::forward<TArgs>(args)...);

	componentPool->Set(entityId, newComponent);
	mEntityComponentSignatures[entityId].set(componentId);
}

template<typename TComponent>
inline void Registry::RemoveComponent(Entity entity)
{
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.GetID();

	std::shared_ptr<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>(mComponentPools[componentId]);
	componentPool->Remove(entityId);

	mEntityComponentSignatures[entityId].set(componentId, false);
}

template<typename TComponent>
inline bool Registry::HasComponent(Entity entity)
{
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.GetID();

	return mEntityComponentSignatures[entityId].test(componentId);
}

template<typename TComponent>
inline TComponent& Registry::GetComponent(Entity entity) const
{
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.GetID();

	auto componentPool = std::static_pointer_cast<Pool<TComponent>>(mComponentPools[componentId]);

	return componentPool->Get(entityId);
}

template<typename TSystem, typename ...TArgs>
inline void Registry::AddSystem(TArgs && ...args)
{
	std::shared_ptr<TSystem> newSystem = std::make_shared<TSystem>(TSystem(std::forward<TArgs>(args)...));

	std::type_index typeIndex = std::type_index(typeid(TSystem));
	mSystems.insert(std::make_pair(typeIndex, newSystem));

	mSystems.at(typeIndex)->SetRegsitry(this);
}

template<typename TSystem>
inline void Registry::RemoveSystem()
{
	auto system = mSystems.find(std::type_index(typeid(TSystem)));

	mSystems.erase(system);
}

template<typename TSystem>
inline bool Registry::HasSystem()
{
	return mSystems.find(std::type_index(typeid(TSystem))) != mSystems.end();
}

template<typename TSystem>
inline TSystem& Registry::GetSystem()
{
	auto system = mSystems.find(std::type_index(typeid(TSystem)));
	return *(std::static_pointer_cast<TSystem>(system->second));
}

template<typename TComponent, typename ...TArgs>
inline void Entity::AddComponent(TArgs && ...args)
{
	mRegistry->AddComponent<TComponent>(*this, std::forward<TArgs>(args)...);
}

template<typename TComponent>
inline void Entity::RemoveComponent()
{
	mRegistry->RemoveComponent<TComponent>(*this);
}

template<typename TComponent>
inline bool Entity::HasComponent() const
{
	return mRegistry->HasComponent<TComponent>(*this);
}

template<typename TComponent>
inline TComponent& Entity::GetComponent()
{
	return mRegistry->GetComponent<TComponent>(*this);
}