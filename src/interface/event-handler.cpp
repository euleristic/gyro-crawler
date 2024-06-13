#include "event-handler.hpp"

#include "graphics-include.hpp"

namespace Interface {
	EventHandler::EventHandler() /* Set up state */ {}

	void EventHandler::Poll() {
		glfwPollEvents();
	}

	void EventHandler::Dispatch() {
		// Resolve events
	}
}
