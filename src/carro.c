#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>
#include <GL/freeglut.h>
#include <time.h>

//Declara��o de Vari�veis Globais
int projecao=0;	//Vari�vel L�gica para Definir o Tipo de Proje��o (Perspectiva ou Ortogonal)
//TODO: vai ser necessario imprementar a visao ortogonal

int posx=0, posy=50, posz=-80; //Vari�veis que definem a posi��o da c�mera
int oy=0,ox=0,oz=50;         //Vari�veis que definem para onde a c�mera olha
int lx=0, ly=1,  lz=0;         //Vari�veis que definem qual eixo estar� na vertical do monitor.

//TODO:	as posi��es de camera precisam ser ajustadas ainda

int xcarro=0, xcarro1=28, xcarro2=25, xcarro3=-15,xcerca=-40; //posicoes inicias dos elementos em X
				//inicialmete, recebem uma constante, dps eh aleatorio
float faixa=-50,cerca=0,carro=-10,carro1=10,carro2=100,carro3=25; //posi��o inicial dos elementos em Z

int limiteEsq=-35, limiteDir=35;	//define os limites e o centro da pista em X
float centro;

float passo=0.5;		//distancia percorrida em cada tick (velocidade inicial do jogo)
float incremento=0.01;	//valor incrementado em passo a cada tick
float limite=20;			//limite de velocidade para o jogo

int gameOver = 0;				//variavel do fim do jogo

float threshold[3] = {0.01, 0.001, 0.005};				//limiar de velocidade

float faixaOver=-50, cercaOver=0, carroOver=-10, passoOver=0.5, incrementoOver=0.01; //variaveis de fim do jogo

void initRand(){
		srand(time(NULL));			//inicia a seed de aleatoriedade
}

int r1=123, g1=73, b1=30;
int r2=200, g2=121, b2=56;   //para aleatoriedade de cores
int r3=90, g3=133, b3=213;
//observei q depende do processamento da maquina
//EX: no meu pc com VGA os "ticks" s�o bem mais rapidos, eu tenho q colocar valores menores


//Prot�tipos das Fun��es
void Inicializa();
void Display();
void Mouse(int botao, int estado, int x, int y);
void keyboard (unsigned char key, int x, int y);
void TeclasEspeciais (int key, int x, int y);

void ruaReta() {

	glPushMatrix();
	glTranslatef(0,.2,0);
	glColor3ub(50,50,50); //rua
	glBegin(GL_QUADS);
	glVertex3f(limiteEsq, 0, -50);
	glVertex3f(limiteDir, 0, -50);
	glVertex3f(limiteDir, 0, 500);
	glVertex3f(limiteEsq, 0, 500);
	glEnd();
        glPopMatrix();
}

