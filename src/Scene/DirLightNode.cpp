#include "DirLightNode.h"

DirLightNode::DirLightNode(DirLight* light, Mesh* mesh, GraphNode* parent) : GraphNode(mesh, parent), light(light) {
	rotationZ = 0.0f;
	rotationX = 0.0f;
	appliedZ = 0.0f;
	appliedX = 0.0f;
	lastEnabled = true;
}

void DirLightNode::update(double timeDiff) {
	light->model = worldTransform.Matrix();
	GraphNode::update(timeDiff);
}

void DirLightNode::drawGui(bool autoUpdate) {
	ImGui::PushID((uintptr_t)this);
	ImGui::Checkbox("DirLight enabled", &lastEnabled);
	ImGui::NewLine();
	if (lastEnabled) {
		ImGui::SliderAngle("DirLight rotationZ", &rotationZ);
		ImGui::NewLine();
		ImGui::SliderAngle("DirLight rotationX", &rotationX);
		ImGui::NewLine();
		ImGui::ColorEdit3("DirLight ambient", (float*)&(light->ambient));
		ImGui::NewLine();
		ImGui::ColorEdit3("DirLight diffuse", (float*)&(light->diffuse));
		ImGui::NewLine();
		ImGui::ColorEdit3("DirLight specular", (float*)&(light->specular));
		ImGui::NewLine();
	}

	if (autoUpdate || ImGui::Button("Apply DirLight changes")) {
		if (rotationZ != appliedZ || rotationX != appliedX) {
			appliedZ = rotationZ;
			appliedX = rotationX;
			/*local = glm::mat4(1.0f);
			local = rotate(local, appliedZ, glm::vec3(0.0f, 0.0f, 1.0f));
			local = rotate(local, appliedX, glm::vec3(1.0f, 0.0f, 0.0f));*/
			localTransform.SetMatrix(glm::mat4(1.0f));
			localTransform.RotateByRadians(appliedZ, glm::vec3(0.0f, 0.0f, 1.0f));
			localTransform.RotateByRadians(appliedX, glm::vec3(1.0f, 0.0f, 0.0f));
			dirty = true;
			//light->model = getWorld();
			//light->model = worldTransform.Matrix(); the world transform is not updated here yet so it's pointless to reset it. It gets updated later anyway.
		}
		if (lastEnabled != enabled) {
			enabled = lastEnabled;
			if (enabled) {
				light->ambient = lastAmbient;
				light->diffuse = lastDiffuse;
				light->specular = lastSpecular;
			}
			else {
				lastAmbient = light->ambient;
				lastDiffuse = light->diffuse;
				lastSpecular = light->specular;
				light->ambient = glm::vec4(0.0f);
				light->diffuse = glm::vec4(0.0f);
				light->specular = glm::vec4(0.0f);
			}
		}
	}
	ImGui::PopID();
}

DirLight* DirLightNode::getLight() {
	return light;
}
