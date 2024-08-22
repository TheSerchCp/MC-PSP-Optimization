#include "UpdateMenu.h"
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


void UpdateMenu::Init() {
    Clean();
    LoadResources();  // Cargar los recursos necesarios
    InitializeStateVariables();  // Inicializar variables de estado
}

void UpdateMenu::LoadResources() {
    // Cargar los sprites específicos para la pantalla "Update Info"
    backSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Dirt), 0, 0, 32, 32);
    buttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 0, 95, 12); // stand
    sbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 12, 95, 12); // stand selected
    blackBackground = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::background));
}

void UpdateMenu::InitializeStateVariables() {
    donatePos = 0;  // Iniciar en la primera opción del menú "Update Info"
}

void UpdateMenu::Draw() {
    DrawBackground();
    DrawMenuOptions();
    DrawUpdateText();
    DrawTextButtons();
}

void UpdateMenu::DrawMenuOptions() {
    posDrawBt drawBt;
    btScale scale;

   // Definir la escala
    scale.X = 2;
    scale.Y = 2;

    // Dibujar botones
    drawBt.button.posX = 240;
    drawBt.button.posY = 225;
    drawBt.txt.posX = 240;
    drawBt.txt.posY = 235;
    DrawButton(drawBt, scale, false, "Check for update");

   drawBt.button.posX = 240;
    drawBt.button.posY = 255;
    drawBt.txt.posX = 240;
    drawBt.txt.posY = 265;
    DrawButton(drawBt, scale, false, "Back");

 // Dibujar el botón seleccionado
    float y_pos_button = static_cast<float>(donatePos * 30) + 225;
    float y_pos_txt = static_cast<float>(donatePos * 30) + 235;

    drawBt.button.posX = 240;
    drawBt.button.posY = y_pos_button;
    drawBt.txt.posX = 240;
    drawBt.txt.posY = y_pos_txt;
    DrawSButton(drawBt, scale, true, "");  // Texto vacío porque se dibuja por separado
}

void UpdateMenu::DrawUpdateText() {
    // Dibuja los textos específicos de la sección "Update Info"
    if (mRender->GetFontLanguage() == ENGLISH) {
        mRender->SetFontStyle(0.36, GU_COLOR(1, 1, 1, 1), 1, 0x00000000);
        mRender->DebugPrint(30, 40, "-Clouds 3D");
        mRender->DebugPrint(30, 50, "-Fixed some bugs");
        mRender->DebugPrint(30, 60, "-Fixed world generation");
        mRender->DebugPrint(30, 70, "-Legacy Inventory");
        mRender->DebugPrint(30, 80, "-Spanish language updated");
        mRender->DebugPrint(30, 90, "-Fix XP number system");
        mRender->DebugPrint(30, 100, "-New font");
    }

    // Lógica para el idioma español
    if (mRender->GetFontLanguage() == SPANISH) {
        mRender->SetFontStyle(0.36, GU_COLOR(1, 1, 1, 1), 1, 0x00000000);
        mRender->DebugPrint(30, 40, "-Clouds 3D");
        mRender->DebugPrint(30, 50, "-Fixed some bugs");
        mRender->DebugPrint(30, 60, "-Fixed world generation");
        mRender->DebugPrint(30, 70, "-Legacy Inventory");
        mRender->DebugPrint(30, 80, "-Spanish language updated");
        mRender->DebugPrint(30, 90, "-Fix XP number system");
        mRender->DebugPrint(30, 100, "-New font");
    }
}

void UpdateMenu::DrawTextButtons() {
    // Dibujar los botones de texto (Nothing Here/Cancel) en función de la posición seleccionada
    DrawTextLabel(240, 234, mRender->GetFontLanguage() == ENGLISH ? "Nothing Here" : "Como jugar", donatePos == 0);
    DrawTextLabel(240, 264, mRender->GetFontLanguage() == ENGLISH ? "Cancel" : "Regresar", donatePos == 1);
    DrawMenuHeader(mRender->GetFontLanguage() == ENGLISH ? "Whats new?!" : "Novedades!");
}

void UpdateMenu::Clean(){
        // Liberar recursos si es necesario
    delete backSprite;
    delete buttonSprite;
    delete sbuttonSprite;
    delete blackBackground;
}