void carroBuilder(int xcarro, int carro, int r, int g, int b) {

	if(!r && !b && !g) {

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(255, 108, 0);
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, -2);
		glVertex3f(-2, 2, -2);
		glVertex3f(-2, 2, 0);
		glVertex3f(-2, 4, 2);						//lado esquerdo lider
		glVertex3f(-2, 4, 4);
		glVertex3f(-2, 2, 6);
		glVertex3f(-2, 2, 8);
		glVertex3f(-2, 0, 8);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(255, 108, 0);
		glBegin(GL_POLYGON);
		glVertex3f(2, 0, -2);
		glVertex3f(2, 2, -2);
		glVertex3f(2, 2, 0);
		glVertex3f(2, 4, 2);						//lado direito lider
		glVertex3f(2, 4, 4);
		glVertex3f(2, 2, 6);
		glVertex3f(2, 2, 8);
		glVertex3f(2, 0, 8);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(255,108,0);
		glBegin(GL_QUADS);
		glVertex3f(-2,4,2);
		glVertex3f(2,4,2);            	//capo lider
		glVertex3f(2, 4,4);
		glVertex3f(-2, 4,4);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(255,108,0);
		glBegin(GL_QUADS);
		glVertex3f(-2,2,8);
		glVertex3f(2, 2,8);
		glVertex3f(2, 0,8);
		glVertex3f(-2,0,8);               //parachouqe traseiro lider
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(255,108,0);
		glBegin(GL_QUADS);
		glVertex3f(-2,2,0);
		glVertex3f(2,2,0);                //parabrisa lider
		glVertex3f(2,4,2);
		glVertex3f(-2,4,2);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(255,108,0);
		glBegin(GL_QUADS);
		glVertex3f(-2,4,4);
		glVertex3f(2,4,4);                //parabrisa traseiro lider
		glVertex3f(2, 2,6);
		glVertex3f(-2,2,6);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(255,108,0);
		glBegin(GL_QUADS);
		glVertex3f(-2,2,-2);
		glVertex3f(2,2,-2);                //parachoque dianteiro lider
		glVertex3f(2, 0,-2);
		glVertex3f(-2, 0,-2);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(255,108,0);
		glBegin(GL_QUADS);
		glVertex3f(-2,2,-2);							//motor lider
		glVertex3f(2,2,-2);
		glVertex3f(2, 2, 0);
		glVertex3f(-2, 2, 0);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(255,108,0);
		glBegin(GL_QUADS);
		glVertex3f(-2,2,6);							//porta malas lider
		glVertex3f(2,2,6);
		glVertex3f(2,2,8);
		glVertex3f(-2,2,8);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(0,0,0);
		glBegin(GL_QUADS);
		glVertex3f(-1,4.2,2);
		glVertex3f(1,4.2,2);            	//faixa capo lider
		glVertex3f(1,4.2,4);
		glVertex3f(-1,4.2,4);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(0,0,0);
		glBegin(GL_QUADS);
		glVertex3f(-1,2.2,-2);
		glVertex3f(1,2.2,-2);            	//faixa motor lider
		glVertex3f(1,2.2,0);
		glVertex3f(-1,2.2,0);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(0,0,0);
		glBegin(GL_QUADS);
		glVertex3f(-1,2.2,6);
		glVertex3f(1,2.2,6);            	//faixa porta malas lider
		glVertex3f(1,2.2,8);
		glVertex3f(-1,2.2,8);
		glEnd();
		glPopMatrix();
	} else {

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(r, g, b);
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, -2);
		glVertex3f(-2, 2, -2);
		glVertex3f(-2, 2, 0);
		glVertex3f(-2, 4, 2);						//lado esquerdo
		glVertex3f(-2, 4, 4);
		glVertex3f(-2, 2, 6);
		glVertex3f(-2, 2, 8);
		glVertex3f(-2, 0, 8);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(r, g, b);
		glBegin(GL_POLYGON);
		glVertex3f(2, 0, -2);
		glVertex3f(2, 2, -2);
		glVertex3f(2, 2, 0);
		glVertex3f(2, 4, 2);						//lado direito
		glVertex3f(2, 4, 4);
		glVertex3f(2, 2, 6);
		glVertex3f(2, 2, 8);
		glVertex3f(2, 0, 8);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(r, g, b);
		glBegin(GL_QUADS);
		glVertex3f(-2,4,2);
		glVertex3f(2,4,2);            	//capo
		glVertex3f(2, 4,4);
		glVertex3f(-2, 4,4);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(r, g, b);
		glBegin(GL_QUADS);
		glVertex3f(-2,2,8);
		glVertex3f(2, 2,8);
		glVertex3f(2, 0,8);
		glVertex3f(-2,0,8);               //parachouqe traseiro
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(r, g, b);
		glBegin(GL_QUADS);
		glVertex3f(-2,2,0);
		glVertex3f(2,2,0);                //parabrisa
		glVertex3f(2,4,2);
		glVertex3f(-2,4,2);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(r, g, b);
		glBegin(GL_QUADS);
		glVertex3f(-2,4,4);
		glVertex3f(2,4,4);                //parabrisa traseiro
		glVertex3f(2, 2,6);
		glVertex3f(-2,2,6);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(r, g, b);
		glBegin(GL_QUADS);
		glVertex3f(-2,2,-2);
		glVertex3f(2,2,-2);                //parachoque dianteiro
		glVertex3f(2, 0,-2);
		glVertex3f(-2, 0,-2);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(r, g, b);
		glBegin(GL_QUADS);
		glVertex3f(-2,2,-2);							//motor
		glVertex3f(2,2,-2);
		glVertex3f(2, 2, 0);
		glVertex3f(-2, 2, 0);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(r, g, b);
		glBegin(GL_QUADS);
		glVertex3f(-2,2,6);							//porta malas
		glVertex3f(2,2,6);
		glVertex3f(2,2,8);
		glVertex3f(-2,2,8);
		glEnd();
		glPopMatrix();
	}

}

