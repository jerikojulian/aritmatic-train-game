#include "Demo.h"


Demo::Demo()
{
}


Demo::~Demo()
{
	ImGui_ImplSdlGL3_Shutdown();
}

void Demo::Init()
{
	ISoundEngine *SoundEngine = createIrrKlangDevice();
	SoundEngine->play2D("Waterworks.ogg", GL_TRUE);
	BuildPalang();
	BuildSprite();
	BuildScreenStart();
	BuildGameScreen();
	BuildScreenGameOver();
	ImGui_ImplSdlGL3_Init(this->window);
	InitFont();
	
	
}

void Demo::Update(float deltaTime)
{
	ImGuiStyle style;
	
	
	if (menu == 0) {
		ImGui_ImplSdlGL3_NewFrame(window);
		ImGui::SetNextWindowPos(ImVec2(323, 200));
		ImGui::SetNextWindowSize(ImVec2(175, 400), ImGuiSetCond_Once);
		ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(1.0f,1.0f,1.0f,0.0f);
		ImGuiWindowFlags window_flags = 0;
		window_flags |= ImGuiWindowFlags_NoTitleBar;
		window_flags |= ImGuiWindowFlags_NoResize;
		ImGui::Begin("Main Menu", false, window_flags);
		style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
		/*ImGui::Text("Instruction:");
		ImGui::Text("<arrow right> for turn right");
		ImGui::Text("<arrow kiri> for turn left");
		ImGui::Text("<arrow down> for lurus");*/
		ImGui::Text("");
		ImGui::Text("");
		ImGui::PushID(1);
		ImGui::PushStyleColor(ImGuiCol_Button, ImColor::HSV(0.0f, 0.0f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor::HSV(1 / 7.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImColor::HSV(1 / 7.0f, 0.8f, 0.8f));
		ImGui::Text("   ");
		if (ImGui::Button("MULAI",ImVec2(150.0f, 50.0f))) {
			ISoundEngine *SoundEngine = createIrrKlangDevice();
			SoundEngine->play2D("button.mp3", GL_FALSE);
			menu = 1;
		}
		ImGui::Text("                        ");
		if (ImGui::Button("KELUAR", ImVec2(150.0f, 50.0f))) {

			SDL_Quit();
			exit(1);
		}
		ImGui::PopStyleColor(3);
		ImGui::PopID();
		ImGui::End();

	}

	if (menu == 1) {

		UpdateSprite(deltaTime);
		MoveSprite(deltaTime);
		

	}

	if (menu == 2) {
		

		ImGui_ImplSdlGL3_NewFrame(window);
		
		ImGui::SetNextWindowPos(ImVec2(123, 270));
		ImGui::SetNextWindowSize(ImVec2(700, 300),ImGuiSetCond_Always);
		ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
		ImGuiWindowFlags window_flags = 0;
		window_flags |= ImGuiWindowFlags_NoTitleBar;
		window_flags |= ImGuiWindowFlags_NoResize;
		ImGui::Begin("Main Menu", false, window_flags);
		style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
		/*ImGui::Text("Instruction:");
		ImGui::Text("<arrow right> for turn right");
		ImGui::Text("<arrow kiri> for turn left");
		ImGui::Text("<arrow down> for lurus");*/
		ImGui::Text("                              SCORE ANDA %i",scoreDis);
		ImGui::Text("");
		ImGui::Text("");
		ImGui::Text("");
		ImGui::Text("");
		ImGui::Text("");
		ImGui::Text("");
		ImGui::Text("");
		ImGui::Text("");
		ImGui::PushID(2);
		ImGui::PushStyleColor(ImGuiCol_Button, ImColor::HSV(0.0f, 0.0f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor::HSV(1 / 7.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImColor::HSV(1 / 7.0f, 0.8f, 0.8f));
		ImGui::Text("   ");
		if (ImGui::Button("RETRY", ImVec2(150.0f, 50.0f))) {
			ISoundEngine *SoundEngine = createIrrKlangDevice();
			SoundEngine->play2D("button.mp3", GL_FALSE);
			menu = 1;
		}
		ImGui::SameLine();
		ImGui::Text("                              ");
		ImGui::SameLine();
		if (ImGui::Button("KELUAR", ImVec2(150.0f, 50.0f))) {
			SDL_Quit();
			exit(1);
		}
		ImGui::PopStyleColor(3);
		ImGui::PopID();
		ImGui::End();

	}
		
	
	//
}

void Demo::Render()
{
	//Setting Viewport
	glViewport(0, 0, screenWidth, screenHeight);

	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set the background color
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//DrawPalang();
	glDisable(GL_BLEND);
	if (menu==0)
	{
		
		DrawStartScreen();
		ImGui::Render();
	}

	if (menu == 2) {
		DrawGameOverScreen();
		ImGui::Render();
	}
	
	if (menu == 1) {
		DrawGameScreen();
		DrawSprite();
		mat4 projection2 = ortho(0.0f, (float)this->screenWidth, 0.0f, (float)this->screenHeight);
		GLint location3 = glGetUniformLocation(this->program3, "projection");
		UseShader(this->program3);
		glUniformMatrix4fv(location3, 1, GL_FALSE, value_ptr(projection2));

		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		string text ;
		text.append(to_string(score));

		RenderText(text, 710.0f, 620.0f, 3.0f, vec3(0.0f, 0.0f, 0.0f));

		string text2;
		text2.append(to_string(pilihan[0]));
		RenderText(text2, 180.0f, 70.0f, 1.5f, vec3(0.0f, 0.0f, 0.0f));

		string text3;
		text3.append(to_string(pilihan[1]));
		RenderText(text3, 395.0f, 45.0f, 1.5f, vec3(0.0f, 0.0f, 0.0f));

		string text4;
		text4.append(to_string(pilihan[2]));
		RenderText(text4, 585.0f, 70.0f, 1.5f, vec3(0.0f, 0.0f, 0.0f));

		string text5;
		text5.append(to_string(angka1));
		if (locOperat == 0) text5.append(" + ");
		if (locOperat == 1) text5.append(" - ");
		if (locOperat == 2) text5.append(" * "); 
		text5.append(to_string(angka2));
		RenderText(text5, 100.0f, 420.0f, 2.0f, vec3(0.0f, 0.0f, 0.0f));

		glDisable(GL_BLEND);
	}

	
}

void Demo::UpdateSprite(float deltaTime)
{
	// Update animation
	frame_dur += deltaTime;


	if (frame_dur > FRAME_DUR) {
		frame_dur = 0;
		if (frame_idx == NUM_FRAMES - 1) frame_idx = 0;  else frame_idx++;

		// Pass frameIndex to shader
		GLint location = glGetUniformLocation(this->program, "frameIndex");
		UseShader(this->program);
		glUniform1i(location, frame_idx);
	}

	GLint location2 = glGetUniformLocation(this->program2, "frameIndex");
	UseShader(this->program2);
	glUniform1i(location2, indexpalang);

	
}

void Demo::MoveSprite(float deltaTime)
{
	ypos -= deltaTime * 0.0004f;
	mat4 transform;
	
	if (statusAkhir == true) {
		angka1 = (rand() % 15)+1 ;
		angka2 = (rand() % 15)+1 ;
		locJawaban = (rand() % 3);
		locOperat = (rand() % 3);
		if (locOperat == 0) jawaban = angka1 + angka2;
		if (locOperat == 1) jawaban = angka1 - angka2;
		if (locOperat == 2) jawaban = angka1 * angka2;
		
		
		for (int i = 0; i < 3; i++)
		{
			if (i == locJawaban) {
				pilihan[i] = jawaban;
			}
			else {
				pilihan[i] = (rand() % 100) + 1;
			}
			
		}
		
		statusAkhir = false;

	}


	if ((IsCollided(xpos, ypos, spriteWidth, spriteHeight, xpos2, ypos2+0.2, crateWidth, crateHeight))&&(!statusTabrakan)) {
		statusTabrakan = true;
		directi = direction;
		jawabUser = jawabanUser;
		
	}

	if (statusTabrakan == true) {
		if (!isMilih) {
			ISoundEngine *SoundEngine = createIrrKlangDevice();
			SoundEngine->play2D("Explosion.mp3", GL_FALSE);
			menu = 2;
			direction = NULL;
			directi = NULL;
			ypos = 1;
			statusAkhir = true;
			statusTabrakan = false;
			scoreDis = score;
			score = 0;

		}
		else { //jika sudah milih
			indexpalang = 1;

			if (rot <= 0.6f) {
				rot += deltaTime * 0.0025f;
			}

			
			if (ypos < -0.5) {
				if (locJawaban == jawabUser) { //cek jawaban user
					ISoundEngine *SoundEngine = createIrrKlangDevice();
					SoundEngine->play2D("success.wav", GL_FALSE);
					direction = NULL;
					directi = NULL;
					statusAkhir = true;
					indexpalang = 2;
					statusTabrakan = false;
					isMilih = false;
					rot = 0;
					ypos = 1;
					score++;
				}
				else {
					ISoundEngine *SoundEngine = createIrrKlangDevice();
					SoundEngine->play2D("Explosion.mp3", GL_FALSE);
					direction = NULL;
					directi = NULL;
					rot = 0;
					ypos = 1;
					indexpalang = 2;
					statusAkhir = true;
					statusTabrakan = false;
					isMilih = false;
					menu = 2;
					scoreDis = score;
					score = 0;
				}
					
				
			}
		}
		
	}
	transform = rotate(transform, float(directi*rot), vec3(0.0f, 0.0f, 1.0f));
	transform = translate(transform, vec3(xpos, ypos, 0.0f));

	GLint location = glGetUniformLocation(this->program, "transform");
	UseShader(this->program);
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(transform));


}

void Demo::DrawSprite() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	GLint location = glGetUniformLocation(this->program, "ourTexture");
	// Activate shader
	UseShader(this->program);
	glUniform1i(location, 0);

	// Draw sprite
	glBindVertexArray(VAO);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	GLint location2 = glGetUniformLocation(this->program2, "ourTexture");
	// Activate shader
	UseShader(this->program2);
	glUniform1i(location2, 1);

	// Draw sprite
	glBindVertexArray(VAO2);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	glDisable(GL_BLEND);
}

void Demo::DrawPalang() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture2);

	// Activate shader
	UseShader(this->program2);

	// Draw sprite
	glBindVertexArray(VAO2);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	glDisable(GL_BLEND);
}

