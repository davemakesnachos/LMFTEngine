

class Vec2 { double x; double y; };

#include <component.h>

class Transform2dComponent : public EntityComponent {
public:

    virtual int init(json data);
    virtual void postInit(void);
    virtual void update(double dt);

    virtual const char * getComponentName(void) const;

    const static char *_name;
    const static unsigned int _id;

    Vec2 _pos;
    Vec2 _scale;
    double _angle;
};
