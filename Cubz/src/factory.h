#ifndef FACTORY_INCLUDED
#define FACTORY_INCLUDED

#include <map>

template<typename Key, typename Value>
class Factory
{
public:
	Value* createInstance(Key key)
	{
		auto it = m_models.find(key);
		if (it != m_models.end())
			return it->second->clone();
	}

	void registerInstance(Key key, Value* value)
	{
		m_models[key] = value;
	}

private:
	std::map<Key, Value*> m_models;
};

#endif FACTORY_INCLUDED