void Demo::DrawStartScreen() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture3);
	// Activate shader
	UseShader(this->program4);

	//mat4 transform3 = translate(transform3, vec3(0.5f, 0.5f, 0.0f));

	/*GLint location3 = glGetUniformLocation(this->program3, "transform");
	UseShader(this->program3);
	glUniformMatrix4fv(location3, 1, GL_FALSE, value_ptr(transform3));*/

	// Draw sprite
	glBindVertexArray(VAO4);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	glDisable(GL_BLEND);

	
	
}

void Demo::DrawGameOverScreen() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture5);
	// Activate shader
	UseShader(this->program4);

	//mat4 transform3 = translate(transform3, vec3(0.5f, 0.5f, 0.0f));

	/*GLint location3 = glGetUniformLocation(this->program3, "transform");
	UseShader(this->program3);
	glUniformMatrix4fv(location3, 1, GL_FALSE, value_ptr(transform3));*/

	// Draw sprite
	glBindVertexArray(VAO4);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	glDisable(GL_BLEND);



}

void Demo::DrawGameScreen() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture4);
	// Activate shader
	UseShader(this->program5);

	//mat4 transform3 = translate(transform3, vec3(0.5f, 0.5f, 0.0f));

	/*GLint location3 = glGetUniformLocation(this->program3, "transform");
	UseShader(this->program3);
	glUniformMatrix4fv(location3, 1, GL_FALSE, value_ptr(transform3));*/

	// Draw sprite
	glBindVertexArray(VAO5);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	glDisable(GL_BLEND);



}





