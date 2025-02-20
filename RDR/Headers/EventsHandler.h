#pragma once



using EventHandler = std::function<void()>;



enum Event
{
	Event_OnInitialize,
	Event_OnRender,
	Event_OnReset,
	Event_OnShutdown
};



class EventsHandler
{
	public:
		EventsHandler() = default;
		~EventsHandler()
		{
			m_Events.clear();
		}

		void RegisterEvent(Event _Event, const EventHandler& _Handler)
		{
			m_Events.insert_or_assign(_Event, _Handler);
		}

		void ExecuteEvent(Event _Event)
		{
			if (!m_Events.contains(_Event))
				return;
			
			const auto& handler = m_Events.at(_Event);

			if (handler)
				handler();
		}

	private:
		std::unordered_map<Event, EventHandler> m_Events;
};