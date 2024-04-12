#pragma once

#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel {

	class HAZEL_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}  // when pushed onto the layer stack  (init)
		virtual void OnDetach() {}  // when removed from the layer stack  (shutdown)
		virtual void OnUpdate() {}  // when the layer is updated (every frame)
		virtual void OnEvent(Event& event) {}  // when event is sent to the layer

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}