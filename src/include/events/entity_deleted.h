#ifndef _EVENTS_ENTITY_DELETED_
#define _EVENTS_ENTITY_DELETED_

#include <memory>

#include <eventmanager.h>

class EventData_EntityDeleted : public EventData
{
public:
	static const unsigned long _eventType;

	EventData_EntityDeleted(void)
	{
		_entityId = 0;
	}

    explicit EventData_EntityDeleted(unsigned long entityId)
        : _entityId(entityId)
	{
	}

	virtual const unsigned long & getType(void) const
	{
		return _eventType;
	}

	virtual std::shared_ptr<IEventData> copy(void) const
	{
		return std::shared_ptr<IEventData> (new EventData_EntityDeleted(_entityId));
	}

    virtual const char* getName(void) const
    {
        return "EventData_EntityDeleted";
    }

	const unsigned long getEntityId(void) const
	{
		return _entityId;
	}

private:
	unsigned long _entityId;
};
#endif /* _EVENTS_ENTITY_DELETED_ */