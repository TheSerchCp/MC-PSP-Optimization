#ifndef DRAWWORLDMENU_H_
#define DRAWWORLDMENU_H_

#include <stdlib.h>

#include <include/Aurora/Utils/StateManager.h>
#include <Aurora/Utils/GameState.h>
#include <Minecraft/Screens/StateMenu.h>
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

#include <fstream>
#include <iostream>

#include <dirent.h>
#include <fcntl.h>
#include <errno.h>

#ifdef __PSP__
#include <sys/stat.h>
#endif

using namespace Aurora::Graphics;
using namespace Aurora::Utils;
using namespace Aurora::System;
using namespace Aurora;



class WorldMenu : public StateMenu
{
public:
    void Init();
    void Draw() ;
private:
    void LoadResources();
    void InitializeStateVariables();
      void DrawMenuOptions();
      void DrawSelectedWorldInfo();
      void DrawTextButtons();
      void DrawParametricView();
      void Clean();
};

#endif