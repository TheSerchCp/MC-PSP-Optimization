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

#define ENGLISH 1
#define SPANISH 2

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

    buttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 0, 95, 12);        // stand
    buttonSmallSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 0, 95, 12);   // stand
    buttonSmallSprite->Scale(0.45f,1.0f);
    sbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 12, 95, 12);      // stand selected
    sbuttonSmallSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 12, 95, 12); // stand selected
    sbuttonSmallSprite->Scale(0.45f,1.0f);

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

void MainMenu::Draw()
{
    DrawBackground();
    DrawMinecraft(240, 40);
    DrawButton({{240, 110}, {240, 119}},{2,2}, selectPos == 0, "Play");
    DrawButton({{240, 140}, {240, 149}},{2,2}, selectPos == 0, "Options");
    DrawSmallButton({{188, 170}, {188, 179}},{2,2}, selectPos == 0, "About");
    DrawSmallButton({{292, 170}, {292, 179}},{2,2}, selectPos == 0, "Texture Pack");
    DrawSmallButton({{188, 200}, {188, 209}},{2,2}, selectPos == 0, "More");
    DrawSmallButton({{292, 200}, {292, 209}},{2,2},  selectPos == 0,"Quit");
    DrawSkin(130, 170);
    DrawLanguage(130, 200);

    // Validación de ingles o español, solo si son 2 idiomas.
    switch (selectPos)
    {
    case 0:
        DrawSButton({{240, 100}, {240, 119}},{2,2}, selectPos == 0, RenderManager::InstancePtr()->GetFontLanguage() == ENGLISH ? "Play" : "Jugar");
        break;
    case 1:
        DrawSButton({{240, 140}, {240, 149}},{2,2}, selectPos == 1, RenderManager::InstancePtr()->GetFontLanguage() == ENGLISH ? "Options" : "Opciones");
        break;
    case 2:
        DrawSButton({{188, 170}, {188, 179}},{2,2}, selectPos == 2, RenderManager::InstancePtr()->GetFontLanguage() == ENGLISH ? "About" : "Sobre");
        break;
    case 3:
        DrawSButton({{292, 170}, {292, 179}},{2,2}, selectPos == 3, RenderManager::InstancePtr()->GetFontLanguage() == ENGLISH ? "Textures" : "Texturas");
        break;
    case 4:
        DrawSButton({{188, 200}, {188, 209}},{2,2}, selectPos == 4, RenderManager::InstancePtr()->GetFontLanguage() == ENGLISH ? "More" : "Más");
        break;
    case 5:
        DrawSButton({{292, 200}, {292, 209}},{2,2}, selectPos == 5, RenderManager::InstancePtr()->GetFontLanguage() == ENGLISH ? "Quit" : "Salir");
        break;
    case 6:
        DrawSSkin(130, 170);
        break;
    default:
        DrawSLanguage(130, 200);
        break;
    }
    // Pintar a steve en posiciones correspondientes {head},{headCapa},{body},{leg1},{leg2},{hand1},{hand2}
    DrawSteve({{366, 128}, {366, 128}, {366, 158}, {360, 194}, {372, 194}, {348, 158}, {384, 158}});

    // Splash
    splashSize += 0.13f;
    if (splashSize > 2 * PI)
    {
        splashSize = 0.0f;
    }
    DrawText(420, 272, GU_COLOR(1, 1, 1, 1), 0.35, "Minecraft PSP BETA By Serch");

    switch (SplashNumber)
    {
    case 0:
        DrawText(328, 66, GU_COLOR(1, 1, 0, 1), 0.35 + sinf(splashSize) * 0.02f, "More polygons!");
        break;
    case 1:
        DrawText(328, 66, GU_COLOR(1, 1, 0, 1), 0.35 + sinf(splashSize) * 0.02f, "Find dungeons!");
        break;
    case 2:
        DrawText(328, 66, GU_COLOR(1, 1, 0, 1), 0.35 + sinf(splashSize) * 0.02f, "Kaaneeeedaaaa!");
        break;
    case 3:
        DrawText(328, 66, GU_COLOR(1, 1, 0, 1), 0.35 + sinf(splashSize) * 0.02f, "Music by C418!");
        break;
    case 4:
        DrawText(328, 66, GU_COLOR(1, 1, 0, 1), 0.35 + sinf(splashSize) * 0.02f, "Ride the pig!");
        break;
    case 5:
        DrawText(328, 66, GU_COLOR(1, 1, 0, 1), 0.35 + sinf(splashSize) * 0.02f, "Not approved by Mojang!");
        break;
    case 6:
        DrawText(328, 66, GU_COLOR(1, 1, 0, 1), 0.35 + sinf(splashSize) * 0.02f, "Do not distribute!");
        break;
    case 7:
        DrawText(328, 66, GU_COLOR(1, 1, 0, 1), 0.35 + sinf(splashSize) * 0.02f, "Spiders everywhere!");
        break;
    case 8:
        DrawText(328, 66, GU_COLOR(1, 1, 0, 1), 0.35 + sinf(splashSize) * 0.02f, "Sublime!");
        break;
    case 9:
        DrawText(328, 66, GU_COLOR(1, 1, 0, 1), 0.35 + sinf(splashSize) * 0.02f, "12345 is a bad password!");
        break;
    case 10:
        DrawText(328, 66, GU_COLOR(1, 1, 0, 1), 0.35 + sinf(splashSize) * 0.02f, "Follow the train, CJ!");
        break;
    case 11:
        DrawText(328, 66, GU_COLOR(1, 1, 0, 1), 0.35 + sinf(splashSize) * 0.02f, "Exploding creepers!");
        break;
    case 12:
        DrawText(328, 66, GU_COLOR(1, 1, 0, 1), 0.35 + sinf(splashSize) * 0.02f, "RegenStudio = new Regen();");
        break;
    }
}