#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

namespace Interface {
	class EventHandler {
	public:
		EventHandler();

		void Poll();
		void Dispatch();
	};
}

#endif // EVENT_HANDLER_HPP
