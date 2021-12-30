#include <cassert>
#include <memory>

#include <error.h>
#include <eventmanager.h>
#include <logger.h>

#include <events/entity_create.h>

EventManager *EventManager::m_instance = nullptr;

int compareEvents(EventListener handler1, EventListener handler2) {
    typedef void(fnType)(std::shared_ptr<IEventData>);
    fnType ** fnPointer1 = handler1.template target<fnType*>();
    fnType ** fnPointer2 = handler2.template target<fnType*>();
    if (fnPointer1 == fnPointer2) return 0;
    else return -1;
}

EventManager *EventManager::create(void)
{
    if (m_instance) {
        ERROR("Attempting to create second event manager!");
        return nullptr;
    } else {
        m_instance = new EventManager;
    }
    return m_instance;
}

EventManager *EventManager::get(void)
{
    return m_instance;
}

EventManager::EventManager()
{
}

EventManager::~EventManager(void)
{
}

int EventManager::addListener (const EventListener& eventListener, const unsigned long & type)
{
    DEBUG("Registering listener for " << std::hex << type);

    std::list<EventListener > & eventListenerList = m_eventListeners[type];  // this will find or create the entry
    for (auto it = eventListenerList.begin(); it != eventListenerList.end(); ++it)
    {
        if (compareEvents(eventListener, *it) != 0)
        {
            WARN("Listener " << std::hex << type << "has been added already, this is duplicate.");
            return -1;
        }
    }

    eventListenerList.push_back(eventListener);
    INFO("Successfully registered listener for " << std::hex << type);

    return 0;
}

int EventManager::removeListener(const EventListener& eventListener, const unsigned long & type)
{
    DEBUG("Removing listener for event type " << std::hex << type);
	int ret = -ERR_ENOENT;

    auto findIt = m_eventListeners.find(type);
    if (findIt != m_eventListeners.end())
    {
        std::list<EventListener> & listeners = findIt->second;
        for (auto it = listeners.begin(); it != listeners.end(); ++it)
        {
            if (compareEvents(eventListener, *it) != 0)
            {
                listeners.erase(it);
                INFO("Successfully removed listener from event type " << std::hex << type);
                ret = 0;
                break;
            }
        }
    }

    return ret;
}

int EventManager::triggerEvent(const std::shared_ptr<IEventData>& event) const
{
    DEBUG("Attempting to trigger event " << std::string(event->getName()));
    bool processed = false;

    auto findIt = m_eventListeners.find(event->getType());
	if (findIt != m_eventListeners.end())
    {
	    const std::list<EventListener>& eventListenerList = findIt->second;
	    for (std::list<EventListener>::const_iterator it = eventListenerList.begin(); it != eventListenerList.end(); ++it)
	    {
		    EventListener listener = (*it);
            DEBUG("Sending Event " + std::string(event->getName()) + " to listener.");
		    listener(event);
            processed = true;
	    }
    }

    if (processed) return 0;

    return -ERR_ENOENT;
}

int EventManager::queueEvent(const std::shared_ptr<IEventData>& event)
{
    if (!event)
    {
        ERROR("Empty event cannot be queued.");
        return -ERR_EINVAL;
    }

    DEBUG("Attempting to queue event " << std::string(event->getName()));

	auto findIt = m_eventListeners.find(event->getType());
    if (findIt != m_eventListeners.end())
    {
        m_queues[m_activeQueue].push_back(event);
        INFO("Successfully queued event " << std::string(event->getName()));
        return 0;
    }
    else
    {
        INFO("Skipping event " << std::string(event->getName()) << "since there are no listeners registered to receive it.");
        return -ERR_ENOENT;
    }
}

int EventManager::abortEvent(const unsigned int& type, int allOfType)
{
    int ret = -ERR_ENOENT;
	auto findIt = m_eventListeners.find(type);

	if (findIt != m_eventListeners.end())
    {
        std::list<std::shared_ptr<IEventData> > & eventQueue = m_queues[m_activeQueue];
        auto it = eventQueue.begin();
        while (it != eventQueue.end())
        {
            auto thisIt = it;
            ++it;

	        if ((*thisIt)->getType() == type)
	        {
		        eventQueue.erase(thisIt);
		        ret = 0;
		        if (!allOfType)
			        break;
	        }
        }
    }

	return ret;
}

int EventManager::onUpdate(unsigned long max_dt)
{
    unsigned long start_ms = Timer::timestamp();
	unsigned long end_ms = ((max_dt == 0) ? INT64_MAX : (start_ms + max_dt));

	/*
     * Swap active queues. This is done to allow events to be processed, which may cause additional
     * events to be queued, without needing to worry about queue in use being changed.
     */
    int queueToProcess = m_activeQueue;
	m_activeQueue = (m_activeQueue + 1) % EVENTMANAGER_QUEUE_COUNT;
	m_queues[m_activeQueue].clear();

    DEBUG("Processing Event Queue " << queueToProcess << " with " << m_queues[queueToProcess].size() << " events to process");

	while (!m_queues[queueToProcess].empty())
	{
		std::shared_ptr<IEventData> event = m_queues[queueToProcess].front();
        m_queues[queueToProcess].pop_front();
        DEBUG("Processing Event " << std::string(event->getName()));

		const unsigned long & eventType = event->getType();

        // find all the delegate functions registered for this event
		auto findIt = m_eventListeners.find(eventType);
		if (findIt != m_eventListeners.end())
		{
			const std::list<EventListener> & eventListeners = findIt->second;

			for (auto it = eventListeners.begin(); it != eventListeners.end(); ++it)
			{
                EventListener listener = (*it);
                DEBUG("Sending event " << std::string(event->getName()) << " to delegate");
				listener(event);
			}
		}

        // Check to see if time ran out
		start_ms = Timer::timestamp();
		if (max_dt != 0 && start_ms >= end_ms)
        {
            INFO("Event queue did not complete processing in this interation, " << m_queues[queueToProcess].size() << " remain.");
			break;
        }
	}

    /*
     * Move events to other queue if we ran out of time...
     */
	bool queueFlushed = (m_queues[queueToProcess].empty());
	if (!m_queues[queueToProcess].empty())
	{
		while (!m_queues[queueToProcess].empty())
		{
			std::shared_ptr<IEventData> event = m_queues[queueToProcess].back();
			m_queues[queueToProcess].pop_back();
			m_queues[m_activeQueue].push_front(event);
		}
	}

    return 0;
}

const unsigned long EventData_EntityCreate::_eventType(0x12020712);