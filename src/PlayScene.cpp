#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"


// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}
// test
void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	m_pTarget = new Target();
	m_pTarget->getTransform()->position = glm::vec2(400.0f, 300.0f);
	addChild(m_pTarget);



	m_pSpaceship = new Spaceship();
	m_pSpaceship->getTransform()->position = glm::vec2(100.0f, 100.0f);
	m_pSpaceship->setEnabled(false);
	addChild(m_pSpaceship);
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Target Mover", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if(ImGui::Button("START"))
	{	
		m_pSpaceship->setEnabled(true);
	}
	ImGui::SameLine();
	if (ImGui::Button("restart"))
	{
		m_pSpaceship->getTransform()->position = glm::vec2(100.0f, 100.0f);
		m_pSpaceship->setEnabled(false);
	}
	

	ImGui::Separator();

	static float float2[2] = {m_pTarget->getTransform()->position.x, m_pTarget->getTransform()->position.y};
	if(ImGui::SliderFloat2("TARGET", float2, 0.0f, 800.0f))
	{
		m_pTarget->getTransform()->position = glm::vec2(float2[0], float2[1]);
	}
	
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
