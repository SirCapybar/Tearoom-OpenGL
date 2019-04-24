#ifndef MISZUK_SCENE
#define MISZUK_SCENE

#include "Scene.h"
#include <map>
#include "Render/Camera.h"

class MiszukScene : public Scene {
public:
	void render() override;
	void renderUi() override;
	void update(double deltaTime) override;
	MiszukScene();
	~MiszukScene();
protected:
	//--------------ANIMACJA---------------------
	bool f_keyPressed = false;
	//-----------------------------------------
	void keyEvent(int key, bool pressed) override;
};

#endif