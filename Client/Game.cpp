#include "pch.h"
#include "Game.h"
#include "Engine.h"


shared_ptr<Mesh> mesh = make_shared<Mesh>();
shared_ptr<Shader> shader = make_shared<Shader>();

void Game::Init(const WindowInfo& Info)
{
	GEngine->Init(Info);

	vector<Vertex> vec(3);
	vec[0].Pos = Vec3(0.f, 0.5f, 0.5f);
	vec[0].Color = Vec4(1.f, 0.f, 0.f, 1.f);
	vec[1].Pos = Vec3(0.5f, -0.5f, 0.5f);
	vec[1].Color = Vec4(0.f, 1.0f, 0.f, 1.f);
	vec[2].Pos = Vec3(-0.5f, -0.5f, 0.5f);
	vec[2].Color = Vec4(0.f, 0.f, 1.f, 1.f);
	mesh->Init(vec);

	shader->Init(L"..\\Resources\\Shader\\default.hlsli");

	GEngine->GetCmdQueue()->WaitSync();
}

void Game::Update()
{
    GEngine->RenderBegin();

	shader->Update();
	mesh->Render();
	
    GEngine->RenderEnd();
}
