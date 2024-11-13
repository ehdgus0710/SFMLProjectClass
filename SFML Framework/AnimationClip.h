#pragma once

enum class AnimationLoopTypes
{
	Single,
	Loop,
	PingPong,
};

struct AnimationFrame
{
	std::string textureId;
	sf::IntRect texCoord;

	AnimationFrame() {}
	AnimationFrame(const std::string& texId, const sf::IntRect& texCoord)
		: texCoord(texCoord)
		, textureId(texId) {}
		
};

struct AnimationClip
{
	std::vector<AnimationFrame>		frames;
	std::string						id;
	AnimationLoopTypes				loopType = AnimationLoopTypes::Loop;
	int								fps = 30;

	bool loadFromFile(const std::string& filePath);
};