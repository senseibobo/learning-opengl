#include "memory"
#include "GunComponent.h"
#include "Camera.h"
#include "Model.h"
#include "Material.h"
#include "RenderComponent.h"

GunComponent* GunComponent::gun = nullptr;

void GunComponent::Process(float delta)
{
	recoilT -= delta*3.0f;
	if (recoilT < 0.0) recoilT = 0.0;
	Camera* cam = Camera::currentCamera;
	Node3D* owner3D = (Node3D*)owner;
	owner3D->transform.SetPosition(cam->GetPosition() + cam->GetForwardVector()*2.0f + cam->GetRightVector() - recoilT * cam->GetUpVector()*0.5f);
	owner3D->transform.SetQuaternion(glm::quatLookAt(-cam->GetForwardVector() + recoilT*cam->GetUpVector()*0.8f, glm::vec3(0.0, 1.0, 0.0)));
}

void GunComponent::Shoot()
{
	recoilT = 0.5f;
	Node3D* bullet = new Node3D();
	Node3D* owner3D = (Node3D*)owner;
	bullet->transform.SetPosition(owner3D->transform.GetPosition());
	bullet->transform.SetScale(glm::vec3(0.5, 0.5, 0.5));
	std::shared_ptr<Model> godotModel = Model::Load("godot_plush_model.glb");
	std::shared_ptr<Material> godotMaterial = std::make_shared<Material>();
	std::shared_ptr<Shader> godotShader = std::make_shared<Shader>("./litVertex.glsl", "./litFragment.glsl");
	godotMaterial->SetShader(godotShader);
	godotMaterial->SetAlbedoMap(std::make_shared<Texture2D>("godot_plush_albedo.png"));
	godotMaterial->SetSpecular(0.1);
	godotMaterial->SetRoughness(0.8);
	auto renderComponent = std::make_unique<RenderComponent>();
	renderComponent->SetModel(godotModel);
	renderComponent->SetMaterial(godotMaterial);
	auto godotComponent = std::make_unique<GodotComponent>();
	godotComponent->SetDirection(owner3D->transform.GetForwardVector());
	bullet->AddComponent(std::move(godotComponent));
	bullet->AddComponent(std::move(renderComponent));
	bullet->transform.SetQuaternion(owner3D->transform.GetQuaternion());
}
