#include "AboutMenu.h"
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

void AboutMenu::Init() {
    Clean();
    LoadResources();
    InitializeStateVariables();  // Llamar a la inicialización de variables de estado
    // Inicializar recursos adicionales si es necesario
}

void AboutMenu::InitializeStateVariables() {
    aboutPos = 0;  // Iniciar en la primera opción del menú "About"
}

void AboutMenu::LoadResources(){

// Cargar los sprites específicos para la pantalla "About"
    backSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Dirt), 0, 0, 32, 32);
    buttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 0, 95, 12); // stand
    sbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 12, 95, 12); // stand selected
    blackBackground = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::background));
}

void AboutMenu::Draw() {
    DrawBackground();
    DrawMenuOptions();
    DrawAboutText();
    DrawTextButtons();
}

void AboutMenu::DrawMenuOptions() {
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
    float y_pos_button = static_cast<float>(aboutPos * 30) + 225;
    float y_pos_txt = static_cast<float>(aboutPos * 30) + 235;
    
    drawBt.button.posX = 240;
    drawBt.button.posY = y_pos_button;
    drawBt.txt.posX = 240;
    drawBt.txt.posY = y_pos_txt;
    DrawSButton(drawBt, scale, true, "");  // Texto vacío porque se dibuja por separado
}

void AboutMenu::DrawAboutText() {
    // Dibuja los textos específicos de la sección "About"
    if (mRender->GetFontLanguage() == ENGLISH) {
        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000000);
        mRender->DebugPrint(40, 60, "Developer  :");
        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000400);
        mRender->DebugPrint(440, 60, "Wandemberg Armijos(RegenStudio)");

        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000000);
        mRender->DebugPrint(40, 80, "Past Modder:");
        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000400);
        mRender->DebugPrint(440, 80, "Kirill Skibin(Woolio)");

        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000000);
        mRender->DebugPrint(40, 100, "Created By :");
        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000400);
        mRender->DebugPrint(440, 100, "Marcin Ploska(Drakon)");

        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000000);
        mRender->DebugPrint(40, 140, "Website:");
        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000400);
        mRender->DebugPrint(440, 140, "vk.com/mine_psp_game");

        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000000);
        mRender->DebugPrint(40, 160, "Donate :");
        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000400);
        mRender->DebugPrint(440, 160, "Paypal.me/Mikegaming210");

        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000000);
        mRender->DebugPrint(40, 180, "Version:");
        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000400);
        mRender->DebugPrint(440, 180, "Minecraft PSP BETA");

        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000000);
        mRender->DebugPrint(40, 200, "Stage  :");
        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000400);
        mRender->DebugPrint(440, 200, "Under Development");
    }

    // Lógica para el idioma español
    if (mRender->GetFontLanguage() == SPANISH) {
        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000000);
        mRender->DebugPrint(40, 60, "Desarrollador:");
        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000400);
        mRender->DebugPrint(440, 60, "Wandemberg Armijos(RegenStudio)");

        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000000);
        mRender->DebugPrint(40, 80, "Past Modder  :");
        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000400);
        mRender->DebugPrint(440, 80, "Kirill Skibin(Woolio)");

        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000000);
        mRender->DebugPrint(40, 100, "Creador por  :");
        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000400);
        mRender->DebugPrint(440, 100, "Marcin Ploska(Drakon)");

        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000000);
        mRender->DebugPrint(40, 140, "SitioWeb:");
        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000400);
        mRender->DebugPrint(440, 140, "vk.com/mine_psp_game");

        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000000);
        mRender->DebugPrint(40, 160, "Donacion:");
        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000400);
        mRender->DebugPrint(440, 160, "Paypal.me/Mikegaming210");

        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000000);
        mRender->DebugPrint(40, 180, "Version :");
        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000400);
        mRender->DebugPrint(440, 180, "Minecraft PSP v3.3.0");

        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000000);
        mRender->DebugPrint(40, 200, "Estado  :");
        mRender->SetFontStyle(0.5, GU_COLOR(1, 1, 1, 1), 2, 0x00000400);
        mRender->DebugPrint(440, 200, "Bajo Desarrollo");
    }
}

void AboutMenu::DrawTextButtons() {
    // Dibujar los botones de texto (converter/cancel) en función de la posición seleccionada
    DrawTextLabel(240, 234, mRender->GetFontLanguage() == ENGLISH ? "Converter" : "Convertidor", aboutPos == 0);
    DrawTextLabel(240, 264, mRender->GetFontLanguage() == ENGLISH ? "Cancel" : "Regresar", aboutPos == 1);
    DrawMenuHeader("About");
}

void AboutMenu::Clean(){
    delete backSprite;
    delete buttonSprite; 
    delete sbuttonSprite;
    delete blackBackground;
}