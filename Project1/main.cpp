#include"raylib.h"
#include"iostream"

using namespace std;
const int SCREEN_WIDHT = 1280;
const int SCREEN_HEIGHT = 900;


enum  SCREEN
{
	MENU,
	GAME,
	CREDITS,
	EXIT,
};

int centerScreenX;
int centerScreenY;
int screenX;

//bool pause;
//bool resetPause;
//bool exitGame;
//bool gameOver;
bool loadJumping = false;
//float scrollingBack = 0.0f;
float scrollingSemiBack = 0.0f;
float scrollingMid = 0.0f;
float scrollingFore = 0.0f;

Texture2D background;

Rectangle obstaculo_box;
struct Patrol
{
	
	Vector2 velocity;
	Vector2 gravity;
};

void Input();
void Update(int&screen, bool& gameOver);
void Draw(/*bool& pause,*/ int& screen/*, bool& resetPause*/);

void Pause(bool& pause, int& screen, bool& resetPause);
void DrawMenu(Rectangle cursor, Rectangle game, Rectangle credits, Rectangle instruction);
void TextMenu();
void Menu(int& screen);
void Game(Rectangle game, Rectangle caja, int& screen);
void ExitGame(Rectangle exit, Rectangle caja, int& screen);
void Credits(Rectangle credits, Rectangle cursor, int& screen);
Rectangle Cursor(Rectangle& cursor);
Rectangle patrol;


//Texture2D semibackground = LoadTexture(" marsfar.png");
//Texture2D midground = LoadTexture(" marsmid.png");
//Texture2D foreground = LoadTexture(" marsclose.png");

int main()
{
	InitWindow(SCREEN_WIDHT, SCREEN_HEIGHT, "Moon Patrol");

	background = LoadTexture("marsmountain.png");

	Rectangle regresarMenu = { static_cast<int>(GetScreenWidth()) - 980.0f, static_cast<int>(GetScreenHeight()) - 135.0f,250, 100 };
	Rectangle cursor = { 0 };

	centerScreenX = GetScreenWidth() / 2;
	centerScreenY = GetScreenHeight() / 2;
	screenX = GetScreenWidth() - 10;
	/*Patrol patrol;
	patrol.velocity.x = 0;
	patrol.velocity.y = 0;
	patrol.gravity.x = 0;
	patrol.gravity.y = 0;
	*/
	 bool pause = false;
	 bool resetPause = false;
	 bool exitGame = false;
	 bool gameOver = false;
	 int screen = MENU;
	
	obstaculo_box = { static_cast<float>(screenX),static_cast<float>(centerScreenY+5), 15.0f, 15.0f };

	patrol= { static_cast<float>(centerScreenX),
			static_cast<float>(centerScreenY),
			20.0f,
			20.0f };

	/*SetTargetFPS(60);*/
	while (!WindowShouldClose() && !exitGame)
	{
	switch (screen)
	{
	 case MENU:
		Menu(screen);
		Draw(/*pause,*/ screen/*, resetPause*/);
		break;

	 case GAME:

		
			if (!gameOver)
			{
				if (!pause)
				{
					Input();
					Update(screen, gameOver);
					Draw( /*pause,*/ screen/*, resetPause*/);
					Pause(pause, screen, resetPause);
				}
			}

		break;

	 case CREDITS:

		cursor = Cursor(cursor);

		/*DrawText("CREDITOS:", GetScreenWidth() / 2 - 300, GetScreenHeight() / 2 - 350, 30, WHITE);
		DrawText("SONIDO METEORO Robinhood76 ", 0, GetScreenHeight() / 2 - 200, 20, WHITE);
		DrawText("PAGINA PRINCIPAL:", 0, GetScreenHeight() / 2 - 150, 20, WHITE);
		DrawText("https://freesound.org/people/Robinhood76/", 0, GetScreenHeight() / 2 - 100, 20, WHITE);
		DrawText("PAGINA DEL SONIDO DESCARGADO:", 0, GetScreenHeight() / 2 - 50, 20, WHITE);
		DrawText(" https://freesound.org/people/Robinhood76/sounds/503554/", 0, GetScreenHeight() / 2 - 20, 20, WHITE);
		DrawText("MUSICA: StephieQueen", 0, GetScreenHeight() / 2, 20, WHITE);
		DrawText("PAGINA PRINCIPAL:", 0, GetScreenHeight() / 2 + 20, 20, WHITE);
		DrawText("https://freesound.org/people/StephieQueen/", 0, GetScreenHeight() / 2 + 50, 20, WHITE);
		DrawText("PAGINA DE LA MUSICA: ", 0, GetScreenHeight() / 2 + 80, 20, WHITE);
		DrawText(" https://freesound.org/people/StephieQueen/sounds/650556/", 0, GetScreenHeight() / 2 + 100, 20, WHITE);
		DrawText("ASSETS:https://kenney.nl/assets/space-shooter-redux", GetScreenWidth() / 2 - 200, GetScreenHeight() / 2 + 150, 20, WHITE);*/
		DrawText("CODIGO: LEONARDO BRIZUELA", GetScreenWidth() / 2 - 200, GetScreenHeight() / 2 + 250, 20, WHITE);

		BeginDrawing();
		ClearBackground(BLACK);

		DrawRectangleRec(regresarMenu, PURPLE);
		DrawText("VOLVER AL MENU", GetScreenWidth() - 970, GetScreenHeight() - 100, 26, WHITE);

		if (CheckCollisionRecs(regresarMenu, cursor))
		{

			DrawRectangleRec(regresarMenu, VIOLET);
			DrawText("VOLVER AL MENU", GetScreenWidth() - 970, GetScreenHeight() - 100, 26, WHITE);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{

				DrawRectangleRec(regresarMenu, DARKPURPLE);
				DrawText("VOLVER AL MENU", GetScreenWidth() - 970, GetScreenHeight() - 100, 26, WHITE);

				screen = MENU;


			}

		}

		EndDrawing();

		break;

	 case EXIT:

		exitGame = true;
		
		break;


	 default:
		 UnloadTexture(background);

		CloseWindow();
		return 0;
		break;
	}
  }

	
}
 
