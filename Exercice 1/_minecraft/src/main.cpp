//Includes application
#include <conio.h>
#include <vector>
#include <string>
#include <windows.h>

#include "external/gl/glew.h"
#include "external/gl/freeglut.h"

//Moteur
#include "engine/utils/types_3d.h"
#include "engine/timer.h"
#include "engine/log/log_console.h"
#include "engine/render/renderer.h"
#include "engine/gui/screen.h"
#include "engine/gui/screen_manager.h"


NYRenderer * g_renderer = NULL;
NYTimer * g_timer = NULL;
int g_nb_frames = 0;
float g_elapsed_fps = 0;
int g_main_window_id;
int g_mouse_btn_gui_state = 0;
bool g_fullscreen = false;

//GUI 
GUIScreenManager * g_screen_manager = NULL;
GUIBouton * BtnParams = NULL;
GUIBouton * BtnClose = NULL;
GUILabel * LabelFps = NULL;
GUILabel * LabelCam = NULL;
GUIScreen * g_screen_params = NULL;
GUIScreen * g_screen_jeu = NULL;
GUISlider * g_slider;

float timeOfDay=0;
//////////////////////////////////////////////////////////////////////////
// GESTION APPLICATION
//////////////////////////////////////////////////////////////////////////
void update(void)
{
	float elapsed = g_timer->getElapsedSeconds(true);

	static float g_eval_elapsed = 0;

	//Calcul des fps
	g_elapsed_fps += elapsed;
	g_nb_frames++;
	if(g_elapsed_fps > 1.0)
	{
		LabelFps->Text = std::string("FPS : ") + toString(g_nb_frames);
		g_elapsed_fps -= 1.0f;
		g_nb_frames = 0;
	}

	//Rendu
	g_renderer->render(elapsed);
}


void render2d(void)
{
	g_screen_manager->render();
}

float interpolation(float h, float debut, float fin){
	return (1 - h)*debut + h*fin;
}