//outros metodos
void cercaBuilder(int z) {

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
}

void faixasBuilder(int z) {

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
}

void terrenoBuilder() {

	glColor3ub(70, 100, 40); //terreno verde
	glBegin(GL_QUADS);
	glVertex3f(-500, 0, -50);
	glVertex3f(500, 0, -50);
	glVertex3f(500, 0, 500);
	glVertex3f(-500, 0, 500);
	glEnd();
}

void projecaoConfig() {

	if (projecao==1)
 //glOrtho(-150, 150, -150, 150, -150, 150); //Define a proje��o como ortogonal
		 glOrtho(-50,50,50,-50, -50, 50); //Define a proje��o como ortogonal
	else
		 gluPerspective(45,1,1,500); //Define a proje��o como perspectiva
}

void Display() {

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

   projecaoConfig();

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

	terrenoBuilder();

/////////////////// RUA ///////////////////////////////////////

	// treixo de rua reta (sempre desenhada da mesma forma)
	ruaReta();

////////////////// FAIXAS DA RUA ///////////////////////////////

	faixasBuilder(z);

	//movimentacao da faixa
	// a cada tick a faixa vai para -Z
	faixa-=passo;

	// quando a faixa se desloca um certo valor para tras
	// a variavel "faixa" � alterada e a faixa vai para frente novamente
	// a faixa � o unico elemento que � maior que a pista e nunca mostra o seu fim
	// a variavel "faixa" "reseta" rapidamente para dar a impressao de ser infinita
	if(faixa<-100)
		faixa=-10;

//////////////// CERCA DAHORA! ///////////////////////

	cercaBuilder(z);
	//deslocamento da cerca
	cerca-=passo;
	//reset da posicao da cerca
	if(cerca < -1000) {

		cerca=400;

		if(rand()%2 )
			xcerca=-40;
		else
			xcerca=40;
	}

//////////////////// CARRO LIDER ////////////////////

	carroBuilder(xcarro, carro, 0, 0, 0);

//////////////////// CARRO 1 //////////////////////////

	carroBuilder(xcarro1, carro1, r1, g1, b1);

	carro1-=0.9*passo-threshold[0]*(rand()%20); //controle de velocidade do carro1

	//reset do carro1
	if(carro1<-100) { //passou de -100 em Z

		r1 = rand() % 256;
		g1 = rand() % 256;
		b1 = rand() % 256;

		carro1=600; //vai para 600 em Z

		 //e sorteia uma posicao nova em X
		xcarro1=(rand()%(limiteDir-limiteEsq-10)+limiteEsq+10); //sorteia uma posicao no meio dos limites
		//o "-10" � para trazer mais para o meio da pista

		while(xcarro2 < xcarro1+10 && xcarro2 > xcarro1-10 && carro2 > 50 || xcarro3 < xcarro1+10 && xcarro3 > xcarro1-10 && carro3 > 50){

			xcarro1+=10;
			if(xcarro1 > limiteDir-10)
				xcarro1=limiteEsq+10;
			puts("carro 1 muda");
		}

	}

	/////// Colisao carro 1

	if(carro1 < carro+8 && carro1 > carro-8) {

		if(xcarro1 < xcarro+10 && xcarro1 > xcarro-10) {

			gameOver = 1;
			passo=0;
			incremento=0;
			cerca=0;
			faixa=0;
			carro=0;
			carro1=-99;											//zera tudo e joga os carros longe
			carro2=-499;
			carro3=-499;
			threshold[0]=0;
			threshold[1]=0;
			threshold[2]=0;
		}
	}

////////////////// CARRO 2 ///////////////////////////

	carroBuilder(xcarro2, carro2, r2, g2, b2);

	carro2-=passo-threshold[1]*(rand()%20); //controle de velocidade do carro2

	//reset do carro2 (o reset demora um pouco mais pq esse carro � mais lerdo)
	if(carro2<-500) {

		r2 = rand() % 256;
		g2 = rand() % 256;
		b2 = rand() % 256;

		carro2=800;

		xcarro2=(rand()%(int)(limiteDir-limiteEsq-10)+limiteEsq+10); //sorteia posicao em X


 		while(xcarro1 < xcarro2+10 && xcarro1 > xcarro2-10 && carro1 > 50 || xcarro3 < xcarro2+10 && xcarro3 > xcarro2-10 && carro3 > 50) {

                        xcarro2-=10;
                        if(xcarro2 < limiteEsq+10)
                        	xcarro2=limiteDir-10;
                }

	}

	/////// Colisao carro 2

	if(carro2 < carro+8 && carro2 > carro-8) {

		if(xcarro2 < xcarro+10 && xcarro2 > xcarro-10) {

			gameOver = 1;
			passo=0;
			incremento=0;
			cerca=0;
			faixa=0;
			carro=0;								//zera tudo e joga os carros longe
			carro1=-99;
			carro2=-499;
			carro3=-499;
			threshold[0]=0;
			threshold[1]=0;
			threshold[2]=0;
		}
	}

/////////////////////// CARRO 3 //////////////////////////

	carroBuilder(xcarro3, carro3, r3, g3, b3);

	carro3-=0.3*passo-threshold[2]*(rand()%20); //controle de velocidade do carro3

	//reset do carro3
	if(carro3<-500) {

		r3 = rand() % 256;
		g3 = rand() % 256;
		b3 = rand() % 256;

		carro3=500;

		xcarro3=(rand()%(int)(limiteDir-limiteEsq-10)+limiteEsq+10); //nova pos em X


		 while(xcarro1 < xcarro3+10 && xcarro1 > xcarro3-10 && carro1 > 50 || xcarro2 < xcarro3+10 && xcarro2 > xcarro3-10 && carro2 > 50) {
    							xcarro3-=10;
      						if(xcarro3 < limiteEsq+10)
                  	xcarro3=15;
			}

	}

	/////// Colisao carro 3

	if(carro3 < carro+8 && carro3 > carro-8) {

		if(xcarro3 < xcarro+10 && xcarro3 > xcarro-10) {

			gameOver = 1;
			passo=0;
			incremento=0;
			cerca=0;
			faixa=0;
			carro=0;
			carro1=-99;
			carro2=-499;				//zera tudo e joga os carros longe
			carro3=-499;
			threshold[0]=0;
			threshold[1]=0;
			threshold[2]=0;
		}
	}


////////////// Colisões laterais ////////////////

	//verificar a colisao com as laterais
	if(xcarro > limiteDir || xcarro < limiteEsq) {

			gameOver = 1;
			passo=0;
			incremento=0;
			cerca=0;
			faixa=0;
			carro=0;
			carro1=-99;
			carro2=-499;				//zera tudo e joga os carros longe
			carro3=-499;
			threshold[0]=0;
			threshold[1]=0;
			threshold[2]=0;
	}

	glutSwapBuffers(); //Executa a Cena. SwapBuffers d� suporte para mais de um buffer, permitindo execu��o de anima��es sem cintila��es.

  glutPostRedisplay();
}

