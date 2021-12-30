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
    return 0;
}

int EventManager::queueEvent(const std::shared_ptr<IEventData>& event)
{
    return 0;
}

int EventManager::abortEvent(const unsigned int& type, int allOfType)
{
    return 0;
}

int EventManager::onUpdate(unsigned long max_dt)
{
    return 0;
}

const unsigned long EventData_EntityCreate::_eventType(0x12020712);