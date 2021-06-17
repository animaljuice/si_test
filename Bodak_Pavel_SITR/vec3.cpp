#include "vec3.h"
#include <iostream>

void calc_mesh_normals(vec3* normals, const vec3* verts, const int* faces, int nverts, int nfaces)
{
	for (size_t faceIndex = 0; faceIndex < nfaces; faceIndex++)
	{
		auto baseIndex = faceIndex * 3;
		auto vx = verts[faces[baseIndex + 2]] - verts[faces[baseIndex]];
		auto vy = verts[faces[baseIndex + 1]] - verts[faces[baseIndex]];

		auto vz = vec3::crossProduct(vx, vy);
		vz.normalize();

		normals[faces[baseIndex]] += vz;
		normals[faces[baseIndex + 1]] += vz;
		normals[faces[baseIndex + 2]] += vz;
	}

	for (size_t vertIndex = 0; vertIndex < nverts; vertIndex++)
	{
		normals[vertIndex].normalize();
	}
}
