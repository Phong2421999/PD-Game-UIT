#pragma once
#include "dsutil.h"
#include <unordered_map>
#include "FrameWork//Game.h"
using namespace std;
class SoundController
{
private:
	static bool isMute;
	static float liVolume; // linear volume (NOTE: lVolume value used in IDirectSoundBuffer::SetVolume is logarithmic volume - not linear)
	static CSoundManager dsound;
	static unordered_map<int, CSound*> sounds;

	//static bool  CheckHoldingVolume();
public:
	
	static void LoadResources(LPCSTR soundData);
	static void Play(int id);
	static void PlayLoop(int id);
	/*void Stop(int id);
	static void StopAll();
	static bool CheckIsPlay(int id);
	static 
	static void VolumeUp();
	static void VolumeDown();
	static 
	static void SetMute(bool ismute);
	static static bool IsMute() { return isMute; }
	static 
	static void HandleInput();*/
};



