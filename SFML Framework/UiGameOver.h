#pragma once

#include "TextGo.h"

class UiGameOver : public TextGo
{
public:
	void Update(float dt) override;

public:
	UiGameOver(const std::string& fontId = "", const std::string& name = "");
	~UiGameOver() = default;

};
