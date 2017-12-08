#include <windows.h>
#include "bibutil.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <unistd.h>
#include <GL/glut.h>
#include <MMSystem.h>

//these two headers are already included in the <Windows.h> header

//#pragma comment(lib, "winmm.lib")

float rotame;

void PosicionaObservador(void);

void EspecificaParametrosVisualizacao(void);
//#define DEBUG 1
// Variáveis para controles de navegação
GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;

GLfloat obxix, obys, obsziz;

GLfloat rotaX, rotaY, rotaZ; // var de posição e vai ser usado pra rodar
GLfloat andaTx, andaTy,andaTz;
GLfloat roteY;
int x_ini,y_ini,bot;
unsigned int microseconds = 120000;

int has_the_festa_started_q = 1;
int angle_starter = 1;
// Apontador para objeto
OBJ *objeto;
OBJ *objeto2;
OBJ *objeto3;

int is_on;

int bg_on;

int bg_timer;
int timer_of_timer;
float aBola = 1;
float bBola = 0;
float cBola = 0.4;

float ball_rotation;
float ball_X;
float ball_Y;
int side;

float cubo_size;
float cubo_rotation;
float cuboX;
float cuboY;
float cuboZ;
int side2;



float mkX,mkY,mkZ;
int mkTurn;

float ns;

GLfloat lux1_pos[4] = {10,10,0,1.0};
GLfloat kuro[4] = {0,0,0,1};
GLfloat shiro[4] = {1,1,1,1};
GLfloat aka[4]= {1.0,0.0,0.0};
GLfloat globalLux[4]= {0.9,0.9,0.9,1};

int scena;

int tea;

float tea_size;
float teaX, teaY,teaZ;
float random()//random 0 a1
{
  float scale=RAND_MAX+1.;
  float base=rand()/scale;
  float fine=rand()/scale;
  return base+fine/scale;
}







void balada_top(){

	glLightfv(GL_LIGHT1, GL_AMBIENT, aka);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, kuro );
	glLightfv(GL_LIGHT1, GL_SPECULAR, shiro );
	glLightfv(GL_LIGHT1,GL_POSITION,lux1_pos); //luz loca

	glLightf(GL_LIGHT1,GL_CONSTANT_ATTENUATION, 0.5);
	glLightf(GL_LIGHT1,GL_LINEAR_ATTENUATION,0.5);
	glLightf(GL_LIGHT1,GL_QUADRATIC_ATTENUATION,0.2);

	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalLux); //luz global

	glEnable(GL_LIGHT1);

}



void desenha_teapot(){


		glColor3f (aBola, bBola, cBola);

		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
		glShadeModel(GL_SMOOTH);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,aka);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, kuro);
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 65);
		glPushMatrix();
		glTranslatef(teaX, teaY, teaZ);
		glutSolidTeapot (tea_size);
		glPopMatrix();

}


void desenha_bola(){

	if(bg_on){

		aBola = random();
		bBola = random();
		cBola = random();


		ball_rotation++;

		//ball_Y++;
		if(side){
			ball_X++;
			if(ball_X > 20){
				side = 0;
			}

		}
		if(!side){
			ball_X--;
			if(ball_X < -5){
				side = 1;
			}
		}

	}

	glColor3f (aBola, bBola, cBola);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
		glShadeModel(GL_SMOOTH);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,shiro);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, shiro);
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 40);

	glPushMatrix ();
	       glTranslatef    (ball_X, ball_Y, 0.0);
	       glRotatef       (60.0, 1,0,0);
	       glRotatef       (ball_rotation, 0,0,1);   // Red ball rotates at twice the rate of blue ball.
	       glutWireSphere (5.0, 20, 10);
	 glPopMatrix ();
}



void desenha_cubo(){

	if(bg_on){

		if(cubo_rotation > 360){
			cubo_rotation = 0;
		}

			aBola = random();
			bBola = random();
			cBola = random();


			cubo_rotation++;

			//ball_Y++;



			if(side){
				cuboX--;
				cuboY--;
				cubo_size--;
				if(cuboX < -14){
					side=0;
				}
			}
			if(!side){
				cuboY++;
				cuboX++;
				cubo_size++;
				if(cuboX > 30){
					side =1;
				}
			}



	}


	glColor3f (aBola, bBola, cBola);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
		glShadeModel(GL_SMOOTH);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,shiro);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, shiro);
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 100);
	glPushMatrix ();
		       glTranslatef(cuboX, cuboY, 0.0);
		       glRotatef(60.0, 1,0,0);
		       glRotatef(cubo_rotation,cubo_rotation,0.0,1);   // Red ball rotates at twice the rate of blue ball.
		       glutWireCube(cubo_size);
	 glPopMatrix ();
}


