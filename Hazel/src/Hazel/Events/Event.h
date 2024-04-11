#pragma once

#include "hzpch.h"
#include "Hazel/Core.h"

namespace Hazel {

	// Events in Hazel are blocking, meaning when an event occurs it has to be dealt with immediately

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory  // bit field because an event could be in multiple categories
	{
		None = 0,
		EventCategoryApplication = BIT(0), 
		EventCategoryInput       = BIT(1), 
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	// This simplies declaring the event type in the class, instead just making it a simple define
	#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
									virtual EventType GetEventType() const override { return GetStaticType(); }\
									virtual const char* GetName() const override { return "KeyPressed"; }

	// same as above but just for category
	#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class HAZEL_API Event
	{
		friend class EventDispatcher;  // friend essentially says "hey man you can all my protected and private stuff yk"
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const   { return GetName(); }

		inline bool IsInCategory(EventCategory category)  // inline essentially replaces the function call with the actual code inside the function.
		{
			return GetCategoryFlags() & category;
		}
	protected:  // only difference from private is that protected values can be accessed by subclasses
		bool m_Handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}