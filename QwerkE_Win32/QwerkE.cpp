// include platform libraries
#include "QwerkE.h"

// include engine framework
#include "QwerkE_Include.h"
#include "Systems/GameCore.h"
#include "Input/Controller.h"
#include "Libraries/MyGLFW/MyGLFW.h"
#include "Graphics/OpenGLManager.h"
#include "Systems/ResourceManager.h"
#include "Input/InputManager.h"
#include "Libraries/EasyXinput/EasyXinput.h"
#include "Graphics/OpenGLHelpers.h"
#include "Utilities/PrintFunctions.h"

int g_WindowWidth = 1600, g_WindowHeight = 900; // (1280x720)(1600x900)(1920x1080)(2560x1440)
double g_TimeSinceExe = 0.0f;
float g_FrameRate = 0.0f;
GameCore* g_GameCore = new GameCore();
MyGLFW* g_MainWindow;
extern InputManager* g_InputManager = nullptr;
extern Controller* g_Player1Controller = nullptr;
extern XinputHandler* g_XinputHandler = nullptr;

int main()
{
	//// setup
	g_MainWindow = new MyGLFW("Title", vec2(g_WindowWidth, g_WindowHeight), vec2(400, 400));

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	bool result = ImGui_ImplGlfwGL3_Init(g_MainWindow->GetWindow(), true);

	// TODO: Setup Callbacks

	// GameCore
	g_GameCore = new GameCore();
	g_GameCore->Initialize(); // set openGL state
	g_GameCore->OnWindowResize(g_WindowWidth, g_WindowHeight);
	SceneManager* t_SceneManager = g_GameCore->GetSceneManager();
	t_SceneManager->EnableScene(Scene_TestScene);
	OpenGLManager* t_GLManager = g_GameCore->GetGLManager();
	t_GLManager->ResetGLState();

	// Input
	g_InputManager = new InputManager();
	g_Player1Controller = g_InputManager->GetController(0);

	// Xinput
	g_XinputHandler = new XinputHandler(1); // (numPlayers)
	g_XinputHandler->SetPlayer(0); // Set player controller to poll

	// background image or HUD layout
	// TODO:: Add background image
	/*Sprite2D* m_Background = new Sprite2D();
	m_Background->SetPosition(vec3(0, 0, 0));
	m_Background->SetScale(vec3(2, 2, 1));
	m_Background->SetMesh(g_GameCore->GetResourceManager()->GetMesh("Box"));
	m_Background->SetShader(g_GameCore->GetResourceManager()->GetShader("Sprite2D"));
	m_Background->SetTexture(g_GameCore->GetResourceManager()->GetTexture("Blue_Engine_UI1"));*/

	//// load
	// TODO: ResourceManager->LoadDirectory();

	//// frame rate
	// Deltatime
	double deltaTime = 0.0f;    // Time between current frame and last frame
	double lastFrame = 0.0f;      // Time of last frame
	// limit framerate
	int FPS_MAX = 120; // maximum number of frames that can be run be second
	float FPS_MAX_DELTA = 1.0f / FPS_MAX;
	g_TimeSinceExe = 0.0f; // TODO: Cleanup names and other FPS_MAX code.
	// FPS
	float timePassed = 0.0f;
	float period = 3.0f; // Print period in seconds
	short numFrames = 0;
	//// game loop
	// TODO: Place loop inside a game system like GameCore or something. It should not be in a platform specific main() function.
	while (g_MainWindow->CloseRequested() == false)
	{
		// Calculate deltatime of current frame
		double currentFrame = g_MainWindow->GetTime();
		deltaTime = currentFrame - lastFrame; // time since last frame
		lastFrame = currentFrame; // save last frame
								  // FPS display + tracking
		if (timePassed > period) // print period
		{
			g_FrameRate = numFrames / timePassed;
			OutputPrint("\nFPS: %f", g_FrameRate); // FPS printout
			timePassed = 0.0f;
			numFrames = 0;
		}
		timePassed += (float)deltaTime;
		// MAX_FPS (limit framerate)
		g_TimeSinceExe += deltaTime;
		if (g_TimeSinceExe >= FPS_MAX_DELTA) // Run frame?
		{
			//* Begin Game Loop *//
			/* Input */
			g_MainWindow->CheckInput();
			ImGui_ImplGlfwGL3_NewFrame();

			/* Logic */
			// t_SceneManager->Update(g_TimeSinceExe);
			if (ImGui::Button("Close")) { g_MainWindow->RequestClose(); }

			/* Render */
			// t_GLManager->ClearScreen(); // Clear screen buffers after FBO has been generated
			g_MainWindow->Clear();

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			// m_Background->Draw();

			g_MainWindow->SwapBuffers(); // Flip new image (buffer) to screen
			CheckforGLErrors(__FILE__, __LINE__);
			numFrames++; // Framerate tracking
			g_TimeSinceExe = 0.0f; // FPS_Max
		}
		else
		{
			// skip this frame
			// TODO: Calculate "Effective Frame Rate" based on how many frames we skip.
		}
	}

	// tear down
	ImGui_ImplGlfwGL3_Shutdown(); // shutdown imgui
	ImGui::DestroyContext(); // destroy imgui

	return 0;
}