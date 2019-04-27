#include "MenuScene.h"
#include "MiszukScene.h"
#include "TestScene.h"
#include "Ui/UiTextButton.h"
#include "Ui/UiPlane.h"
#include "Serialization/Serializer.h"
#include "EditorScene.h"

class UiTextButton;

MenuScene::MenuScene() {
	optionsScene = new OptionsScene(this);
	UiTextButton *miszukScene = new UiTextButton(glm::vec2(windowCenterX, 3 * windowHeight / 9.0f), "Miszuk scene");
	miszukScene->setButtonCallback([]() {GameManager::getInstance()->setCurrentScene(new MiszukScene()); });
	UiTextButton *newTestScene = new UiTextButton(glm::vec2(windowCenterX, 4 * windowHeight / 9.0f), "New test scene");
	newTestScene->setButtonCallback([]() {GameManager::getInstance()->setCurrentScene(new TestScene()); });
	UiTextButton *loadTestScene = new UiTextButton(glm::vec2(windowCenterX, 5 * windowHeight / 9.0f), "Load test scene");
	loadTestScene->setButtonCallback([this]() {
		Scene *scene = Serializer::getInstance()->loadScene("test");
		if(scene != nullptr) {
			gameManager->setCurrentScene(scene);
		}
	});
	UiTextButton *editorScene = new UiTextButton(glm::vec2(windowCenterX, 6 * windowHeight / 9.0f), "Editor scene");
	editorScene->setButtonCallback([]() {GameManager::getInstance()->setCurrentScene(new EditorScene()); });
	UiTextButton *options = new UiTextButton(glm::vec2(windowCenterX, 7 * windowHeight / 9.0f), "Options");
	options->setButtonCallback([this]() {showOptions(); });
	UiTextButton *quit = new UiTextButton(glm::vec2(windowCenterX, 8 * windowHeight / 9.0f), "Quit");
	quit->setButtonCallback([]() {GameManager::getInstance()->quit(); });
	rootUiElement->addChild(miszukScene);
	rootUiElement->addChild(newTestScene);
	rootUiElement->addChild(loadTestScene);
	rootUiElement->addChild(editorScene);
	rootUiElement->addChild(options);
	rootUiElement->addChild(quit);
	rootUiElement->addChild(new UiText(glm::vec2(windowCenterX, 1.0f * windowHeight / 9.0f), glm::vec2(windowWidth, 2.0f * windowHeight / 9.0f), "MAIN MENU", glm::vec3(1.0f, 1.0f, 1.0f), MatchHeight));
	reinitializeRenderMap();
}

void MenuScene::render() {
	if(showingOptions) {
		optionsScene->render();
	} else {
		Scene::render();
	}
}

void MenuScene::renderUi() {
	if(showingOptions) {
		optionsScene->renderUi();
	} else {
		Scene::renderUi();
	}
}

void MenuScene::update(double deltaTime) {
	if (showingOptions) {
		optionsScene->update(deltaTime);
	} else {
		Scene::update(deltaTime);
	}
}

void MenuScene::keyboard_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {
	if (showingOptions) {
		optionsScene->keyboard_callback(window, key, scancode, action, mods);
	} else {
		//poof
	}
}

void MenuScene::mouse_callback(GLFWwindow * window, double xpos, double ypos) {
	if (showingOptions) {
		optionsScene->mouse_callback(window, xpos, ypos);
	} else {
		Scene::mouse_callback(window, xpos, ypos);
	}
}

void MenuScene::mouse_button_callback(GLFWwindow * window, int butt, int action, int mods) {
	if (showingOptions) {
		optionsScene->mouse_button_callback(window, butt, action, mods);
	} else {
		Scene::mouse_button_callback(window, butt, action, mods);
	}
}

void MenuScene::updateWindowSize(float windowWidth, float windowHeight, float screenWidth, float screenHeight) {
	Scene::updateWindowSize(windowWidth, windowHeight, screenWidth, screenHeight);
	optionsScene->updateWindowSize(windowWidth, windowHeight, screenWidth, screenHeight);
}

MenuScene::~MenuScene() {
	delete optionsScene;
}

void MenuScene::showOptions() {
	showingOptions = true;
}

void MenuScene::hideOptions() {
	showingOptions = false;
}
