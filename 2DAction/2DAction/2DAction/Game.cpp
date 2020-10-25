#include"enum.h"
#include"Game.h"
#include"Src/Engine/Engine.h"
#include"Button.h"

static int FadeIn = 255;

void UpdateGameScene()
{
	// g_SceneStepの値から各ステップ関数を実行する
	switch (g_SceneStep)
	{
	case SceneStep::Init:
		InitGameScene();
		break;
	case SceneStep::Run:
		RunGameScene();
		break;
	case SceneStep::Finish:
		FinishGameScene();
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

void InitGameScene()
{
	Engine::Update();

	// 初期化
	//printf("ゲームシーンの初期化\n");
	Engine::DrawFont(0, 0, "ゲームシーンの初期化\n", FontSize::Large, FontColor::White);

	// ステップをRunに変更 => 初期化が終わったら変更
	if (Engine::IsKeyboardKeyHeld(DIK_D))
	{
		g_SceneStep = SceneStep::Run;
	}
}

void RunGameScene()
{
	Engine::Update();
	
	Engine::DrawFont(0, 0, "ゲームシーン\n", FontSize::Large, FontColor::White);
	Engine::DrawTexture(0, 0, "Inori",255, 0, 0.8f, 0.8f);
	Engine::DrawRect(0, 0, 1000, 1000, 0x000000, FadeIn);

	Engine::DrawTextureUV(100.0f, 400.0f, "StartButton", 0.0f, 128.0f, 256.0f, 128.0f);
	
	FadeIn -= 1;

	if (FadeIn <= 0)
	{
		FadeIn = 0;
	}

	if (Engine::IsKeyboardKeyPushed(DIK_Z))
	{
		if (FadeIn <= 0)
		{
			FadeIn = 255;

			g_SceneKind = SceneKind::TitleScene;
			g_SceneStep = SceneStep::Init;
		}	
	}

	if (Engine::IsKeyboardKeyHeld(DIK_E))
	{
		g_SceneStep = SceneStep::Finish;

		FadeIn = 255;
	}
	
}

void FinishGameScene()
{
	Engine::Update();

	// 後始末
	//printf("ゲームシーン終了\n");
	Engine::DrawFont(0, 0, "ゲームシーンの終了\n", FontSize::Large, FontColor::White);

	if (Engine::IsKeyboardKeyHeld(DIK_F))
	{
		// ステップをInitに変更(次のシーンのための初期化)
		g_SceneStep = SceneStep::Init;

		// SceneKindを変更したい種類に変更する
		g_SceneKind = SceneKind::TitleScene;
	}
}