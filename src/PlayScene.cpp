#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "Util.h"


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
	m_pTarget->getTransform()->position = glm::vec2(500.0f, 400.0f);
	addChild(m_pTarget);

	m_pObstacle = new Obstacle();
	m_pObstacle->getTransform()->position = glm::vec2(300.0f, 300.0f);
	addChild(m_pObstacle);

	m_pSpaceship = new Spaceship();
	m_pSpaceship->getTransform()->position = glm::vec2(100.0f, 300.0f);
	m_pSpaceship->setEnabled(false);
	m_pSpaceship->setDestination(m_pTarget->getTransform()->position);
	addChild(m_pSpaceship);
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	




	ImGui::Begin("Target Mover", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);
	static float float1 = 10.0f;
	if (ImGui::SliderFloat("MAXSPEED", &float1, 0.0f, 100.0f))
	{
		m_pSpaceship->setMaxSpeed(float1);
	}
	static float angleInRadians = 0.0f;
	//if (ImGui::SliderAngle("Orientation Angle", &angleInRadians))
	//{
	//	m_pSpaceship->setRotation(angleInRadians * Util::Rad2Deg);
	//}
	static float accelerationRate = 2.0f;
	if (ImGui::SliderFloat("Acceleration Rate", &accelerationRate, 0.0f, 50.0f))
	{
		m_pSpaceship->setAccelerationRate(accelerationRate);
	}
	static float turnRate = 5.0f;
	if (ImGui::SliderFloat("Turn Rate", &turnRate, 0.0f, 20.0f))
	{
		m_pSpaceship->setTurnRate(turnRate);
	}
	if(ImGui::Button("START"))
	{	
		m_pSpaceship->setEnabled(true);
	}

	ImGui::SameLine();
	if (ImGui::Button("RESTART"))
	{
		m_pSpaceship->getTransform()->position = glm::vec2(100.0f, 100.0f);
		m_pSpaceship->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pSpaceship->setRotation(0.0f);
		m_pSpaceship->setEnabled(false);
		turnRate = 5.0f;
		accelerationRate = 2.0f;
		float1 = 10.0f;
		angleInRadians = m_pSpaceship->getRotation();
		
	}
	

	ImGui::Separator();

	static float float2[2] = {m_pTarget->getTransform()->position.x, m_pTarget->getTransform()->position.y};
	if(ImGui::SliderFloat2("TARGET", float2, 0.0f, 800.0f))
	{
		m_pTarget->getTransform()->position = glm::vec2(float2[0], float2[1]);
		m_pSpaceship->setDestination(m_pTarget->getTransform()->position);
	}
	
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
