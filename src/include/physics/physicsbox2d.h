#ifndef _PHYSICS_BOX_2D_H_
#define _PHYSICS_BOX_2D_H_

#include <box2d/box2d.h>

#include <physicssystem.h>

struct PhysicsSystemData
{
	double gravityX;
	double gravityY;
};

class Box2dPhysicsSystem : public PhysicsSystem
{
public:
	virtual void init(PhysicsSystemData& data);
	virtual void onUpdate(double dt);
	virtual std::string getName(void) { return "physics_box2d"; };

	void addBody(std::shared_ptr<Entity> entity, json data);
	void addBody(std::shared_ptr<Entity> entity, b2BodyDef& body);

private:
	b2World *m_b2World;
	b2Body* dynamicBody;

	float m_timestepAccumulator;
};
#endif /* _PHYSICS_BOX_2D_H_ */