#include "GSMenu.h"
#include "Camera.h"

GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU), 
	m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_textGameName(nullptr)
{
}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	//init sound
	gSoloud.init(); // Initialize SoLoud
	m_titleBGM.load("titleBGM.wav");
	m_titleBGM.setLooping(true);
	gSoloud.play(m_titleBGM); // Play BGM
	handle = gSoloud.play(m_titleBGM);

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	//gamelogo
	texture = ResourceManagers::GetInstance()->GetTexture("gametil.tga");
	m_gameTitle = std::make_shared<Sprite2D>(model, shader, texture);
	m_gameTitle->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2 - 100);
	m_gameTitle->SetSize(600, 280);

	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_play2.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight/2 + 150);
	button->SetSize(150, 150);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);		
		});
	m_listButton.push_back(button);


	// instruction button
	texture = ResourceManagers::GetInstance()->GetTexture("q_button.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 190, 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_INSTRUCTION);
		});
	m_listButton.push_back(button);
	
	// credit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_credit.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 120, 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_CREDIT);
		
		});
	m_listButton.push_back(button);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_x.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);

	
}

void GSMenu::Exit()
{
}


void GSMenu::Pause()
{
}

void GSMenu::Resume()
{
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			gSoloud.setPauseAll(true);
			break;
		}
	}
}

void GSMenu::HandleMouseMoveEvents(int x, int y)
{
}

void GSMenu::Update(float deltaTime)
{
	
	m_background->Update(deltaTime);
	if (gSoloud.getPause(handle)) handle = gSoloud.play(m_titleBGM);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
		
	}
}

void GSMenu::Draw()
{
	m_background->Draw();	
	m_gameTitle->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	
}