void renderObjects(void)
{

	//Bfloat valueTime = timeOfDay % 100;


	//Rendu des axes
	//glDisable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_LINES);
		glColor3d(1, 0, 0);//x
		glVertex3d(0, 0, 0);
		glVertex3d(10000, 0, 0);

		glColor3d(0, 1, 0);//y
		glVertex3d(0, 0, 0);
		glVertex3d(0, 10000, 0);

		glColor3d(0, 0, 1);//z
		glVertex3d(0, 0, 0);
		glVertex3d(0, 0, 10000);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);

	//On active l'illumination 
	glEnable(GL_LIGHTING);

	//On active la light 0
	glEnable(GL_LIGHT0);

	//On d�finit une lumi�re






	float position[4] = { 0, 0, 7, 1 }; // w = 1 donc c'est une point light (w=0 -> directionelle, point � l'infini)
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	float diffuse[4] = { 0.5f, 0.5f, 0.5f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	float specular[4] = { 0.5f, 0.5f, 0.5f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	float ambient[4] = { 0.3f, 0.3f, 0.3f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);


	GLfloat materialDiffuseV[] = { 0, 0.7, 0, 1.0 };
	GLfloat materialAmbientV[] = { 0, 0.2, 0, 1.0 };

	GLfloat materialDiffuseR[] = { 0.7, 0, 0, 1.0 };
	GLfloat materialAmbientR[] = { 0.2, 0, 0, 1.0 };

	GLfloat materialDiffuseB[] = { 0, 0, 0.7, 1.0 };
	GLfloat materialAmbientB[] = { 0, 0, 0.2, 1.0 };

	GLfloat materialDiffuseA[] = { 0.7, 0.7, 0.7, 0.5 };
	GLfloat materialAmbientA[] = { 0.2, 0.2, 0.2, 0.58 };

	//On active l'illumination 
	glEnable(GL_LIGHTING);

	//On active la light 0
	glEnable(GL_LIGHT0);

	//glEnable(GL_COLOR_MATERIAL); //(pour afficher les glColor au lieu des materials
	float color = 0.7;
	//A rajouter pour debug : rotation dans le temps
	//glRotatef(NYRenderer::_DeltaTimeCumul * 100,g_slider->Value*10.0f, 1, cos(NYRenderer::_DeltaTimeCumul));
	/*
	glBegin(GL_QUADS);

	//Face1
	glColor3d(0, 0.5f, 0);
	glVertex3f(-1, -1, -1);
	glVertex3f(1, -1, -1);
	glVertex3f(1, -1, 1);
	glVertex3f(-1, -1, 1);

	//Face2
	glColor3d(0, 0.5f, 0);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, -1);

	//Face3
	glColor3d(0.5f, 0, 0);
	glVertex3f(1, -1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, -1, 1);

	//Face4
	glColor3d(0.5f, 0, 0);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, -1, 1);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, 1, -1);

	//Face5
	glColor3d(0, 0, 0.5f);
	glVertex3f(-1, -1, 1);
	glVertex3f(1, -1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(-1, 1, 1);

	//Face6
	glColor3d(0, 0, 0.5f);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, -1, -1);

	glEnd();*/


	//[exo 2 :
		//glTranslatef(2, 2, 0);
		//glRotatef(45, 0, 0, 1);

		//ou 
		//glRotatef(45, 0, 0, 1);
		//glTranslatef(sqrt(8.f), 1, 0);
		// ( nope nope nope )
	//exo2]-----------------------------------------------------
	//[exo 1 :

	



	glPushMatrix();
	glRotatef(NYRenderer::_DeltaTimeCumul * 100, 1, 1, cos(NYRenderer::_DeltaTimeCumul));
	glBegin(GL_TRIANGLES);
	//face +x
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuseR);
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbientR);


	glNormal3f(1, 0, 0);
	glColor3d(color, 0, 0);
		glVertex3d(1, -1, -1);
		glVertex3d(1, 1, -1);
		glVertex3d(1, 1, 1);


	glColor3d(color/2, 0, 0);
		glVertex3d(1, -1, -1);
		glVertex3d(1, 1, 1);
		glVertex3d(1, -1, 1);
	//face +y


	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuseV);
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbientV);

	glNormal3f(0, 1, 0);
	glColor3d(0, color, 0);
		glVertex3d(1, 1, -1);
		glVertex3d(-1, 1, -1);
		glVertex3d(-1, 1, 1);


	glColor3d(0, color/2, 0);
		glVertex3d(1, 1, -1);
		glVertex3d(-1, 1, 1);
		glVertex3d(1, 1, 1);


	//face +z

		glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuseB);
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbientB);

	glNormal3f(0, 0, 1);
	glColor3d(0, 0, color);
		glVertex3d(1, 1, 1);
		glVertex3d(-1, 1, 1);
		glVertex3d(-1, -1, 1);


	glColor3d(0, 0, color/2);
		glVertex3d(1, 1, 1);
		glVertex3d(-1, -1, 1);
		glVertex3d(1, -1, 1);

	//face -x
		glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuseR);
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbientR);
	glNormal3f(-1, 0, 0);
	glColor3d(color, 0, 0);
		glVertex3d(-1, -1, -1);
		glVertex3d(-1, 1, 1);
		glVertex3d(-1, 1, -1);


	glColor3d(color/2, 0, 0);
		glVertex3d(-1, -1, -1);
		glVertex3d(-1, -1, 1);
		glVertex3d(-1, 1, 1);
	//face -y
		glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuseV);
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbientV);
	glNormal3f(0, -1, 0);
	glColor3d(0, color, 0);
		glVertex3d(1, -1, -1);
		glVertex3d(-1, -1, 1);
		glVertex3d(-1, -1, -1);


	glColor3d(0, color/2, 0);
		glVertex3d(1, -1, -1);
		glVertex3d(1, -1, 1);
		glVertex3d(-1, -1, 1);


	//face -z

		glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuseB);
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbientB);
	glNormal3f(0, 0, -1);
	glColor3d(0, 0, color);
		glVertex3d(1, 1, -1);
		glVertex3d(-1, -1, -1);
		glVertex3d(-1, 1, -1);


	glColor3d(0, 0, color/2);
		glVertex3d(1, 1, -1);
		glVertex3d(1, -1, -1);
		glVertex3d(-1, -1,- 1);
	glEnd();
	//exo1]-----------------------------------------------------

	glPopMatrix();


	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuseA);
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbientA);

	glutSolidSphere(2, 50, 50);

	//Changement de la couleur de fond



	NYColor skyColor(0, 181.f / 255.f, 221.f / 255.f, 1);
	g_renderer->setBackgroundColor(skyColor);
}

void setLights(void)
{
	//On active la light 0
	glEnable(GL_LIGHT0);

	//On d�finit une lumi�re directionelle (un soleil)
	float direction[4] = {0,0,1,0}; ///w = 0 donc elle est a l'infini
	glLightfv(GL_LIGHT0, GL_POSITION, direction );
	float color[4] = {0.5f,0.5f,0.5f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color );
	float color2[4] = {0.3f,0.3f,0.3f};
	glLightfv(GL_LIGHT0, GL_AMBIENT, color2 );
	float color3[4] = {0.3f,0.3f,0.3f};
	glLightfv(GL_LIGHT0, GL_SPECULAR, color3 );
}

