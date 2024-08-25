#ifndef MANAGEPLAYERSTATE_H_
#define MANAGEPLAYERSTATE_H_

#include <Aurora/Utils/StateManager.h>
#include <Aurora/Utils/GameState.h>

#include <math.h>
#include <psptypes.h>

#include <Aurora/Graphics/RenderManager.h>
#include <Aurora/Utils/Logger.h>
#include <Aurora/Utils/Timer.h>
#include <Aurora/System/SystemManager.h>
#include <Aurora/Graphics/Models/ObjModel.h>
#include <Aurora/Graphics/Camera.h>
#include <Aurora/Graphics/Sprite.h>

#include <Aurora/Graphics/Effects/InventoryPlayer.h>
#include <Aurora/Graphics/Effects/SkyLight.h>
#include <Aurora/Graphics/Effects/SnowBall2.h>
#include <Aurora/Graphics/Effects/Arrow2.h>
#include <Aurora/Graphics/Effects/SkyBox.h>
#include <Aurora/Graphics/Effects/Destroyer.h>
#include <Aurora/Graphics/Effects/StarsBox.h>
#include <Aurora/Graphics/Effects/Drop.h>
#include <Aurora/Graphics/Effects/Particle.h>

#include <Minecraft/World/ChunkDataProvider.h>

#include <Minecraft/Mobs/Zombie2.h>
#include <Minecraft/Mobs/Spider2.h>
#include <Minecraft/Mobs/Spidercave2.h>
#include <Minecraft/Mobs/Cow2.h>
#include <Minecraft/Mobs/Chicken2.h>
#include <Minecraft/Mobs/Pig2.h>
#include <Minecraft/Mobs/Creeper2.h>
#include <Minecraft/Mobs/Enderman.h>
#include <Minecraft/Mobs/Sheep2.h>
#include <Minecraft/Mobs/LameMob.h>

#include <Minecraft/CraftWorld2.h>
#include <Minecraft/InputHelper.h>
#include <Minecraft/SoundManager.h>
#include <Minecraft/Chest2.h>
#include <Minecraft/Furnace2.h>
#include <Minecraft/NoteBlockEntity.h>
#include <Minecraft/JukeboxEntity.h>
#include <Minecraft/Mobs/MonsterSpawnerEntity.h>
#include <Minecraft/ItemFrameEntity.h>
#include <Minecraft/Screens/StateMenu.h>

#include <Minecraft/Mobs/LameFunctions.h>

using namespace Aurora::Graphics;
using namespace Aurora::Utils;
using namespace Aurora::System;
using namespace Aurora;


class ManagePlayerState : public CGameState
{
public:
	ManagePlayerState();
	virtual ~ManagePlayerState();

	void Init();
	void Init(char gameMode);
	void InitParametric(bool makeTrees,bool makeDungeons,bool makeBonus,bool makeCaves, unsigned int seedIII, int worldType, char gameMode);
	void Enter();
	void CleanUp();

	void Pause();
	void Resume();
	void LoadTextures(char gameMode);
	void LoadTexturesCreative(float invGuiScale,int utilsSize,float utilScale);
    void LoadTexturesSurvival(int iconsSize,int utilsSize);

	void HandleEventsSurvival(StateManager* sManager);
	void HandleEventsCreative(StateManager* sManager);
	void HandleEvents(StateManager* sManager);
	void Update(StateManager* sManager);
	void Draw(StateManager* sManager);
	void Update(StateManager* sManager,char gameMode);
	void Draw(StateManager* sManager,char gameMode);

	void LoadMap(std::string fileName,bool compressed,char gameMode);
	void SetWorldAndSaveName(std::string worldName,std::string fileName);
	void InitCamera();

	//keys helpers
	bool keyPressed(int currentKey);
	bool keyHold(int currentKey);
	void PutInInventory(int id, int num, bool st);

private:

	void advancedBlit(int sx, int sy, int sw, int sh, int dx, int dy, int slice);
	bool TryToMove(Vector3 moveVector,float dt,char gameMode);
	void SetDayTimeAfterLoad();
	void CraftItem2x2();
	void CraftItem3x3();

	void DrawSlotItem(short& itemId);
	void DrawSlotAmount(short& itemAmount, bool& itemStackable);
	void DrawSlotToolPoints(short& itemAmount, bool& itemStackable);

