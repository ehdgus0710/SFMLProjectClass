#pragma once

template<typename T>
class ResourceMgr : public Singleton<ResourceMgr<T>>
{
	friend Singleton<ResourceMgr<T>>;

protected:
	std::unordered_set<std::string> notUnloadAllResrouces;
	std::unordered_map<std::string, T*> resources;

	ResourceMgr() = default;
	~ResourceMgr()
	{
		for (const auto& pair : resources)
		{
			delete pair.second;
		}
		resources.clear();
	}

	ResourceMgr(const ResourceMgr&) = delete;
	ResourceMgr& operator=(const ResourceMgr&) = delete;

public:
	static T Empty;

	void UnloadAll()
	{
		auto iter = resources.begin();

		while (iter != resources.end())
		{
			if (notUnloadAllResrouces.find(iter->first) != notUnloadAllResrouces.end())
			{
				delete iter->second;
				iter = resources.erase(iter);
			}
			else
				++iter;
		}
	}

	bool Load(const std::string& id, bool notUnloadAll = false)
	{
		if (resources.find(id) != resources.end())
			return false;

		T* resource = new T();
		bool success = resource->loadFromFile(id);
		if (success)
		{
			resources.insert({ id, resource });
			notUnloadAllResrouces.insert(id);
		}
		else
		{
			delete resource;
		}
		return success;
	}

	bool Unload(const std::string& id)
	{
		auto it = resources.find(id);
		if (it == resources.end())
			return false;

		delete it->second;
		resources.erase(it);

		auto find = notUnloadAllResrouces.find(id);
		if (find != notUnloadAllResrouces.end())
		{
			notUnloadAllResrouces.erase(find);
		}

		return true;
	}

	T& Get(const std::string& id)
	{
		auto it = resources.find(id);
		if (it == resources.end() && !Load(id))
		{
			return Empty;
		}
		return *(resources[id]);
	}
};

template<typename T>
T ResourceMgr<T>::Empty;

#define TEXTURE_MGR (ResourceMgr<sf::Texture>::Instance())
#define FONT_MGR (ResourceMgr<sf::Font>::Instance())
#define SOUNDBUFFER_MGR (ResourceMgr<sf::SoundBuffer>::Instance())