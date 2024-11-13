#pragma once

#include "AnimationClip.h"

struct AnimationEvent
{
	std::string id;
	int frame = 0;
	std::vector<std::function<void()>> actionVector;
	bool operator==(const AnimationEvent& other) const
	{
		return (id == other.id) && (frame == other.frame);
	}
};

struct AnimationEventHash
{

	std::size_t operator()(const std::pair<std::string, int>& pair) const
	{
		std::size_t h1 = std::hash<std::string>()(pair.first);
		std::size_t h2 = std::hash<int>()(pair.second);
		return h1 ^ (h2 << 1);
	}
};

class Animator
{
protected:
	std::unordered_map<std::pair<std::string, int>, AnimationEvent, AnimationEventHash> events;
	std::queue<std::string> playQueue;
	AnimationClip* currentClip;
	sf::Sprite* sprite;

	bool isPlaying = false;
	int currentFrame = 0;
	int totalFrame = 0;
	float frameDuration = 0.f;
	float accumTime = 0.f;

	float speed = 1.f;
	bool rewind = false;

public:
	void Init();
	void Update(float dt);

	void SetTarget(sf::Sprite* target) { sprite = target; }
	void SetFrame(const AnimationFrame& frame);
	void SetSpeed(float speed) { this->speed = speed; if (speed < 0.f) { Play(currentClip, true); speed *= -1.f; } }

	AnimationClip* GetCurrentCilp() { return currentClip; }
	const std::string& GetCurrentCilpID() { return currentClip->id; }

	void Play(const std::string& clipId, bool clearQueue = false, bool rewind = false);
	void Play(AnimationClip* clip, bool clearQueue = false, bool rewind = false);
	void PlayQueue(const std::string& clipId);
	void RewinPlay();
	//void Pause(bool pause);
	void Stop();

	void SetSprite(sf::Sprite* sprite) { this->sprite = sprite; }
	bool IsPlaying() const { return isPlaying; }


	void AddEvent(const std::string& id, int frame, std::function<void()> action)
	{
		auto iter = events.find({ id, frame });
		if (iter != events.end())
		{
			events[{id, frame}].actionVector.push_back(action);
			return;
		}
		else
		{
			std::vector<std::function<void()>> actionVector;
			actionVector.push_back(action);
			events.insert({ {id, frame}, { id, frame, actionVector } });
		}
	}
public:
	Animator();
	~Animator();
};

