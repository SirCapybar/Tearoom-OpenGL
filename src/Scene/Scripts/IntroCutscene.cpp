//
// Created by MB on 5/29/2019.
//
/*
 Skoro to czytasz, znaczy że już mnie nie ma. a mój dorobek na Ciebie czeka.

Nigdy nie mieliśmy czasu by razem napić się herbaty.

Zostawiam ci wszystko co posiadam w moim domu.

Mój testament czeka na ciebie, w schowku który oznaczyłem na zdjęciu.

Twój wujek,
Yoshiro
 */
#include <Scene/SoundSystem.h>
#include "IntroCutscene.h"

IntroCutscene::IntroCutscene(Scene* scene, glm::vec3 cameraPos) {
    this->scene = scene;
    boxNode = new GraphNode(box, scene->getRootNode());
    boxNode->localTransform.setPosition(glm::vec3(cameraPos.x - 3.5f, cameraPos.y - 1.0f, cameraPos.z - 3.8f));
    UiElement *root = scene->getUiRoot();
    mainCanvas = new UiCanvas(glm::vec2(0.0f, 0.0f), root->getSize());
    root->addChild(mainCanvas);
    mainCanvas->addChild(backgroundPlane);
    mainCanvas->addChild(paperTexture);
    mainCanvas->addChild(text1);
    mainCanvas->addChild(text2);
    mainCanvas->addChild(text3);
    mainCanvas->addChild(text4);
    mainCanvas->addChild(text5);
    mainCanvas->addChild(transitionPlane);
    transitionPlane->setOpacity(1.0f);
    text1->setOpacity(0.0f);
    text2->setOpacity(0.0f);
    text3->setOpacity(0.0f);
    text4->setOpacity(0.0f);
    text5->setOpacity(0.0f);

}

void IntroCutscene::runIntro() {
    run = true;
}

void IntroCutscene::showNext(UiElement* uiElement) {
    while (elapsed <= 1.0f) {
        uiElement->setOpacity(elapsed);
        elapsed += 0.01f;
    }
    elapsed = 0.0f;
}

void IntroCutscene::update(float msec) {

    if(run) {
        switch (phase) {
            case 0:
            if (transitionPlane->getOpacity() > 0.0f) {
                transitionPlane->setOpacity(elapsed);
                elapsed -= 0.01f;
            } else {
                elapsed = 0.0f;
                phase = 1;
            }
            break;
            case 1:
                if (text1->getOpacity() < 1.0f) {
                    text1->setOpacity(elapsed);
                    elapsed += 0.01f;
                } else {
                    elapsed = 0.0f;
                    phase = 2;
                }
                break;
            case 2:
                if (text2->getOpacity() < 1.0f) {
                    text2->setOpacity(elapsed);
                    elapsed += 0.01f;
                } else {
                    elapsed = 0.0f;
                    phase = 3;
                }
                break;
            case 3:
                if (text3->getOpacity() < 1.0f) {
                    text3->setOpacity(elapsed);
                    elapsed += 0.01f;
                } else {
                    elapsed = 0.0f;
                    phase = 4;
                }
                break;
            case 4:
                if (text4->getOpacity() < 1.0f) {
                    text4->setOpacity(elapsed);
                    elapsed += 0.01f;
                } else {
                    elapsed = 0.0f;
                    phase = 5;
                }
                break;
            case 5:
                if (text5->getOpacity() < 1.0f) {
                    text5->setOpacity(elapsed);
                    elapsed += 0.01f;
                } else {
                    elapsed = 0.0f;
                    phase = 6;
                    SoundSystem::getSound("slidingCutsceneDoor")->setDefaultVolume(0.60f);
                    SoundSystem::getEngine()->play2D(SoundSystem::getSound("slidingCutsceneDoor"));
                }
                break;
            case 6:
                if (transitionPlane->getOpacity() < 1.0f) {
                    transitionPlane->setOpacity(elapsed);
                    elapsed += 0.01f;
                } else {
                    elapsed = 1.0f;
                    phase = 7;
                    boxNode->setActive(false);
                }
                break;
            case 7:
                paperTexture->setActive(false);
                text1->setActive(false);
                text2->setActive(false);
                text3->setActive(false);
                text4->setActive(false);
                text5->setActive(false);

                if (backgroundPlane->getOpacity() > 0.0f) {
                    transitionPlane->setOpacity(elapsed);
                    backgroundPlane->setOpacity(elapsed);
                    elapsed -= 0.01f;
                } else {
                    elapsed = 0.0f;
                    backgroundPlane->setActive(false);
                    transitionPlane->setActive(false);
                    run = false;
                }
                break;
        }
    }
}

IntroCutscene::~IntroCutscene() {}
