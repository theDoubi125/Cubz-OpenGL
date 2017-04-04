#ifndef MESH_RENDER_INCLUDED
#define MESH_RENDER_INCLUDED

#include "component.h"
#include "resource_manager.h"

class Mesh;

typedef ResourceManager<Mesh> MeshManager;

class MeshRenderer : public Component
{
public:
	MeshRenderer();
	virtual ~MeshRenderer();

	virtual void init(json descr) override;
	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void render() const override;
	virtual void debugUI() override;

	virtual Component* clone() const override;

	virtual const std::string& getName() const
	{
		return "MeshRenderer";
	}

	static void registerMeshes();

private:
	Mesh* m_mesh;

	static MeshManager m_meshManager;
};

#endif MESH_RENDER_INCLUDED
