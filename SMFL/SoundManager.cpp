#include "stdafx.h"
#include "SoundManager.h"
#include "SFML\System\Vector2.hpp"


const char * SoundManager::BACKGROUND_MUSIC_LVL_1 = "../resources/stage1.mp3";
const char * SoundManager::BACKGROUND_MUSIC_LVL_2 = "../resources/stage2.mp3";
const char * SoundManager::CURSOR = "../resources/cursor.wav";
const char * SoundManager::EXPLOSION = "../resources/exp.wav";
const char * SoundManager::CONFIRM = "../resources/confirm.wav";
const char * SoundManager::SHOOT = "../resources/shoot.wav";
const char * SoundManager::PLAYEREXPLOSION = "../resources/pExp.wav";
const char * SoundManager::COMPLETE = "../resources/complete.mp3";
const char * SoundManager::TITLE = "../resources/title.mp3";
const char * SoundManager::GAMEOVER = "../resources/gameover.mp3";
const char * SoundManager::EXPLOSIONB = "../resources/expB.wav";

SoundManager::SoundManager()
{
	reverbEnabled = false;
	dopplerEnabaled = false;
	Sound3Denabled = false;
	sounds = std::vector<FMOD::Sound *>();
	result = FMOD::System_Create(&FMODsys);         // Create the main system object.
	result = FMODsys->init(100, FMOD_INIT_NORMAL, 0);   // Initialize FMOD.
}

void SoundManager::PlaySoundEffect3D(sf::Vector2f p_pos)
{
	sourcePos = { p_pos.x, 0.0f, p_pos.y };

	float volume = 1.0f;
	FMODsys->playSound(FMOD_CHANNEL_REUSE, sounds.at(1), false, &channel20);
	channel20->setVolume(volume);
	channel20->set3DMinMaxDistance(250, 10000);
	channel20->set3DDopplerLevel(0);

}
void SoundManager::PlaySoundBG(SoundManager::SoundsList p_effect, int p_trackNum)
{
	sourcePos = { 300, 0.0f, 400 };
	float volume = 1.0f;
	FMODsys->playSound(FMOD_CHANNEL_REUSE, sounds.at(p_trackNum), false, &channel);
	channel->setVolume(volume);
	channel->set3DMinMaxDistance(10000, 10000);

	FMODsys->createReverb(&reverb);
	FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_SEWERPIPE;
	reverb->setProperties(&prop);
	FMOD_VECTOR pos = { 300, 0.0f, 400 };
	float mindist = 150;
	float maxdist = 150;
	reverb->set3DAttributes(&pos, mindist, maxdist);
	reverb->setActive(false);
}

void SoundManager::StopSound(bool p_paused)
{
	//if (p_paused)
	//	channel->stop();
	//else
	//	this->PlaySoundBG(BACKGROUND_MUSIC_LEVEL_1);
}

void SoundManager::UpdateSound(sf::Vector2f p_pos, sf::Vector2f p_vel)
{
	FMOD_VECTOR  listenerpos = { p_pos.x, 0.0f, p_pos.y };
	FMOD_VECTOR  listenervel = { 0.0f, 0.0f, 0.0f };

	if (Sound3Denabled)
	{
		if (dopplerEnabaled)
			listenervel = { p_vel.x, 0.0f, p_vel.y };

		FMODsys->set3DListenerAttributes(0, &listenerpos, &listenervel, 0, 0);
		channel20->set3DAttributes(&sourcePos, 0);
	}
	else
	{
		FMOD_VECTOR zero = { 0, 0, 0 };
		channel20->set3DAttributes(&zero, 0);
		FMODsys->set3DListenerAttributes(0, &zero, &zero, 0, 0);
	}
	FMODsys->update();
}

void SoundManager::Init()
{
	FMODsys->createStream(BACKGROUND_MUSIC_LVL_1, FMOD_LOOP_NORMAL | FMOD_3D, 0, &sound);
	sounds.push_back(sound);

	FMODsys->createSound(EXPLOSION, FMOD_LOOP_OFF | FMOD_3D, 0, &sound);
	sounds.push_back(sound);

	FMODsys->createSound(CURSOR, FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	FMODsys->createSound(CONFIRM, FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	FMODsys->createSound(SHOOT, FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	FMODsys->createSound(PLAYEREXPLOSION, FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	FMODsys->createSound(COMPLETE, FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	FMODsys->createStream(TITLE, FMOD_LOOP_NORMAL | FMOD_3D, 0, &sound);
	sounds.push_back(sound);

	FMODsys->createSound(GAMEOVER, FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	FMODsys->createSound(BACKGROUND_MUSIC_LVL_2, FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	FMODsys->createSound(EXPLOSIONB, FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);
}

SoundManager& SoundManager::Instance()
{
	static SoundManager instance;
	return instance;
}

void SoundManager::PlaySFX(SoundsList p_effect)
{

	if (p_effect == SoundManager::SoundsList::CURSOR_SFX)
		FMODsys->playSound(FMOD_CHANNEL_FREE, sounds.at(2), false, NULL);
	if (p_effect == SoundManager::SoundsList::CONFIRM_SFX)
		FMODsys->playSound(FMOD_CHANNEL_FREE, sounds.at(3), false, NULL);
	if (p_effect == SoundManager::SoundsList::SHOOT_SFX)
		FMODsys->playSound(FMOD_CHANNEL_FREE, sounds.at(4), false, NULL);
	if (p_effect == SoundManager::SoundsList::PLAYEREXPLOSION_SFX)
		FMODsys->playSound(FMOD_CHANNEL_FREE, sounds.at(5), false, NULL);
	if (p_effect == SoundManager::SoundsList::COMPLETE_SFX)
		FMODsys->playSound(FMOD_CHANNEL_FREE, sounds.at(6), false, NULL);
	if (p_effect == SoundManager::SoundsList::GAMEOVER_SFX)
		FMODsys->playSound(FMOD_CHANNEL_FREE, sounds.at(8), false, NULL);
	if (p_effect == SoundManager::SoundsList::EXPLOSIONB_SFX)
		FMODsys->playSound(FMOD_CHANNEL_FREE, sounds.at(10), false, NULL);
}

void SoundManager::StopAllSounds()
{
	for (int i = 0; i < 128; i++)
	{
		FMOD::Channel* pChannel = nullptr;
		FMOD_RESULT res = FMODsys->getChannel(i, &pChannel);

		if (res == FMOD_OK && pChannel)
			pChannel->stop();
	}
}
