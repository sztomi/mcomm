#include "../system.h"

namespace mcomm
{

class CollidingSystem : public System
{
public:
	std::string toString() const;
	void update(float dt);
};

}
