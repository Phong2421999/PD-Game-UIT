#include "SoundController.h"
#include "FrameWork//debug.h"
#include "tinyxml.h"
#include <string>
#include <atlbase.h>
bool                                SoundController::isMute = false;
float                               SoundController::liVolume = 1.0f;
CSoundManager                       SoundController::dsound;
unordered_map<int, CSound*> SoundController::sounds;

void SoundController::LoadResources(LPCSTR soundData) {
	if (dsound.Initialize(CGame::GetInstance()->GetHWnd(), DSSCL_PRIORITY) != DS_OK)
		MessageBox(NULL, L"Init sound fail", L"Error", MB_OK);
	if (dsound.SetPrimaryBufferFormat(2, 22050, 16) != DS_OK)
		MessageBox(NULL, L"Set sound buffer fail", L"Error", MB_OK);

	TiXmlDocument doc(soundData);
	if (!doc.LoadFile())
	{
		DebugOut(L"Can't read Sound XML file");
		MessageBox(NULL, L"Can't Read XML File", L"Error", MB_OK);
		return;
	}
	else
	{
		DebugOut(L"[INFO]Read XML success\n");
	}
	// get info root
	TiXmlElement* root = doc.RootElement();
	TiXmlElement* soundElems = nullptr;
	TiXmlElement* sound = nullptr;
	// gameObjectId = 0 -- Simon

	for (soundElems = root->FirstChildElement(); soundElems != NULL; soundElems = soundElems->NextSiblingElement())
	{
		

		for (sound = soundElems->FirstChildElement(); sound != NULL; sound = sound->NextSiblingElement())
		{
			int soundId;
			string filePath;
			CSound* waveSound;
			sound->QueryIntAttribute("soundId", &soundId);
			filePath = sound->Attribute("soundPath");
			if (dsound.Create(&waveSound, CA2T(filePath.c_str()), DSBCAPS_CTRLVOLUME) != S_OK)
			{
				DebugOut(L"Create wav fail, id: %d", soundId);
				MessageBox(NULL, L"Create wav fail", L"Error", MB_OK);
			}

			sounds[soundId] = waveSound;
		}
	}
	

}

void SoundController::Play(int id) {
	sounds[id]->Reset();
	sounds[id]->Play(0, 0, LinearToLogVol(liVolume));
}
void SoundController::PlayLoop(int id) {
	sounds[id]->Play(0, DSBPLAY_LOOPING, LinearToLogVol(liVolume));
}
void SoundController::Stop(int id) {
	sounds[id]->Stop();
	sounds[id]->Reset();
}

void SoundController::StopAll() {
	for (int i = 0; i < sounds.size(); i++)
	{
		sounds[i]->Stop();
		sounds[i]->Reset();
	}
}
