#ifndef MESHMODELINSTANCED_H
#define MESHMODELINSTANCED_H

#include "Headers.h"
#include "MeshModel.h"
#include <string>
#include <vector>

class MeshModelInstanced : public Mesh {
public:
	MeshModelInstanced(std::vector<ModelVertex> vertices, std::vector<unsigned int> indices,
	                   std::vector<ModelTexture> textures, glm::vec3* offsets, int offsetSize);
	void draw(Shader *shader, glm::mat4 world, float scale = 1.0f) override;
	ShaderType getShaderType() override;
protected:
	void setupMesh();
	glm::vec3* offsets;
	int offsetSize;
	GLuint instanceVBO;
	std::vector<unsigned int> indices;
	std::vector<ModelVertex> vertices;
	std::vector<ModelTexture> textures;
};

#endif
