#ifndef DEMO_H
#define DEMO_H


#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <irrKlang/irrKlang.h>
#include <imgui\imgui.h>
#include <imgui/imgui_impl_sdl_gl3.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <map>


#include "Game.h"

#define NUM_FRAMES 1
#define FRAME_DUR 80
#define FONTSIZE 20
#define FONTNAME "fonts/chintzy.ttf"

using namespace glm;
using namespace irrklang;

class Demo :
	public Engine::Game
{

	struct Character {
		GLuint TextureID; // ID handle of the glyph texture
		ivec2 Size; // Size of glyph
		ivec2 Bearing; // Offset from baseline to left/top of glyph
		GLuint Advance; // Offset to advance to next glyph
	};
public:
	Demo();
	~Demo();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	bool IsCollided(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);
	void OnUserDefinedEvent(SDL_Event & evt);
	void InitFont();
private:
	void RenderText(string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color);
	map<GLchar, Character> Characters;
	int angka1, angka2, jawaban, locJawaban;
	int pilihan[3];
	int operat[3];
	int locOperat;
	int menu=0;
	int score = 0;
	int scoreDis = 0;
	GLuint VBO, VAO, EBO, texture, program,program2, program3, program4, program5, texture2, texture3, texture4, texture5,VBO2, VAO2, EBO2, VBO4, VAO4, EBO4, VBO3, VAO3, EBO3, VBO5, VAO5, EBO5;
	float frame_dur = 0, frame_width = 0, frame_width2 = 0, frame_width3 = 0, frame_width4 = 0, xpos = 0.03f, ypos = 1, xpos2 = 0.0f, ypos2 = 0, rot = 0, crateWidth, crateHeight, spriteWidth, startWidth, startHeight, spriteHeight, indexpalang = 2;
	unsigned int frame_idx = 0;
	void BuildSprite();
	void DrawStartScreen();
	void DrawGameOverScreen();
	void BuildScreenStart();
	void BuildScreenGameOver();
	void DrawSprite();
	void DrawPalang();
	void BuildPalang();
	void DrawGameScreen();
	void BuildGameScreen();
	void UpdateSprite(float deltaTime);
	void MoveSprite(float deltaTime);
	double directi=NULL;
	int jawabUser = NULL;
	int st = 1;
	bool statusAkhir = true;
	bool statusTabrakan=false;
	ImVec4 clear_color = ImColor(100, 50, 80);
	bool show_window = true;
};
#endif

