#pragma once

#include "Event.h"
#include "Observer.h"
#include "GameObject.h"

#include <vector>

class EventManager
{
private:
	static std::vector<Observer*> mObservers;

private:
	EventManager() {}
	~EventManager() {}

public:
	static void AddObserver(Observer* observer) { mObservers.push_back(observer); }
	static void RemoveObserver(Observer* observer)
	{
		for (auto i = mObservers.begin(); i != mObservers.end(); i++)
		{
			if (*i == observer)
			{
				mObservers.erase(i);
			}
		}
	}
	static void ClearObservers() { mObservers.clear(); }

	static void NotifyObservers(const GameObject& gameObject, Event nEvent)
	{
		for (size_t i = 0; i < mObservers.size(); i++)
		{
			mObservers[i]->OnNotify(gameObject, nEvent);
		}
	}

};