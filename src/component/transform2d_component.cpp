
#include <logger.h>

#include <component/transform2d_component.h>

const char *Transform2dComponent::_name = "Transform2d";

int Transform2dComponent::init(json data)
{
    DEBUG("Init "<< _name);

    return 0;
}

void Transform2dComponent::postInit(void)
{

}

void Transform2dComponent::update(double dt)
{

}

const char * Transform2dComponent::getComponentName(void) const
{
    return _name;
}