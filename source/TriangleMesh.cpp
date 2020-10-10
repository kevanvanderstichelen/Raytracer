#include "pch.h"
#include "TriangleMesh.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>

TriangleMesh::TriangleMesh(const std::vector<FVector3*>& vertexBuffer, const std::vector<Triplet*>& idBuffer, const std::vector<FVector3*>& normBuffer, const Material* material)
	:Object{ material }
	,m_pVertexBuffer{ vertexBuffer }
	,m_pIdBuffer{ idBuffer }
    ,m_pNormBuffer{ normBuffer }
{
}

TriangleMesh::~TriangleMesh()
{
	for (FVector3* vec3 : m_pVertexBuffer)
	{
		delete vec3;
		vec3 = nullptr;
	}
	m_pVertexBuffer.clear();

	for (Triplet* tri : m_pIdBuffer)
	{
		delete tri;
		tri = nullptr;
	}
	m_pIdBuffer.clear();

	for (FVector3* norm : m_pNormBuffer)
	{
		delete norm;
		norm = nullptr;
	}
	m_pNormBuffer.clear();


}

bool TriangleMesh::Hit(const Ray& ray, HitRecord& hitrecord) const
{
	bool hit{ false };
	HitRecord hitrecordTemp;
	hitrecordTemp.tValue = FLT_MAX;

	for (size_t i{}; i < m_pIdBuffer.size(); ++i)
	{
		const FVector3 v0 = *(m_pVertexBuffer[m_pIdBuffer[i]->one]);
		const FVector3 v1 = *(m_pVertexBuffer[m_pIdBuffer[i]->two]);
		const FVector3 v2 = *(m_pVertexBuffer[m_pIdBuffer[i]->three]);

		const FVector3 N = *(m_pNormBuffer[i]);
		const FVector3 C = (v0 + v1 + v2) / 3.f;
		if (Dot(ray.direction, N) == 0.f) continue;
		const FVector3 L = C - FVector3(ray.origin);
		const float t = Dot(L, N) / Dot(ray.direction, N);
		if (t < ray.tMin || t > ray.tMax) continue;

		const FPoint3 p = ray.origin + t * ray.direction;

		FVector3 edge = v1 - v0;
		FVector3 pointToSide = FVector3(p) - v0;
		if (Dot(N, Cross(edge, pointToSide)) < 0.f) continue;

		edge = v2 - v1;
		pointToSide = FVector3(p) - v1;
		if (Dot(N, Cross(edge, pointToSide)) < 0.f) continue;

		edge = v0 - v2;
		pointToSide = FVector3(p) - v2;
		if (Dot(N, Cross(edge, pointToSide)) < 0.f) continue;

		if (t > hitrecordTemp.tValue) continue;

		hitrecordTemp.hitPoint = p;
		hitrecordTemp.material = m_Material;
		hitrecordTemp.tValue = t;
		hitrecordTemp.normal = N;
		
		hitrecord = hitrecordTemp;

		hit = true;
	}

	return hit;
}

void TriangleMesh::Update(float elapsedSec)
{
}

TriangleMesh* TriangleMesh::LoadFromFile(const std::string& fileName, const FVector3& position, const Material* material)
{
	std::ifstream file{ fileName };
	std::vector<FVector3*> pVertexBuffer;
	std::vector<Triplet*> pIndexBuffer;

	std::regex regex_V("^v\\s*(\\-?\\d*\\.\\d*) (\\-?\\d*\\.?\\d*) (\\-?\\d*\\.?\\d*)");
	std::regex regex_F("^f\\s(\\d*)\\s(\\d*)\\s(\\d*)\\s*");
	std::smatch match;

	if (!file.eof())
	{
		std::string line;

		while (std::getline(file, line))
		{
			if (line.empty()) continue;

			if (regex_match(line, regex_V))
			{
				if (regex_search(line, match, regex_V))
				{
					pVertexBuffer.push_back(new FVector3{ std::stof(match[1].str()) + position.x, std::stof(match[2].str()) + position.y, std::stof(match[3].str()) + position.z });
				}
			}

			if (regex_match(line, regex_F))
			{
				if (regex_search(line, match, regex_F))
				{
					pIndexBuffer.push_back(new Triplet{ unsigned(std::stoi(match[1].str()) - 1), unsigned(std::stoi(match[2].str()) - 1) , unsigned(std::stoi(match[3].str()) - 1) });
				}
			}

		}
	}

	return new TriangleMesh(pVertexBuffer, pIndexBuffer, PreComputeNormals(pVertexBuffer, pIndexBuffer), material);
}

const std::vector<FVector3*> TriangleMesh::PreComputeNormals(const std::vector<FVector3*>& vertexBuffer, const std::vector<Triplet*>& idBuffer)
{
	std::vector<FVector3*> normals;
	for (size_t i{}; i < idBuffer.size(); ++i)
	{
		const FVector3 v0 = *(vertexBuffer[idBuffer[i]->one]);
		const FVector3 v1 = *(vertexBuffer[idBuffer[i]->two]);
		const FVector3 v2 = *(vertexBuffer[idBuffer[i]->three]);
		normals.push_back(new FVector3(GetNormalized(Cross(v0 - v1, v0 - v2))));
	}
	return normals;
}