void resizeFunction(int width, int height)
{
	glViewport(0, 0, width, height);
	g_renderer->resize(width,height);
}

//////////////////////////////////////////////////////////////////////////
// GESTION CLAVIER SOURIS
//////////////////////////////////////////////////////////////////////////

void specialDownFunction(int key, int p1, int p2)
{
	//On change de mode de camera
	if(key == GLUT_KEY_LEFT)
	{
	}

}

void specialUpFunction(int key, int p1, int p2)
{

}

void keyboardDownFunction(unsigned char key, int p1, int p2)
{
	if(key == VK_ESCAPE)
	{
		glutDestroyWindow(g_main_window_id);	
		exit(0);
	}

	if(key == 'f')
	{
		if(!g_fullscreen){
			glutFullScreen();
			g_fullscreen = true;
		} else if(g_fullscreen){
			glutLeaveGameMode();
			glutLeaveFullScreen();
			glutReshapeWindow(g_renderer->_ScreenWidth, g_renderer->_ScreenWidth);
			glutPositionWindow(0,0);
			g_fullscreen = false;
		}
	}


	if (key == 'a')timeOfDay++;
	if (key == 'z')timeOfDay--;

}

void keyboardUpFunction(unsigned char key, int p1, int p2)
{
}

void mouseWheelFunction(int wheel, int dir, int x, int y)
{
	g_renderer->_Camera->move(NYVert3Df(0, 0, dir));
}

void mouseFunction(int button, int state, int x, int y)
{
	//Gestion de la roulette de la souris
	if((button & 0x07) == 3 && state)
		mouseWheelFunction(button,1,x,y);
	if((button & 0x07) == 4 && state)
		mouseWheelFunction(button,-1,x,y);

	//GUI
	g_mouse_btn_gui_state = 0;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		g_mouse_btn_gui_state |= GUI_MLBUTTON;
	
	bool mouseTraite = false;
	mouseTraite = g_screen_manager->mouseCallback(x,y,g_mouse_btn_gui_state,0,0);
}

/*
void mouseMoveFunction(int x, int y, bool pressed)
{
	bool mouseTraite = false;

	mouseTraite = g_screen_manager->mouseCallback(x,y,g_mouse_btn_gui_state,0,0);
	if(pressed && mouseTraite)
	{
		//Mise a jour des variables li�es aux sliders
	}

}*/

void mouseMoveFunction(int x, int y, bool pressed)
{
	static int lastx = -1;
	static int lasty = -1;

	if (!pressed)
	{
		lastx = x;
		lasty = y;
	}
	else
	{
		if (lastx == -1 && lasty == -1)
		{
			lastx = x;
			lasty = y;
		}

		int dx = x - lastx;
		int dy = y - lasty;

		lastx = x;
		lasty = y;

		if (GetKeyState(VK_LCONTROL) & 0x80)
		{
			NYVert3Df strafe = g_renderer->_Camera->_NormVec;
			strafe.Z = 0;
			strafe.normalize();
			strafe *= (float)-dx / 50.0f;

			NYVert3Df avance = g_renderer->_Camera->_Direction;
			avance.Z = 0;
			avance.normalize();
			avance *= (float)dy / 50.0f;

			g_renderer->_Camera->move(avance + strafe);
		}
		else
		{
			g_renderer->_Camera->rotate((float)-dx / 300.0f);
			g_renderer->_Camera->rotateUp((float)-dy / 300.0f);
		}

	}
}


void mouseMoveActiveFunction(int x, int y)
{
	mouseMoveFunction(x,y,true);
}
void mouseMovePassiveFunction(int x, int y)
{
	mouseMoveFunction(x,y,false);
}


void clickBtnParams (GUIBouton * bouton)
{
	g_screen_manager->setActiveScreen(g_screen_params);
}

void clickBtnCloseParam (GUIBouton * bouton)
{
	g_screen_manager->setActiveScreen(g_screen_jeu);
}

/**
  * POINT D'ENTREE PRINCIPAL
  **/
