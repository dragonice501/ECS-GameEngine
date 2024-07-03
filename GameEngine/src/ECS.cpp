#include "ECS.h"

#include "Logger.h"

void Entity::Kill()
{
    mRegistry->KillEntity(*this);
}

void Entity::Tag(const std::string& tag)
{
    mRegistry->TagEntity(*this, tag);
}

bool Entity::HasTag(const std::string& tag)
{
    return mRegistry->EntityHasTag(*this, tag);
}

void Entity::Group(const std::string& group)
{
    mRegistry->GroupEntity(*this, group);
}

bool Entity::BelongsToGroup(const std::string& group)
{
    return mRegistry->EntityBelongsToGroup(*this, group);
}

void System::AddEntityToSystem(const Entity& entity)
{
    mEntities.push_back(entity);
}

void System::RemoveEntity(const Entity& entity)
{
    mEntities.erase(std::remove_if(mEntities.begin(), mEntities.end(), [&entity](Entity other)
        {
            return entity == other;
        }), mEntities.end());
}

std::vector<Entity>& System::GetSystemEntities()
{
    return mEntities;
}

const Signature& System::GetComponentSignature() const
{
    return mComponentSignature;
}

void Registry::Update()
{
    for (auto entity : mEntitiesToBeAdded)
    {
        AddEntityToSytems(entity);
    }
    mEntitiesToBeAdded.clear();

    for (auto entity : mEntitiesToBeKilled)
    {
        RemoveEntityFromSystems(entity);
        
        mEntityComponentSignatures[entity.GetID()].reset();

        for (auto pool : mComponentPools)
        {
            if(pool)
                pool->RemoveEntityFromPool(entity.GetID());
        }

        mFreeIds.push_back(entity.GetID());

        RemoveEntityTag(entity);
        RemoveEntityGroup(entity);
    }
    mEntitiesToBeKilled.clear();
}

Entity Registry::CreateEntity()
{
    size_t entityId;
    if (mFreeIds.empty())
    {
        entityId = mNumEntities++;
        if (entityId >= mEntityComponentSignatures.size()) mEntityComponentSignatures.resize(entityId + 1);
    }
    else
    {
        entityId = mFreeIds.front();
        mFreeIds.pop_front();
    }

    Entity entity(entityId, this);
    mEntitiesToBeAdded.insert(entity);

    Logger::Log("Entity created with id " + std::to_string(entityId));

    return entity;
}

void Registry::KillEntity(Entity entity)
{
    mEntitiesToBeKilled.insert(entity);
}

void Registry::TagEntity(Entity entity, const std::string& tag)
{
    mEntityPerTag.emplace(tag, entity);
    mTagPerEntity.emplace(entity.GetID(), tag);
}

bool Registry::EntityHasTag(Entity entity, const std::string& tag) const
{
    if (mTagPerEntity.find(entity.GetID()) == mTagPerEntity.end()) return false;

    return mEntityPerTag.find(tag)->second == entity;
}

Entity Registry::GetEntityByTag(const std::string& tag) const
{
    return mEntityPerTag.at(tag);
}

void Registry::RemoveEntityTag(Entity entity)
{
    auto taggedEntity = mTagPerEntity.find(entity.GetID());
    if (taggedEntity != mTagPerEntity.end())
    {
        auto tag = taggedEntity->second;
        mEntityPerTag.erase(tag);
        mTagPerEntity.erase(taggedEntity);
    }
}

void Registry::GroupEntity(Entity entity, const std::string& group)
{
    mEntitiesPerGroup.emplace(group, std::set<Entity>());
    mEntitiesPerGroup[group].emplace(entity);
    mGroupPerEntity.emplace(entity.GetID(), group);
}

bool Registry::EntityBelongsToGroup(Entity entity, const std::string& group) const
{
    auto groupEntities = mEntitiesPerGroup.at(group);

    return groupEntities.find(entity) != groupEntities.end();
}

std::vector<Entity> Registry::GetEntitiesByGroup(const std::string& group) const
{
    auto& setOfEntities = mEntitiesPerGroup.at(group);

    return std::vector<Entity>(setOfEntities.begin(), setOfEntities.end());
}

void Registry::RemoveEntityGroup(Entity entity)
{
    auto groupedEntity = mGroupPerEntity.find(entity.GetID());
    if (groupedEntity != mGroupPerEntity.end())
    {
        auto group = mEntitiesPerGroup.find(groupedEntity->second);
        if (group != mEntitiesPerGroup.end())
        {
            auto entityInGroup = group->second.find(entity);
            if (entityInGroup != group->second.end())
            {
                group->second.erase(entityInGroup);
            }
        }
        mGroupPerEntity.erase(groupedEntity);
    }
}

void Registry::AddEntityToSytems(Entity entity)
{
    const auto entityId = entity.GetID();
    const auto entityComponentSignature = mEntityComponentSignatures[entityId];

    for (auto& system : mSystems)
    {
        auto systemComponentSignature = system.second->GetComponentSignature();

        if ((entityComponentSignature & systemComponentSignature) == systemComponentSignature)
        {
            system.second->AddEntityToSystem(entity);
        }
    }
}

void Registry::RemoveEntityFromSystems(Entity entity)
{
    for (auto& system : mSystems)
    {
        system.second->RemoveEntity(entity);
    }
}