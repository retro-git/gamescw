#pragma once

#include "bulletobject.h"
#include "enemybulletobject.h"
#include "followcamera.h"
#include "gameobject.h"
#include "ode/ode.h"
#include "ofMain.h"
#include "physicsobject.h"
#include "playerobject.h"
#include "queueobjstruct.h"
#include "staticobject.h"
#include "trackplayerobject.h"
#include <unordered_map>

#include "ofxAssimpModelLoader.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    template <typename T>
    std::shared_ptr<GameObject> createObject(glm::vec3 pos,
        glm::vec3 rot,
        glm::vec3 scale,
        string modelName,
        dWorldID w,
        dSpaceID s);

    void createQueuedObjects();
    void destroyQueuedObjects();
    void destroyObject(std::shared_ptr<GameObject>);

    void collide(dGeomID o1, dGeomID o2);

    void startNextWave();
    void drawHud();

    int highScore{ 0 };

    FollowCamera cam;

    dWorldID world;
    dSpaceID space;
    dJointGroupID contactgroup;
    // dGeomID ground;

    /* A light */
    ofLight m_light1;

    glm::vec2 prevMousePosition;

    float inputVertical{};
    float inputHorizontal{};
    float inputMouseVertical{};
    float inputMouseHorizontal{};

    std::shared_ptr<PlayerObject> player;

    std::vector<std::shared_ptr<GameObject>> objects;
    std::vector<QueueObjStruct> objectsCreateQueue;
    std::vector<std::shared_ptr<GameObject>> objectsDestroyQueue;
    std::unordered_map<dGeomID, std::shared_ptr<GameObject>> geomObjectMap;

    ofTrueTypeFont HUDFont;

    int waveCounter = 0;
    int numEnemies = 0;

    int projectileDamage = 20;

    bool resetFlag = false;
    bool wallhackPowerup = false;
    bool menuFlag = true;

    int killsSinceLastPowerup = 0;
    float lastPowerupActivateTime = 0;
    float powerupEnableTime = 15;
    float powerupKillsRequired = 10;
};

static void
nearCallback(void*, dGeomID o1, dGeomID o2);
extern ofApp* myApp;
