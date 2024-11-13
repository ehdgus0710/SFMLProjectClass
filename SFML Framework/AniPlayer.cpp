#include "stdafx.h"
#include "AniPlayer.h"


AniPlayer::AniPlayer(const std::string& name)
{
}

void AniPlayer::Init()
{
	sortingLayer = SortingLayers::Foreground;


	animator.SetTarget(&body);

	{
		idle.loadFromFile("Animations/idle.csv");
	}

	{
		run.loadFromFile("Animations/run.csv");
	}

	{
		jump.loadFromFile("Animations/jump.csv");
	}

	animator.AddEvent( "Idle" , 0 , []() {std::cout << "!!" << std::endl;  });
	animator.AddEvent("Idle", 0, std::bind(&AniPlayer::Test, this));
	
}

void AniPlayer::Release()
{
}

void AniPlayer::Reset()
{
	animator.Play(&idle);
	SetOrigin(Origins::MC);
}

void AniPlayer::Update(float dt)
{
	animator.Update(dt);


	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		animator.Play("Animations/jump.csv");
		animator.PlayQueue("Animations/idle.csv");
	}

	return;

	float horizontalValue = InputMgr::GetAxis(Axis::Horizontal);

	velocity.x = horizontalValue * speed;
	if (!isGrounded)
	{
		velocity.x += gravity * dt;
		velocity.y += gravity * dt;
	}

	if (position.y > 0.f)
	{
		position.y = 0.f;
		velocity.y = 0.f;
		isGrounded = true;
	}

	SetPosition(position + velocity * dt);


	if (isJump && isGrounded)
	{
		isJump = animator.IsPlaying();

		if(!isJump)
			animator.Play(&idle);
	}
	else
	{
		if (isGrounded && horizontalValue == 0.f && animator.GetCurrentCilp() != &idle)
		{
			animator.Play(&idle, true);
		}

		else if (isGrounded && horizontalValue != 0.f && animator.GetCurrentCilp() != &run)
		{
			animator.Play(&run);
			animator.SetSpeed(3.f);
		}

		if (InputMgr::GetKeyDown(sf::Keyboard::Space) && animator.GetCurrentCilp() != &jump)
		{
			animator.Play(&jump, true);
			isJump = true;
			isGrounded = false;
			velocity.y = -250.f;
		}

		auto scale = body.getScale();
		if (horizontalValue < 0.f && scale.x > 0.f)
		{
			scale.x *= -1.f;
			body.setScale(scale);
		}
		else if (horizontalValue > 0.f && scale.x < 0.f)
		{
			scale.x *= -1.f;
			body.setScale(scale);
		}
	}
	

}

void AniPlayer::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void AniPlayer::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void AniPlayer::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void AniPlayer::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void AniPlayer::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void AniPlayer::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void AniPlayer::Test()
{
	std::cout << "¤·¤µ¤·" << std::endl;
}
