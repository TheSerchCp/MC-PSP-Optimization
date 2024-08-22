#include <Minecraft/Screens/InitMenu/InitMenu.h>
#include <Minecraft/TextureHelper.h>
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

using namespace Aurora::Graphics;
using namespace Aurora::Utils;
using namespace Aurora::System;
using namespace Aurora;


void InitMenu::Init()
{
    Clean();
    LoadResources();
    InitializeStateVariables();
}

void InitMenu::LoadResources()
{
    // Inicializar los sprites
    buttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 0, 95, 12); // stand
    // buttonSprite->SetPosition(240,150);
    sbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 12, 95, 12); // stand selected
    // sbuttonSprite->SetPosition(240,150);
    backSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Dirt), 0, 0, 32, 32);
}

void InitMenu::InitializeStateVariables()
{
    selectPos = 0;
    menuState = -1;
    // start rendering
    mRender->StartFrame(1, 1, 1);
}

void InitMenu::Draw()
{
     // Definir la estructura para cada botón
    posDrawBt button1Pos = {{240, 120}, {240, 129}};
    posDrawBt button2Pos = {{240, 160}, {240, 169}};
    posDrawBt selectButtonPos = {{240, static_cast<float>((selectPos * 40) + 120)}, {240, 24}};
      // Definir la escala
    btScale buttonScale = {2, 2};
    DrawBackground();
    DrawButton(button1Pos,buttonScale,selectPos == 0,"English");
    DrawButton(button2Pos,buttonScale,selectPos == 0,"Spanish");
    DrawSButton(selectButtonPos,buttonScale,selectPos == 3,"Select your Language");
}

void InitMenu::Clean(){
    delete buttonSprite;
    delete sbuttonSprite;
    delete backSprite;
}