	void CheckForFurnFuel(Furnace* Fur);
	void CheckForFurnWorking(Furnace* Fur);
	void ReadyFurnSmelting(Furnace* Fur);

    int FindFurnaceId(int x, int y, int z);
	int FindChestId(int x, int y, int z);

	void HungerTime();
	void FireBurning(); //delete
	void HealthTime();
	void OxygenTime();
	void HurtPlayer(float damage);
	void HurtPlayerConsiderArmor(float damage);

private:

    double time12;

	RenderManager *mRender;
	SystemManager *mSystemMgr;
	SoundManager *mSoundMgr;
	InputHelper *mIhelper;
	Camera *fppCam;

	std::string saveFileName;
	int freeMemory;
	float freeMemoryTimer;

    float cloudsOffset;

	CraftWorld *mWorld;

	StateMenu *mMenu;

    SkyLight *skyLight;
    SkyLight *skyMoonLight;
    SkyBox *skyBox;
    Destroyer *destroyer;
    StarsBox *starsBox;
    InventoryPlayer* invPlayer;

    double temp_total_time_ms;

    float starsAngle;
    bool check;
    bool cycle;
    bool loadReady;
	bool startDt;
	bool tryToDt;
    float dT;
    float dET;          // ����� �������
    char dStd;          // ������ �������� ���������� �����
    float last_HP;

    float sleepMessageTime;
    int sleepMessageType;
    float sleepTime;

    bool hurt;
    float hurt_time;
    float dtt;

    float furnaceTimes;

    Vector3 testPos1;
	Vector3 cubePos;

	bool showCube;

    short craftSlotId[4];
    short craftSlotAm[4];
    bool craftSlotSt[4];

    short craftSlotId3[9];
    short craftSlotAm3[9];
    bool craftSlotSt3[9];

    short creativeSlotId[27];

    short craftItemId;
    short craftItemAm;
    bool craftItemSt;

    short craftItemId3;
    short craftItemAm3;
    bool craftItemSt3;

    float musicTimeGo;
    float musicTime;

    char chestId;
    char furnaceId;

    Chest* UseChest;
    Furnace* UseFurnace;
	//zmienne do poruszania
	float GRAVITY;
	float JUMPVELOCITY;
	float CLIMBVELOCITY;

	Vector3 playerVelocity;
	Vector3 playerPosition;
	Vector3 newPlayerPos;
	Vector3 oldPlayerPos;

	bool footInFire;
	bool playerInCobweb;
	bool moveForward;
	bool walkingOnGround;
	bool moving;
	bool jumping;
	bool headInWater;
	bool footInWater;
	bool headInLava;
	bool InHellPortal;
	bool footInLava;
	bool touchingCactus;
	bool burning;

	bool HungerPoisoned;
	bool HPPoisoned;

	bool armorEn;
	bool invEn;
	bool upEn;
	bool craft3xEn;
	bool chestEn;
	bool furnaceEn;
	bool sprint;
	bool crouch;

	bool usingSlider; // craive vars
	bool onDestroySlot;

	bool showSlotName;
	float showSlotTimer;
	float showSlotTimerMax;
	int slotId;

    char barPosition;
    int invXPosition;
    int invYPosition;
    float invSteveAngle;

	char tempXFurnace;
    char tempYFurnace;
    bool tempUpFurnace;

    char tempXInv;
    char tempYInv;
    bool tempUpInv;

    char tempXCT;
    char tempYCT;
    bool tempUpCT;

	char tempXChest;
    char tempYChest;
    bool tempUpChest;

	int ram1;
	int ram2;
	
	int HGP;
	int HPE;

    float tickCave; //cave sounds timer
	float tickHunger;
	float tickHealth;
	float tickChunk;
	float tickLavaDamage;
	float tickFireDamage; //fire
	float tickCactusDamage;
	float tickOS;
	float tickFR;
	float tickHungerPoisoned;
	float tickHPveneno;
	float tickFlyTime;
	float tickShowFlymodeMessage;
	float tickSprintTime;
	float tickShowSlotName;
	float rainSoundFrequency;

	short chunks; // 0 - 7;

	float tutorialTimer;

	float inputDiskNameTimer;
	std::string inputDiskName;

