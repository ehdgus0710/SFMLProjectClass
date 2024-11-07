#pragma once
class SoundMgr : public Singleton<SoundMgr>
{
	friend class Singleton<SoundMgr>;

protected:

	sf::Sound bgm;

	std::list <sf::Sound*> playing;
	std::list <sf::Sound*> waiting;
	
	float sfxVolume = 100.f;
	float bgmVolume = 100.f;

public:
	void SetBgmVolume(float volume)
	{
		bgmVolume = volume;
		bgm.setVolume(bgmVolume);
	}
	void SetSfxVolume(float volume);

	void PlayBgm(std::string id, bool loop = true);
	void PlayBgm(sf::SoundBuffer& buffer, bool loop = true);
	void StopBgm();

	void PlaySfx(std::string id, bool loop = false);
	void PlaySfx(sf::SoundBuffer& buffer, bool loop = true);
	void StopAllSfx(sf::SoundBuffer& buffer, bool loop = false);

public:

	void Init(int totalChannels = 64);
	void Release();
	void Update(float dt);

protected:
	SoundMgr() = default;
	virtual ~SoundMgr() = default;

	SoundMgr(const SoundMgr& other) = delete;
	SoundMgr& operator=(const SoundMgr& other) = delete;
};

