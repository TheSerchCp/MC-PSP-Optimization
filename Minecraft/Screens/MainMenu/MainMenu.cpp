#include "MainMenu.h"
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

void MainMenu::Init()
{
    LoadResources();
    InitializeStateVariables();
        bx = 240;
    by = 136;
    directionx = rand() % 2;
    directiony = rand() % 2;
}

void MainMenu::LoadResources()
{
    MinecraftSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Minecraft), 0, 0, 320, 90);
    skinSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 36, 60, 12, 12);
    lenguageSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 12, 60, 12, 12);
    sskinSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 48, 60, 12, 12);
    slenguageSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 24, 60, 12, 12);
    backgroundSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::panorama));
    
    buttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 0, 95, 12); // stand
    buttonSmallSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 0, 95, 12); // stand
    sbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 12, 95, 12); // stand selected
    sbuttonSmallSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 12, 95, 12); // stand selected
    
    ///*-----STEVE MODEL-----*///
    steveHead = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve), 8, 8, 8, 8);
    steveHeadCapa = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve), 40, 8, 8, 8);
    steveBody = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve), 20, 20, 8, 12);
    steveHand = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve), 44, 20, 4, 12);
    steveLeg = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Steve), 4, 20, 4, 12);
}


void MainMenu::InitializeStateVariables()
{
    directionx = false;
    directiony = false;
    bx = 0.0f;
    selectPos = 0;
    splashSize = 0.0f;
}

void MainMenu::Draw(){

}