#include "WorldMenu.h"
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
#define SURVIVAL 0
#define CREATIVE 1
#define HARDCORE 2




void WorldMenu::Init()
{
    Clean();
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
     saveSubmenu = false;          // No estamos en un submenú inicialmente
    saveSubMenuSelect = 2;        // Posición predeterminada del submenú
    loadSelectPos = 0;            // Posición de selección inicial
    loadSavePos = 0;              // Posición inicial de guardado
    loadSaveStart = 0;            // Inicio de los archivos guardados a mostrar
    loadSaveMax = 4;              // Número máximo de archivos guardados a mostrar
    loadSaveEnd = 0; // Fin de los archivos guardados
    bx = 240;                     // Posición inicial del fondo en el eje X
    directionx = true;            // Dirección inicial del movimiento en X
    directiony = true;   
    makeTrees = true;
    makeDungeons = true;
    makeBonus = false;
    makeCaves = true;
    generateSelectPose = 0;
    gameMode = SURVIVAL;
    worldType = 0; // default
    newWorldName = "New World";
    newWorldSeed = "";
     seed_1 = 0;
}

void WorldMenu::Draw() {
    DrawBackground();
    DrawMenuOptions();
    DrawSelectedWorldInfo();
    DrawTextButtons();
}


void WorldMenu::DrawMenuOptions() {
    posDrawBt drawBt;
    btScale scale;
    // Definir la escala
    scale.X = 2;
    scale.Y = 2;

    if (saveSubmenu) {
       drawBt.button.posX = 240;
        drawBt.button.posY = 235;
        drawBt.txt.posX = 240;
        drawBt.txt.posY = 245;
        DrawButton(drawBt, scale, false, "Yes");

             drawBt.button.posX = 240;
        drawBt.button.posY = 260;
        drawBt.txt.posX = 240;
        drawBt.txt.posY = 270;
        DrawButton(drawBt, scale, false, "No");
    } else {
        if (!saveFilesList.empty()) {
      drawBt.button.posX = 120;
            drawBt.button.posY = 222;  // play selected world
            drawBt.txt.posX = 120;
            drawBt.txt.posY = 232;
            DrawButton(drawBt, scale, loadSelectPos == 0, "Play Selected World");

                     drawBt.button.posX = 67.75f;
            drawBt.button.posY = 255;  // rename
            drawBt.txt.posX = 67.75f;
            drawBt.txt.posY = 265;
            DrawSmallButton(drawBt, scale, loadSelectPos == 1, "Rename");

                   drawBt.button.posX = 172.25f;
            drawBt.button.posY = 255;  // delete
            drawBt.txt.posX = 172.25f;
            drawBt.txt.posY = 265;
            DrawSmallButton(drawBt, scale, loadSelectPos == 2, "Delete");
        } else {
      drawBt.button.posX = 120;
            drawBt.button.posY = 222;  // play selected world
            drawBt.txt.posX = 120;
            drawBt.txt.posY = 232;
            DrawNButton(drawBt, scale, loadSelectPos == 0, "Play Selected World");

            drawBt.button.posX = 67.75f;
            drawBt.button.posY = 255;  // rename
            drawBt.txt.posX = 67.75f;
            drawBt.txt.posY = 265;
            DrawNButtonSmall(drawBt, scale, loadSelectPos == 1, "Rename");

          drawBt.button.posX = 172.25f;
            drawBt.button.posY = 255;  // delete
            drawBt.txt.posX = 172.25f;
            drawBt.txt.posY = 265;
            DrawNButtonSmall(drawBt, scale, loadSelectPos == 2, "Delete");
        }

       drawBt.button.posX = 360;
        drawBt.button.posY = 222;  // create new world
        drawBt.txt.posX = 360;
        drawBt.txt.posY = 232;
        DrawButton(drawBt, scale, loadSelectPos == 3, "Create New World");

          drawBt.button.posX = 360;
        drawBt.button.posY = 255;  // cancel
        drawBt.txt.posX = 360;
        drawBt.txt.posY = 265;
        DrawButton(drawBt, scale, loadSelectPos == 4, "Cancel");
    }
}

