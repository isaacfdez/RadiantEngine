#include <assimp/mesh.h>
#include <vector>

class Mesh {

public:
	Mesh(unsigned int program);
	void LoadVBO(const aiMesh* mesh);
	void LoadEBO(const aiMesh* mesh);
	void CreateVAO();
	void Draw(const std::vector<unsigned>& textures);

	unsigned int numVertices = 0;
	unsigned int numIndices = 0;
	unsigned int materialIndex = 0;

	unsigned vao = 0;
	unsigned vbo = 0;
	unsigned ebo = 0;

private:
	unsigned int program = 0;
};
