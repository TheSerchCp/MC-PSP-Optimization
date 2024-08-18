#include <Minecraft/Screens/baseScreen.h>
#include <Minecraft/StateOptions.h>
#include <Minecraft/LoadingScreen.h>
#include <Minecraft/InputHelper.h>
#include <Minecraft/TextureHelper.h>
#include <Aurora/System/NetworkManager.h>
#include <zlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>


using namespace Aurora::Graphics;
using namespace Aurora::Utils;
using namespace Aurora::System;
using namespace Aurora;

BaseScreen::BaseScreen()
{

}

BaseScreen::~BaseScreen()
{

}

void BaseScreen::InitScreen()
{
    //start rendering
    mRender->StartFrame(1,1,1);
	
}


