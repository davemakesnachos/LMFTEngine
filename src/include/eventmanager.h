#ifndef _EVENTMANAGER_
#define _EVENTMANAGER_

#include <functional>
#include <istream>
#include <list>
#include <ostream>
#include <map>
#include <memory>

class IEventData;

#define EVENTMANAGER_QUEUE_COUNT        2

#define makeEventHandler(__method) EventListener(std::bind(&__method, this, std::placeholders::_1))

typedef std::function<void(std::shared_ptr<IEventData>)> EventListener;

class IEventData
{
public:
	virtual const unsigned long & getType(void) const = 0;
	virtual std::shared_ptr<IEventData> copy(void) const = 0;
	virtual const char* getName(void) const = 0;
};

class EventData : public IEventData
{
public:
	explicit EventData(const unsigned long timestamp = 0) : m_timestamp(timestamp) { }
	virtual ~EventData() { }

	virtual const unsigned long & getType(void) const = 0;

	float timestamp(void) const { return m_timestamp; }

	virtual std::shared_ptr<IEventData> copy(void) const = 0;
	virtual const char* getName(void) const = 0;

	const unsigned long m_timestamp;
};

class EventManager
{
public:
	explicit EventManager(void);
	virtual ~EventManager();

	virtual int addListener(const EventListener& eventDelegate, const unsigned long & type);
	virtual int removeListener(const EventListener& eventDelegate, const unsigned long & type);

	virtual int triggerEvent(const std::shared_ptr<IEventData>& event) const;
	virtual int queueEvent(const std::shared_ptr<IEventData>& event);
	virtual int abortEvent(const unsigned int& type, int allOfType = false);

	virtual int onUpdate(unsigned long max_dt = 0);

	static EventManager *create(void);
	static EventManager *get(void);

private:
	std::map<unsigned long, std::list<EventListener> > m_eventListeners;
	std::list<std::shared_ptr<IEventData> > m_queues[EVENTMANAGER_QUEUE_COUNT];
	int m_activeQueue;

	static EventManager *m_instance;
};

/*
 * We must manually compare std::function objects with this function, as the
 * C++11 standard does not provide any equivalency operation by default
 * due to many possiblities of ambiguity. This implementation is based
 * on https://stackoverflow.com/a/35920804
 */
int compareEvents(EventListener handler1, EventListener handler2);
#endif /* EVENTMANAGER */