#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& name)
	: GameObject(name)
	, texture(nullptr)
	, spriteSheetId("graphics/background_sheet.png")
{
}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	UpdateTransform();
}

void TileMap::SetRotation(float angle)
{
	rotation = angle;
	UpdateTransform();
}

void TileMap::SetScale(const sf::Vector2f& s)
{
	scale = s;
	//cellSize = cellSize * scale;
	UpdateTransform();
}

void TileMap::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		sf::FloatRect rect = GetLocalBounds();
		origin.x = rect.width * ((int)preset % 3) * 0.5f;
		origin.y = rect.height * ((int)preset / 3) * 0.5f;
		UpdateTransform();
	}
}

void TileMap::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	UpdateTransform();
}

void TileMap::SetInfo(const sf::Vector2u& count, const sf::Vector2f& size)
{
	cellCount = count;
	cellSize = size;
	
	vertexArray.clear();
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(count.x * count.y * 4);
	
	texture = &TEXTURE_MGR.Get("graphics/background_sheet.png");

	sf::Vector2u textureCount = { texture->getSize().x / (unsigned int)size.x , texture->getSize().y / (unsigned int)size.y };

	//  타일 당 위치 값, 크기 정하기
	sf::Vector2f positionOffset[4] =
	{
		{ 0.f , 0.f }
		, { size.x , 0.f }
		, { size.x , size.y }
		, { 0.f , size.y }
	};

	// 텍스쳐 좌표 정하기
	sf::Vector2f textUv[4] =
	{
		{ 0.f , 0.f }
		, { 50.f, 0.f}
		, { 50.f, 50.f }
		, {0.f , 50.f }
	};

	for (int i = 0; i < (int)count.y; ++i)
	{
		for (int j = 0; j < (int)count.x; ++j)
		{
			// 사용할 텍스쳐 UV 구하기
			int texIndex = Utils::RandomRange(0, 2);

			// 외곽 라인 기본 맵으로 지정
			if (i == 0 || i == count.y - 1 || j == 0 || j == count.x - 1)
			{
				texIndex = 3;
			}

			// 쿼드 좌표
			auto quadIndex = i * count.x + j;
			// 쿼드 위치 값 정하기
			sf::Vector2f quadPosition(j * size.y, i * size.y);

			for (int k = 0; k < 4; ++k)
			{
				// 쿼드 생성 시 총 4개의 버텍스가 필요하기 때문에 * 4 및 버텍스 인덱스 구하기
				int vertexIndex = quadIndex * 4 + k;
				// 정점 위치 정하기
				vertexArray[vertexIndex].position = quadPosition + positionOffset[k];
				// 기본 UV 위치 지정
				vertexArray[vertexIndex].texCoords = textUv[k];
				// 텍스쳐에 따라 다른 타일 맵 설정
				vertexArray[vertexIndex].texCoords.y += texIndex * 50.f;
			}
		}
	}
}

void TileMap::SetInfo(const sf::Vector2u& tileCount, const sf::Vector2f& tileSize, const sf::Vector2u textTileSize)
{
	cellCount = tileCount;
	cellSize = tileSize;

	vertexArray.clear();
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(tileCount.x * tileCount.y * 4);

	texture = &TEXTURE_MGR.Get("graphics/background_sheet.png");

	sf::Vector2f totalTileMapSize = { (sf::Vector2f)tileCount * tileSize };

	sf::Vector2u textureCount = { texture->getSize().x / (unsigned int)tileSize.x , texture->getSize().y / (unsigned int)tileSize.y };

	sf::Vector2f positionOffset[4] =
	{
		{ 0.f , 0.f }
		, { tileSize.x , 0.f }
		, { tileSize.x , tileSize.y }
		, { 0.f , tileSize.y }
	};

	sf::Vector2f textUv[4] =
	{
		{ 0.f , 0.f }
		, { (float)textTileSize.x , 0.f}
		, (sf::Vector2f)textTileSize
		, {0.f , (float)textTileSize.y }
	};

	for (int i = 0; i < (int)tileCount.y; ++i)
	{
		sf::Vector2f createPosition = totalTileMapSize * -0.5f;

		for (int j = 0; j < (int)tileCount.x; ++j)
		{
			sf::Vector2i textureIndex;
			textureIndex.x = Utils::RandomRange(0, textureCount.x - 1);
			textureIndex.y = Utils::RandomRange(0, textureCount.y - 1);

			if (i == 0 || i == tileCount.y - 1 || j == 0 || j == tileCount.x - 1)
			{
				textureIndex.y = 3;
			}

			auto quadIndex = i * tileCount.x + j;
			sf::Vector2f quadPosition(j * tileSize.y, i * tileSize.y);

			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = quadIndex * 4 + k;
				vertexArray[vertexIndex].position = quadPosition + positionOffset[k];
				vertexArray[vertexIndex].texCoords = textUv[k];
				vertexArray[vertexIndex].texCoords.x += textureIndex.x * (float)tileSize.x;
				vertexArray[vertexIndex].texCoords.y += textureIndex.y * (float)tileSize.y;
			}
		}
	}
}

void TileMap::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = -1;

	//SetInfo({ 10,10 }, { 50.f,50.f });
	SetInfo({ 30,30 }, { 50.f,50.f }, { 50,50 });
	SetOrigin(Origins::MC);
}

void TileMap::Release()
{
}

void TileMap::Reset()
{
	texture = &TEXTURE_MGR.Get(spriteSheetId);
	
	position = { 300.f,300.f };
	SetScale(sf::Vector2f::one * 1.25f);
	UpdateTransform();
}

void TileMap::UpdateTransform()
{
	transform = transform.Identity;
	transform.translate(position);
	transform.rotate(rotation);
	transform.scale(scale);
	transform.translate(-origin);
}

sf::FloatRect TileMap::GetLocalBounds() const
{
	return sf::FloatRect(0.f, 0.f, cellCount.x * cellSize.x, cellCount.y * cellSize.y);
}

sf::FloatRect TileMap::GetGlobalBounds() const
{
	sf::FloatRect bounds = GetLocalBounds();
	return  transform.transformRect(bounds);
}

// return transform.transformRect((sf::FloatRect(cellSize.x, cellSize.y, cellCount.x - 2 * cellSize.x, cellCount.y-2 * cellSize.y));


void TileMap::Update(float dt)
{
	/*direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	if (direction.SqrMagnitude() > 1.f)
		direction.Normalized();

	SetPosition(position + direction * 100.f * dt);
	
	if (InputMgr::GetKeyDown(sf::Keyboard::PageUp))
	{
		SetRotation(rotation + 1.f);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::P))
	{
		SetScale(scale += {0.1f, 0.1f});
	}*/
}

void TileMap::Draw(sf::RenderWindow& window)
{
	renderState.texture = texture;
	renderState.transform = transform;

	window.draw(vertexArray, renderState);
}
