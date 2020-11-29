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
		LOG("Model loaded.")
	}
	else {
		LOG("Error loading %s: %s", modelPath, aiGetErrorString());
	}
	aiReleaseImport(scene);
}

void ModuleModels::Load(const char* modelPath) {
	char extension[_MAX_EXT];
	_splitpath_s(modelPath, NULL, 0, NULL, 0, NULL, 0, extension, _MAX_EXT);

	if (strcmp(extension, ".fbx") == 0) {
		LOG("Loading model in path %s...", modelPath);
		Load(modelPath, "vertex.glsl", "fragment.glsl");
	}
	else if (strcmp(extension, ".png") == 0 || strcmp(extension, ".dds") == 0 || strcmp(extension, ".jpg") == 0 || strcmp(extension, ".jpeg") == 0 || strcmp(extension, ".tga") == 0) {
		LOG("Loading texture %s", modelPath);

		unsigned int texture = App->texture->LoadTexture(modelPath);
		if (texture) {
			if (!textures.empty()) {
				textures.clear();
			}
			textures.push_back(texture);
			LOG("Texture loaded.");
		}
	}
}

void ModuleModels::LoadTextures(const char* modelPath, aiMaterial** const mMaterials, unsigned int mNumMaterials) {
	aiString file;
	textures.reserve(mNumMaterials);
	for (unsigned i = 0; i < mNumMaterials; ++i) {
		if (mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS) {
			LOG("Looking for texture %s...", file.data)
			unsigned int texture = App->texture->LoadTexture(file.data);

			if (texture) {
				textures.push_back(texture);
				LOG("Texture %s found in %s", file.data, modelPath);
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
					LOG("Texture %s found in %s", file.data, texturePathFromSameLocationOfModel);
				}
				else {
					std::string texturePathFromAssetsDirectory = ".\\Assets\\Textures\\";
					texturePathFromAssetsDirectory.append(textureFilename);
					texturePathFromAssetsDirectory.append(textureExtension);

					texture = App->texture->LoadTexture(texturePathFromAssetsDirectory.c_str());
					if (texture) {
						textures.push_back(texture);
						LOG("Texture %s found in %s", file.data, texturePathFromAssetsDirectory.c_str());
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

float4x4 ModuleModels::GetModelMatrix() const
{
	return modelMatrix;
}

std::vector<Mesh> ModuleModels::GetMeshes() const
{
	return meshes;
}

std::vector<unsigned int> ModuleModels::GetTextures() const
{
	return textures;
}

void ModuleModels::LoadMeshes(aiMesh** const mMeshes, unsigned int mNumMeshes, unsigned int program) {
	meshes.reserve(mNumMeshes);

	for (unsigned int i = 0; i < mNumMeshes; ++i) {
		meshes.push_back(Mesh(program));
		meshes[i].LoadVBO(mMeshes[i]);
		meshes[i].LoadEBO(mMeshes[i]);
		meshes[i].CreateVAO();
	}
}

void ModuleModels::Draw() {
	modelMatrix = float4x4::identity;
	for (unsigned int i = 0; i < meshes.size(); ++i) {
		meshes[i].Draw(textures, modelMatrix);
	}
}

bool ModuleModels::CleanUp() {
	textures.clear();
	meshes.clear();
	return true;
}