void WorldMenu::DrawSelectedWorldInfo() {
    posDrawBt drawBt;
    btScale scale;
    bool smallButton = false;

// Definir la escala
    scale.X = 2;
    scale.Y = 2;

    if (saveSubmenu) {
       drawBt.button.posX = 240;
        drawBt.button.posY = static_cast<float>(saveSubMenuSelect * 25) + 210;
        drawBt.txt.posX = 240;
        drawBt.txt.posY = static_cast<float>(saveSubMenuSelect * 25) + 220;
        DrawSButton(drawBt, scale, false, "");
    } else {
        switch (loadSelectPos) {
            case 0:
                drawBt.button.posX = 120;
                drawBt.button.posY = 222;
                drawBt.txt.posX = 120;
                drawBt.txt.posY = 232;
                DrawSButton(drawBt, scale, true, "Play Selected World");
                break;
            case 1:
                drawBt.button.posX = 67.75f;
                drawBt.button.posY = 255;
                drawBt.txt.posX = 67.75f;
                drawBt.txt.posY = 265;
                smallButton = true;
                DrawSButtonSmall(drawBt, scale, true, "Rename");
                break;
            case 2:
                drawBt.button.posX = 172.25f;
                drawBt.button.posY = 255;
                drawBt.txt.posX = 172.25f;
                drawBt.txt.posY = 265;
                smallButton = true;
                DrawSButtonSmall(drawBt, scale, true, "Delete");
                break;
            case 3:
               drawBt.button.posX = 360;
                drawBt.button.posY = 222;
                drawBt.txt.posX = 360;
                drawBt.txt.posY = 232;
                DrawSButton(drawBt, scale, true, "Create New World");
                break;
            case 4:
               drawBt.button.posX = 360;
                drawBt.button.posY = 255;
                drawBt.txt.posX = 360;
                drawBt.txt.posY = 265;
                DrawSButton(drawBt, scale, true, "Cancel");
                break;
        }
    }

    blackBackground->Draw();

    if (!saveFilesList.empty()) {
        for (int i = loadSaveStart; i < loadSaveMax; i++) {
           drawBt.button.posX = 46;
            drawBt.button.posY = static_cast<float>(56 + (i * 41) - (loadSaveStart * 41));
            drawBt.txt.posX = 46;
            drawBt.txt.posY = static_cast<float>(66 + (i * 41) - (loadSaveStart * 41));
            DrawMenuHeader("Select World");
        }
    }
}

void WorldMenu::DrawTextButtons() {
    // Este método se encargará de dibujar los textos de los botones, similar a InitMenu y MainMenu
    if (mRender->GetFontLanguage() == ENGLISH) {
        if (saveSubmenu) {
            DrawTextLabel(240, 219, "Are you sure?", saveSubMenuSelect == 0);
            DrawTextLabel(240, 244, "Yes", saveSubMenuSelect == 1);
            DrawTextLabel(240, 269, "No", saveSubMenuSelect == 2);
        } else {
            float buttonTextColor = saveFilesList.empty() ? 0.5f : 1.0f;

            DrawTextLabel(120, 231, "Play Selected World", loadSelectPos == 0);
            DrawTextLabel(67.75f, 264, "Rename", loadSelectPos == 1);
            DrawTextLabel(172.25f, 264, "Delete", loadSelectPos == 2);
            DrawTextLabel(360, 231, "Create New World", loadSelectPos == 3);
            DrawTextLabel(360, 264, "Cancel", loadSelectPos == 4);
        }
        DrawMenuHeader("Select World");
    }

    // Se puede agregar lógica similar para el idioma español
    if (mRender->GetFontLanguage() == SPANISH) {
        // Implementar la lógica similar a la del inglés
           if (saveSubmenu) {
            DrawTextLabel(240, 219, "Estas seguro?", saveSubMenuSelect == 0);
            DrawTextLabel(240, 244, "Si", saveSubMenuSelect == 1);
            DrawTextLabel(240, 269, "No", saveSubMenuSelect == 2);
        } else {
            float buttonTextColor = saveFilesList.empty() ? 0.5f : 1.0f;

            DrawTextLabel(120, 231, "Jugar Mundo Seleccionado", loadSelectPos == 0);
            DrawTextLabel(67.75f, 264, "Renombrar", loadSelectPos == 1);
            DrawTextLabel(172.25f, 264, "Eliminar", loadSelectPos == 2);
            DrawTextLabel(360, 231, "Crear Mundo Nuevo", loadSelectPos == 3);
            DrawTextLabel(360, 264, "Cancelar", loadSelectPos == 4);
        }
        DrawMenuHeader("Seleccionar Mundo");
    }
}

void WorldMenu::Clean(){
       delete backSprite;
    delete buttonSprite;
    delete buttonSmallSprite;
    delete nbuttonSprite;
    delete nbuttonSmallSprite;
    delete sbuttonSprite;
    delete sbuttonSmallSprite;
    delete blackBackground;
    delete menuSprite;
    delete smenuSprite;
}