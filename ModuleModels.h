#pragma once
#include "Module.h"
#include "Mesh.h"
#include <assimp/material.h>

class ModuleModels : public Module {

public:
	void Load(const char* modelPath);
	void Draw();
	float4x4 GetModelMatrix() const;
	std::vector<Mesh> GetMeshes() const;
	std::vector<unsigned int> GetTextures() const;
	bool CleanUp() override;

private:
	void Load(const char* modelPath, const char* vertexShaderPath, const char* fragmentShaderPath);
	void LoadMeshes(aiMesh** const mMeshes, unsigned int mNumMeshes, unsigned int program);
	void LoadTextures(const char* modelPath, aiMaterial** const mMaterials, unsigned int mNumMaterials);
	unsigned int CreateProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
	
private:
	std::vector<Mesh> meshes;
	std::vector<unsigned int> textures;
	float4x4 modelMatrix = float4x4::zero;
	
};