void Mouse(int botao, int estado, int x, int y) {
	//bot�o - recebe o c�digo do bot�o pressionado
   //estado - recebe se est� pressionado ou n�o
   //x, y - recebem respectivamente as posi��es do mouse na tela
   switch (botao) {

      case GLUT_LEFT_BUTTON:
	      if (estado == GLUT_DOWN) {

		      posx=0;posy=50;posz=-80;
		      oy=0;ox=0;oz=50;
		      lx=0; ly=1;  lz=0;


		      //projecao=1; //TA CAGADO
		      //posx=0; posy=10; posz=20;
		      //ox=0,oy=0,oz=0;
		      //lx=0, ly=1,lz=0;
		      glutPostRedisplay();

					if(gameOver) {

						gameOver = 0;

						passo=passoOver;
						incremento=incrementoOver;
						faixa=faixaOver;
						cerca=cercaOver;
						carro=carroOver;
						xcarro=0;
						threshold[0]=0.01;
						threshold[1]=0.001;
						threshold[2]=0.005;
					}
      	}
      break;

      case GLUT_RIGHT_BUTTON:
	      if(estado == GLUT_DOWN) {

					posx=0;
					posy=250;
					posz=60;
					oy=0;
					ox=0;
					oz=80;
					lx=0;
					ly=0;
					lz=1;

	        glutPostRedisplay();
	      }

      break;
   }
}

