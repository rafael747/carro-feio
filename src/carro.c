#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>
#include <GL/freeglut.h>

//Declara��o de Vari�veis Globais
int projecao=0;	//Vari�vel L�gica para Definir o Tipo de Proje��o (Perspectiva ou Ortogonal)
//TODO: vai ser necessario imprementar a visao ortogonal

int posx=0, posy=50, posz=-80; //Vari�veis que definem a posi��o da c�mera
int oy=0,ox=0,oz=20;         //Vari�veis que definem para onde a c�mera olha
int lx=0, ly=1,  lz=0;         //Vari�veis que definem qual eixo estar� na vertical do monitor.

//TODO:	as posi��es de camera precisam ser ajustadas ainda

int xcarro=0, xcarro1=10, xcarro2=25, xcarro3=-5,xcerca=-35; //posicoes inicias dos elementos em X
				//inicialmete, recebem uma constante, dps eh aleatorio
float faixa=-50,cerca=0,carro=-10,carro1=80,carro2=100,carro3=25; //posi��o inicial dos elementos em Z

int limiteEsq=-30, limiteDir=30;	//define os limites e o centro da pista em X
float centro;

float passo=0.001;		//distancia percorrida em cada tick (velocidade inicial do jogo)
float incremento=0.0001;	//valor incrementado em passo a cada tick
float limite=2;			//limite de velocidade para o jogo

//observei q depende do processamento da maquina
//EX: no meu pc com VGA os "ticks" s�o bem mais rapidos, eu tenho q colocar valores menores 


//Prot�tipos das Fun��es
void Inicializa();
void Display();
void Mouse(int botao, int estado, int x, int y);
void keyboard (unsigned char key, int x, int y);
void TeclasEspeciais (int key, int x, int y);





void ruaReta() //Fun��o para desenhar a rua (constante, nao se mexe)
{ 
	glPushMatrix();
	glTranslatef(0,.2,0);
	glColor3ub(50,50,50); //rua
	glBegin(GL_QUADS);
	glVertex3f(limiteEsq, .2, -50);
	glVertex3f(limiteDir, .2, -50);
	glVertex3f(limiteDir, .2, 500);
	glVertex3f(limiteEsq, .2, 500);
	glEnd();
        glPopMatrix();
}

//outros metodos


void Display()
{
   
   // Inicializa par�metros de rendering
    // Define a cor de fundo da janela de visualiza��o como azul (ceu)
   glClearColor(0.2, 0.2, 0.5, 0.0);

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LINE_SMOOTH);
   glEnable(GL_POLYGON_SMOOTH);


   glEnable(GL_SMOOTH);
   glEnable(GL_BLEND);

   glMatrixMode(GL_PROJECTION);/*glMatrixMode()- define qual matriz ser� alterada. SEMPRE defina o tipo de apresenta��o 
                              (Ortogonal ou Perspectiva) na matriz PROJECTION.*/
   glLoadIdentity();//"Limpa" ou "transforma" a matriz em identidade, reduzindo poss�veis erros.

   if (projecao==1)
	//glOrtho(-150, 150, -150, 150, -150, 150); //Define a proje��o como ortogonal
	glOrtho(-50,50,50,-50, -50, 50); //Define a proje��o como ortogonal
   else
      gluPerspective(45,1,1,500); //Define a proje��o como perspectiva
   
   glMatrixMode(GL_MODELVIEW);/*glMatrixMode()- define qual matriz ser� alterada. SEMPRE defina a c�mera 
                              (Ortogonal ou Perspectiva) na matriz MODELVIEW (onde o desenho ocorrer�).*/
   glLoadIdentity(); ////"Limpa" ou "transforma" a matriz em identidade, reduzindo poss�veis erros.

   gluLookAt(posx,posy,posz,ox,oy,oz,lx,ly,lz); //Define a pos da c�mera, para onde olha e qual eixo est� na vertical.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /* "limpa" um buffer particular ou combina��es de buffers, 
                                                         onde buffer � uma �rea de armazenamento para informa��es da imagem. 
                                                        Nesse caso, est� "limpando os buffers para suportarem anima��es */
   //Chamada para Fun��o  ou fun��es para desenhar o objeto/cena...
   //----------------------------------------------------------------
   //glPushMatrix(); //Salva o estado atual da cena. O que for desenhado ap�s o Push n�o influenciar� o j� representado

	int x,y,z; //variaveis auxiliares

	centro=(limiteDir+limiteEsq)/2; //Atualizacao do centro da pista (nao faz sentido sem curvas)

//Incremento da velocidade do jogo
//a cada execucao de Display() (tick) o valor de passo � incrementado at� um certo limite	
//os outros elementos tomam esse "passo" como metrica para seus movimentos

	if(passo < limite) 	
		passo+=incremento;



//////////////// TERRENO VERDE /////////////////////////////

	glColor3ub(70, 100, 40); //terreno verde
	glBegin(GL_QUADS);
	glVertex3f(-500, 0, -50);
	glVertex3f(500, 0, -50);
	glVertex3f(500, 0, 500);
	glVertex3f(-500, 0, 500);
	glEnd();
 

