#include <logger.h>

#include <component/physicsbox2d_component.h>
#include <game.h>
#include <gamelogic.h>
#include <physics/physicsbox2d.h>

const char *PhysicsBox2dComponent::_name = "PhysicsBox2d";

std::shared_ptr<PhysicsSystem> getPhysics(void);

int PhysicsBox2dComponent::init(json data)
{
    DEBUG("Init "<< _name);

    std::shared_ptr<PhysicsSystem> p = g_game->m_gameLogic->getPhysics();

    p->addBody(m_owner, data.at("fixture"));

    return 0;
}

void PhysicsBox2dComponent::postInit(void)
{

}

void PhysicsBox2dComponent::update(double dt)
{

}

const char * PhysicsBox2dComponent::getComponentName(void) const
{
    return _name;
}

Vec2 PhysicsBox2dComponent::getPosition(void)
{
	return Vec2(m_b2Body->GetPosition().x, m_b2Body->GetPosition().y);
}

void PhysicsBox2dComponent::setPosition(Vec2 pos)
{
	m_b2Body->SetTransform(b2Vec2(pos.x, pos.y), m_b2Body->GetAngle());
}

float PhysicsBox2dComponent::getRotation(void)
{
	return RAD2DEG(m_b2Body->GetAngle());
}

void PhysicsBox2dComponent::setRotation(float angle)
{
	m_b2Body->SetTransform(m_b2Body->GetPosition(), DEG2RAD(angle));
}

Vec2 PhysicsBox2dComponent::getVelocity(void)
{
	b2Vec2 b = m_b2Body->GetLinearVelocity();
	return Vec2(b.x, b.y);
}

void PhysicsBox2dComponent::setVelocity(Vec2 vel)
{
	m_b2Body->SetLinearVelocity(b2Vec2(vel.x, vel.y));
}

void PhysicsBox2dComponent::applyForce(Vec2 force)
{
	m_b2Body->ApplyForceToCenter(b2Vec2(force.x, force.y), true);
}

void PhysicsBox2dComponent::applyLinearImpulse(Vec2 impulse)
{
	m_b2Body->ApplyLinearImpulse(b2Vec2(impulse.x, impulse.y), m_b2Body->GetPosition(), true);
}

void PhysicsBox2dComponent::applyTorque(float torque)
{
	m_b2Body->ApplyTorque(torque, true);
}

void PhysicsBox2dComponent::applyAngularImpulse(float impulse)
{
	m_b2Body->ApplyAngularImpulse(impulse, true);
}

void PhysicsBox2dComponent::stopRotation()
{
	m_b2Body->SetAngularVelocity(0);
}
