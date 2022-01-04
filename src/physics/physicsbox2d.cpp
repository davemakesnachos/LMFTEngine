#include <box2d/box2d.h>
#include <memory>

#include <entity.h>
#include <logger.h>
#include <physics/physicsbox2d.h>

#define BOX2D_FIXED_TIMESTEP		(1.0f / 60.0f)

void Box2dPhysicsSystem::init(PhysicsSystemData& data)
{
	// Define the gravity vector, this will need to come from data.
	b2Vec2 gravity(data.gravityX, data.gravityY);
	m_timestepAccumulator = 0;
	m_b2World = new b2World(gravity);
}

void Box2dPhysicsSystem::addBody(std::shared_ptr<Entity> entity, json data)
{
	b2BodyDef bodyDef;

	json shapeData = data.at("shape");
	int vertCount = shapeData.at("num_verts");

	DEBUG("vert count " << vertCount);

	if (vertCount < 3) {
		ERROR("Invalid vertCount for physics body.");
		return;
	}

	b2Vec2 *vertices = new b2Vec2[vertCount];
	for (int vertIndex = 0; vertIndex < vertCount; vertIndex++) {
		json verts = shapeData.at("verts");
		float x = verts.at(vertIndex).at("x");
		float y = verts.at(vertIndex).at("y");

		vertices[vertIndex].Set(x, y);
		DEBUG("x["<<vertIndex<<"] = " << x << "    y["<<vertIndex<<"] = " << y );
	}

	b2PolygonShape* poly = new b2PolygonShape;

	poly->Set(vertices, vertCount);

	b2FixtureDef *f = new b2FixtureDef;
	f->shape = poly;

	f->density = 50;
	f->restitution = 1.0;

	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(entity.get());

	addBody(entity, bodyDef);
}

void Box2dPhysicsSystem::addBody(std::shared_ptr<Entity> entity, b2BodyDef& bodyDef)
{
	b2Body* b = m_b2World->CreateBody(&bodyDef);
}

void Box2dPhysicsSystem::onUpdate(double dt)
{
	// Borrow these from Box2d folks
	int velocityIterations = 6;
	int positionIterations = 2;

	/* Use timestep Accumulator to keep as close to constant 60 fps as possible */
	m_timestepAccumulator += dt;

	while ( m_timestepAccumulator >= BOX2D_FIXED_TIMESTEP )
	{
		m_b2World->Step(dt, velocityIterations, positionIterations);
		m_timestepAccumulator -= dt;
	}
}

std::shared_ptr<PhysicsSystem> createPhysicsSystem(void)
{
	return std::shared_ptr<Box2dPhysicsSystem>(new Box2dPhysicsSystem);
}