/////////////////// RUA ///////////////////////////////////////

	// treixo de rua reta (sempre desenhada da mesma forma)
	ruaReta();

////////////////// FAIXAS DA RUA ///////////////////////////////

	glColor3ub(217,217,25); // faixas amarelas da rua (no centro da rua)
	for( z=550; z>-50; z=z-15)
	{
		glPushMatrix();
		glTranslatef(0,.3,faixa); //vai transladando o valor de "faixa"
					//da o efeito de "vindo para traz"
		glBegin(GL_QUADS);
		glVertex3f(centro-1, 0.3, z-6); //desenhas as feixas no "centro" da pista
		glVertex3f(centro-1, 0.3, z);
		glVertex3f(centro+1, 0.3, z);
		glVertex3f(centro+1, 0.3, z-6);
		glEnd();
		glPopMatrix();
	}	

	//movimentacao da faixa
	// a cada tick a faixa vai para -Z
	faixa-=passo;
	
	// quando a faixa se desloca um certo valor para tras
	// a variavel "faixa" � alterada e a faixa vai para frente novamente
	// a faixa � o unico elemento que � maior que a pista e nunca mostra o seu fim
	// a variavel "faixa" "reseta" rapidamente para dar a impressao de ser infinita
	if(faixa<-100)faixa=-10;



//////////////// CERCA DAHORA! ///////////////////////

     	glColor3ub(235,199,158); // cerca
	for( z=150; z<800; z=z+3)
	{
		glPushMatrix();
		glTranslatef(0,0,cerca);
		
		glBegin(GL_QUADS);
		glVertex3f(xcerca, 0, z);
		glVertex3f(xcerca, 6, z);
		glVertex3f(xcerca, 6, z+2);
		glVertex3f(xcerca, 0, z+2);
		glEnd();
		
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(0,0,cerca);
		glBegin(GL_QUADS); //divisoria
		glVertex3f(xcerca, 3, z+2);
		glVertex3f(xcerca, 4, z+2);
		glVertex3f(xcerca, 4, z+3);
		glVertex3f(xcerca, 3, z+3);
		glEnd();
		glPopMatrix();
		
	}
	//deslocamento da cerca
	cerca-=passo;
	//reset da posicao da cerca
	if(cerca < -1000) cerca=400;

//TODO: criar uma funcao e escolher posicoes aleatorias para colocar a cerca (lado direito ou esquerdo da pista)



//////////////////// CARRO (o meu) ////////////////////
	
	glPushMatrix();
        glColor3ub(23,234,23); //carro
        glTranslatef(xcarro,3,carro);
        glScalef(8, 3, 6);
        glutSolidCube(1);
	glPopMatrix();

//TODO: o resto do carro


///////////////// CARRO 1 ////////////////////////

	glPushMatrix();
        glColor3ub(232,23,56); //carro1
        glTranslatef(xcarro1,3,carro1);
        glScalef(8, 3, 6);
        glutSolidCube(1);
	glPopMatrix();

	carro1-=0.9*passo-0.01*(rand()%20); //controle de velocidade do carro1

	//reset do carro1
	if(carro1<-100) //passou de -100 em Z
	{
		carro1=600; //vai para 600 em Z
		srand(time(NULL)); //e sorteia uma posicao nova em X
		xcarro1=(rand()%(limiteDir-limiteEsq-10)+limiteEsq); //sorteia uma posicao no meio dos limites
		//o "-10" � para trazer mais para o meio da pista

		//TODO: fazer com q um carro nao apareca no mesmo X de outro carro
		//TODO: sortear uma nova cor para o carro
		//TODO: fazer o resto do carro tbm
	}

//////////////// CARRO 2 ////////////////////

	glPushMatrix();
        glColor3ub(100,50,100); //carro2
        glTranslatef(xcarro2,3,carro2);
        glScalef(8, 3, 6);
        glutSolidCube(1);
	glPopMatrix();

	carro2-=passo-0.001*(rand()%20); //controle de velocidade do carro2

	//reset do carro2 (o reset demora um pouco mais pq esse carro � mais lerdo)
	if(carro2<-500)
	{
		carro2=800;
		srand(time(NULL));
		xcarro2=(rand()%(int)(limiteDir-limiteEsq-10)+limiteEsq); //sorteia posicao em X
		
		//TODO: modelar o resto do carro (fazer um carro diferente do outro)
	}

//////////////// CARRO 3 /////////////////////

	glPushMatrix();
        glColor3ub(25,25,90); //carro3
        glTranslatef(xcarro3,3,carro3);
        glScalef(8, 3, 6);
        glutSolidCube(1);
	glPopMatrix();

	carro3-=0.3*passo-0.005*(rand()%20); //controle de velocidade do carro3

	//reset do carro3
	if(carro3<-500)
	{
		carro3=500;
		srand(time(NULL));
		xcarro3=(rand()%(int)(limiteDir-limiteEsq-10)+limiteEsq); //nova pos em X
	}


