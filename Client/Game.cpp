#include "pch.h"
#include "Game.h"
#include "Engine.h"

void Game::Init(const WindowInfo& Info)
{
    GEngine->Init(Info);
}

void Game::Update()
{
    GEngine->Render();
}
