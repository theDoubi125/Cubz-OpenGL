#ifndef SCENE_HEADER
#define SCENE_HEADER

#include <vector>
#include <glm/vec2.hpp>
#include <glm\mat4x4.hpp>
#include <json.hpp>
#include "render_target.h"
#include "image_effect.h"

class Entity;
class Mesh;

class Scene
{
public:
	Scene();
	~Scene();

	void init(json descr);
	void start();
	void update(float deltaTime);
	void debugUI();
	void debugUISpecial();

	void addEntity(Entity* entity);
	void removeEntity(Entity* entity);

	void render() const;

	Entity* getEntity(const std::string& entity) const;
	Entity* getEntity(const std::string& entity);

	bool isGamePaused() const { return m_paused; }
	void setGamePaused(bool paused) { m_paused = paused; }

private:
	std::vector<Entity*> m_entities;
	std::map<std::string, Entity*> m_entitiesByName;

	bool m_paused;
	RenderTarget m_renderTarget;

	ImageEffect* m_imageEffect;
};

#endif SCENE_HEADER
