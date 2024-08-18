#ifndef BASESCREEN_H_
#define BASESCREEN_H_

#include <stdlib.h>

#include <Aurora/Utils/StateManager.h>
#include <Aurora/Utils/GameState.h>
#include <Aurora/Graphics/RenderManager.h>
#include <Aurora/Utils/Logger.h>
#include <Aurora/Utils/Timer.h>
#include <Aurora/Utils/pgeZip.h>
#include <Aurora/Utils/pgeDir.h>
#include <Aurora/Utils/pge.h>

#include <Aurora/System/SystemManager.h>
#include <Aurora/Graphics/Models/ObjModel.h>
#include <Aurora/Graphics/Camera.h>
#include <Aurora/Graphics/Sprite.h>

#include <pspiofilemgr.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include<fstream>
#include<iostream>

#include <dirent.h>
#include <fcntl.h>
#include <errno.h>

#include "SoundManager.h"

#ifdef __PSP__
	#include <sys/stat.h>
#endif

using namespace Aurora::Graphics;
using namespace Aurora::Utils;
using namespace Aurora::System;
using namespace Aurora;

class BaseScreen
{
public:
    // Variables base para pintado y posicionamiento
    Sprite *buttonSmallSprite;
    Sprite *sbuttonSmallSprite;
    Sprite *nbuttonSmallSprite;

    Sprite *buttonSprite;
    Sprite *sbuttonSprite;

    Sprite *nbuttonSprite;

    Sprite *mbuttonSprite;
    Sprite *smbuttonSprite;

    Sprite *menuSprite; // menu
    Sprite *smenuSprite;

    Sprite *backSprite;
    Sprite *lenguageSprite;
    Sprite *slenguageSprite;
    Sprite *skinSprite;
    Sprite *sskinSprite;
    Sprite *logoSprite;
    Sprite *MinecraftSprite;

    Sprite *rectFilledSprite;
    Sprite *rectEmptySprite;

    Sprite *blackBackground;

    Sprite *steveHead;
    Sprite *steveHeadCapa;
    Sprite *steveBody;
    Sprite *steveHand;
    Sprite *steveLeg;
    Sprite *backgroundSprite;

    // Managers base
    RenderManager *mRender;
    SystemManager *mSystemMgr;
    SoundManager *mSoundMgr;

    // Variables
    float bx, by;
    bool directionx;
    bool directiony;
    int SplashNumber;
    float splashSize;
    int selectPos;
    int loadSelectPos;
    int loadSavePos;
    int aboutPos;
    int donatePos;
    int skinPos;
    unsigned int seed_1;
    float size_f = 0.347f;

    // Al parece esta variable no es usada
    char worldName[32];
    //---------------------

    // converter vars
    bool schematicExists;
    short newW_width;
    short newW_height;
    short newW_length;
    char newW_gameMode;
    bool newW_deleteCaves;
    int conversionStage;
    int errorType;
    std::string lol;
    // Font vars
    float fontcolor;
    bool fontcoloroption;

    // Main menu
    bool saveSubmenu;
    int saveSubMenuSelect;
    int loadSaveStart;
    int loadSaveEnd;
    int loadSaveMax;

    short animationscreen;
    
    int nextSaveFileNumber;

    std::string nextSaveFileName;
    std::vector<SaveFile> saveFilesList;
    std::vector<TP> texturePackList;
    std::string newWorldName;
    std::string newWorldSeed;
    std::string newWorldNamestr;

    // options for parametric map generation
    bool makeTrees;
    bool makeWater;
    bool makeBonus;
    bool makeDungeons;
    bool makeCaves;
    int terrainBuilder;
    short gameMode;
    int worldType;

    short generateSelectPose;
    // game version
    short currentVersion;
    int tpCurrent;
    int tpMax;
    int tpEnd;
    int tpStart;
    int tpPos;
    int tpSelectPos;

    int converterPos;

    // Functions base
    /*painting text*/
    void DrawText(int x, int y, unsigned int color, float size, const char *message, ...);
    /*painting button*/
    void DrawButton(int posX, int posY, bool isSelected, const char* label);
    /*painting text in buttons*/
    void DrawTextLabel(int posX, int posY, const char* label, bool isSelected = false);
    /*painting headers in screens*/
    void DrawMenuHeader(const char* heade);

    void InitScreen();
}

#endif