void timero(){


	if(bg_on){

		rotaX++;
		rotaY++;
		roteY++;

		if (rotaX >= 360){
				rotaX = rotX;
				rotaY = rotY;
			}

		if(roteY >= 1080){
			roteY = rotaY;
		}

	}


glutPostRedisplay();


}



void bg_color_changer(){

if(timer_of_timer == 495){
	bg_on = 1;
}


	if(bg_timer > 10){

		bg_timer = 0;

		if(bg_on){

			float a = random();
			float b = random();
			float c = random();
			float d = random();
			glClearColor(a, b, c, d);

		}
	}
timer_of_timer++;
bg_timer++;
glutPostRedisplay();

}





void sound_player(){

	if(scena == 0){

		PlaySound(TEXT("Bag Raiders - Shooting Stars.wav"), NULL, SND_LOOP | SND_ASYNC);
	}
	if(scena == 1){
		PlaySound(TEXT("C:\\Users\\Thiago\\workspace\\projetus\\ponponpon.wav"), NULL, SND_LOOP | SND_ASYNC);
	}

}

void angle_fixer_starter_boy(){
	angle= 155;
	angle_starter= 0;
}

void the_party_starter(int value){
	//sound_player();

	angle -= 5;
	//printf("anggole %d\n",angle);
	if(glIsEnabled(GL_LIGHTING))
				glDisable(GL_LIGHTING);
	else
	            glEnable(GL_LIGHTING);

	if(angle <= 5.000000){
		//printf("opa\n");
		has_the_festa_started_q = 0;
		EspecificaParametrosVisualizacao();
		glutPostRedisplay();
		return;
	}

	EspecificaParametrosVisualizacao();
	glutPostRedisplay();

	glutTimerFunc(110,the_party_starter,1);
}




void DefineIluminacao (void)
{
	GLfloat luzAmbiente[4]={1.2,1.2,1.2,1.0};
	GLfloat luzDifusa[4]={1.0,1.0,1.0,1.0};	   	// "cor"
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};	// "brilho"
	GLfloat posicaoLuz[4]={0.0, 10.0, 100.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 60;


	// Define a refletância do material
	//glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	//glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );


	balada_top();

}


// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	glEnable(GL_NORMALIZE);
	// Limpa a janela de visualização com a cor
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	// Altera a cor do desenho para blue
	glColor3f(0.5f, 0.5f, 0.5f);

	// Desenha o objeto 3D lido do arquivo com a cor corrente

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,shiro);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, shiro);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 20);
	glPushMatrix();
	glTranslatef(andaTx,0.0,0.0);
	glScalef(0.2,0.2,0.2);
	glTranslatef(-andaTx,0.0,0.0);
    glRotatef(rotaX,1,0,0);//rotaX, rotaY, rotaZ; default rotX, 1,0.0
	glRotatef(rotaY,0,1,0);
	glTranslatef(andaTx,0.0,0.0);// translada x pa dirieta andaTx, andaTy,andaTz; default 4.0 0.0 0.0
	DesenhaObjeto(objeto);//teddyurso
    glPopMatrix();


    // Desenha o objeto 3D lido do arquivo com a cor corrente




    if(bg_on){
    	  	glPushMatrix();
    	    desenha_bola();
    	    glPopMatrix();


    	    glPushMatrix();
    	    desenha_cubo();
    	    glPopMatrix();



    	       glColor3f(1.0f, 1.0f, 0.5f);
    	       glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    	       glShadeModel(GL_SMOOTH);
    	       glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,aka);
    	       glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, kuro);
    	       glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 15);
    	       glPushMatrix();
    	       glRotatef(rotaY,0,rotaX,1);
    	       glRotatef(rotaY,0,0,1);
    	       glTranslatef(9.0,0.0,0.0);// translada x pa dirieta
    	       DesenhaObjeto(objeto2);// desenha stickboy
    	       glPopMatrix();


    	       glColor3f(1.0, 0.4f, 0.5f);
    	       glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    	       glShadeModel(GL_SMOOTH);
    	       glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,aka);
    	       glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, kuro);
    	       glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 65);
    	       glPushMatrix();
    	       glRotatef(rotY,1,0,1);
    	       glRotatef(rotaX,0,1,1);
    	       glTranslatef(mkX,mkY,mkZ);//6,8,3
    	       DesenhaObjeto(objeto3);// desenha monkey man
    	       glPopMatrix();

    }


    desenha_teapot();
    PosicionaObservador();

    bg_color_changer();
    timero();
	// Executa os comandos OpenGL
    glFlush();
	glutSwapBuffers();
}



