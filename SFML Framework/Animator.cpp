#include "stdafx.h"
#include "Animator.h"
#include "AnimationClip.h"

Animator::Animator()
{
}

Animator::~Animator()
{
}

void Animator::Init()
{
}

void Animator::Update(float dt)
{
	if (!isPlaying)
		return;

	accumTime += dt * speed;

	if (accumTime < frameDuration)
		return;

	if (rewind)
		RewinPlay();
	else
	{
		++currentFrame;
		accumTime = 0.f;

		if (currentFrame == totalFrame)
		{
			if (!playQueue.empty())
			{
				std::string clipId = playQueue.front();

				Play(clipId);
				playQueue.pop();
				return;
			}

			switch (currentClip->loopType)
			{
			case AnimationLoopTypes::Single:
				currentFrame = totalFrame - 1;
				isPlaying = false;
				break;
			case AnimationLoopTypes::Loop:
				currentFrame = 0;
				break;
			case AnimationLoopTypes::PingPong:
				break;
			default:
				break;
			}

		}
		SetFrame(currentClip->frames[currentFrame]);
		auto find = events.find({ currentClip->id, currentFrame });
		if (find != events.end() && !find->second.actionVector.empty())
		{
			for(auto& action : find->second.actionVector)
				action();
		}
	}
}

void Animator::SetFrame(const AnimationFrame& frame)
{
	sprite->setTexture(TEXTURE_MGR.Get(frame.textureId), true);
	sprite->setTextureRect(frame.texCoord);
	sprite->setOrigin(frame.texCoord.width * 0.5f, frame.texCoord.height * 0.5f);
}

void Animator::Play(const std::string& clipId, bool clearQueue, bool rewind)
{
	if (clearQueue)
	{
		while (!playQueue.empty())
		{
			playQueue.pop();
		}
	}

	this->rewind = rewind;

	isPlaying = true;
	currentClip = &ResourceMgr<AnimationClip>::Instance().Get(clipId);
	totalFrame = (int)currentClip->frames.size();
	speed = 1.f;
	frameDuration = 1.f / currentClip->fps;

	if (rewind)
		currentFrame = totalFrame - 1;
	else
		currentFrame = 0;
	accumTime = 0.f;
}

void Animator::Play(AnimationClip* clip, bool clearQueue, bool rewind)
{
	if (clearQueue)
	{
		while (!playQueue.empty())
		{
			playQueue.pop();
		}
	}

	this->rewind = rewind;

	isPlaying = true;
	currentClip = clip;
	totalFrame = (int)clip->frames.size();
	speed = 1.f;
	frameDuration = 1.f / clip->fps;

	if (rewind)
		currentFrame = totalFrame - 1;
	else
		currentFrame = 0;
	accumTime = 0.f;
}

void Animator::PlayQueue(const std::string& clipId)
{
	playQueue.push(clipId);
}

void Animator::RewinPlay()
{
	--currentFrame;

	accumTime = 0.f;

	if (currentFrame == -1)
	{
		switch (currentClip->loopType)
		{
		case AnimationLoopTypes::Single:
			currentFrame = 0;
			isPlaying = false;
			break;
		case AnimationLoopTypes::Loop:
			currentFrame = totalFrame - 1;
			break;
		case AnimationLoopTypes::PingPong:
			break;
		default:
			break;
		}

	}
	SetFrame(currentClip->frames[currentFrame]);
}

void Animator::Stop()
{
	isPlaying = false;
}