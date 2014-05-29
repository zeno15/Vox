#ifndef INCLUDED_FRUSTRUM_HPP
#define INCLUDED_FRUSTRUM_HPP

#include <glm/glm.hpp>
#include <vector>

#include "Plane.hpp"

class Frustrum
{
private:
	enum {
		NEAR_P = 0,
		FAR_P,
		RIGHT_P,
		LEFT_P,
		TOP_P,
		BOTTOM_P
	};
public:
	static enum {OUTSIDE, INTERSECT, INSIDE};

	Frustrum();
	~Frustrum();

	void setCamInternals(float _fov, float _aspectRatio, float _near, float _far);
	void setCamDef(glm::vec3 _eye, glm::vec3 _view, glm::vec3 _up);

	int pointInFrustum(glm::vec3 _pos);
	int sphereInFrustum(glm::vec3 _center, float _radius);
	int boxInFrustum(glm::vec3 _center, glm::vec3 _size);

private:
	Plane								m_Planes[6];

	float								m_Fov;
	float								m_AspectRatio;
	float								m_Near;
	float								m_Far;
};

#endif //~ INCLUDED_FRUSTRUM_HPP