#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Singleton.cpp"
#include "EventListener.hpp"

class EventManager : public Singleton<EventManager>
{
	friend class Singleton<EventManager>;

public:
	void captureEvent(sf::Window *w);
	void subscribe(EventListener *subscriber);

private:
	EventManager();

	void forward(const sf::Event &event);

	std::vector<EventListener*> *listeners;

};

#endif // EVENTMANAGER_H