void Demo::BuildPalang()
{


	this->program2 = BuildShader("crate.vert", "crate.frag");

	GLint location3 = glGetUniformLocation(this->program2, "n");
	UseShader(this->program2);
	glUniform1f(location3, 1.0f / 2);

	// Load and create a texture 
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

											// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("palang.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

									 // Set up vertex data (and buffer(s)) and attribute pointers
	frame_width2 = ((float)width) / 2;
	float w = 0.025f;
	float x = frame_width2 * w / height;
	float y = w;
	crateWidth = x;
	crateHeight = y;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		x,  y, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Top Right
		x, -y, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Bottom Right
		-x, -y, 0.0f,  1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-x,  y, 0.0f,  1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Top Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	ypos2 = 0.0f;
	xpos2 = -0.07f;

	mat4 transform2;
	//transform2 = rotate(transform2, 3.14f/2, vec3(0.0f, 0.0f, 1.0f));
	transform2 = translate(transform2, vec3(xpos2, ypos2, 0.0f));
	GLint location = glGetUniformLocation(this->program2, "transform");
	UseShader(this->program2);
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(transform2));

	GLint location2 = glGetUniformLocation(this->program2, "frameIndex");
	UseShader(this->program2);
	glUniform1i(location2, indexpalang);

}

bool Demo::IsCollided(float x1, float y1, float width1, float height1,float x2, float y2, float width2, float height2) {
	return (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2);
}
void Demo::BuildSprite()
{
	this->program = BuildShader("spriteAnim.vert", "spriteAnim.frag");

	// Pass n to shader
	GLint location = glGetUniformLocation(this->program, "n");
	UseShader(this->program);
	glUniform1f(location, 1.0f / NUM_FRAMES);

	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("sepur.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width = ((float)width) / NUM_FRAMES;
	float w = 0.2f;
	float x = frame_width * w / height;
	float y = w;
	spriteWidth = x;
	spriteHeight = y;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		x,  y, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Top Right
		x, -y, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Bottom Right
		-x, -y, 0.0f,  1.0f, 1.0f, 1.0f,    0.0f, 0.0f, // Bottom Left
		-x,  y, 0.0f,  1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Top Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

}

void Demo::BuildScreenStart()
{
	this->program4 = BuildShader("spriteAnim1.vert", "spriteAnim1.frag");

	// Pass n to shader
	GLint location4 = glGetUniformLocation(this->program4, "n");
	UseShader(this->program4);
	glUniform1f(location4, 1.0f / NUM_FRAMES);

	// Load and create a texture 
	glGenTextures(1, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

										   // Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width3, height3;
	unsigned char* image3 = SOIL_load_image("start.jpg", &width3, &height3, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width3, height3, 0, GL_RGBA, GL_UNSIGNED_BYTE, image3);
	SOIL_free_image_data(image3);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

									 // Set up vertex data (and buffer(s)) and attribute pointers
	frame_width3 = ((float)width3) / NUM_FRAMES;
	float w3 = 1.0f;
	float x3 = frame_width3 * w3 / height3;
	float y3 = w3;
	startWidth = x3;
	startHeight = y3;
	GLfloat vertices3[] = {
		// Positions   // Colors           // Texture Coords
		x3,  y3, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Top Right
		x3, -y3, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Bottom Right
		-x3, -y3, 0.0f,  1.0f, 1.0f, 1.0f,    0.0f, 0.0f, // Bottom Left
		-x3,  y3, 0.0f,  1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Top Left 
	};

	GLuint indices3[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO4);
	glGenBuffers(1, &VBO4);
	glGenBuffers(1, &EBO4);

	glBindVertexArray(VAO4);

	glBindBuffer(GL_ARRAY_BUFFER, VBO4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices3), indices3, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	mat4 transform3;
	//transform2 = rotate(transform2, 3.14f/2, vec3(0.0f, 0.0f, 1.0f));
	transform3 = translate(transform3, vec3(0.0f, 0.0f, 0.0f));
	GLint location3 = glGetUniformLocation(this->program4, "transform");
	UseShader(this->program4);
	glUniformMatrix4fv(location3, 1, GL_FALSE, value_ptr(transform3));

	GLint location5 = glGetUniformLocation(this->program4, "frameIndex");
	UseShader(this->program4);
	glUniform1i(location5, 0);

}

void Demo::BuildScreenGameOver()
{
	this->program4 = BuildShader("spriteAnim1.vert", "spriteAnim1.frag");

	// Pass n to shader
	GLint location4 = glGetUniformLocation(this->program4, "n");
	UseShader(this->program4);
	glUniform1f(location4, 1.0f / NUM_FRAMES);

	// Load and create a texture 
	glGenTextures(1, &texture5);
	glBindTexture(GL_TEXTURE_2D, texture5); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

											// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width3, height3;
	unsigned char* image3 = SOIL_load_image("start1.jpg", &width3, &height3, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width3, height3, 0, GL_RGBA, GL_UNSIGNED_BYTE, image3);
	SOIL_free_image_data(image3);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

									 // Set up vertex data (and buffer(s)) and attribute pointers
	frame_width3 = ((float)width3) / NUM_FRAMES;
	float w3 = 1.0f;
	float x3 = frame_width3 * w3 / height3;
	float y3 = w3;
	startWidth = x3;
	startHeight = y3;
	GLfloat vertices3[] = {
		// Positions   // Colors           // Texture Coords
		x3,  y3, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Top Right
		x3, -y3, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Bottom Right
		-x3, -y3, 0.0f,  1.0f, 1.0f, 1.0f,    0.0f, 0.0f, // Bottom Left
		-x3,  y3, 0.0f,  1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Top Left 
	};

	GLuint indices3[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO4);
	glGenBuffers(1, &VBO4);
	glGenBuffers(1, &EBO4);

	glBindVertexArray(VAO4);

	glBindBuffer(GL_ARRAY_BUFFER, VBO4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices3), indices3, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	mat4 transform8;
	//transform2 = rotate(transform2, 3.14f/2, vec3(0.0f, 0.0f, 1.0f));
	transform8 = translate(transform8, vec3(0.0f, 0.0f, 0.0f));
	GLint location3 = glGetUniformLocation(this->program4, "transform");
	UseShader(this->program4);
	glUniformMatrix4fv(location3, 1, GL_FALSE, value_ptr(transform8));

	GLint location8 = glGetUniformLocation(this->program4, "frameIndex");
	UseShader(this->program4);
	glUniform1i(location8, 0);

}

void Demo::BuildGameScreen()
{
	this->program5 = BuildShader("spriteAnim1.vert", "spriteAnim1.frag");

	// Pass n to shader
	GLint location6 = glGetUniformLocation(this->program5, "n");
	UseShader(this->program5);
	glUniform1f(location6, 1.0f / NUM_FRAMES);

	// Load and create a texture 
	glGenTextures(1, &texture4);
	glBindTexture(GL_TEXTURE_2D, texture4); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

											// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width4, height4;
	unsigned char* image4 = SOIL_load_image("game.png", &width4, &height4, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width4, height4, 0, GL_RGBA, GL_UNSIGNED_BYTE, image4);
	SOIL_free_image_data(image4);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

									 // Set up vertex data (and buffer(s)) and attribute pointers
	frame_width4 = ((float)width4) / NUM_FRAMES;
	float w4 = 1.0f;
	float x4 = frame_width4 * w4 / height4;
	float y4 = w4;
	GLfloat vertices4[] = {
		// Positions   // Colors           // Texture Coords
		x4,  y4, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Top Right
		x4, -y4, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Bottom Right
		-x4, -y4, 0.0f,  1.0f, 1.0f, 1.0f,    0.0f, 0.0f, // Bottom Left
		-x4,  y4, 0.0f,  1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Top Left 
	};

	GLuint indices4[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO5);
	glGenBuffers(1, &VBO5);
	glGenBuffers(1, &EBO5);

	glBindVertexArray(VAO5);

	glBindBuffer(GL_ARRAY_BUFFER, VBO5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices4), vertices4, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO5);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices4), indices4, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	mat4 transform4;
	//transform2 = rotate(transform2, 3.14f/2, vec3(0.0f, 0.0f, 1.0f));
	transform4 = translate(transform4, vec3(0.0f, 0.0f, 0.0f));
	transform4 = scale(transform4, vec3(0.87f, 1.0f, 1.0f));
	GLint location3 = glGetUniformLocation(this->program5, "transform");
	UseShader(this->program5);
	glUniformMatrix4fv(location3, 1, GL_FALSE, value_ptr(transform4));

	GLint location7 = glGetUniformLocation(this->program5, "frameIndex");
	UseShader(this->program5);
	glUniform1i(location7, 0);

}

