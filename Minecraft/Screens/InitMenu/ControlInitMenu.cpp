#include "ControlInitMenu.h"


using namespace Aurora::Graphics;
using namespace Aurora::Utils;
using namespace Aurora::System;
using namespace Aurora;


void ControlInitMenu::ControlSystemInit(StateManager* sManager,	SystemManager *mSystemMgr,SoundManager *mSoundMgr,int selectPos,short menuState,int SplashNumber)
{

      //up, down
        if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
        {
            selectPos--;
            if(selectPos < 0)
                selectPos = 1;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
        {
            selectPos++;
            if(selectPos > 1)
                selectPos = 0;
			mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            RenderManager::InstancePtr()->defaultFontType = selectPos+1;
            RenderManager::InstancePtr()->SetDefaultFont();
            selectPos = 0;
            menuState = 0;

            SplashNumber = rand() % 13;
			
			mSoundMgr->PlayRandomMenu(); //MENU
        }
}