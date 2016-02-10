//FMOD includes
#pragma once
#pragma comment(lib,"fmodex_vc.lib")
#include "fmod.hpp"
#include "fmod_errors.h"
#include <vector>
#include<string>
#include "SFML\System\Vector2.hpp"

class SoundManager
{

public:
	enum SoundsList
	{
		BACKGROUND_MUSIC_LEVEL_1,
		CURSOR_SFX,
		CONFIRM_SFX,
		EXPLOSTION_SFX,
		SHOOT_SFX,
		PLAYEREXPLOSION_SFX,
		COMPLETE_SFX,
		TITLE_SFX,
		GAMEOVER_SFX
	};

	static SoundManager& Instance();


	void PlaySoundEffect3D(sf::Vector2f p_pos);
	void PlaySoundBG(SoundManager::SoundsList p_effect, int p_trackNum);
	void PlaySFX(SoundManager::SoundsList p_effect);

	void PlaySoundBGTest();

	void StopSound(bool p_paused);
	void StopAllSounds();
	void UpdateSound(sf::Vector2f p_pos, sf::Vector2f p_vel);
	void Init();

	bool Sound3Denabled;
	bool dopplerEnabaled;
	bool reverbEnabled;
	FMOD::Reverb *reverb;


private:
	SoundManager();

	const static char* BACKGROUND_MUSIC_LVL_1;
	const static char* CURSOR;
	const static char* EXPLOSION;
	const static char* CONFIRM;
	const static char* SHOOT;
	const static char* PLAYEREXPLOSION;
	const static char* COMPLETE;
	const static char* TITLE;
	const static char* GAMEOVER;
	float volume;
	FMOD::System *FMODsys; //will point to the FMOD system
	FMOD::System *FMODsys2;
	FMOD_RESULT result;
	FMOD::Sound *sound;
	std::vector<FMOD::Sound*> sounds;
	FMOD::Channel *channel;
	FMOD::Channel *channel20;
	FMOD_VECTOR sourcePos;
};
