#pragma once
#include "json/json.h"

class Serializer;

enum SerializableType {
	SNone,
	SGraphNode,
	SMesh,
	SMeshBox,
	SMeshColorBox,
	SMeshColorCone,
	SMeshColorCylinder,
	SMeshColorPlane,
	SMeshColorSphere,
	SMeshColorTorus,
	SMeshCone,
	SMeshCylinder,
	SMeshPlane,
	SMeshRef,
	SMeshRefBox,
	SMeshRefSphere,
	SMeshSimple,
	SMeshSphere,
	SMeshTexture,
	SModel,
	SModelInstanced,
	SMeshTorus,
	SScene,
	SCamera,
	SComponent,
	SAnimationController,
	SBillboard,
	SBoxCollider,
	SSphereCollider,
	SCollider,
	SCollectableObject,
	SPhysicalObject,
	SPicking,
	SPlayerMovement,
	SRotatingObject,
	SDirLightComp,
	SLightComp,
	SQuadraticLightComp,
	SPointLightComp,
	SSpotLightComp,
	SSun,
	SCollisionTest,
	SDirLight,
	SSpotLight,
	SPointLight,
	STestScene
};

class Serializable {
public:
	virtual Json::Value serialize(Serializer *serializer) = 0;
	virtual void deserialize(Json::Value &root, Serializer *serializer) = 0;
	virtual SerializableType getSerializableType() = 0;
};