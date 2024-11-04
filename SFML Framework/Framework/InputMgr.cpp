#include "stdafx.h"

std::list<int> InputMgr::downKeys;
std::list<int> InputMgr::heldKeys;
std::list<int> InputMgr::upKeys;
sf::Vector2i InputMgr::mousePosition;

std::unordered_map<Axis, AxisInfo> InputMgr::axisInfoMap;

void InputMgr::Init()
{
	AxisInfo infoHorizontal;
	infoHorizontal.axis = Axis::Horizontal;
	infoHorizontal.AddKey(true, sf::Keyboard::D);
	infoHorizontal.AddKey(true, sf::Keyboard::Right);
	infoHorizontal.AddKey(false, sf::Keyboard::A);
	infoHorizontal.AddKey(false, sf::Keyboard::Left);
	axisInfoMap.insert({ Axis::Horizontal, infoHorizontal });
	
	AxisInfo infoVertical;
	infoVertical.axis = Axis::Vertical;
	infoVertical.AddKey(true, sf::Keyboard::S);
	infoVertical.AddKey(true, sf::Keyboard::Down);
	infoVertical.AddKey(false, sf::Keyboard::W);
	infoVertical.AddKey(false, sf::Keyboard::Up);
	axisInfoMap.insert({ Axis::Vertical, infoVertical });
}

void InputMgr::Clear()
{
	upKeys.clear();
	downKeys.clear();
}

bool InputMgr::Contains(const std::list<int>& list, int code)
{
	return std::find(list.begin(), list.end(), code) != list.end();
}

void InputMgr::Remove(std::list<int>& list, int code)
{
	list.remove(code);
}

void InputMgr::UpdateEvent(const sf::Event& ev)
{
	switch (ev.type)
	{
	case sf::Event::KeyPressed:
		{
			int code = ev.key.code;
			if (!Contains(heldKeys, code))
			{
				heldKeys.push_back(code);
				downKeys.push_back(code);
			}
		}
		break;
	case sf::Event::KeyReleased:
		{
			int code = ev.key.code;
			Remove(heldKeys, code);
			upKeys.push_back(code);
		}
		break;
	case sf::Event::MouseButtonPressed:
		{
			int code = sf::Keyboard::KeyCount + ev.mouseButton.button;
			if (!Contains(heldKeys, code))
			{
				heldKeys.push_back(code);
				downKeys.push_back(code);
			}
		}
		break;
	case sf::Event::MouseButtonReleased:
		{
			int code = sf::Keyboard::KeyCount + ev.mouseButton.button;
			Remove(heldKeys, code);
			upKeys.push_back(code);
		}
		break;
	case sf::Event::MouseMoved:
		mousePosition.x = ev.mouseMove.x;
		mousePosition.y = ev.mouseMove.y;
		break;
	}
}

void InputMgr::Update(float deltaTime)
{
	for (auto& pair : axisInfoMap)
	{
		auto& axisInfo = pair.second;
		float raw = GetAxisRaw(axisInfo.axis);
		float dir = raw;

		if (dir == 0.f && axisInfo.value != 0.f)
		{
			dir = axisInfo.value > 0.f ? -1.f : 1.f;
		}

		axisInfo.value += dir * axisInfo.sensi * deltaTime;
		axisInfo.value = Utils::Clamp(axisInfo.value, -1.f, 1.f);

		float stopThreshold = std::abs(dir * axisInfo.sensi * deltaTime);
		if (raw == 0.f && std::abs(axisInfo.value) < stopThreshold)
		{
			axisInfo.value = 0.f;
		}
	}
}

bool InputMgr::GetKeyDown(sf::Keyboard::Key key)
{
	return Contains(downKeys, key);
}

bool InputMgr::GetKey(sf::Keyboard::Key key)
{
	return Contains(downKeys, key) || Contains(heldKeys, key);
}

bool InputMgr::GetKeyUp(sf::Keyboard::Key key)
{
	return Contains(upKeys, key);
}

bool InputMgr::GetMouseButtonDown(sf::Mouse::Button button)
{
	return Contains(downKeys, sf::Keyboard::KeyCount + button);
}

bool InputMgr::GetMouseButton(sf::Mouse::Button button)
{
	int code = sf::Keyboard::KeyCount + button;
	return Contains(downKeys, code) || Contains(heldKeys, code);
}

bool InputMgr::GetMouseButtonUp(sf::Mouse::Button button)
{
	return Contains(upKeys, sf::Keyboard::KeyCount + button);
}

float InputMgr::GetAxisRaw(Axis axis)
{
	auto findIter = axisInfoMap.find(axis);

	if (findIter == axisInfoMap.end())
	{
		return 0.0f;
	}

	auto iter = heldKeys.rbegin();
	auto& axisInfo = findIter->second;

	while (iter != heldKeys.rend())
	{
		int code = *iter;

		if (Contains(axisInfo.positivieslist, code))
			return 1.f;
		else if (Contains(axisInfo.negativeslist, code))
			return -1.f;

		++iter;
	}


	return 0.0f;
}

float InputMgr::GetAxis(Axis axis)
{
	auto findIter = axisInfoMap.find(axis);

	if (findIter == axisInfoMap.end())
	{
		return 0.0f;
	}
	return findIter->second.value;
}

