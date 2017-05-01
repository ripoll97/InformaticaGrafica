#pragma once
#include "Mesh.h"
#include <src\SOIL.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

class Model {
public:
	Model(GLchar* path);
	void Draw(Shader shader, GLint drawMode);
private:
	vector<Mesh> meshes;
	string directory;
	vector<Texture> textures_loaded;
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	GLint TextureFromFile(const char* path, string directory);
};