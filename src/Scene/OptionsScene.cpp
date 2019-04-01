#include "OptionsScene.h"
#include "MenuScene.h"
#include "GLFW/glfw3.h"
#include "Ui/UiTextButton.h"
#include "Ui/UiCheckbox.h"

OptionsScene::OptionsScene(MenuScene* menuScene) {
	this->menuScene = menuScene;
	textRenderer = sceneManager->getTextRenderer();
	UiCheckbox *useLight = new UiCheckbox(glm::vec2(windowCenterX - 100.0f, 4 * windowHeight / 9.0f), sceneManager->useLight, true);
	useLight->setCheckboxCallback([&manager = sceneManager](bool useLight) { manager->useLight = useLight; });
	UiTextButton *back = new UiTextButton(glm::vec2(windowCenterX, 8 * windowHeight / 9.0f), "Back to menu");
	back->setButtonCallback([menuScene]() { menuScene->hideOptions(); });
	uiElements.emplace_back(back);
	uiElements.emplace_back(useLight);
}

void OptionsScene::render() {
	textRenderer->renderText("OPTIONS", windowCenterX, 1.5f * windowCenterY / 9.0f, 1.5f, true);
	textRenderer->renderText("Use light", windowCenterX, 4 * windowHeight / 9.0f);
	Scene::render();
}

void OptionsScene::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_ESCAPE) {
			menuScene->hideOptions();
		}
	}
}
