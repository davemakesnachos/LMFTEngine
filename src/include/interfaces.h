#ifndef _INTERFACES_H_
#define _INTERFACES_H_

#include <memory>
#include <string>

class IEventData
{
public:
	virtual const unsigned long & getType(void) const = 0;
	virtual std::shared_ptr<IEventData> copy(void) const = 0;
	virtual const char* getName(void) const = 0;
};

class ISystem {
public:
	virtual void onUpdate(double dt) = 0;
	virtual std::string getName(void) = 0;
};

#endif /* _INTERFACES_H_ */