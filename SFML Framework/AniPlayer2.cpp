#include "stdafx.h"
#include "AniPlayer2.h"


AniPlayer2::AniPlayer2(const std::string& name)
	: GameObject(name)
{
}

void AniPlayer2::Init()
{
	sortingLayer = SortingLayers::Foreground;

	std::string textureId = "graphics/RubySheet.png";
	int width = 256;
	int height = 256;

	{
		AnimationClip clipIdleSide;
		clipIdleSide.id = "IdleSide";
		clipIdleSide.fps = 3;
		clipIdleSide.loopType = AnimationLoopTypes::Loop;
		clipIdleSide.frames.push_back({ textureId, { 0, 3 * height, width, height } });
		clipIdleSide.frames.push_back({ textureId, { 1 * width, 5 * height, width, height } });
		temp.insert({ "IdleSide" ,clipIdleSide });
		//animator.AddClip(clip);
	}
	{
		AnimationClip clipIdleDown;
		clipIdleDown.id = "IdleDown";
		clipIdleDown.fps = 3;
		clipIdleDown.loopType = AnimationLoopTypes::Loop;
		clipIdleDown.frames.push_back({ textureId, { 1 * width, 3 * height, width, height } });
		clipIdleDown.frames.push_back({ textureId, { 2 * width, 5 * height, width, height } });		
		temp.insert({ "IdleDown" ,clipIdleDown });
	}
	{
		AnimationClip clipIdleUp;
		clipIdleUp.id = "IdleUp";
		clipIdleUp.fps = 3;
		clipIdleUp.loopType = AnimationLoopTypes::Loop;
		clipIdleUp.frames.push_back({ textureId, { 2 * width, 3 * height, width, height } });
		clipIdleUp.frames.push_back({ textureId, { 3 * width, 5 * height, width, height } });
		temp.insert({ "IdleUp" ,clipIdleUp });
	}
	{
		AnimationClip clipMoveSide;
		clipMoveSide.id = "MoveSide";
		clipMoveSide.fps = 10;
		clipMoveSide.loopType = AnimationLoopTypes::Loop;
		for (int i = 0; i < 4; ++i)
		{
			clipMoveSide.frames.push_back({ textureId, { i * width, 0, width, height } });
		}
		temp.insert({ "MoveSide" ,clipMoveSide });
	}
	{
		AnimationClip clipMoveUp;
		clipMoveUp.id = "MoveUp";
		clipMoveUp.fps = 10;
		clipMoveUp.loopType = AnimationLoopTypes::Loop;
		for (int i = 0; i < 4; ++i)
		{
			clipMoveUp.frames.push_back({ textureId, { i * width, height, width, height } });
		}
		temp.insert({ "MoveUp" ,clipMoveUp });
	}
	{
		AnimationClip clipMoveDown;
		clipMoveDown.id = "MoveDown";
		clipMoveDown.fps = 10;
		clipMoveDown.loopType = AnimationLoopTypes::Loop;
		for (int i = 0; i < 4; ++i)
		{
			clipMoveDown.frames.push_back({ textureId, { i * width, 2 * height, width, height } });
		}
		temp.insert({ "MoveDown" ,clipMoveDown });
	}

	clipInfos.push_back({ "IdleSide", "MoveSide" , false, Utils::GetNormal({ -1.f,-1.f }) });
	clipInfos.push_back({ "IdleUp", "MoveUp" , false, { 0.f,-1.f } });
	clipInfos.push_back({ "IdleSide", "MoveSide" , true, Utils::GetNormal({ 1.f,-1.f }) });

	clipInfos.push_back({ "IdleSide", "MoveSide" , false, { -1.f, 0.f } });
	clipInfos.push_back({ "IdleSide", "MoveSide" , true, { 1.f,0.f } });

	clipInfos.push_back({ "IdleSide", "MoveSide" , false, Utils::GetNormal({ -1.f,1.f }) });
	clipInfos.push_back({ "IdleDown", "MoveDown" , false, { 0.f, 1.f } });
	clipInfos.push_back({ "IdleSide", "MoveSide" , true, Utils::GetNormal({ 1.f,1.f }) });

	animator.SetTarget(&body);

}

void AniPlayer2::Release()
{
}

void AniPlayer2::Reset()
{
	// body.setTexture(TEXTURE_MGR.Get("graphics/RubySheet.png"));
	// body.setTextureRect({ 0,0,256,256 });
	animator.Play(&temp["IdleDown"]);
	currentClipInfo = &clipInfos[6];
	SetOrigin(Origins::MC);
}

void AniPlayer2::Update(float dt)
{
	animator.Update(dt);

	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	float mag = Utils::Magnitude(direction);
	if (mag > 1.f)
		direction.Normalized();

	SetPosition(position + direction * speed * dt);

	if (direction.x != 0.f || direction.y != 0.f)
	{
		// 컨테이너에서 최소 값을 찾는 함수
		auto min = std::min_element(clipInfos.begin(), clipInfos.end(), 
			[this](const ClipInfo& lhs, const ClipInfo& rhs) 
			{
				float d1 = Utils::Distance(direction, lhs.point);
				float d2 = Utils::Distance(direction, rhs.point);
				return d1 < d2;
			});
		currentClipInfo = &(*min);
	}


	if (currentClipInfo->flipX)
		SetScale({ -1.f, 1.f });
	else
		SetScale({ 1.f, 1.f });

	const auto& clipId = (direction.x != 0.f || direction.y != 0.f) ? currentClipInfo->move : currentClipInfo->idle;

	if (animator.GetCurrentCilpID() != clipId)
	{
		animator.Play(&temp[clipId]);
	}
}

void AniPlayer2::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void AniPlayer2::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void AniPlayer2::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void AniPlayer2::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void AniPlayer2::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void AniPlayer2::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void AniPlayer2::Test()
{
	std::cout << "ㅇㅅㅇ" << std::endl;
}
