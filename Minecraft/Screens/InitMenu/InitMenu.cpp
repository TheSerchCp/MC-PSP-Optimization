#include "InitMenu.h"
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
    DrawBackground();
    DrawButton(240,120,selectPos,"English");
    DrawButton(240,120,selectPos,"Spanish");
    DrawSButton(240,(selectPos * 40) + 120,"Select Language");
}
