#include "stdafx.h"
#include "Framework.h"
#include "SpriteGo.h"

void Framework::Init(int width, int height, const std::string& name)
{
	window.create(sf::VideoMode(width, height), name);

    DATATABLE_MANEGER.Init();
    Utils::Init();
    SoundMgr::Instance().Init();
    SCENE_MGR.Init();
    InputMgr::Init();
}

void Framework::Do()
{
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        realDeltaTime = deltaTime = dt.asSeconds();
        deltaTime *= timeScale;
        realTime += realDeltaTime;
        time += deltaTime;

        // 이벤트 루프
        InputMgr::Clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            InputMgr::UpdateEvent(event);
        }

        InputMgr::Update(deltaTime);
        // 업데이트
        SCENE_MGR.Update(deltaTime);
        SCENE_MGR.LateUpdate(deltaTime);
        SCENE_MGR.FixedUpdate(deltaTime);

        // 드로우
        window.clear();
        SCENE_MGR.Draw(window);
        window.display();
    }
}

void Framework::Release()
{
    SCENE_MGR.Release();
    SoundMgr::Instance().Release();
    DATATABLE_MANEGER.Release();
}
