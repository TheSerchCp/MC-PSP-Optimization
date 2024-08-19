#include "CreateWorld.h"
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

#define ENGLISH 1
#define SPANISH 2

void WorldMenu::Init()
{
    LoadResources();
    InitializeStateVariables();
}

void WorldMenu::LoadResources()
{
    backSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Dirt), 0, 0, 32, 32);
    buttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 0, 95, 12); // stand
    buttonSmallSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 0, 95, 12);   // stand
    buttonSmallSprite->Scale(0.45f,1.0f);
    nbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,24,95,12); // dark
    nbuttonSmallSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons),0,24,95,12); // dark
    nbuttonSmallSprite->Scale(0.45f,1.0f);
    sbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 12, 95, 12);      // stand selected
    sbuttonSmallSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 12, 95, 12); // stand selected
    sbuttonSmallSprite->Scale(0.45f,1.0f);
    smenuSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::DeselectedWorld),0,0,64,64);
    menuSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::World),0,0,64,64);
    
}

void WorldMenu::InitializeStateVariables()
{
      saveSubmenu = false;
      saveSubMenuSelect = 2;
      loadSelectPos = 0;
      loadSavePos = 0;

}

void WorldMenu::Draw()
{
 DrawBackground();

 if(saveSubmenu){ // delete world
    DrawButton({{240,235},{}},{2,2},saveSubMenuSelect = 0,mRender->GetFontLanguage() == ENGLISH ? "Are you sure?" : "¿Estás seguro?");
    DrawButton({{240,260},{}},{2,2},saveSubMenuSelect = 1,mRender->GetFontLanguage() == ENGLISH ? "Are you sure?" : "¿Estás seguro?");
 }else {
    if(saveFilesList.empty() == false){
        DrawButton({{120,222},{}},{2,2},loadSelectPos == 0,"Play Selected World"); //play select world
        DrawSmallButton({{67.75,255}},{2,2},loadSelectPos == 1,"Rename");
        DrawSmallButton({{172.25,255}},{0.45f,1.0f},loadSelectPos == 2,"Delete");
    }else{
        DrawNButton({{120,222}},{2,2},loadSelectPos == 0,"Play selected world");
        DrawNButtonSmall({{67.75,255},{}},{2,2},loadSelectPos == 1, "Rename");
         DrawNButtonSmall({{172.25,255},{}},{2,2},loadSelectPos == 2, "Delete");
    }

    //Right part
    DrawButton({{360,222},{}},{2,2},loadSelectPos == 3,"Create new World");
    DrawButton({{360,255},{}},{2,2},loadSelectPos == 4,"Cancel");
 }

    bool smallButton = false;
    if(saveSubmenu){
        DrawSButton({{240,(saveSubMenuSelect*25) + 210}},{2,2}, saveSubMenuSelect == 1,saveSubMenuSelect == 1 ? "Yes" : saveSubMenuSelect == 2 ? "No" : "")
    }else{
        switch(loadSelectPos)
        {
            case 0: 
            DrawSButton({{120,222},{}},{2,2},loadSelectPos == 0,"");
            break;
            case 1: 
            DrawSButtonSmall({{67.75,255}},{2,2},smallButton == true , "");
            smallButton = true;
            break;
            case 2: 
            DrawSButtonSmall({{172.25,255}},{2,2},smallButton == true , "");
            break;
            case 3: 
            DrawSButton({{360,222},{}},{2,2},smallButton == false,"");
            break;
            case 4: 
            DrawSButton({{360,255},{}},{2,2},smallButton == false,"");
            break;
        }
    }
    

}