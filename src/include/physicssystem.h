#ifndef _PHYSICSSYSTEM_H_
#define _PHYSICSSYSTEM_H_

#include <interfaces.h>

class Entity;
class PhysicsSystemData;

class PhysicsSystem : public ISystem
{
public:
	virtual void init(PhysicsSystemData& data) = 0;
	virtual void onUpdate(double dt) = 0;
	virtual void addBody(std::shared_ptr<Entity> entity, json data) = 0;

	virtual std::string getName(void) { return "physics"; };
};

std::shared_ptr<PhysicsSystem> createPhysicsSystem(void);

#endif /* _PHYSICSSYSTEM_H_ */