// Função usada para especificar a posição do observador virtual
void PosicionaObservador(void){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();//carrega a matriz de identidade
    gluLookAt(obxix,roteY,obsziz,//posição da câmera obsX,obsY,obsZ, onde a camera ta to munhdo obxix, obys, obsziz; obxix,obys,obsziz
              5.0,0.0,0.0,//para onde a câmera aponta defaultk : 00 00 00 reference point
              0.0,1.0,0.0);//vetor view-up// defaukt 00 10 00 direction fo up vector
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{

	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,dnear,dfar)
	gluPerspective(angle,fAspect,0.01,1200);

	// Chama as funções que especificam os parâmetros da câmera e os parâmetros de iluminação
	PosicionaObservador();
	DefineIluminacao();

}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimensões da viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar eventos de teclas normais (ESC)
void Teclas (unsigned char tecla, int x, int y)
{

	if(tecla=='p'){

		if(bg_on){
			is_on = 0;
			bg_on = 0;
		}else{
			is_on =1;
			bg_on =1;
			timer_of_timer=0;
			bg_timer = 0;
		}



	}


	if(tecla==27) // ESC ?
	{
		// Libera memória e finaliza programa
		LiberaObjeto(objeto);
		exit(0);
	}
	if(tecla == 'q'){
		if(is_on){
			is_on = 0;

		}else{
			is_on=1;
		}
	}
	if(tecla=='m')
	{
		if(glIsEnabled(GL_LIGHTING))
			glDisable(GL_LIGHTING);
		else
            glEnable(GL_LIGHTING);
	}

	if(tecla == 'w'){
		//rotame++;
		if(mkTurn){
			mkY++;
		}else{
			rotaX++;
			rotaY++;
		}



	}
	if(tecla == 's'){

		if(mkTurn){
			mkY--;
		}else{
			rotaX--;
			rotaY--;
		}


	}

	if(tecla == 'd'){

		if(mkTurn){
			mkX++;
		}else{
			andaTx++;
		}

	}
	if(tecla == 'a'){
		if(mkTurn){
			mkX--;
		}else{
			andaTx--;
		}

	}

	if(tecla == 't'){
		if(mkTurn){
			mkTurn =0;
		}
		else{
			mkTurn = 1;
		}
	}

	if(tecla == 'y'){

		if(tea){
			tea =0;
		}else{
			tea=1;
		}

	}

	if(tecla =='n'){
		scena++;
		sound_player();
		if(scena == 2){
			scena =0;
		}


	}

	if(tecla == 'r'){

		bg_timer = 0;
		is_on = 0;
		timer_of_timer = 0;
		bg_on=0;
		ball_rotation = 0;
		ball_X = 10;
		ball_Y =2;
		side  = 1;
		cubo_size = 2;
		cubo_rotation = 0;
		cuboX = 15;
		cuboY = 2 ;
		cuboZ = 0;
		side =1;
		scena=0;
		sound_player();
	}


	if(tecla == 'b'){
		tea_size++;
	}
	if(tecla=='c'){
		tea_size--;
	}

	if(tecla == 'i'){
		if(tea){
		teaY++;
		}
	}

	if(tecla == 'k'){
		if(tea){
			teaY--;
		}
	}
	if(tecla == 'l'){
		if(tea){
				teaX++;
		}
	}
	if(tecla=='j'){

		if(tea){
			teaX--;
		}
	}

	glutPostRedisplay();
}

// Função callback para tratar eventos de teclas especiais
void TeclasEspeciais (int tecla, int x, int y)
{
	switch (tecla)
	{
		case GLUT_KEY_UP:	if(angle>=10){
								angle -=5;

							}

								break;
			case GLUT_KEY_DOWN:	if(angle<=150){
								angle +=5;

							}

							break;
		}

	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

// Função callback para eventos de botões do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN)
	{
		// Salva os parâmetros atuais
		x_ini = x;
		y_ini = y;
		obsX_ini = obxix; //obsX; obxix, obys, obsziz;
		obsY_ini = obys;//obsY;
		obsZ_ini = obsziz;//obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = button;
	}
	else bot = -1;
}

