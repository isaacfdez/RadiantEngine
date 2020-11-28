#pragma once
#include "Module.h"
#include "Mesh.h"
#include <assimp/material.h>

class ModuleModels : public Module {

public:
	void Load(const char* modelPath, const char* vertexShaderPath, const char* fragmentShaderPath);
	void LoadMeshes(aiMesh** const mMeshes, unsigned int mNumMeshes, unsigned int program);
	void Draw();
	void LoadTextures(aiMaterial** const mMaterials, unsigned int mNumMaterials);

	unsigned int GetNumVertices();
	bool CleanUp() override;

private:
	std::vector<Mesh> meshes;
	std::vector<unsigned int> textures;
};


