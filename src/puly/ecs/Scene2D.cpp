#include "Scene2D.h"
#include "../lowlevel/Scene.h"

namespace Puly {

	Scene2D::Scene2D(Window& window)
	{
		m_EntityManager = std::make_shared<EntityManager>(&window);
	}

	Scene2D::~Scene2D()
	{
	}

	void Scene2D::OnStart()
	{
		//Puly::GameObject& checkerboard(m_EntityManager->AddObject(1, "checkerboard"));
		//checkerboard.AddComponent<Puly::SpriteRenderer>("resources/textures/checkerboard.png");
	}

	void Scene2D::OnUpdate(Timestep deltaTime)
	{
		m_EntityManager->Update(deltaTime);
	}

	void Scene2D::Render()
	{
		m_EntityManager->Render();
	}

	void Scene2D::LoadSceneFromFile(std::string path)
	{
		SceneConfig sceneConfig(path.c_str());
		bool foundFile = sceneConfig.Init();

		// Load entities and components
		
		PL_LOG_INFO(foundFile ? "Loading scene" : "Failed finding the scene file");
		for (auto objName : sceneConfig.GetObjects()) {
			PL_LOG_INFO("Created Obj: {}", objName);

			int priority = atoi(sceneConfig.GetValue(objName.c_str(), "priority"));
			double isActive = atoi(sceneConfig.GetValue(objName.c_str(), "isActive"));
			float positionX = atof(sceneConfig.GetValue(objName.c_str(), "positionX"));
			float positionY = atof(sceneConfig.GetValue(objName.c_str(), "positionY"));
			float positionZ = atof(sceneConfig.GetValue(objName.c_str(), "positionZ"));
			float scaleX = atof(sceneConfig.GetValue(objName.c_str(), "scaleX"));
			float scaleY = atof(sceneConfig.GetValue(objName.c_str(), "scaleY"));
			float scaleZ = atof(sceneConfig.GetValue(objName.c_str(), "scaleZ"));
			float rotation = atof(sceneConfig.GetValue(objName.c_str(), "rotation"));

			Puly::GameObject& importedObj(m_EntityManager->AddObject(priority, objName));
			importedObj.m_IsActive = isActive;
			importedObj.m_Position.x = positionX;
			importedObj.m_Position.y = positionY;
			importedObj.m_Position.z = positionZ;
			importedObj.m_Scale.x = scaleX;
			importedObj.m_Scale.y = scaleY;
			importedObj.m_Scale.z = scaleZ;
			importedObj.m_Rotation = rotation;

			for (auto objName : sceneConfig.GetComponentsInObject(objName)) {
				PL_LOG_INFO("Created Component: {}", objName);
			}
		}

		sceneConfig.Shutdown();
	}

}
