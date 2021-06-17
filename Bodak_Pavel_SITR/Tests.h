#pragma once

#include "List.h"
#include "PrintBinStr.h"
#include "vec3.h"

#include <stdint.h>
#include <iostream>

void intToBinStrTests()
{
	std::vector<int> testNumbers = { 123456, -1, 0, INT32_MAX, INT32_MIN, -623848, 256, -513 };

	for (size_t numberIndex = 0; numberIndex < testNumbers.size(); numberIndex++)
	{
		std::cout << testNumbers[numberIndex] << " ";
		PrintBinStr(testNumbers[numberIndex]);
		std::cout << std::endl;
	}
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
		std::cout << "/////////////////////////////" << std::endl << std::endl;
		List outList(initData[initDataIndex]);
		std::cout << "Serialize:" << std::endl;
		outList.print();
		std::cout << std::endl;

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

		std::cout << "Deserialize:" << std::endl;
		inList.print();
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

	std::cout << "вершины, нормали: " << std::endl;
	for (size_t vertIndex = 0; vertIndex < m1.m_vertices.size(); vertIndex++)
	{
		std::cout << "вершина: " << m1.m_vertices[vertIndex]._m_x << ' ' << m1.m_vertices[vertIndex]._m_y << ' ' << m1.m_vertices[vertIndex]._m_z << std::endl;
		std::cout << "нормаль: " << m1.m_normals[vertIndex]._m_x << ' ' << m1.m_normals[vertIndex]._m_y << ' ' << m1.m_normals[vertIndex]._m_z << std::endl;
		std::cout << std::endl;
	}

	std::cout << "фэйсы: " << std::endl;
	for (size_t faceIndex = 0; faceIndex < m1.m_faces.size(); faceIndex++)
	{
		std::cout << m1.m_faces[faceIndex].v0 << ' ' << m1.m_faces[faceIndex].v1 << ' ' << m1.m_faces[faceIndex].v2 << std::endl;
	}
}