// Função callback para eventos de movimento do mouse
#define SENS_ROT	5.0
#define SENS_OBS	15.0
#define SENS_TRANSL	20.0
void GerenciaMovim(int x, int y)
{
	// Botão esquerdo
	if(bot==GLUT_LEFT_BUTTON)
	{
		// Calcula diferenças
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica ângulos
		rotY = rotY_ini - deltax/SENS_ROT;
		rotX = rotX_ini - deltay/SENS_ROT;
	}
	// Botão direito (zoom-in e zoom-out)
	else if(bot==GLUT_RIGHT_BUTTON){
		// Calcula diferença
		int deltaz = y_ini - y;
		// E modifica distância do observador
		//obsZ = obsZ_ini + deltaz/SENS_OBS;///      obsZ   obxix, obys, obsziz;
		obsziz = obsZ_ini + deltaz/SENS_OBS;
	}
	// Botão do meio
	else if(bot==GLUT_MIDDLE_BUTTON)
	{
		// Calcula diferenças
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica posições
		//obsX = obsX_ini + deltax/SENS_TRANSL;
		obxix = obsX_ini + deltax/SENS_TRANSL;
		//obsY = obsY_ini - deltay/SENS_TRANSL;
		obsziz = obsY_ini - deltay/SENS_TRANSL;
	}
	PosicionaObservador();
	glutPostRedisplay();
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{
	char nomeArquivo[30];


	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);//remove faces ocultas
	glEnable(GL_BACK);
	// Habilita o modelo de tonalização de Gouraud
	glShadeModel(GL_SMOOTH);

	// Inicializa a variável que especifica o ângulo da projeção
	// perspectiva
	angle=55;

	// Inicializa as variáveis usadas para alterar a posição do
	// observador virtual
	obsX = obsY = 0;
	obsZ = 100;

	obxix = 220;
	obys = 1.0;
	obsziz  = 220;
	rotame= 0;

	//rotaX, rotaY, rotaZ;
	rotaX = rotX;
	rotaY = rotY;
	//andaTx, andaTy,andaTz;
	andaTx=4.0;

	bg_timer = 0;
	is_on = 0;
	timer_of_timer = 0;
	bg_on=0;


	ball_rotation = 0;
	ball_X = 10;
	ball_Y =2;
	side  = 1;





	aBola = random();
	bBola = random();
	cBola = random();


	cubo_size = 2;
	cubo_rotation = 0;
	cuboX = 15;
	cuboY = 2 ;
	cuboZ = 0;
	side =1;


	mkX = 6.0;
	mkY =9.0;
	mkZ = 3;
	mkTurn =0;
	scena =0;
	ns = 65.0f; //shineeeeeee

	roteY = rotY;

	tea=0;
	tea_size = 3;
	teaX =11 ;
	teaY =10;
	teaZ=0;


	// Lê o nome do arquivo e chama a rotina de leitura
	//printf("Digite o nome do arquivo que contem o modelo 3D: ");
	//gets(nomeArquivo);

	// Carrega o objeto 3D
	//ProcuraMaterial("fabric.mtl");
	objeto3 = CarregaObjeto("monkey.obj",true);
	objeto = CarregaObjeto("obj.obj",true);

	ProcuraMaterial("stick.mtl");
	objeto2 = CarregaObjeto("stick.obj",true);

    printf("Objeto carregado!");

	// E calcula o vetor normal em cada face
	if(objeto->normais)
	{
		// Se já existirem normais no arquivo, apaga elas
		free(objeto->normais);
		objeto->normais_por_vertice = false;
	}
	CalculaNormaisPorFace(objeto);

	if(objeto2->normais)
		{
			// Se já existirem normais no arquivo, apaga elas
			free(objeto2->normais);
			objeto2->normais_por_vertice = false;
		}
	CalculaNormaisPorFace(objeto2);


	if(objeto3->normais){
				// Se já existirem normais no arquivo, apaga elas
				free(objeto3->normais);
				objeto3->normais_por_vertice = false;
	}
	CalculaNormaisPorFace(objeto3);

	glOrtho(-2.0,2.0,-2.0,2.0,-2.0,2.0);
}

// Programa Principal
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    //sound_player();
	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5,5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450);

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("CGZAO TOP");
	sound_player();// music boys
	usleep(microseconds);
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas normais
	glutKeyboardFunc (Teclas);

	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc (TeclasEspeciais);

	// Registra a função callback para eventos de botões do mouse
	glutMouseFunc(GerenciaMouse);

	// Registra a função callback para eventos de movimento do mouse
	glutMotionFunc(GerenciaMovim);


	// Chama a função responsável por fazer as inicializações
	Inicializa();//


	if(angle_starter == 1){
		angle_fixer_starter_boy();
	}


	if (has_the_festa_started_q == 1){

		glutTimerFunc(1100,the_party_starter,1);
		if(angle >= 5){
			has_the_festa_started_q= 0;

		}

	}

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}