    int chunkId;
	
	//int EXPcount;

	Timer mTimer;
	float dt;

	//int texture[16];
	int barItems;
	int texture;
	int texture_mips;
	int waterAnimation;

	unsigned char blue;
	unsigned char red;
	unsigned char black;
	unsigned char stars;

    int invPlayerTex;
    int zombieTex;
	int endermanTex;
    int spiderTex;
    int spidercaveTex;
    int cowTex;
	int chickenTex;
	int pigTex;
    int snowBall4;
	int cloudsTex;
	int clouds2Tex;
	int suntex;
	int moontex;
	int rainTex;
	int grassColorTex;

	unsigned char currentTexture;
	unsigned char timeTexture;

	float pre_fps;
	int average_fps;
	float tick_fps;
	int ticks;

	Sprite *waterScreen;
	Sprite *pumpkinMask;
	Sprite *fireScreen;

    Sprite *invCellSprite;
	Sprite *invSprite;
	Sprite *sliderSprite;
	Sprite *sliderLightedSprite;
    Sprite *crtSprite;
    Sprite *chtSprite;
    Sprite *selectInvSprite;
	Sprite *barSprite;
	Sprite *XPbarSprite;
	Sprite *XPprogressSprite[182];
	Sprite *crossSprite;
	Sprite *lSprite;
	Sprite *l2Sprite;
	Sprite *r2Sprite;
	Sprite *rSprite;
	Sprite *selectSprite;

	Sprite *furArrowSprite[22];
	Sprite *furFireSprite[14];
    Sprite *furSprite;

	Sprite *hpCellSprite;
	Sprite *hpCellSpriteW;
	Sprite *hpSprite;
	Sprite *hpSpriteW;
	Sprite *hpHardSprite;
	Sprite *hpHardSpriteW;
	Sprite *hpHalfSprite;
	Sprite *hpHalfSpriteW;
	Sprite *hpHardHalfSprite;
	Sprite *hpHardHalfSpriteW;
	
	Sprite *hpVenenoSprite;
	Sprite *hpVenenoHalfSprite;
	Sprite *hpVenenoSpriteW;
	Sprite *hpVenenoHalfSpriteW;

	Sprite *hgCellSprite;
	Sprite *hgSprite;
	Sprite *hgHalfSprite;
	
	Sprite *hg2CellSprite;
	Sprite *hg2Sprite;
	Sprite *hg2HalfSprite;
	
	Sprite *bubbleSprite;

    Sprite *arCellSprite;
	Sprite *arSprite;
	Sprite *arHalfSprite;

	Sprite *toolPointSprite[14];
	Sprite *smallToolPointSprite[14];

	float hpAnim;

	float cameraSpeed;
	float cameraMoveSpeed;

	//menu sprites
	Sprite *buttonSprite;
	Sprite *sbuttonSprite;
	Sprite *nbuttonSprite;
	Sprite *moverSprite;

	bool menuOptions;
	char menuState;//0 game,1 menu
	char optionsMenuPos;
	char selectPos;
	char diePos;//muerte

    char statisticsPage;

	//some settings
	bool canFly;
	bool devMode;
	bool analogLeft,analogRight,analogUp,analogDown;

	//for sound of walkinng
	float walkSoundAccu;
	bool  isWalking;

	//Headbob
	bool canHeadBob;
	float bobCycle;
	bool bobType;
	
	float bobCiclo;
	bool bobTipo;
	
	float cubeLight;

    float shift_x;
    float shift_y;
    float idle_y;
	
    float changeY;
    float changeScale;
    int slotForChangeScale;

    float animDest;
    float animSpeed;
    bool animGo;

    bool anim[3];
	bool makeScreen;
	bool dieFactor;

	float angleFactor;

	void SetCreativePage(char page);
    void InitCreativeInventory();

    void DrawText(int x,int y, unsigned int color, float size, const char *message, ...);
    void DrawText2(int x,int y, unsigned int color, float size, const char *message, ...);

    void DrawAmount(int x,int y, int amount);
	
	std::vector<SnowBall2*> mSnowBalls;
	std::vector<Arrow2*> mArrows;
	std::vector<Particle*> mParticles;
	std::vector<int> inventoryItems;

	int creativePage;
    int creativePageMax;
};

#endif
