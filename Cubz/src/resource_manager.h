#ifndef RESOURCE_MANAGER_INCLUDED
#define RESOURCE_MANAGER_INCLUDED

template<typename T>
class ResourceManager
{
public:
	ResourceManager() {}

	~ResourceManager()
	{
		for (auto it = m_resources.begin(); it != m_resources.end(); it++)
		{
			if (it->second != NULL)
				delete it->second;
		}
	}

	void removeResource(std::string name)
	{
		T* resource = m_resources[name];
		if (resource != NULL)
			delete resource;
	}

	void registerResource(std::string name, T* resource)
	{
		removeResource(name);
		m_resources[name] = resource;
	}

	T* getResource(const std::string& name) const
	{
		auto it = m_resources.find(name);
		if (it == m_resources.end())
			return NULL;
		return it->second;
	}

	bool hasResource(const std::string& name) const
	{
		auto it = m_resources.find(name);
		return it != m_resources.end();
	}

private:
	std::map<std::string, T*> m_resources;
};


#endif RESOURCE_MANAGER_INCLUDED
