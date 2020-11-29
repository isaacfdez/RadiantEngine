#include "ModuleModels.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleProgram.h"
#include <GL\glew.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

void ModuleModels::Load(const char* modelPath, const char* vertexShaderPath, const char* fragmentShaderPath) {
	unsigned int program = CreateProgram(vertexShaderPath, fragmentShaderPath);
	
	const aiScene* scene = aiImportFile(modelPath, aiProcessPreset_TargetRealtime_MaxQuality);
	if (program && scene) {

		if (!textures.empty()) {
			textures.clear();
		}
		LoadTextures(modelPath, scene->mMaterials, scene->mNumMaterials);

		if (!meshes.empty()) {
			meshes.clear();
		}
		LoadMeshes(scene->mMeshes, scene->mNumMeshes, program);
	}
	else {
		LOG("Error loading %s: %s", modelPath, aiGetErrorString());
	}
	aiReleaseImport(scene);
}

void ModuleModels::Load(const char* modelPath) {
	Load(modelPath, "vertex.glsl", "fragment.glsl");
}

void ModuleModels::LoadTextures(const char* modelPath, aiMaterial** const mMaterials, unsigned int mNumMaterials) {
	aiString file;
	textures.reserve(mNumMaterials);
	for (unsigned i = 0; i < mNumMaterials; ++i) {
		if (mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS) {
			unsigned int texture = App->texture->LoadTexture(file.data);

			if (texture) {
				textures.push_back(texture);
			}
			else {
				char sourceDirectory[_MAX_DIR];
				char sourceHarddrive[_MAX_DRIVE];
				_splitpath_s(modelPath, sourceHarddrive, _MAX_DRIVE, sourceDirectory, _MAX_DIR, NULL, 0, NULL, 0);

				char textureFilename[_MAX_FNAME];
				char textureExtension[_MAX_EXT];
				_splitpath_s(file.data, NULL, 0, NULL, 0, textureFilename, _MAX_FNAME, textureExtension, _MAX_EXT);

				char texturePathFromSameLocationOfModel[_MAX_PATH];
				_makepath_s(texturePathFromSameLocationOfModel, _MAX_PATH, sourceHarddrive, sourceDirectory, textureFilename, textureExtension);

				texture = App->texture->LoadTexture(texturePathFromSameLocationOfModel);
				if (texture) {
					textures.push_back(texture);
				}
				else {
					std::string texturePathFromAssetsDirectory = ".\\Assets\\Textures\\";
					texturePathFromAssetsDirectory.append(textureFilename);
					texturePathFromAssetsDirectory.append(textureExtension);

					texture = App->texture->LoadTexture(texturePathFromAssetsDirectory.c_str());
					if (texture) {
						textures.push_back(texture);
					}
					else {
						LOG("Could not find a texture");
					}
				}
			}
		}
	}
}

unsigned int ModuleModels::CreateProgram(const char* vertexShaderPath, const char* fragmentShaderPath) {
	unsigned int vertexShader = 0;
	unsigned int fragmentShader = 0;
	unsigned int program = 0;

	char* vertex_shader_url = App->program->LoadShaderSource(vertexShaderPath);
	if (vertex_shader_url) {
		vertexShader = App->program->CompileShader(GL_VERTEX_SHADER, vertex_shader_url);
	}

	char* fragment_shader_url = App->program->LoadShaderSource(fragmentShaderPath);
	if (fragment_shader_url) {
		fragmentShader = App->program->CompileShader(GL_FRAGMENT_SHADER, fragment_shader_url);
	}

	if (vertexShader && fragmentShader) {
		program = App->program->CreateProgram(vertexShader, fragmentShader);
	}

	return program;
}

unsigned int ModuleModels::GetNumVertices() {
	unsigned int total_vertices = 0;
	for (unsigned int i = 0; i < meshes.size(); i++) {
		total_vertices += meshes[i].numIndices;
	}
	return total_vertices;
}

void ModuleModels::LoadMeshes(aiMesh** const mMeshes, unsigned int mNumMeshes, unsigned int program) {
	meshes.reserve(mNumMeshes);

	for (unsigned int i = 0; i < mNumMeshes; i++) {
		meshes.push_back(Mesh(program));
		meshes[i].LoadVBO(mMeshes[i]);
		meshes[i].LoadEBO(mMeshes[i]);
		meshes[i].CreateVAO();
	}
}

void ModuleModels::Draw() {
	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i].Draw(textures);
	}
}

bool ModuleModels::CleanUp() {
	textures.clear();
	meshes.clear();
	return true;
}