void keyboard (unsigned char key, int x, int y) {
	//Key - recebe o c�digo ASCII da tecla
 //x, y - recebem as posi��es do mouse na tela (permite tratar os dois dispositivos)
      if (key=='a') {

	 			posx-=3;
				ox-=3;
      }
      else if (key=='s') {

				posz+=3;
				oz+=3;
      }
      else if (key=='d') {

	 			posx+=3;
				ox+=3;
      }
      else if (key=='w') {

	 			posz-=3;
				oz-=3;
      }
      else if (key==' ') {

	//TODO: solta nitro

      }
      else if (key==27) {

         exit(0);
      }

      glutPostRedisplay();
}

void TeclasEspeciais (int key, int x, int y) {
		//Key - recebe o c�digo ASCII da tecla
		//x, y - recebem respectivamente as posi��es mouse na tela (permite tratar os dois dispositivos)
      if (key==GLUT_KEY_RIGHT) {

				xcarro-=5;
      }
      else if (key==GLUT_KEY_PAGE_UP) {

         posy+=3;
      }
      else if (key==GLUT_KEY_UP) {

				if(carro < 180)
					carro+=5;
	    }
      else if (key==GLUT_KEY_LEFT) {

	 			xcarro+=5;
      }
      else if (key==GLUT_KEY_PAGE_DOWN) {

	 			posy-=3;
      }
      else if (key==GLUT_KEY_DOWN) {

				if(carro > -10)
					carro-=5;
			}

      glutPostRedisplay();
}

int main(int argc,char **argv) {

   glutInit(&argc, argv); // Initializes glut


	 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); /*Define as caracter�sticas do espa�o vetorial.
                                                                           //  Nesse caso, permite anima��es (sem cintila��es), cores compostas por Verm. Verde e Azul,
                                                                           //  Buffer que permite trablhar com profundidade e elimina faces escondidas.*/
   glutInitWindowSize(1000, 1000);
   glutInitWindowPosition(400, 400);
   glutCreateWindow("Estrutura para uma Aplicacao 3D");
   glutDisplayFunc(Display);
   glutMouseFunc(Mouse);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(TeclasEspeciais);
   glutMainLoop();
   return 0;
}
