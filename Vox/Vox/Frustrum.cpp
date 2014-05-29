#include "Frustrum.hpp"

#include <cmath>
#include <iostream>

#define TO_RADIANS			3.14159f / 180.0f

Frustrum::Frustrum()
{
}

Frustrum::~Frustrum()
{
}


void Frustrum::setCamInternals(float _fov, float _aspectRatio, float _near, float _far)
{
	m_Fov = _fov;
	m_AspectRatio = _aspectRatio;
	m_Near = _near;
	m_Far = _far;
}
void Frustrum::setCamDef(glm::vec3 _eye, glm::vec3 _view, glm::vec3 _up)
{
	float hnear = 2.0f * tanf(m_Fov / 2.0f * TO_RADIANS) * m_Near;
	float wnear = hnear * m_AspectRatio;
	
	float hfar = 2.0f * tanf(m_Fov / 2.0f * TO_RADIANS) * m_Far;
	float wfar = hfar * m_AspectRatio;

	glm::vec3 right = glm::cross(_view, _up);

	glm::vec3 fc = _eye + _view * m_Far;
	glm::vec3 nc = _eye + _view * m_Near;

	glm::vec3 ntl = nc + (_up * hnear / 2.0f) - (right * wnear / 2.0f);
	glm::vec3 ntr = nc + (_up * hnear / 2.0f) + (right * wnear / 2.0f);
	glm::vec3 nbl = nc - (_up * hnear / 2.0f) - (right * wnear / 2.0f);
	glm::vec3 nbr = nc - (_up * hnear / 2.0f) + (right * wnear / 2.0f);

	glm::vec3 ftl = fc + (_up * hfar / 2.0f) - (right * wfar / 2.0f);
	glm::vec3 ftr = fc + (_up * hfar / 2.0f) + (right * wfar / 2.0f);
	glm::vec3 fbl = fc - (_up * hfar / 2.0f) - (right * wfar / 2.0f);
	glm::vec3 fbr = fc - (_up * hfar / 2.0f) + (right * wfar / 2.0f);


	m_Planes[NEAR_P  ].setPoints(ntr, nbr, nbl);
	m_Planes[FAR_P   ].setPoints(ftl, fbl, fbr);
	m_Planes[RIGHT_P ].setPoints(ftr, fbr, nbr);
	m_Planes[LEFT_P  ].setPoints(ntl, nbl, fbl);
	m_Planes[TOP_P   ].setPoints(ftl, ftr, ntr);
	m_Planes[BOTTOM_P].setPoints(fbr, fbl, nbl);
}

int Frustrum::pointInFrustum(glm::vec3 _pos)
{
	int result = INSIDE;

	for(int i=0; i < 6; i += 1) 
	{
		if (m_Planes[i].getDistance(_pos) < 0)
		{
			return OUTSIDE;
		}
	}

	return result;
}
int Frustrum::sphereInFrustum(glm::vec3 _center, float _radius)
{
	float distance;
	int result = INSIDE;

	for(int i=0; i < 6; i += 1) 
	{
		distance = m_Planes[i].getDistance(_center);
		if (distance < -_radius)
		{
			return OUTSIDE;
		}
		else if (distance < _radius)
		{
			result = INTERSECT;
		}
	}

	return result;
}
int Frustrum::boxInFrustum(glm::vec3 _center, glm::vec3 _size)
{
	int result = INSIDE;

	for (int i = 0; i < 6; i += 1)
	{
		glm::vec3 normal = m_Planes[i].getNormal();

		float x = normal.x >= 0.0f ? _center.x + _size.x / 2.0f : _center.x - _size.x / 2.0f;
		float y = normal.y >= 0.0f ? _center.y + _size.y / 2.0f : _center.y - _size.y / 2.0f;
		float z = normal.z >= 0.0f ? _center.z + _size.z / 2.0f : _center.z - _size.z / 2.0f;

		glm::vec3 p(x, y, z);

		if (m_Planes[i].getDistance(p) < 0)
		{
			return OUTSIDE;
		}


		x = normal.x >= 0.0f ? _center.x - _size.x / 2.0f : _center.x + _size.x / 2.0f;
		y = normal.y >= 0.0f ? _center.y - _size.y / 2.0f : _center.y + _size.y / 2.0f;
		z = normal.z >= 0.0f ? _center.z - _size.z / 2.0f : _center.z + _size.z / 2.0f;

		glm::vec3 n(x, y, z);

		if (m_Planes[i].getDistance(n) < 0)
		{
			result = INTERSECT;
		}
	}

	return result;
}