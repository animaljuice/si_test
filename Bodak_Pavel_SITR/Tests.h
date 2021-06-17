#pragma once

#include "List.h"
#include "IntToBinStr.h"
#include "vec3.h"

#include <stdint.h>
#include <iostream>

void intToBinStrTests()
{
	IntToBinStr(123456);
	IntToBinStr(-1);
	IntToBinStr(0);
	IntToBinStr(INT32_MAX);
	IntToBinStr(INT32_MIN);
	IntToBinStr(-623848);
	IntToBinStr(256);
	IntToBinStr(-513);
}

void serializationTest()
{
	FILE* f;
	std::vector<std::vector<std::string>> initData = { { "возмите", "меня", "к", "себе", "работать", ")" } ,
		{},
		{ "адин", "два", "три", "читыри" },
		{ "/0/n", "qwe123$%^@#()///..." }
	};

	// компилятор ругается на fopen, по этому работаю с *_s версией функции
	for (size_t initDataIndex = 0; initDataIndex < initData.size(); initDataIndex++)
	{
		List outList(initData[initDataIndex]);

		char strInt[3];
		_itoa_s(initDataIndex, strInt, 10);
		std::string fileName(strInt);
		fileName += ".bin";
		fopen_s(&f, fileName.data(), "wb");
		outList.Serialize(f);
		fclose(f);

		List inList;
		fopen_s(&f, fileName.data(), "rb");
		inList.Deserialize(f);
		fclose(f);
	}
}

void averageNormalTest()
{
	struct Mesh
	{
		struct Face
		{
			int v0, v1, v2;
		};

		std::vector<vec3> m_vertices;
		std::vector<vec3> m_normals;
		std::vector<Face> m_faces;

		Mesh(int vertCount)
		{
			m_vertices.resize(vertCount);
			m_normals.resize(vertCount);
		}

		Mesh() {}
	};

	Mesh m1(5);
	m1.m_vertices[0] = { 0., 0., 0.01 };
	m1.m_vertices[1] = { 1., 1., 0. };
	m1.m_vertices[2] = { 1., -1., 0. };
	m1.m_vertices[3] = { -1., -1., 0. };
	m1.m_vertices[4] = { -1., 1., 0. };

	m1.m_faces.push_back({ 0, 4, 1 });
	m1.m_faces.push_back({ 0, 1, 2 });
	m1.m_faces.push_back({ 0, 2, 3 });
	m1.m_faces.push_back({ 0, 3, 4 });
	
	m1.m_vertices[0];
	calc_mesh_normals(m1.m_normals.data(),
		m1.m_vertices.data(), 
		reinterpret_cast<int*>(m1.m_faces.data()),
		m1.m_vertices.size(),
		m1.m_faces.size());
}