////////////// Controle de colisoes ////////////////

	//verificar a colisao com as laterais
	if(xcarro > limiteDir || xcarro < limiteEsq)
		puts("bateu");

	//TODO: Verificar a colicao com outros carros
	// isso pode ser feito dentro da funcao de cada carro (se tiver) 
	// ou no espe�o reservado para eles (logo depois dos "resets")

	//TODO: Implementar algo para quando ocorrer uma colisao (tela game over)
   
   
   


	glutSwapBuffers(); //Executa a Cena. SwapBuffers d� suporte para mais de um buffer, permitindo execu��o de anima��es sem cintila��es. 

        glutPostRedisplay();
}

void Mouse(int botao, int estado, int x, int y)
{  //bot�o - recebe o c�digo do bot�o pressionado
   //estado - recebe se est� pressionado ou n�o
   //x, y - recebem respectivamente as posi��es do mouse na tela
   switch (botao)
   {
      case GLUT_LEFT_BUTTON:
      if (estado == GLUT_DOWN)
      {
	      
      
      printf("pos:  x: %d  y: %d  z: %d\nolho:  x: %d  y: %d  z: %d\n",posx,posy,posz,ox,oy,oz);

		      
      projecao=1; //TA CAGADO
      //posx=0; posy=10; posz=20;
      //ox=0,oy=0,oz=0;
      //lx=0, ly=1,lz=0;
      glutPostRedisplay();
      }
      break;

      case GLUT_RIGHT_BUTTON:
      if(estado == GLUT_DOWN)
      {
         projecao=0;
        // posx=0; posy=10; posz=20;
         //oy=0; ox=0;  oz=0;
        // lx=0, ly=1, lz=0;
         glutPostRedisplay();
      }
      break;
   }
}

void keyboard (unsigned char key, int x, int y)
{//Key - recebe o c�digo ASCII da tecla
 //x, y - recebem as posi��es do mouse na tela (permite tratar os dois dispositivos)
      if (key=='a')
      {
	 posx-=3;ox-=3;
         //lz=0; ly=1; ox+=5;
      }
      else if (key=='s')
      {
	 posz+=3;oz+=3;
         //lz=0; ly=1; ox-=5;
      }
      else if (key=='d')
      {
	 posx+=3;ox+=3;
         //lz=0; ly=1; oy+=5;
      }
      else if (key=='w')    
      {
	 posz-=3;oz-=3;
      }
      else if (key==' ')
      {
	//TODO: solta nitro	  
      }
      else if (key==27)
      {         
         exit(0);
      }
      printf("pos:  x: %d  y: %d  z: %d\nolho:  x: %d  y: %d  z: %d\n",posx,posy,posz,ox,oy,oz);
      glutPostRedisplay();
}
void TeclasEspeciais (int key, int x, int y)
{//Key - recebe o c�digo ASCII da tecla
 //x, y - recebem respectivamente as posi��es mouse na tela (permite tratar os dois dispositivos)
      if (key==GLUT_KEY_RIGHT)
      {
	xcarro-=5;
	//TODO: limitar o quanto o carro pode ir para os lados
	 //ox+=3;
         //posx+=5; ox+=5;
      }
      else if (key==GLUT_KEY_PAGE_UP)
      {
         posy+=3;
         //posy+=5; oy+=5;
      }
      else if (key==GLUT_KEY_UP)
      {
	//TODO: limitar o quanto o carro pode ir para a frente
	carro+=5;
	 //oz+=3;
	 //oy+=3;
         //posz-=5; oz-=5;
      }
      else if (key==GLUT_KEY_LEFT)    
      { 
	 xcarro+=5;
         //posx-=5; ox-=5;
      }
      else if (key==GLUT_KEY_PAGE_DOWN)
      {
	 posy-=3;
         //posy-=5; oy-=5;
      }
      else if (key==GLUT_KEY_DOWN)
      {    
	//TODO: limitar o quanto o carro pode ir para tras
	carro-=5;
	 //oz-=3;
	 //oy-=3;  
         //posz+=5; oz+=5;
      }
      
      printf("pos:  x: %d  y: %d  z: %d\nolho:  x: %d  y: %d  z: %d\n",posx,posy,posz,ox,oy,oz);
      
      glutPostRedisplay();
}
int main(int argc,char **argv)
{

   glutInit(&argc, argv); // Initializes glut
    
   
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); /*Define as caracter�sticas do espa�o vetorial. 
                                                                           //  Nesse caso, permite anima��es (sem cintila��es), cores compostas por Verm. Verde e Azul,
                                                                           //  Buffer que permite trablhar com profundidade e elimina faces escondidas.*/           
  
   glutInitWindowSize(1000, 1000);
   glutInitWindowPosition(400, 400);
   glutCreateWindow("Estrutura para uma Aplica��o 3D");
   glutDisplayFunc(Display);
   glutMouseFunc(Mouse);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(TeclasEspeciais);
   glutMainLoop();
   return 0; 
}
