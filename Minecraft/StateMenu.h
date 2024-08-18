#ifndef STATEMENU_H_
#define STATEMENU_H_

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

#ifdef __PSP__
	#include <sys/stat.h>
#endif

#include "SoundManager.h"

//Inclusion de pantallas
#include <Minecraft/Screens/InitMenu/InitMenu.h>

using namespace Aurora::Graphics;
using namespace Aurora::Utils;
using namespace Aurora::System;
using namespace Aurora;
//Actuara como la clase base para todas las pantallas
class SaveFile
{
public:

	int saveVersion;
	bool compression;
	char worldGameMode;
	char worldName[50];
	bool locked;
	std::string fileName;

	int saveSize;
};

class TP
{
public:
    Sprite* packSprite;
	std::string name;
	std::string description;
};

class StateMenu : public CGameState
{
public:
	StateMenu();
	virtual ~StateMenu();
	
	void Init();
	void Enter();
	void CleanUp();

	void Pause();
	void Resume();

	void NetherEnteringSystem(StateManager* sManager,std::string mundoNombre);
	void HandleEvents(StateManager* sManager);
	void Update(StateManager* sManager);
	void Draw(StateManager* sManager);

	//Controls Independents for each screen d-pad,analog

	
	/*Draw independents for each screen*/

	//DrawText
	void DrawText(int x,int y, unsigned int color, float size, const char *message, ...);
	//buttonSprite
	void DrawButton(int posX, int posY, bool isSelected, const char* label); 
	//sbuttonSprite
	void DrawSButton(int posX, int posY, const char *label); 
	//buttonSmallSprite
	void DrawSmallButton(int posX, int posY, const char *label); 
	//sbuttonSmallSprite
	void DrawSButtonSmall(int posX, int posY, const char *label); 
	//backSprite
	void DrawBackButton(int posX, int posY, bool isSelected, const char* label);

	void DrawTextLabel(int posX, int posY, const char* label, bool isSelected = false);
	void DrawMenuHeader(const char* header);
	void DrawBackground();
	void DrawMinecraft(int posX, int posY);
	void DrawSkin(int posX, int posY);
	void DrawLanguage(int posX, int posY);
	void DrawSSkin(int posX, int posY);
	void DrawSLanguage(int posX, int posY);
	void DrawSteve(int posX, int posY);

    Sprite *backgroundSprite;
    float bx, by;
    bool directionx;
    bool directiony;

    Sprite *buttonSmallSprite;
	Sprite *sbuttonSmallSprite;
	Sprite *nbuttonSmallSprite;

	Sprite *buttonSprite;
	Sprite *sbuttonSprite;

	Sprite *nbuttonSprite;

	Sprite *mbuttonSprite;
	Sprite *smbuttonSprite;
	
	Sprite *menuSprite;//menu
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


	RenderManager *mRender;
	SystemManager *mSystemMgr;
	SoundManager *mSoundMgr;

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

    int converterPos;
	//

    int SplashNumber;
    float splashSize;

    unsigned int seed_1;
	int selectPos;
	int loadSelectPos;
	int loadSavePos;
	int aboutPos;
	int donatePos;
	int skinPos;
	char worldName[32];

    float size_f;

	float fontcolor;
	bool fontcoloroption;

	bool saveSubmenu;
	int saveSubMenuSelect;

    pgeZip* theZip;

	int loadSaveStart;
	int loadSaveEnd;
	int loadSaveMax;

	short animationscreen;
	short menuState;//0 main,1 load,2 options

	int nextSaveFileNumber;
	std::string nextSaveFileName;

	std::vector<SaveFile> saveFilesList;
	std::vector<TP> texturePackList;
	std::string newWorldName;
	std::string newWorldSeed;
	std::string newWorldNamestr;
	//options for parametric map generation
	bool makeTrees;
	bool makeWater;
	bool makeBonus;
	bool makeDungeons;
	bool makeCaves;
    int terrainBuilder;
	short gameMode;
	int worldType;

    short generateSelectPose;

	//game version
	short currentVersion;

	int tpCurrent;
	int tpMax;
	int tpEnd;
	int tpStart;
	int tpPos;
	int tpSelectPos;

private:

	void ScanSaveFiles(const char* dirName);
	void ScanTexturePacks(const char* dirName);
	
	inline bool fileExists(const std::string& name);
	int fileSize(const std::string& name);

    unsigned int hash(const char* s, unsigned int seed);

	InitMenu initMenu;

private:

    typedef struct Statistics
    {
        unsigned short blockPlaced;
        unsigned short blockDestroyed;
        unsigned short daysInGame;
        unsigned short minutesPlayed;
        unsigned short itemsCrafted;
        unsigned short itemsSmelted;
        unsigned short jumps;
        unsigned short dies;
        unsigned short foodEaten;
        unsigned short badlyFalls;
        unsigned short blocksWalked;
        unsigned short treesGrowned;
        unsigned short cropsGrowned;
        unsigned short soilPlowed;
        unsigned short timeInWater;
        unsigned short timeInAir;
        unsigned short damageRecieved;
    } st;

    typedef struct Options
    {
        bool useMipsTexturing;
        bool detailedSky;
        bool fastRendering;
        bool newSprintOption;
        bool freezeDayTime;
        bool sounds;
        bool music;
        bool autoJump;
        bool worldBlockAnimation;
        bool fogRendering;
        bool smoothLighting;
        bool particles;
        bool guiDrawing;
        bool buttonsDrawing;

        float fov;
        char horizontalViewDistance;
        char verticalViewDistance;
        int difficult;
    } opt;

	st mainStatistics;
    opt mainOptions;
};

#endif
