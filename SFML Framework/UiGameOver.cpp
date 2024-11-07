#include "stdafx.h"
#include "UiGameOver.h"

void UiGameOver::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		Framework::Instance().SetTimeScale(1.f);
		SCENE_MGR.ChangeScene(SceneIds::Game);
		SetActive(false);
	}
}

UiGameOver::UiGameOver(const std::string& fontId, const std::string& name)
	: TextGo(fontId, name)
{
}