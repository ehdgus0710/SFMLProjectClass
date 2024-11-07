#include "stdafx.h"


void SoundMgr::Init(int totalChannels)
{
	for (int i = 0; i < totalChannels; ++i)
	{
		waiting.push_back(new sf::Sound());
	}
}

void SoundMgr::Release()
{
	for (auto sound : waiting)
	{
		delete sound;
	}
	waiting.clear();

	for (auto sound : playing)
	{
		delete sound;
	}
	playing.clear();
}

void SoundMgr::Update(float dt)
{
	auto iter = playing.begin();

	while (iter != playing.end())
	{
		if ((*iter)->getStatus() == sf::Sound::Stopped)
		{
			waiting.push_back(*iter);
			playing.erase(iter);
		}
		else
			++iter;
	}
}


void SoundMgr::SetSfxVolume(float volume)
{
	sfxVolume = volume;

	for (auto sound : playing)
	{
		sound->setVolume(sfxVolume);
	}
}

void SoundMgr::PlayBgm(std::string id, bool loop)
{
	PlayBgm(SOUNDBUFFER_MGR.Get(id), loop);
}

void SoundMgr::PlayBgm(sf::SoundBuffer& buffer, bool loop)
{
	bgm.stop();
	bgm.setVolume(bgmVolume);
	bgm.setLoop(loop);
	bgm.setBuffer(buffer);
	bgm.play();
}

void SoundMgr::StopBgm()
{
	bgm.stop();
}

void SoundMgr::PlaySfx(std::string id, bool loop)
{
	PlaySfx(SOUNDBUFFER_MGR.Get(id), loop);
}

void SoundMgr::PlaySfx(sf::SoundBuffer& buffer, bool loop)
{
	sf::Sound* sound = nullptr;

	if (waiting.empty())
	{
		sound = playing.front();
		playing.pop_front();
		sound->stop();
	}
	else
	{
		sound = waiting.front();
		waiting.pop_front();
	}
		
	sound->setVolume(sfxVolume);
	sound->setBuffer(buffer);
	sound->setLoop(loop);
	sound->play();
	playing.push_back(sound);
}

void SoundMgr::StopAllSfx(sf::SoundBuffer& buffer, bool loop)
{
	for (auto sound : playing)
	{
		sound->stop();
		waiting.push_back(sound);
	}

	playing.clear();

}
