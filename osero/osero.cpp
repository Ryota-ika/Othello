#define WIN_MAX_X 1600
#define WIN_MAX_Y 900
#define WIN_POS_X 0
#define WIN_POS_Y 0

#include "DxLib.h"
#include"sub.h"
#include"pic.h"
#include"act.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nShowCmd) {
	ChangeWindowMode(TRUE);
	DxLib_Init();

	//DXlibの画面大きさ指定
	SetWindowInitPosition(WIN_POS_X, WIN_POS_Y);
	/*SetWindowText("Othello");*/
	SetGraphMode(WIN_MAX_X, WIN_MAX_Y, 32);
	SetBackgroundColor(255, 255, 255);
	SetDrawScreen(DX_SCREEN_BACK);

	Col.Read();
	Fon.Read();
	Pic.Read();

	while (ScreenFlip() == 0 &&
		ClearDrawScreen() == 0 &&
		ProcessMessage() == 0 &&
		Key.Read() == 0 &&
		Key.Inf[KEY_INPUT_ESCAPE] == 0)
	{
		Act.Out();
	}

	//WaitKey();

	DxLib_End();
	return 0;
}