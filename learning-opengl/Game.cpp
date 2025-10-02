#include "Game.h"

bool Game::over = false;

void Game::Init()
{
	AddObjects();
}

void Game::Process(float deltaTime)
{
	if (!over)
	{
		std::vector<Node*> tNodes = std::vector<Node*>(Node::nodes);

		for (Node* node : tNodes)
		{
			if (node)
				node->Process(deltaTime);
		}
		Node::FreeQueuedObjects();
	}
}

void Game::AddObjects()
{
	Node3D* cube1 = new Node3D();
	auto unitySpawnerComponent = std::make_unique<UnitySpawnerComponent>();
	cube1->AddComponent(std::move(unitySpawnerComponent));

	//Node3D* cube2 = new Node3D();
	//auto renderComponent2 = std::make_unique<RenderComponent>();
	//renderComponent2->SetMaterial(material2);
	//renderComponent2->SetModel(Model::Load("./model.glb"));
	//cube2->AddComponent(std::move(renderComponent2));
	//cube2->transform.Translate(glm::vec3(2.0f, 0.0f, 0.0f));

	// Light

	Node3D* light = new Node3D();
	auto directionalLightComponent = std::make_unique<DirectionalLightComponent>();
	light->transform.SetEuler(glm::vec3(1.5f, 1.0f, 0.0f));
	directionalLightComponent->SetIntensity(0.8);
	light->AddComponent(std::move(directionalLightComponent));
	Node3D* light2 = new Node3D();
	auto directionalLightComponent2 = std::make_unique<DirectionalLightComponent>();
	directionalLightComponent2->SetIntensity(0.8);
	light2->transform.SetEuler(glm::vec3(4.5f, 4.0f, 0.0f));
	light2->AddComponent(std::move(directionalLightComponent2));


	std::shared_ptr<Material> skyboxMaterial = std::make_shared<Material>();
	std::shared_ptr<Shader> skyboxShader = std::make_shared<Shader>("./litVertex.glsl", "./litFragment.glsl");
	skyboxMaterial->SetShader(skyboxShader);
	skyboxMaterial->SetSpecular(0.0);
	skyboxMaterial->SetAlbedo(glm::vec3(3.0, 3.0, 3.0));
	skyboxMaterial->SetAlbedoMap(std::make_shared<Texture2D>("skybox_texture.png"));




	std::shared_ptr<Model> planeModel = Model::Load("plane.glb");
	std::shared_ptr<Model> sphereModel = Model::Load("sphere.glb");
	std::shared_ptr<Model> cubeModel = Model::Load("cube.glb");
	std::shared_ptr<Model> coneModel = Model::Load("cone.glb");

	AddShape(planeModel, Material::GetDefaultMaterial(), glm::vec3(0.0, 0.0, 0.0));
	AddShape(sphereModel, Material::GetDefaultMaterial(), glm::vec3(4.0, 0.5, 2.0));
	AddShape(cubeModel, Material::GetDefaultMaterial(), glm::vec3(-2.0, 0.5, 5.0));
	AddShape(coneModel, Material::GetDefaultMaterial(), glm::vec3(-8.0, 0.5, -5.0));
	AddShape(sphereModel, Material::GetDefaultMaterial(), glm::vec3(10.0, 0.5, 20.0));
	AddShape(cubeModel, Material::GetDefaultMaterial(), glm::vec3(-20.0, 0.5, 10.0));
	AddShape(coneModel, Material::GetDefaultMaterial(), glm::vec3(8.0, 0.5, 5.0));
	AddShape(sphereModel, Material::GetDefaultMaterial(), glm::vec3(5.0, 0.5, 2.0));
	AddShape(cubeModel, Material::GetDefaultMaterial(), glm::vec3(15.0, 0.5, 5.0));
	AddShape(coneModel, Material::GetDefaultMaterial(), glm::vec3(40.0, 0.5, -5.0));
	AddShape(sphereModel, Material::GetDefaultMaterial(), glm::vec3(20.0, 0.5, -20.0));
	AddShape(cubeModel, Material::GetDefaultMaterial(), glm::vec3(-10.0, 0.5, -40.0));
	AddShape(coneModel, Material::GetDefaultMaterial(), glm::vec3(16.0, 0.5, -2.0));

	Node3D* skybox = AddShape(sphereModel, skyboxMaterial, glm::vec3(0.0,0.0,0.0));
	
	skybox->transform.SetScale(glm::vec3(80.0, 80.0, 80.0));

	Node3D* gunPickup = new Node3D();
	gunPickup->transform.SetPosition(glm::vec3(10.0, 1.0, 5.0));
	auto pickupComponent = std::make_unique<PickupComponent>();
	auto renderComponent = std::make_unique<RenderComponent>();
	auto material = std::make_shared<Material>();
	material->SetShader(skyboxShader);
	material->SetAlbedo(glm::vec3(0.1, 0.1, 0.1));
	material->SetSpecular(0.2);
	material->SetRoughness(0.9);
	renderComponent->SetMaterial(material);
	renderComponent->SetModel(Model::Load("super_simple_pistol.glb"));
	gunPickup->AddComponent(std::move(renderComponent));
	gunPickup->AddComponent(std::move(pickupComponent));

	//Node3D* spotLightCube = new Node3D();
	//spotLightCube->transform.SetEuler(glm::vec3(1.51f, 0.5f, 0.0f));
	//spotLightCube->transform.Translate(glm::vec3(1.0f, 2.0f, 1.0f));
	//std::unique_ptr<SpotLightComponent> lightComponent = std::make_unique<SpotLightComponent>();
	//lightComponent->SetColor(glm::vec3(1.0f, 0.8f, 1.0f));
	//lightComponent->SetIntensity(1.0f);
	//lightComponent->SetInnerAngle(0.5f);
	//lightComponent->SetOuterAngle(0.7f);
	//std::shared_ptr<Shader> lightShader = std::make_shared<Shader>("./defaultVertex.glsl", "./lightFragment.glsl");
	//std::shared_ptr<Material> lightMaterial = std::make_shared<Material>();
	//lightMaterial->SetShader(lightShader);
	//lightMaterial->SetVec3("color", lightComponent->GetColor());
	//spotLightCube->AddComponent(std::move(lightComponent));

	//auto renderComponent = std::make_unique<RenderComponent>();
	//renderComponent->SetMaterial(lightMaterial);
	//renderComponent->SetModel(Model::Load("./model.glb"));

	//spotLightCube->AddComponent(std::move(renderComponent));

	//Node3D* directionalLightNode = new Node3D();
	//directionalLightNode->transform.SetEuler(glm::vec3(0.3f, 0.2f, 0.0f));
	//auto directionalLightComponent = std::make_unique<DirectionalLightComponent>();
	//directionalLightComponent->SetColor(glm::vec3(1.0f, 1.0f, 0.0f));
	//directionalLightComponent->SetIntensity(0.4f);
	//directionalLightNode->AddComponent(std::move(directionalLightComponent));
	/*std::shared_ptr<Texture2D> junoKilometarTexture = std::make_shared<Texture2D>("./texture.png", GL_RGBA);
	std::shared_ptr<Texture2D> containerTexture = std::make_shared<Texture2D>("./container.jpg", GL_RGB);
	junoKilometarTexture->SetWrap(GL_CLAMP_TO_EDGE);
	containerTexture->SetWrap(GL_REPEAT);

	std::shared_ptr<Shader> shader = std::make_shared<Shader>("./litVertex.glsl", "./litFragment.glsl");
	std::shared_ptr<Material> material1 = std::make_shared<Material>();
	std::shared_ptr<Material> material2 = std::make_shared<Material>();

	material1->SetShader(shader);
	material1->SetAlbedoMap(junoKilometarTexture);
	material1->SetSpecularMap(containerTexture);
	material1->SetRoughnessMap(containerTexture);
	material1->SetDepthTestFunc(GL_ALWAYS);
	material2->SetShader(shader);*/

}

void Game::AddGun()

{
	Node3D* gun = new Node3D();
	auto gunComponent = std::make_unique<GunComponent>();
	auto renderComponent = std::make_unique<RenderComponent>();
	auto material = std::make_shared<Material>();
	material->SetShader(std::make_shared<Shader>("./litVertex.glsl", "./litFragment.glsl"));
	material->SetAlbedo(glm::vec3(0.1, 0.1, 0.1));
	material->SetSpecular(0.2);
	material->SetRoughness(0.9);
	renderComponent->SetMaterial(material);
	renderComponent->SetModel(Model::Load("super_simple_pistol.glb"));
	gun->AddComponent(std::move(gunComponent));
	gun->AddComponent(std::move(renderComponent));
}

Node3D* Game::AddShape(std::shared_ptr<Model> model, std::shared_ptr<Material> material, glm::vec3 position)
{
	Node3D* cube = new Node3D();
	auto renderComponent = std::make_unique<RenderComponent>();
	renderComponent->SetModel(model);
	renderComponent->SetMaterial(material);
	cube->transform.SetPosition(position+glm::vec3(0.0,-0.5,0.0));
	cube->AddComponent(std::move(renderComponent));
	return cube;
}