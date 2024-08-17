#ifndef CONTROLINITMENU_H_
#define CONTROLINITMENU_H_

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


#include <Minecraft/SoundManager.h>

using namespace Aurora::Graphics;
using namespace Aurora::Utils;
using namespace Aurora::System;
using namespace Aurora;

class ControlInitMenu 
{
    public:
        	void ControlSystemInit(StateManager* sManager,	SystemManager *mSystemMgr,SoundManager *mSoundMgr,int selectPos,short menuState,int SplashNumber);
};

#endif