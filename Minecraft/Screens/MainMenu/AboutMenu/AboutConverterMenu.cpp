#include "AboutConverterMenu.h"
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

#define default_size 0.5
#define default_big_size 0.687

void AboutConverterMenu::Init() {
    Clean();
    LoadResources();  // Cargar los recursos necesarios
    InitializeStateVariables();  // Inicializar variables de estado
}

void AboutConverterMenu::LoadResources() {
    // Cargar los sprites específicos para la pantalla "Converter"
    backSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Dirt), 0, 0, 32, 32);
    buttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 0, 95, 12); // stand
    sbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 12, 95, 12); // stand selected
}

void AboutConverterMenu::InitializeStateVariables() {
    converterPos = 0;
    schematicExists = false;
    errorType = 0;
    newW_deleteCaves = false;
    newW_gameMode = SURVIVAL;
}

void AboutConverterMenu::Draw() {
    DrawBackground();
    DrawConverterOptions();
    DrawConverterText();
}

void AboutConverterMenu::DrawConverterOptions() {
    posDrawBt drawBt;
    
    btScale scale;
        // Definir la escala
    scale.X = 2;
    scale.Y = 2;

    // Opciones del menú
    drawBt.button.posX = 240;
    drawBt.button.posY = 130;
    drawBt.txt.posX = 240;
    drawBt.txt.posY = 140;
    DrawButton(drawBt, scale, false, "");

   drawBt.button.posX = 240;
    drawBt.button.posY = 165;
    drawBt.txt.posX = 240;
    drawBt.txt.posY = 175;
    DrawButton(drawBt, scale, false, "");

   drawBt.button.posX = 240;
    drawBt.button.posY = 200;
    drawBt.txt.posX = 240;
    drawBt.txt.posY = 210;
    DrawButton(drawBt, scale, false, "");

     drawBt.button.posX = 240;
    drawBt.button.posY = 245;
    drawBt.txt.posX = 240;
    drawBt.txt.posY = 255;
    DrawButton(drawBt, scale, false, "");

    // Dibujar el botón seleccionado
    float y_pos = 130;
    if (converterPos == 1) {
        y_pos = 165;
    } else if (converterPos == 2) {
        y_pos = 200;
    } else if (converterPos == 3) {
        y_pos = 245;
    }
    drawBt.button.posX = 240;
    drawBt.button.posY = y_pos;
    drawBt.txt.posX = 240;
    drawBt.txt.posY = y_pos + 10;
    DrawSButton(drawBt, scale, true, "");
}

void AboutConverterMenu::DrawConverterText() {
    // Dibujo de texto
    if (mRender->GetFontLanguage() == ENGLISH) {
        if (schematicExists) {
            DrawText(240, 60, GU_COLOR(0.1, 0.9, 0.1, 1), default_size, "world.schematic exists!");
        } else {
            DrawText(240, 60, GU_COLOR(0.9, 0.1, 0.1, 1), default_size, "world.schematic doesn't exist!");
        }
        if (errorType == 1) {
            DrawText(240, 80, GU_COLOR(0.9, 0.1, 0.1, 1), default_size, "invalid schematic size");
        } else {
            DrawText(240, 80, GU_COLOR(0.9, 0.1, 0.1, 1), default_size, "process of conversion can take about 1 minute");
        }

        if (newW_deleteCaves) {
            DrawText(240, 114, GU_COLOR(0.5, 0.5, 0.5, 1), 0.35, "recommended for optimizing normal maps");
            DrawTextLabel(240, 139, "Clean caves: Enabled", converterPos == 0);
        } else {
            DrawText(240, 114, GU_COLOR(0.5, 0.5, 0.5, 1), 0.35, "recommended for competitive maps [skywars, uhc, etc]");
            DrawTextLabel(240, 139, "Clean caves: Disable", converterPos == 0);
        }

        if (newW_gameMode == SURVIVAL) {
            DrawTextLabel(240, 174, "Game Mode: Survival", converterPos == 1);
        } else if (newW_gameMode == CREATIVE) {
            DrawTextLabel(240, 174, "Game Mode: Creative", converterPos == 1);
        }

        DrawTextLabel(240, 209, "Try to convert", converterPos == 2);
        DrawTextLabel(240, 254, "Cancel", converterPos == 3);

        DrawText(240, 29, GU_COLOR(1, 1, 1, 1), default_size, "Converter");
    } else if (mRender->GetFontLanguage() == SPANISH) {
        if (schematicExists) {
            DrawText(240, 60, GU_COLOR(0.1, 0.9, 0.1, 1), default_size, "world.schematic existe!");
        } else {
            DrawText(240, 60, GU_COLOR(0.9, 0.1, 0.1, 1), default_size, "world.schematic no existe!");
        }
        if (errorType == 1) {
            DrawText(240, 80, GU_COLOR(0.9, 0.1, 0.1, 1), default_size, "Tamano de schematic no compatible");
        } else {
            DrawText(240, 80, GU_COLOR(0.9, 0.1, 0.1, 1), default_size, "el proceso de conversion puede durar 1 minuto!");
        }

        if (newW_deleteCaves) {
            DrawText(240, 114, GU_COLOR(0.5, 0.5, 0.5, 1), 0.35, "recomendado para optimizar mapas normales");
            DrawTextLabel(240, 139, "Cuevas: Enabled", converterPos == 0);
        } else {
            DrawText(240, 114, GU_COLOR(0.5, 0.5, 0.5, 1), 0.35, "recomendado para mapas competitivos [skywars, uhc, etc]");
            DrawTextLabel(240, 139, "Cuevas: Disable", converterPos == 0);
        }

        if (newW_gameMode == SURVIVAL) {
            DrawTextLabel(240, 174, "Game Mode: Survival", converterPos == 1);
        } else if (newW_gameMode == CREATIVE) {
            DrawTextLabel(240, 174, "Game Mode: Creativo", converterPos == 1);
        }

        DrawTextLabel(240, 209, "Convertir", converterPos == 2);
        DrawTextLabel(240, 254, "Regresar", converterPos == 3);

        DrawText(240, 29, GU_COLOR(1, 1, 1, 1), default_size, "Convertidor");
    }
}

void AboutConverterMenu::Clean(){
    delete backSprite;
    delete buttonSprite;
    delete sbuttonSprite;
}