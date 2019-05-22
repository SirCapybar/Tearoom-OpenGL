#include "MiszukScene.h"
#include "Mesh/MeshColorPlane.h"
#include "Mesh/MeshColorSphere.h"
#include "Mesh/Model.h"
#include "TestScene.h"
#include "Mesh/MeshColorBox.h"
#include "Scene/OctreeNode.h"
#include <iostream>
#include "Scene/Components/Collider.h"
#include "Scene/Scripts/CollisionTest.h"
#include "Scene/Components/AnimationController.h"
#include "Scene/Components/BoxCollider.h"
#include "Scene/Components/SphereCollider.h"
#include "Scene/Components/PhysicalObject.h"
#include "Scene/Scripts/PlayerMovement.h"
#include "Scene/Scripts/Picking.h"
#include "Scene/Scripts/CollectableObject.h"
#include "Scene/Components/Animation.h"
#include "Ui/UiPlane.h"
#include "Ui/UiMesh.h"
#include "Scene/Components/SunController.h"
#include <ctime>
#include "Mesh/AnimatedModel.h"
#include "Scene/Components/KeyFrameAnimation.h"
#include "Scene/Components/Camera.h"

MiszukScene::MiszukScene() {
	GameManager::getInstance()->setCursorLocked(true);

	lightManager->recreateLights(0, 0, 0);

	rootUiElement->addChild(new UiText(glm::vec2(UI_REF_CEN_X, UI_REF_CEN_Y), "+", 1.0f));

	// for basic animation testing
	MeshColorBox *fallingBox = new MeshColorBox(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	MeshColorBox *animatedBox = new MeshColorBox(glm::vec3(-0.3f, 0.3f, -1), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
	MeshColorBox *slidingDoor = new MeshColorBox(glm::vec3(-0.3f, 0.4f, -1), glm::vec3(0.7f, 5.4f, 0.7f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	MeshColorBox *wall = new MeshColorBox(glm::vec3(-0.3f, 0.3f, 0.0f), glm::vec3(0.7f, 5.4f, 8.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	MeshColorBox *wall2 = new MeshColorBox(glm::vec3(-0.3f, 0.3f, 0.0f), glm::vec3(0.7f, 5.4f, 8.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	GraphNode* animatedBoxNode = new GraphNode(animatedBox, rootNode);
	GraphNode* slidingDoorNode = new GraphNode(slidingDoor, rootNode);
	GraphNode* wallNode = new GraphNode(wall, rootNode);
	GraphNode* wallNode2 = new GraphNode(wall2, rootNode);
	animatedBoxNode->addComponent(new AnimationController(SafePullOutY, animatedBoxNode));
	animatedBoxNode->addComponent(new BoxCollider(animatedBoxNode, STATIC, false, glm::vec3(0), glm::vec3(1)));
	slidingDoorNode->addComponent(new AnimationController(DoorOpeningX, slidingDoorNode));
	slidingDoorNode->addComponent(new BoxCollider(slidingDoorNode, STATIC, true, glm::vec3(0, 1.0f, 0), glm::vec3(0.5f, 1.0f, 0.5f)));

	slidingDoorNode->localTransform.translate(glm::vec3(8.0f, -2.0f, -6.0f));
	animatedBoxNode->localTransform.translate(glm::vec3(8.0f, -1.0f, 0.0f));

	//-------------
	//INVENTORY UI
	UiPlane* boxRepresentation = new UiPlane("res/textures/letterIcon.png", glm::vec2(995.0f, 530.0f), glm::vec2(60.0f, 60.0f), Right);
	UiPlane* boxRepresentation2 = new UiPlane("res/textures/letterIcon.png", glm::vec2(995.0f, 530.0f), glm::vec2(60.0f, 60.0f), Right);
	UiPlane* boxRepresentation3 = new UiPlane("res/textures/letterIcon.png", glm::vec2(995.0f, 530.0f), glm::vec2(60.0f, 60.0f), Right);
	UiPlane* boxRepresentation4 = new UiPlane("res/textures/letterIcon.png", glm::vec2(995.0f, 530.0f), glm::vec2(60.0f, 60.0f), Right);
	UiPlane* boxRepresentation5 = new UiPlane("res/textures/letterIcon.png", glm::vec2(995.0f, 530.0f), glm::vec2(60.0f, 60.0f), Right);
	UiPlane* boxRepresentation6 = new UiPlane("res/textures/letterIcon.png", glm::vec2(995.0f, 530.0f), glm::vec2(60.0f, 60.0f), Right);
	UiPlane* boxRepresentation7 = new UiPlane("res/textures/letterIcon.png", glm::vec2(995.0f, 530.0f), glm::vec2(60.0f, 60.0f), Right);
	UiPlane* boxRepresentation8 = new UiPlane("res/textures/letterIcon.png", glm::vec2(995.0f, 530.0f), glm::vec2(60.0f, 60.0f), Right);
	UiPlane* boxRepresentation9 = new UiPlane("res/textures/letterIcon.png", glm::vec2(995.0f, 530.0f), glm::vec2(60.0f, 60.0f), Right);

	// COLLECTABLE ITEM
	MeshColorBox *tinyItem = new MeshColorBox(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 0.5f, 0.5f, 1.0f));
	GraphNode *tinyItemNode = new GraphNode(tinyItem, rootNode);
	tinyItemNode->addComponent(new PhysicalObject(tinyItemNode));
	tinyItemNode->addComponent(new CollectableObject(tinyItemNode, camera, Letter, boxRepresentation));
	tinyItemNode->addComponent(new BoxCollider(tinyItemNode, STATIC, false, glm::vec3(0), glm::vec3(1)));
	tinyItemNode->localTransform.translate(glm::vec3(3.0f, -1.0f, 2.0f));

	MeshColorBox *tinyItem2 = new MeshColorBox(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec4(0.0f, 0.5f, 0.5f, 1.0f));
	GraphNode *tinyItemNode2 = new GraphNode(tinyItem2, rootNode);
	tinyItemNode2->addComponent(new PhysicalObject(tinyItemNode2));
	tinyItemNode2->addComponent(new CollectableObject(tinyItemNode2, camera, Letter, boxRepresentation2));
	tinyItemNode2->addComponent(new BoxCollider(tinyItemNode2, DYNAMIC, false, glm::vec3(0), glm::vec3(1)));
	tinyItemNode2->localTransform.translate(glm::vec3(3.0f, -0.5f, 4.0f));

	MeshColorBox *tinyItem3 = new MeshColorBox(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 0.5f, 0.5f, 1.0f));
	GraphNode *tinyItemNode3 = new GraphNode(tinyItem3, rootNode);
	tinyItemNode3->addComponent(new PhysicalObject(tinyItemNode3));
	tinyItemNode3->addComponent(new CollectableObject(tinyItemNode3, camera, Letter, boxRepresentation3));
	tinyItemNode3->addComponent(new BoxCollider(tinyItemNode3, STATIC, false, glm::vec3(0), glm::vec3(1)));
	tinyItemNode3->localTransform.translate(glm::vec3(3.0f, -1.0f, 2.0f));

	MeshColorBox *tinyItem4 = new MeshColorBox(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 0.5f, 0.5f, 1.0f));
	GraphNode *tinyItemNode4 = new GraphNode(tinyItem4, rootNode);
	tinyItemNode4->addComponent(new PhysicalObject(tinyItemNode4));
	tinyItemNode4->addComponent(new CollectableObject(tinyItemNode4, camera, Letter, boxRepresentation4));
	tinyItemNode4->addComponent(new BoxCollider(tinyItemNode4, STATIC, false, glm::vec3(0), glm::vec3(1)));
	tinyItemNode4->localTransform.translate(glm::vec3(3.0f, -1.0f, 2.0f));

	MeshColorBox *tinyItem5 = new MeshColorBox(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 0.5f, 0.5f, 1.0f));
	GraphNode *tinyItemNode5 = new GraphNode(tinyItem5, rootNode);
	tinyItemNode5->addComponent(new PhysicalObject(tinyItemNode5));
	tinyItemNode5->addComponent(new CollectableObject(tinyItemNode5, camera, Letter, boxRepresentation5));
	tinyItemNode5->addComponent(new BoxCollider(tinyItemNode5, STATIC, false, glm::vec3(0), glm::vec3(1)));
	tinyItemNode5->localTransform.translate(glm::vec3(3.0f, -1.0f, 2.0f));

	MeshColorBox *tinyItem6 = new MeshColorBox(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec4(0.0f, 0.5f, 0.5f, 1.0f));
	GraphNode *tinyItemNode6 = new GraphNode(tinyItem6, rootNode);
	tinyItemNode6->addComponent(new PhysicalObject(tinyItemNode6));
	tinyItemNode6->addComponent(new CollectableObject(tinyItemNode6, camera, Letter, boxRepresentation6));
	tinyItemNode6->addComponent(new BoxCollider(tinyItemNode6, DYNAMIC, false, glm::vec3(0), glm::vec3(1)));
	tinyItemNode6->localTransform.translate(glm::vec3(3.0f, -0.5f, 4.0f));

	MeshColorBox *tinyItem7 = new MeshColorBox(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 0.5f, 0.5f, 1.0f));
	GraphNode *tinyItemNode7 = new GraphNode(tinyItem7, rootNode);
	tinyItemNode7->addComponent(new PhysicalObject(tinyItemNode7));
	tinyItemNode7->addComponent(new CollectableObject(tinyItemNode7, camera, Letter, boxRepresentation7));
	tinyItemNode7->addComponent(new BoxCollider(tinyItemNode7, STATIC, false, glm::vec3(0), glm::vec3(1)));
	tinyItemNode7->localTransform.translate(glm::vec3(3.0f, -1.0f, 2.0f));

	MeshColorBox *tinyItem8 = new MeshColorBox(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 0.5f, 0.5f, 1.0f));
	GraphNode *tinyItemNode8 = new GraphNode(tinyItem8, rootNode);
	tinyItemNode8->addComponent(new PhysicalObject(tinyItemNode8));
	tinyItemNode8->addComponent(new CollectableObject(tinyItemNode8, camera, Letter, boxRepresentation8));
	tinyItemNode8->addComponent(new BoxCollider(tinyItemNode8, STATIC, false, glm::vec3(0), glm::vec3(1)));
	tinyItemNode8->localTransform.translate(glm::vec3(3.0f, -1.0f, 2.0f));

	MeshColorBox *tinyItem9 = new MeshColorBox(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 0.5f, 0.5f, 1.0f));
	GraphNode *tinyItemNode9 = new GraphNode(tinyItem9, rootNode);
	tinyItemNode9->addComponent(new PhysicalObject(tinyItemNode9));
	tinyItemNode9->addComponent(new CollectableObject(tinyItemNode9, camera, Letter, boxRepresentation9));
	tinyItemNode9->addComponent(new BoxCollider(tinyItemNode9, STATIC, false, glm::vec3(0), glm::vec3(1)));
	tinyItemNode9->localTransform.translate(glm::vec3(3.0f, -1.0f, 2.0f));
	//-----------------
	//miszuk animation
	GraphNode* doorPivot = new GraphNode(nullptr, rootNode);
	MeshColorBox* doorMesh = new MeshColorBox(glm::vec3(2.0f, 3.0f, 0.2f), glm::vec4(0.8f, 1.0f, 1.0f, 1.0f));
	MeshColorBox* handleMesh = new MeshColorBox(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec4(0.8f, 0.0f, 0.0f, 1.0f));
	doorPivot->setName("doorPivot");
	GraphNode* door = new GraphNode(doorMesh, doorPivot);
	door->setName("door");
	GraphNode* handle = new GraphNode(handleMesh, door);
	handle->setName("handle");

	door->addComponent(new BoxCollider(door, STATIC, false, glm::vec3(0), glm::vec3(1.0f, 1.5f, 0.1f)));
	Animation* anim = new KeyFrameAnimation(door, "doorOpening");
	anim->addKeyFrame("door", anim::TRANSLATION, 0.0f, glm::vec3(0));
	anim->addKeyFrame("door", anim::TRANSLATION, 1.0f, glm::vec3(0.4f, 0.0f, 0.0f));
	anim->addKeyFrame("door", anim::TRANSLATION, 2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	anim->addKeyFrame("door", anim::TRANSLATION, 4.0f, glm::vec3(0.0f, 0.0f, 0.0f));
	door->addComponent(anim);
	doorPivot->localTransform.setPosition(-4.0f, -1.0f, -2.0f);
	doorPivot->localTransform.rotateYDegrees(180.0f);

	anim->addKeyFrame("handle", anim::TRANSLATION, 2.0f, glm::vec3(-1.0f, 0.0f, 0.0f));
	anim->addKeyFrame("handle", anim::TRANSLATION, 0.0f, glm::vec3(0));
	anim->addKeyFrame("handle", anim::TRANSLATION, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	anim->addKeyFrame("handle", anim::TRANSLATION, 3.0f, glm::vec3(1.0f, 4.0f, 0.0f));
	anim->addKeyFrame("handle", anim::TRANSLATION, 3.0f, glm::vec3(5.0f, 2.0f, 0.0f));
	anim->addKeyFrame("handle", anim::TRANSLATION, 4.0f, glm::vec3(0));

	anim->addKeyFrame("handle", anim::SCALE, 0.0f, glm::vec3(1));
	anim->addKeyFrame("handle", anim::SCALE, 1.0f, glm::vec3(2.0f, 0.5f, 1.0f));
	anim->addKeyFrame("handle", anim::SCALE, 2.0f, glm::vec3(3.0f, 0.5f, 0.5f));
	anim->addKeyFrame("handle", anim::SCALE, 4.0f, glm::vec3(1));

	anim->addKeyFrame("handle", anim::ROTATION, 0.0f, glm::vec3(0));
	anim->addKeyFrame("handle", anim::ROTATION, 2.0f, glm::vec3(90.0f, 90.0f, 180.0f));
	anim->addKeyFrame("handle", anim::ROTATION, 4.0f, glm::vec3(0.0f, 0.0f, 360.0f));
	//

	MeshColorBox* box = new MeshColorBox(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	MeshColorBox* box1 = new MeshColorBox(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
	MeshColorBox* box2 = new MeshColorBox(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	MeshColorBox* floorMesh = new MeshColorBox(glm::vec3(-10.0f, -0.5f, -10.5f), glm::vec3(10.0f, 0.5f, 10.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	MeshColorBox* meshBox = new MeshColorBox(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	MeshColorBox* meshBox1 = new MeshColorBox(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	GraphNode* boxNode = new GraphNode(box, rootNode);
	GraphNode* boxNode2 = new GraphNode(box1, rootNode);
	GraphNode* simpleBox1 = new GraphNode(meshBox, rootNode);
	GraphNode* simpleBox2 = new GraphNode(meshBox1, rootNode);
	GraphNode* pivot = new GraphNode(nullptr, rootNode);
	GraphNode* planete = new GraphNode(box2, pivot);
	GraphNode* floor = new GraphNode(floorMesh, rootNode);

	Mesh* playerMesh = new MeshColorBox(glm::vec3(1.0f, 2.0f, 1.0f), glm::vec4(1));
	player = new GraphNode(playerMesh, rootNode);
	player->addComponent(new BoxCollider(player, DYNAMIC));
	player->addComponent(new PlayerMovement(player));
	camera = player->getComponent<Camera>();  //playermovement creates a camera if it doesn't exist
	player->localTransform.setPosition(glm::vec3(-5.0f, 0.0f, -3.0f));
	player->addComponent(new SunController(player, this));
	player->addComponent(new Picking(player, camera, this));

	GraphNode* fallingBoxNode = new GraphNode(fallingBox, rootNode);
	fallingBoxNode->addComponent(new SphereCollider(fallingBoxNode, STATIC));
	fallingBoxNode->addComponent(new PhysicalObject(fallingBoxNode));
	boxNode->localTransform.translate(glm::vec3(4.0f, 3.0f, 2.5f));
	boxNode->localTransform.rotateYDegrees(130.0f);
	//boxNode->localTransform.rotate(130.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	boxNode2->localTransform.setPosition(7.0f, 3.0f, 3.0f);
	simpleBox1->localTransform.setPosition(0.0f, 2.0f, 0.0f);
	planete->localTransform.setPosition(7.0f, 3.0f, 0.0f);
	simpleBox2->localTransform.setPosition(0.0f, 0.0f, 1.0f);
	floor->localTransform.setPosition(0.0f, -3.0f, 0.0f);
	fallingBoxNode->localTransform.setPosition(0.0f, -1.5f, -3.0f);

	wallNode->localTransform.translate(glm::vec3(8.0f, -2.0f, -5.0f));
	wallNode2->localTransform.translate(glm::vec3(8.0f, -2.0f, -15.0f));

	boxNode2->addComponent(new SphereCollider(boxNode2, DYNAMIC, true, glm::vec3(-0.5f, 0.0f, 0.0f), 1.0f));
	//boxNode3->addComponent(new AnimationController());
	boxNode->addComponent(new BoxCollider(boxNode, DYNAMIC, true, glm::vec3(1, 0, 0), glm::vec3(1.3f, 1.0f, 0.5f)));
	boxNode->addComponent(new CollisionTest(boxNode));
	simpleBox1->addComponent(new BoxCollider(simpleBox1, STATIC, false, glm::vec3(0, 0, 0), glm::vec3(0.5f, 1.0f, 0.5f)));
	simpleBox2->addComponent(new BoxCollider(simpleBox2, STATIC, false, glm::vec3(0, 0, 0), glm::vec3(0.5f, 0.5f, 0.5f)));
	simpleBox2->setName("animatedObject");
	//simpleBox2->addComponent(new Animation(simpleBox2, "Animation"));
	pivot->addComponent(new BoxCollider(pivot, DYNAMIC, true, glm::vec3(7.0f, 3.0f, 0.0f), glm::vec3(0.5f, 1.0f, 0.5f)));
	pivot->addComponent(new CollisionTest(pivot));

	floor->addComponent(new BoxCollider(floor, STATIC, false, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 0.5f, 10.0f)));
	//simpleBox2->localTransform.setPosition(0.5f, 2.0f, 0.0f);

	auto* robot = AnimatedModel::createModelData("res/models/zabijaka/Pointing.fbx");
	srand(time(NULL));
	AnimatedModel* robo = new AnimatedModel("res/models/zabijaka/Pointing.fbx");
	for (int i = 0; i < 1; i++) {

		int x = (rand() % 50);
		int y = (rand() % 50);
		int z = (rand() % 50);
		GraphNode* node = new GraphNode(robo, rootNode);
		node->localTransform.setPosition(1, -2.5f, 1);
		//node->localTransform.rotateXDegrees(-90);
		node->localTransform.setScale(0.01f);
		node->addComponent(new BoxCollider(node, STATIC, false, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.35f, 2.0f, 0.35f)));
//#todo find out if animation works 
		node->addComponent(new SkeletalAnimation(node, "skeletorAnimation"));
		node->getComponent<SkeletalAnimation>()->setObjectAnimation(AssetManager::getInstance()->getAnimation("res/models/zabijaka/Pointing.fbx").getObjectAnimations());
		node->getComponent<SkeletalAnimation>()->play();
	}

	rootNode->updateDrawData();
	rootUiElement->updateDrawData();
	reinitializeRenderMap();
}

MiszukScene::~MiszukScene() {
	delete rootNode;
}

void MiszukScene::keyEvent(int key, bool pressed) {
	switch (key) {
		case KEY_TOGGLE_MOUSE_LOCK:
			if (pressed) {
				setCursorLocked(!getCursorLocked());
			}
			break;
		case KEY_QUIT:
		{
			gameManager->goToMenu(false);
		}
		break;
	}
}