void Demo::OnUserDefinedEvent(SDL_Event& evt) {
	ImGui_ImplSdlGL3_ProcessEvent(&evt);
}

void Demo::InitFont() {
	// Init Freetype
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		Err("ERROR::FREETYPE: Could not init FreeType Library");
	}
	FT_Face face;
	if (FT_New_Face(ft, FONTNAME, 0, &face)) {
		Err("ERROR::FREETYPE: Failed to load font");
	}

	FT_Set_Pixel_Sizes(face, 0, FONTSIZE);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture3;
		glGenTextures(1, &texture3);
		glBindTexture(GL_TEXTURE_2D, texture3);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture3,
			ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(pair<GLchar, Character>(c, character));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	glGenVertexArrays(1, &VAO3);
	glGenBuffers(1, &VBO3);
	glBindVertexArray(VAO3);
	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL,
		GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	this->program3 = BuildShader("font.vert", "font.frag");
}

void Demo::RenderText(string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color)
{
	// Activate corresponding render state
	UseShader(this->program3);
	glUniform3f(glGetUniformLocation(this->program3, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO3);

	// Iterate through all characters
	string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];
		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos, ypos + h, 0.0, 0.0 },
			{ xpos, ypos, 0.0, 1.0 },
			{ xpos + w, ypos, 1.0, 1.0 },
			{ xpos, ypos + h, 0.0, 0.0 },
			{ xpos + w, ypos, 1.0, 1.0 },
			{ xpos + w, ypos + h, 1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO3);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1 / 64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels(2 ^ 6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}



int main(int argc, char** argv) {

	Engine::Game &game = Demo();
	game.Start("AritmatiC Train Game", 800, 700, true, WindowFlag::WINDOWED, 0, 1);

	return 0;
}