void Input()
{
	if (IsKeyPressed(KEY_SPACE))
	{
		loadJumping = true;
	}

	if (loadJumping)
	{
		patrol.y -= 50 * GetFrameTime();
		cout << patrol.y << endl;
		if (patrol.y < 400)
		{
			loadJumping = false;
		}
	}

	/*else if(IsKeyReleased(KEY_SPACE))
	{
		patrol.y += 50;
	}*/
}

void Update(int& screen,bool& gameOver )
{
	obstaculo_box.x -= 8 *GetFrameTime()*60.0f;

	if (obstaculo_box.x < 0)
	{
		obstaculo_box.x = static_cast<float>(screenX);
	}

	if (CheckCollisionRecs(Rectangle(patrol), Rectangle(obstaculo_box)))
	{
		gameOver = true;
		screen = MENU;
	}
}

void Draw(/*bool& pause,*/ int& screen/*, bool& resetPause*/)
{
	BeginDrawing();
	ClearBackground(BLACK);
	Vector2	scrollingBack;
	scrollingBack.x = 0.0f;
	scrollingBack.y=20;
	//scrollingBack.x -= 0.1f;
	/*scrollingSemiBack -= 0.25f;
	scrollingMid -= 0.5f;
	scrollingFore -= 1.0f;*/



	/*if (scrollingBack.x <= -background.width * 2) scrollingBack.x = 0;*/
	/*if (scrollingMid <= -semibackground.width * 2) scrollingMid = 0;
	if (scrollingMid <= -midground.width * 2) scrollingMid = 0;
	if (scrollingFore <= -foreground.width * 2) scrollingFore = 0;*/

	if (screen==GAME)
	{
		
		DrawTextureEx(background,  scrollingBack, 0.0f, 2.0f, WHITE);
		//DrawTextureEx(background, Vector2 { background.width* 2 + scrollingBack.x, scrollingBack.y }, 0.0f, 2.0f, WHITE);

		/*DrawTextureEx(semibackground, (Vector2) { scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
		DrawTextureEx(semibackground, (Vector2) { semibackground.width * 2 + scrollingBack, 20 }, 0.0f, 2.0f, WHITE);


		DrawTextureEx(midground, (Vector2) { scrollingMid, 20 }, 0.0f, 2.0f, WHITE);
		DrawTextureEx(midground, (Vector2) { midground.width * 2 + scrollingMid, 20 }, 0.0f, 2.0f, WHITE);


		DrawTextureEx(foreground, (Vector2) { scrollingFore, 70 }, 0.0f, 2.0f, WHITE);
		DrawTextureEx(foreground, (Vector2) { foreground.width * 2 + scrollingFore, 70 }, 0.0f, 2.0f, WHITE);*/

		DrawRectangle(static_cast<int>(obstaculo_box.x), static_cast<int>(obstaculo_box.y), static_cast<int> (obstaculo_box.width), static_cast<int> (obstaculo_box.height), WHITE);

		DrawRectangle(static_cast<int>(patrol.x), static_cast<int>(patrol.y), static_cast<int>(patrol.width), static_cast<int>(patrol.height), RED);
	
	}

	EndDrawing();
}


