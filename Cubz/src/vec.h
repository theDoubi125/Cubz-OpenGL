#ifndef VEC_INCLUDED
#define VEC_INCLUDED

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace glm;

#define IVEC_UP ivec3(0, 1, 0)
#define IVEC_DOWN ivec3(0, -1, 0)
#define IVEC_RIGHT ivec3(1, 0, 0)
#define IVEC_LEFT ivec3(-1, 0, 0)
#define IVEC_FORWARD ivec3(0, 0, 1)
#define IVEC_BACK ivec3(0, 0, -1)
#define IVEC_ZERO ivec3(0, 0, 0)


#define VEC_UP vec3(0, 1, 0)
#define VEC_DOWN vec3(0, -1, 0)
#define VEC_RIGHT vec3(1, 0, 0)
#define VEC_LEFT vec3(-1, 0, 0)
#define VEC_FORWARD vec3(0, 0, 1)
#define VEC_BACK vec3(0, 0, -1)
#define VEC_ZERO vec3(0, 0, 0)

#endif
