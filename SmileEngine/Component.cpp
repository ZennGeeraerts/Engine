#include "SmileEnginePCH.h"
#include "Component.h"

dae::Component::Component(dae::GameObject* pGameObject)
	: m_pGameObject{ pGameObject }
{

}

dae::Component::~Component() = default;

void dae::Component::Update() {}

void dae::Component::FixedUpdate(){}

void dae::Component::LateUpdate(){}

void dae::Component::Render() const{}
