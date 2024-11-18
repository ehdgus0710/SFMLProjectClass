#pragma once

#include "SaveData.h"

class SaveLoadManager : public Singleton<SaveLoadManager>
{
	friend class Singleton<SaveLoadManager>;

protected:
	std::string tempSavePath = "save.json";


public:
	void Save(const SaveDataVC& saveData);
	SaveDataVC Load();
protected:
	SaveLoadManager() = default;
	virtual ~SaveLoadManager();
	SaveLoadManager(const SaveLoadManager& other) = delete;
	SaveLoadManager& operator=(const SaveLoadManager& other) = delete;
};