int main(int argc, char* argv[])
{ 
	LogConsole::createInstance();

	int screen_width = 800;
	int screen_height = 600;

	glutInit(&argc, argv); 
	glutInitContextVersion(3,0);
	glutSetOption(
		GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS
		);

	glutInitWindowSize(screen_width,screen_height);
	glutInitWindowPosition (0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE );

	glEnable(GL_MULTISAMPLE);

	Log::log(Log::ENGINE_INFO, (toString(argc) + " arguments en ligne de commande.").c_str());	
	bool gameMode = true;
	for(int i=0;i<argc;i++)
	{
		if(argv[i][0] == 'w')
		{
			Log::log(Log::ENGINE_INFO,"Arg w mode fenetre.\n");
			gameMode = false;
		}
	}

	if(gameMode)
	{
		int width = glutGet(GLUT_SCREEN_WIDTH);
		int height = glutGet(GLUT_SCREEN_HEIGHT);
		
		char gameModeStr[200];
		sprintf(gameModeStr,"%dx%d:32@60",width,height);
		glutGameModeString(gameModeStr);
		g_main_window_id = glutEnterGameMode();
	}
	else
	{
		g_main_window_id = glutCreateWindow("MyNecraft");
		glutReshapeWindow(screen_width,screen_height);
	}

	if(g_main_window_id < 1) 
	{
		Log::log(Log::ENGINE_ERROR,"Erreur creation de la fenetre.");
		exit(EXIT_FAILURE);
	}
	
	GLenum glewInitResult = glewInit();

	if (glewInitResult != GLEW_OK)
	{
		Log::log(Log::ENGINE_ERROR,("Erreur init glew " + std::string((char*)glewGetErrorString(glewInitResult))).c_str());
		_cprintf("ERROR : %s",glewGetErrorString(glewInitResult));
		exit(EXIT_FAILURE);
	}

	//Affichage des capacit�s du syst�me
	Log::log(Log::ENGINE_INFO,("OpenGL Version : " + std::string((char*)glGetString(GL_VERSION))).c_str());

	glutDisplayFunc(update);
	glutReshapeFunc(resizeFunction);
	glutKeyboardFunc(keyboardDownFunction);
	glutKeyboardUpFunc(keyboardUpFunction);
	glutSpecialFunc(specialDownFunction);
	glutSpecialUpFunc(specialUpFunction);
	glutMouseFunc(mouseFunction);
	glutMotionFunc(mouseMoveActiveFunction);
	glutPassiveMotionFunc(mouseMovePassiveFunction);
	glutIgnoreKeyRepeat(1);

	//Initialisation du renderer
	g_renderer = NYRenderer::getInstance();
	g_renderer->setRenderObjectFun(renderObjects);
	g_renderer->setRender2DFun(render2d);
	g_renderer->setLightsFun(setLights);
	g_renderer->setBackgroundColor(NYColor());
	g_renderer->initialise();

	//On applique la config du renderer
	glViewport(0, 0, g_renderer->_ScreenWidth, g_renderer->_ScreenHeight);
	g_renderer->resize(g_renderer->_ScreenWidth,g_renderer->_ScreenHeight);
	
	//Ecran de jeu
	uint16 x = 10;
	uint16 y = 10;
	g_screen_jeu = new GUIScreen(); 

	g_screen_manager = new GUIScreenManager();
		
	//Bouton pour afficher les params
	BtnParams = new GUIBouton();
	BtnParams->Titre = std::string("Params");
	BtnParams->X = x;
	BtnParams->setOnClick(clickBtnParams);
	g_screen_jeu->addElement(BtnParams);

	y += BtnParams->Height + 1;

	LabelFps = new GUILabel();
	LabelFps->Text = "FPS";
	LabelFps->X = x;
	LabelFps->Y = y;
	LabelFps->Visible = true;
	g_screen_jeu->addElement(LabelFps);

	//Ecran de parametrage
	x = 10;
	y = 10;
	g_screen_params = new GUIScreen();

	GUIBouton * btnClose = new GUIBouton();
	btnClose->Titre = std::string("Close");
	btnClose->X = x;
	btnClose->setOnClick(clickBtnCloseParam);
	g_screen_params->addElement(btnClose);

	y += btnClose->Height + 1;
	y+=10;
	x+=10;

	GUILabel * label = new GUILabel();
	label->X = x;
	label->Y = y;
	label->Text = "Param :";
	g_screen_params->addElement(label);

	y += label->Height + 1;

	g_slider = new GUISlider();
	g_slider->setPos(x,y);
	g_slider->setMaxMin(1,0);
	g_slider->Visible = true;
	g_screen_params->addElement(g_slider);

	y += g_slider->Height + 1;
	y+=10;

	//Ecran a rendre
	g_screen_manager->setActiveScreen(g_screen_jeu);
	
	//Init Camera
	g_renderer->_Camera->setPosition(NYVert3Df(10,10,10));
	g_renderer->_Camera->setLookAt(NYVert3Df(0,0,0));
	

	//Fin init moteur

	//Init application



	//Init Timer
	g_timer = new NYTimer();
	
	//On start
	g_timer->start();

	glutMainLoop(); 

	return 0;
}

