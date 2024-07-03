#pragma once

#include <vector>
#include <map>

class IPool
{
public:
	virtual ~IPool() {}

	virtual void RemoveEntityFromPool(size_t entityId) = 0;
};

template <typename T>
class Pool : public IPool
{
private:
	std::vector<T> mData;
	size_t mSize;

	std::unordered_map<size_t, size_t> mEntityIdToIndex;
	std::unordered_map<size_t, size_t> mIndexToEntityId;

public:
	Pool(size_t capacity = 100)
	{
		mSize = 0;
		mData.resize(capacity);
	}
	virtual ~Pool() = default;

	T& operator[] (size_t index) { return mData[index]; }

	inline bool IsEmpty() const { return mSize == 0; }
	inline size_t Size() const { return mSize; }
	inline void Resize(size_t size) { mData.resize(size); }
	inline void Clear() { mData.clear(); mSize = 0; }
	inline void Add(T data) { mData.push_back(data); }

	void RemoveEntityFromPool(size_t entityId) override
	{
		if (mEntityIdToIndex.find(entityId) != mEntityIdToIndex.end())
		{
			Remove(entityId);
		}
	}
	
	T& Get(const size_t entityId)
	{
		size_t index = mEntityIdToIndex[entityId];
		return static_cast<T&>(mData[index]);
	}
	void Set(size_t entityId, T object)
	{
		if (mEntityIdToIndex.find(entityId) != mEntityIdToIndex.end())
		{
			size_t index = mEntityIdToIndex[entityId];
			mData[index] = object;
		}
		else
		{
			size_t index = mSize;
			mEntityIdToIndex.emplace(entityId, index);
			mIndexToEntityId.emplace(index, entityId);

			if (index >= mData.capacity())
			{
				mData.resize(mSize * 2);
			}

			mData[index] = object;
			mSize++;
		}
	}
	void Remove(size_t entityId)
	{
		size_t indexOfRemoved = mEntityIdToIndex[entityId];
		size_t indexOfLast = mSize - 1;
		mData[indexOfRemoved] = mData[indexOfLast];

		size_t entityIdOfLastElement = mIndexToEntityId[indexOfLast];
		mEntityIdToIndex[entityIdOfLastElement] = indexOfRemoved;
		mIndexToEntityId[indexOfRemoved] = entityIdOfLastElement;

		mEntityIdToIndex.erase(entityId);
		mIndexToEntityId.erase(indexOfLast);

		mSize--;
	}
};