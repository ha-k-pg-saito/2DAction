#include"enum.h"
#include"Title.h"
#include"Src/Engine/Engine.h"
#include"Button.h"

static int FadeOut = 0;
static bool IsPushed = false;
static float ClickCounter = 0;
float min = 0;
float max=1800;
float current = 70;
float slide;

void UpdateTitleScene()
{
	// g_SceneStep�̒l����e�X�e�b�v�֐������s
	switch (g_SceneStep)
	{
	case SceneStep::Init:
		InitTitleScene();
		break;
	case SceneStep::Run:
		RunTitleScene();
		break;
	case SceneStep::Finish:
		FinishTitleScene();
		break;
	}

	if (Cursor() == false)
	{
		g_ButtonStatus = ButtonStatus::Normal;
	}
	if (Cursor() == true)
	{
		g_ButtonStatus = ButtonStatus::OnCursor;
	}
	if (Cursor() == true && Engine::IsMouseButtonPushed(MouseButton::Left))
	{
		g_ButtonStatus = ButtonStatus::Clicked;
	}
}

void InitTitleScene()
{
	Engine::Update();

	Engine::DrawFont(0, 0, "�^�C�g���V�[���̏�����\n", FontSize::Large, FontColor::White);

	Engine::LoadTexture("StartButton", "Res/SampleButton.png");


	if (Engine::IsKeyboardKeyHeld(DIK_A))
	{
		g_SceneStep = SceneStep::Run;
	}
}

void RunTitleScene()
{
	Engine::Update();

	Engine::DrawFont(0, 0, "�^�C�g���V�[��\n", FontSize::Large, FontColor::White);
	/*Engine::DrawTexture(0,0,"mona",255,0,0.6f,0.6f);
	Engine::DrawRect(0, 0, 1000, 1000, 0x000000,FadeOut);

	if (Engine::IsKeyboardKeyPushed(DIK_Z))
	{
		IsPushed = true;
	}

	if (IsPushed == true)
	{
		FadeOut += 1;
	}

	if (FadeOut >= 255)
	{
		g_SceneKind = SceneKind::GameScene;
		g_SceneStep = SceneStep::Init;

		FadeOut = 0;

		IsPushed = false;
	}*/

	if (Engine::IsKeyboardKeyHeld(DIK_B))
	{
		g_SceneStep = SceneStep::Finish;
	}
}

void FinishTitleScene()
{
	Engine::Update();

	slide = (current - min) / (max - min);

	current ++;
	if (current >= max)
	{
		current = 0;
	}
		
	
	
	

	Engine::DrawFont(0, 0, "�^�C�g���V�[���̏I��\n", FontSize::Large, FontColor::White);
	Engine::DrawTexture(0, 0, "mona", 255, 0, 0.6f, 0.6f);
	Engine::DrawRect(0, 0, 1000, 1000, 0x000000, FadeOut);
	Engine::DrawRect(0, 0, 640*slide, 50, 0x0000ff,128);
	Engine::DrawRect(0, 0, 640, 50, 0xffffff,64);


	if (g_ButtonStatus == ButtonStatus::Normal)
	{
		Engine::DrawTextureUV(100, 400, "StartButton", 0.0f, 0.0f, 256.0f, 128.0f);
	}
	if (g_ButtonStatus == ButtonStatus::OnCursor)
	{
		Engine::DrawTextureUV(100, 400, "StartButton", 256.0f, 0.0f, 256.0f, 128.0f);
	}
	if (g_ButtonStatus == ButtonStatus::Clicked)
	{
		IsPushed = true;
	}
	if (IsPushed == true)
	{
		ClickCounter += 0.2;
		FadeOut += 1;

		if (ClickCounter < 10.0f)
		{
			Engine::DrawTextureUV(100.0f, 400.0f, "StartButton", 256.0f, 128.0f, 256.0f, 128.0f);
		}
	}
	
	if (ClickCounter >= 10.0f)
	{
		Engine::DrawTextureUV(100.0f, 400.0f, "StartButton", 0.0f, 128.0f, 256.0f, 128.0f);

		if (FadeOut >= 255)
		{
			g_SceneKind = SceneKind::GameScene;
			g_SceneStep = SceneStep::Run;

			FadeOut = 0;
			ClickCounter = 0.0f;

			IsPushed = false;
		}
	}

	if (Engine::IsKeyboardKeyHeld(DIK_C))
	{
		// �X�e�b�v��Init�ɕύX(���̃V�[���̂��߂̏�����)
		g_SceneStep = SceneStep::Init;

		// SceneKind��ύX��������ނɕύX����
		g_SceneKind = SceneKind::GameScene;
	}
}