#pragma once

#include <map>
#include <list>
#include <memory>
#include <typeindex>

#include "Event.h"

class IEventCallback
{
private:
	virtual void Call(Event& e) = 0;

public:
	virtual ~IEventCallback() {}

	void Execute(Event& event)
	{
		Call(event);
	}
};

template <typename TOwner, typename TEvent>
class EventCallback : public IEventCallback
{
private:
	typedef void (TOwner::*CallbackFunction)(TEvent&);

	TOwner* ownerInstance;
	CallbackFunction callbackFunction;

private:
	virtual void Call(Event& event) override
	{
		std::invoke(callbackFunction, ownerInstance, static_cast<TEvent&>(event));
	}

public:
	EventCallback(TOwner* ownerInstance, CallbackFunction callbackFunction)
	{
		this->ownerInstance = ownerInstance;
		this->callbackFunction = callbackFunction;
	}

	virtual ~EventCallback() override {}
};

typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

class EventBus
{
private:
	std::map<std::type_index, std::unique_ptr<HandlerList>> mSubscribers;

public:
	EventBus() {}
	~EventBus() {}

	void Reset()
	{
		mSubscribers.clear();
	}

	template<typename TEvent, typename TOwner>
	void SubscribeToEvent(TOwner* ownerInstance, void (TOwner::*callbackFunction)(TEvent&))
	{
		if (!mSubscribers[typeid(TEvent)].get())
		{
			mSubscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
		}

		auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(ownerInstance, callbackFunction);
		mSubscribers[typeid(TEvent)]->push_back(std::move(subscriber));
	}

	template<typename TEvent, typename ...TArgs>
	void EmitEvent(TArgs&& ... args)
	{
		auto handlers = mSubscribers[typeid(TEvent)].get();
		if (handlers)
		{
			for (auto it = handlers->begin(); it != handlers->end(); it++)
			{
				auto handler = it->get();
				TEvent event(std::forward<TArgs>(args)...);
				handler->Execute(event);
			}
		}
	}
};