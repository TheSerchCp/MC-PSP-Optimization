#include "DrawInitMenu.h"
#include <Minecraft/StateMenu.h>



using namespace Aurora::Graphics;
using namespace Aurora::Utils;
using namespace Aurora::System;
using namespace Aurora;

StateMenu stateMenu;
void DrawInitMenu::DrawSystemInitMenu(StateManager* sManager,Sprite *backSprite,Sprite *buttonSprite,Sprite *sbuttonSprite,int selectPos,float default_size)
{
        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));

        for(int x = 0; x < 8; x++)
        {
            for(int y = 0; y < 5; y++)
            {
                backSprite->SetPosition(x*64,y*64);
                backSprite->Draw();
            }
        }

        // english
        buttonSprite->SetPosition(240,120);
        buttonSprite->Draw();

        // russian
        buttonSprite->SetPosition(240,160);
        buttonSprite->Draw();

        //selected button
        sbuttonSprite->SetPosition(240,(selectPos * 40) + 120);
        sbuttonSprite->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

       stateMenu.DrawText(240, 129, GU_COLOR(1,1,selectPos == 0 ? 0.25f : 1, 1), default_size, "English");
    stateMenu.DrawText(240, 169, GU_COLOR(1,1,selectPos == 1 ? 0.25f : 1, 1), default_size, "Spanish");
    stateMenu.DrawText(240, 24, GU_COLOR(1,1,1,1), default_size, "Select your language");
}