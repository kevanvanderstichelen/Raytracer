#pragma once
#include "Object.h"
#include <unordered_set>

class TriangleMesh : public Object
{
public:
	// CONSTRUCTOR - DESTRUCTOR
	TriangleMesh(const std::vector<FVector3*>& vertexBuffer, const std::vector<Triplet*>& idBuffer, const std::vector<FVector3*>& normBuffer, const Material* material);
	TriangleMesh(const TriangleMesh& rhs) = delete;
	TriangleMesh(TriangleMesh&& other) = delete;
	TriangleMesh& operator=(const TriangleMesh& rhs) = delete;
	TriangleMesh& operator=(const TriangleMesh&& other) = delete;
	~TriangleMesh();

	//FUNCTIONS
	virtual bool Hit(const Ray& ray, HitRecord& hitrecord) const override;
	virtual void Update(float elapsedSec) override;
	static TriangleMesh* LoadFromFile(const std::string& fileName, const FVector3& position, const Material* material);

private:
	//VARIABLES
	std::vector<FVector3*> m_pVertexBuffer;
    std::vector<Triplet*> m_pIdBuffer;
	std::vector<FVector3*> m_pNormBuffer;

	//FUNCTIONS
	static const std::vector<FVector3*> PreComputeNormals(const std::vector<FVector3*>& vertexBuffer, const std::vector<Triplet*>& idBuffer);
};

