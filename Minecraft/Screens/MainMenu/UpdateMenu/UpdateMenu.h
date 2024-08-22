#ifndef DRAWUPDATEMENU_H_
#define DRAWUPDATEMENU_H_

#include <stdlib.h>
#include <Minecraft/Screens/StateMenu.h>
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

class UpdateMenu : public StateMenu {
public:
    void Init();
    void Draw();
    void LoadResources();           // Método para cargar recursos
    void InitializeStateVariables();  // Método para inicializar las variables de estado

private:
    void DrawMenuOptions();
    void DrawUpdateText();
    void DrawTextButtons();
    void Clean();
};

#endif // UPDATEINFOMENU_H_
