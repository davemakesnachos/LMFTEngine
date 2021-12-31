#ifndef _INTERFACES_H_
#define _INTERFACES_H_

#include <memory>

class IEventData
{
public:
	virtual const unsigned long & getType(void) const = 0;
	virtual std::shared_ptr<IEventData> copy(void) const = 0;
	virtual const char* getName(void) const = 0;
};

#endif /* _INTERFACES_H_ */