#ifndef _EVENTS_ENTITY_CREATE_
#define _EVENTS_ENTITY_CREATE_

#include <memory>

#include <eventmanager.h>

class EventData_EntityCreate : public EventData
{
public:
	static const unsigned long _eventType;

	EventData_EntityCreate(void)
	{
		_entityId = 0;
	}

    explicit EventData_EntityCreate(unsigned long entityId)
        : _entityId(entityId)
	{
	}

	virtual const unsigned long & getType(void) const
	{
		return _eventType;
	}

	virtual std::shared_ptr<IEventData> copy(void) const
	{
		return std::shared_ptr<IEventData> (new EventData_EntityCreate(_entityId));
	}

    virtual const char* getName(void) const
    {
        return "EventData_EntityCreate";
    }

	const unsigned long getEntityId(void) const
	{
		return _entityId;
	}

private:
	unsigned long _entityId;
};
#endif /* _EVENTS_ENTITY_CREATE_ */