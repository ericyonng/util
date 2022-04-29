//
// Created by hujianzhe
//

#include "../../../inc/crt/math.h"
#include "../../../inc/crt/math_vec3.h"
#include "../../../inc/crt/geometry/aabb.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void mathPointProjectionPlane(const float p[3], const float plane_v[3], const float plane_n[3], float np[3], float* distance) {
	float pv[3], d;
	mathVec3Sub(pv, plane_v, p);
	d = mathVec3Dot(pv, plane_n);
	if (distance) {
		*distance = d;
	}
	if (np) {
		mathVec3AddScalar(mathVec3Copy(np, p), plane_n, d);
	}
}

void mathPlaneNormalByVertices3(const float vertices[3][3], float normal[3]) {
	float v0v1[3], v0v2[3];
	mathVec3Sub(v0v1, vertices[1], vertices[0]);
	mathVec3Sub(v0v2, vertices[2], vertices[0]);
	mathVec3Cross(normal, v0v1, v0v2);
	mathVec3Normalized(normal, normal);
}

int mathPlaneHasPoint(const float plane_v[3], const float plane_normal[3], const float p[3]) {
	float v[3];
	mathVec3Sub(v, plane_v, p);
	return fcmpf(mathVec3Dot(plane_normal, v), 0.0f, CCT_EPSILON) == 0;
}

int mathPlaneIntersectPlane(const float v1[3], const float n1[3], const float v2[3], const float n2[3]) {
	float n[3];
	mathVec3Cross(n, n1, n2);
	if (!mathVec3IsZero(n)) {
		return 1;
	}
	return mathPlaneHasPoint(v1, n1, v2);
}

int mathRectHasPoint(const float center_o[3], const float axis[3], const float plane_normal[3], float half_w, float half_h, const float p[3]) {
	float v[3], dot;
	mathVec3Sub(v, p, center_o);
	dot = mathVec3Dot(plane_normal, v);
	if (fcmpf(dot, 0.0f, CCT_EPSILON)) {
		return 0;
	}
	dot = mathVec3Dot(axis, v);
	if (dot > half_h + CCT_EPSILON || dot < -half_h - CCT_EPSILON) {
		return 0;
	}
	return mathVec3LenSq(v) - dot * dot <= half_w * half_w + CCT_EPSILON;
}

#ifdef __cplusplus
}
#endif
