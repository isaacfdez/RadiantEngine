#include <assimp/mesh.h>
#include <vector>
#include "Math/float4x4.h"

class Mesh {

public:
	Mesh(unsigned int program);
	void LoadVBO(const aiMesh* mesh);
	void LoadEBO(const aiMesh* mesh);
	void CreateVAO();
	void Draw(const std::vector<unsigned>& textures, const float4x4 modelMatrix);
	unsigned int GetIndices() const;
	unsigned int GetVertices() const;
	unsigned int GetTriangles() const;
	unsigned int GetFaces() const;

private:
	unsigned int numIndices = 0;
	unsigned int numVertices = 0;
	unsigned int numFaces = 0;
	unsigned int program = 0;
	unsigned int materialIndex = 0;
	unsigned vao = 0;
	unsigned vbo = 0;
	unsigned ebo = 0;
};
