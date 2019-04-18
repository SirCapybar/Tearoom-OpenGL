#pragma once

#include "GraphNode.h"
#include "GuiConfigurable.h"

class LightNode : public GraphNode {
public:
	LightNode(Mesh *mesh, GraphNode *parent) : GraphNode(mesh, parent) {}
	void setActive(bool active) override;
	virtual glm::vec4 getAmbient() = 0;
	virtual glm::vec4 getDiffuse() = 0;
	virtual glm::vec4 getSpecular() = 0;
	virtual void setAmbient(glm::vec4 ambient) = 0;
	virtual void setDiffuse(glm::vec4 diffuse) = 0;
	virtual void setSpecular(glm::vec4 specular) = 0;
protected:
	virtual bool getEnabled() = 0;
	virtual void setEnabled(bool enabled) = 0;
	glm::vec4 lastAmbient, lastDiffuse, lastSpecular;
	void updateWorld() override;
	virtual void setModel(glm::mat4 model) = 0;
	void renderGui() override;
};