void Pause(bool& pause, int& screen, bool& resetPause)
{
	if (pause == true)
	{
		Rectangle caja_pausa = { static_cast<int>(GetScreenWidth()) / static_cast <float>(2) - 350, static_cast<int>(GetScreenHeight()) / static_cast <float>(2) - 90, 250, 100 };
		Rectangle volverMenu = { static_cast<int>(GetScreenWidth()) / static_cast <float>(2) + 100, static_cast<int>(GetScreenHeight()) / static_cast <float>(2) - 90,250, 100 };
		Rectangle cursor = { 0 };

		cursor = Cursor(cursor);

		DrawRectangleRec(caja_pausa, PURPLE);
		DrawText("PAUSA", GetScreenWidth() / 2 - 280, GetScreenHeight() / 2 - 50, 30, WHITE);


		if (CheckCollisionRecs(caja_pausa, cursor))
		{

			DrawRectangleRec(caja_pausa, VIOLET);
			DrawText("PAUSA", GetScreenWidth() / 2 - 280, GetScreenHeight() / 2 - 50, 30, WHITE);

			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{

				DrawRectangleRec(caja_pausa, DARKPURPLE);
				DrawText("PAUSA", GetScreenWidth() / 2 - 280, GetScreenHeight() / 2 - 50, 30, WHITE);
				pause = !pause;

			}

		}
		DrawRectangleRec(volverMenu, PURPLE);
		DrawText("VOLVER AL MENU", GetScreenWidth() / 2 + 110, GetScreenHeight() / 2 - 50, 26, WHITE);

		if (CheckCollisionRecs(volverMenu, cursor))
		{

			DrawRectangleRec(volverMenu, VIOLET);
			DrawText("VOLVER AL MENU", GetScreenWidth() / 2 + 110, GetScreenHeight() / 2 - 50, 26, WHITE);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{

				DrawRectangleRec(volverMenu, DARKPURPLE);
				DrawText("VOLVER AL MENU", GetScreenWidth() / 2 + 110, GetScreenHeight() / 2 - 50, 26, WHITE);

				screen = MENU;
				resetPause = !resetPause;


			}

		}

	}

	if (IsKeyPressed('P') || IsKeyPressed('p') || IsKeyPressed(KEY_ESCAPE))
	{
		pause = !pause;

		//cout << pause << endl;
		//0 false
		//1 true
	}
}

void DrawMenu(Rectangle cursor, Rectangle game, Rectangle credits, Rectangle instruction)
{
	DrawRectangleRec(cursor, PURPLE);
	DrawRectangleRec(game, PURPLE);
	DrawRectangleRec(credits, PURPLE);
	DrawRectangleRec(instruction, PURPLE);

}

void TextMenu()
{
	DrawText("MOON PATROL", GetScreenWidth() / 2 - 290, 100, 100, WHITE);
	DrawText("SALIR", GetScreenWidth() / 2 - 80, GetScreenHeight() / 2 + 200, 30, WHITE);
	DrawText("CREDITOS", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 70, 30, WHITE);
	DrawText("JUGAR", GetScreenWidth() / 2 - 80, GetScreenHeight() / 2 - 50, 30, WHITE);


}

void Menu(int& screen)
{

	Rectangle game = { static_cast<int>(GetScreenWidth()) / static_cast <float>(2) - 150, static_cast<int>(GetScreenHeight()) / static_cast <float>(2) - 90, 250, 100 };
	Rectangle exit = { static_cast<int>(GetScreenWidth()) / static_cast <float>(2) - 150, static_cast<int>(GetScreenHeight()) / static_cast <float>(2) + 160, 250, 100 };
	Rectangle credits = { static_cast<int>(GetScreenWidth()) / static_cast <float>(2) - 150, static_cast<int>(GetScreenHeight()) / static_cast <float>(2) + 35, 250, 100 };


	Rectangle cursor = { 0 };
	cursor = Cursor(cursor);

	DrawMenu(cursor, game, credits, exit);

	TextMenu();

	ExitGame(exit, cursor, screen);
	Game(game, cursor, screen);
	Credits(credits, cursor, screen);

}

void Game(Rectangle game, Rectangle caja, int& screen)
{
	if (CheckCollisionRecs(game, caja))
	{
		DrawRectangleRec(game, VIOLET);
		DrawText("JUGAR", GetScreenWidth() / 2 - 80, GetScreenHeight() / 2 - 50, 30, WHITE);

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			screen = GAME;
			DrawRectangleRec(game, DARKPURPLE);
			DrawText("JUGAR", GetScreenWidth() / 2 - 80, GetScreenHeight() / 2 - 50, 30, WHITE);

		}

	}
}

void ExitGame(Rectangle exit, Rectangle caja, int& screen)
{
	if (CheckCollisionRecs(exit, caja))
	{

		DrawRectangleRec(exit, VIOLET);
		DrawText("SALIR", GetScreenWidth() / 2 - 80, GetScreenHeight() / 2 + 200, 30, WHITE);

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			DrawRectangleRec(exit, DARKPURPLE);
			DrawText("SALIR", GetScreenWidth() / 2 - 80, GetScreenHeight() / 2 + 200, 30, WHITE);
			screen = EXIT;
		}


	}
}

void Credits(Rectangle credits, Rectangle cursor, int& screen)
{
	if (CheckCollisionRecs(credits, cursor))
	{
		DrawRectangleRec(credits, VIOLET);
		DrawText("CREDITOS", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 70, 30, WHITE);
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			DrawRectangleRec(credits, DARKPURPLE);
			DrawText("CREDITOS", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 70, 30, WHITE);
			screen = CREDITS;
		}
	}
}

Rectangle Cursor(Rectangle& cursor)
{
	Rectangle _cursor = { static_cast<int>(GetScreenWidth()) / static_cast <float>(2) - 250, static_cast<int>(GetScreenHeight()) / static_cast <float>(2) + 200, 5, 5 };
	cursor.x = GetMouseX() - cursor.width / 2;
	cursor.y = GetMouseY() - cursor.height / 2;
	return cursor;

}

