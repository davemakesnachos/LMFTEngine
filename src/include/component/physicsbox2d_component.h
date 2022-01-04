#include <box2d/box2d.h>

#include <component.h>
#include <types.h>

class PhysicsBox2dComponent : public EntityComponent {
public:

    virtual int init(json data);
    virtual void postInit(void);
    virtual void update(double dt);

    virtual const char * getComponentName(void) const;

    const static char *_name;

	Vec2 getPosition(void);
	void setPosition(Vec2 pos);

	float getRotation(void);
	void setRotation(float angle);

	Vec2 getVelocity(void);
    void setVelocity(Vec2 vel);

	void applyForce(Vec2 force);
	void applyLinearImpulse(Vec2 impulse);

	void applyTorque(float torque);
	void applyAngularImpulse(float impulse);
	void stopRotation(void);

	b2Body *m_b2Body;
};
