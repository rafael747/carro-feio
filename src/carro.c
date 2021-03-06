#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>
#include <GL/freeglut.h>

//Declaração de Variáveis Globais
int ativo=1;	//Variável Lógica para indicar se o jogo esta ativo "1" ou parado "0"

int posx=0, posy=50, posz=-100; //Variáveis que definem a posição da câmera
int oy=0,ox=0,oz=50;         //Variáveis que definem para onde a câmera olha
int lx=0, ly=1,  lz=0;         //Variáveis que definem qual eixo estará na vertical do monitor.

char buff[20];	//buffer que armazena o texto que vai no letreiro
double score=0; //pontuacao

int xcarro=0, xcarro1=0, xcarro2=25, xcarro3=-15,xcerca=-40; //posicoes inicias dos elementos em X
				//inicialmete, recebem uma constante, dps eh aleatorio
float faixa=-50,cerca=0,carro=-10,carro1=60,carro2=150,carro3=75,letreiro=100; //posição inicial dos elementos em Z

int limiteEsq=-35, limiteDir=35;	//define os limites e o centro da pista em X
float centro;

float passo=0;		//distancia percorrida em cada tick (velocidade inicial do jogo)
float incremento=0.01;	//valor incrementado em passo a cada tick
//float incremento=0.0000001;	//valor incrementado em passo a cada tick
float limite=18;			//limite de velocidade para o jogo

int r1=232, g1=23, b1=56; //cor inicial do carro1
int r2=100, g2=50, b2=100; //cor inicial do carro2
int r3=25, g3=25, b3=90; //cor inicial do carro3


//observei q depende do processamento da maquina
//EX: no meu pc com VGA os "ticks" são bem mais rapidos, eu tenho q colocar valores menores 


//Protótipos das Funções
void Inicializa();
void Display();
void Mouse(int botao, int estado, int x, int y);
void keyboard (unsigned char key, int x, int y);
void TeclasEspeciais (int key, int x, int y);

void terrenoBuilder();
void ruaBuilder(); 
void faixasBuilder();
void cercaBuilder();
void letreiroBuilder();
void escreve(char *);
void carroBuilder(int, int, int, int, int);
void carroControl();
void novaCor(int *, int *, int *);
int novaPosicao();
void fim();




void terrenoBuilder() {

        glColor3ub(70, 100, 40); //terreno verde
        glBegin(GL_QUADS);
        glVertex3f(-500, 0, -150);
        glVertex3f(500, 0, -150);
        glVertex3f(500, 0, 800);
        glVertex3f(-500, 0, 800);
        glEnd();
}


void ruaBuilder() //Função para desenhar a rua (constante, nao se mexe)
{ 
	glPushMatrix();
	glTranslatef(0,.2,0);
	glColor3ub(50,50,50); //rua
	glBegin(GL_QUADS);
	glVertex3f(limiteEsq, 0, -150);
	glVertex3f(limiteDir, 0, -150);
	glVertex3f(limiteDir, 0, 800);
	glVertex3f(limiteEsq, 0, 800);
	glEnd();
        glPopMatrix();
}

void faixasBuilder() //funcao para desenhar as faixas da rua
{
	int z; //variavel auxiliar
	glColor3ub(217,217,25); // faixas amarelas da rua (no centro da rua)
	for( z=850; z>-150; z=z-15)
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
	// a variavel "faixa" é alterada e a faixa vai para frente novamente
	// a faixa é o unico elemento que é maior que a pista e nunca mostra o seu fim
	// a variavel "faixa" "reseta" rapidamente para dar a impressao de ser infinita
	if(faixa<-100)faixa=-10;

}

void cercaBuilder() // funcao para desenhar a cerca ao lado da pista
{

	int z; //variavel auxiliar
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
	if(cerca < -1000) //ao passar de -1000 em Z
	{	cerca=400; // volta para 400
		if(rand()%2 ) //sorteia um lado da pista para aparecer
			xcerca=limiteEsq-5; //lado esquerdo
		else
			xcerca=limiteDir+5; //lado direito
	}

}

void escreve(char *string)
{
	while(*string)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*string++);
}


void letreiroBuilder() //funcao que desenha um letreiro com a pontuacao
{
	glPushMatrix();  //base do letreiro
        glColor3ub(64,64,64); 
        glTranslatef(35,40,letreiro);
        glScalef(20, 10, 5);
        glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();  //haste do letreiro
        glColor3ub(128,128,128); 
        glTranslatef(45,20,letreiro);
        glScalef(2, 50, 3);
        glutSolidCube(1);
	glPopMatrix();


	glPushMatrix();
	glColor3f(200,50,0);
	glTranslatef(40,38,letreiro-3);
	glScalef(.04,.04,.04);
	glRotatef(180,0,1,0);
	glLineWidth(2);
	
	if(ativo){ //enquanto ativo, atualiza o score
		sprintf(buff, "%.0f", score*1000);
		escreve(buff);
		glPopMatrix();
	}
	else {
		glTranslatef(-100,100,0);
		glScalef(.5,.5,.5); //escreve o score 
		escreve("Score: ");
		escreve(buff);
		glPopMatrix();
			
		glPushMatrix();		//e mensagem para resetar
		glColor3f(200,50,0);
		glTranslatef(44,38,letreiro-3);
		glScalef(.02,.02,.02);
		glRotatef(180,0,1,0);
		glLineWidth(2);
		escreve("Pressione R");
		glPopMatrix();

	}

	// reset do letreiro
	letreiro-=passo;
	if(letreiro < -400) letreiro=2000+passo*500;
	//TODO: verificar essa conta

}


void carroBuilder(int xcarro, int carro, int r, int g, int b) //função que desenha o carro
{
	//TODO: melhorar esses carros
	
	if(!r && !b && !g) {	//se for o meu carro
		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(255, 108, 0);
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, -2);
		glVertex3f(-2, 2, -2);
		glVertex3f(-2, 2, 0);
		glVertex3f(-2, 4, 2);		//lado esquerdo lider
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
		glVertex3f(2, 4, 2);		//lado direito lider
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
		glVertex3f(-2,0,8);           //parachouqe traseiro lider
		glEnd();
		glPopMatrix();
		
		glPushMatrix();	//farol 1
		glTranslatef(xcarro,3,carro-0.1);
		glScalef(2, 2, -2);
		glColor3ub(200,20 ,10);
		glBegin(GL_QUADS);
		glVertex3f(-1.6,1.4,8);
		glVertex3f(-0.8, 1.4,8);
		glVertex3f(-0.8, 0.6,8);
		glVertex3f(-1.6,0.6,8);   
		glEnd();
		glPopMatrix();
		
		glPushMatrix();	//farol 2
		glTranslatef(xcarro,3,carro-0.1);
		glScalef(2, 2, -2);
		glColor3ub(200,20 ,10);
		glBegin(GL_QUADS);
		glVertex3f(1.6,1.4,8);
		glVertex3f(0.8, 1.4,8);
		glVertex3f(0.8, 0.6,8);
		glVertex3f(1.6,0.6,8);   
		glEnd();
		glPopMatrix();

		
		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(65,65,65);
		glBegin(GL_QUADS);
		glVertex3f(-2,2,0);
		glVertex3f(2,2,0);          //parabrisa lider
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
		glTranslatef(xcarro,4,carro-.01);
		glScalef(2, 2, -2);
		//glColor3ub(80,140,160);
		glColor3ub(65,65,65);
		glBegin(GL_QUADS);
		glVertex3f(-1.5,3.5,4);
		glVertex3f(1.5,3.5,4);      //parabrisa traseiro lider (centro)
		glVertex3f(1.5, 2.5,6);
		glVertex3f(-1.5,2.5,6);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(255,108,0);
		glBegin(GL_QUADS);
		glVertex3f(-2,2,-2);
		glVertex3f(2,2,-2);           //parachoque dianteiro lider
		glVertex3f(2, 0,-2);
		glVertex3f(-2, 0,-2);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(255,108,0);
		glBegin(GL_QUADS);
		glVertex3f(-2,2,-2);		//motor lider
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
		glVertex3f(-2,2,6);		//porta malas lider
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
		glVertex3f(1,4.2,2);       	//faixa capo lider
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
		

		glPushMatrix();			//pneu dianteiro esquerdo
		glTranslatef(4.5, 1.5, 2);
		glTranslatef(xcarro,3,carro);
		glRotatef(90,0,0,1);
		glRotatef(90,1,0,0);
		glScalef(2,2,-2);
		glColor3ub(0,0,0);
		//gluCylinder(gluNewQuadric(), 1, 1, 1, 27, 27);
		glutSolidCylinder( 1, 1, 27, 27);
		glPopMatrix();

		glPushMatrix();		//roda dianteira esquerda
		glTranslatef(4.6,1.5,2);
		glTranslatef(xcarro,3,carro);
		glRotatef(90,0,1,0);
		//glScalef(2,2,-2);
		glScalef(1,1,-2);
		glColor3ub(32,32,32);
		gluDisk(gluNewQuadric(), 0, 1, 27, 27);
		glPopMatrix();
		
		glPushMatrix();		//pneu dianteiro direito
		glTranslatef(-2.5, 1.5, 2);
		glTranslatef(xcarro,3,carro);
		glRotatef(90,0,0,1);
		glRotatef(90,1,0,0);
		glScalef(2,2,-2);
		glColor3ub(0,0,0);
		glutSolidCylinder(1, 1, 27, 27);
		//gluCylinder(gluNewQuadric(), 1, 1, 1, 27, 27);
		glPopMatrix();

		glPushMatrix();		//roda dianteira direita
		glTranslatef(-4.6,1.5,2);
		glTranslatef(xcarro,3,carro);
		glRotatef(90,0,1,0);
		glScalef(1,1,-2);
		//glScalef(2,2,-2);
		glColor3ub(32,32,32);
		gluDisk(gluNewQuadric(), 0, 1, 27, 27);
		glPopMatrix();
		
		glPushMatrix();		//pneu traseiro esquerdo
		glTranslatef(4.5, 1.5, -12);
		glTranslatef(xcarro,3,carro);
		glRotatef(90,0,0,1);
		glRotatef(90,1,0,0);
		glScalef(2,2,-2);
		glColor3ub(0,0,0);
		glutSolidCylinder(1, 1, 27, 27);
		//gluCylinder(gluNewQuadric(), 1, 1, 1, 27, 27);
		glPopMatrix();
		
		glPushMatrix();		//roda traseira esquerda
		glTranslatef(4.6,1.5,-12);
		glTranslatef(xcarro,3,carro);
		glRotatef(90,0,1,0);
		glScalef(1,1,-2);
		//glScalef(2,2,-2);
		glColor3ub(32,32,32);
		gluDisk(gluNewQuadric(), 0, 1, 27, 27);
		glPopMatrix();

		glPushMatrix();		//pneu traseiro direito
		glTranslatef(-2.5, 1.5, -12);
		glTranslatef(xcarro,3,carro);
		glRotatef(90,0,0,1);
		glRotatef(90,1,0,0);
		glScalef(2,2,-2);
		glColor3ub(0,0,0);
		glutSolidCylinder(1, 1, 27, 27);
		//gluCylinder(gluNewQuadric(), 1, 1, 1, 27, 27);
		glPopMatrix();
		
		glPushMatrix();		//pneu traseiro direito
		glTranslatef(-4.6,1.5,-12);
		glTranslatef(xcarro,3,carro);
		glRotatef(90,0,1,0);
		glScalef(1,1,-2);
		//glScalef(2,2,-2);
		glColor3ub(32,32,32);
		gluDisk(gluNewQuadric(), 0, 1, 27, 27);
		glPopMatrix();
		
	}
	else {	//se for outro carro

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(r, g, b);
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, -2);
		glVertex3f(-2, 2, -2);
		glVertex3f(-2, 2, 0);
		glVertex3f(-2, 4, 2);		//lado esquerdo
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
		glVertex3f(2, 4, 2);		//lado direito
		glVertex3f(2, 4, 4);
		glVertex3f(2, 2, 6);
		glVertex3f(2, 2, 8);
		glVertex3f(2, 0, 8);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(r-20, g-10, b);
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

		glPushMatrix();	//farol 1
		glTranslatef(xcarro,3,carro-0.1);
		glScalef(2, 2, -2);
		glColor3ub(200,20 ,10);
		glBegin(GL_QUADS);
		glVertex3f(-1.6,1.4,8);
		glVertex3f(-0.8, 1.4,8);
		glVertex3f(-0.8, 0.6,8);
		glVertex3f(-1.6,0.6,8);   
		glEnd();
		glPopMatrix();
		
		glPushMatrix();	//farol 2
		glTranslatef(xcarro,3,carro-0.1);
		glScalef(2, 2, -2);
		glColor3ub(200,20 ,10);
		glBegin(GL_QUADS);
		glVertex3f(1.6,1.4,8);
		glVertex3f(0.8, 1.4,8);
		glVertex3f(0.8, 0.6,8);
		glVertex3f(1.6,0.6,8);   
		glEnd();
		glPopMatrix();


		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(65, 65, 65);
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
		glTranslatef(xcarro,4,carro-.01);
		glScalef(2, 2, -2);
		glColor3ub(65,65,65);
		glBegin(GL_QUADS);
		glVertex3f(-1.5,3.5,4);
		glVertex3f(1.5,3.5,4);      //parabrisa traseiro (centro)
		glVertex3f(1.5, 2.5,6);
		glVertex3f(-1.5,2.5,6);
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
		glVertex3f(-2,2,-2);	//motor
		glVertex3f(2,2,-2);
		glVertex3f(2, 2, 0);
		glVertex3f(-2, 2, 0);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xcarro,3,carro);
		glScalef(2, 2, -2);
		glColor3ub(r-20, g-10, b);
		glBegin(GL_QUADS);
		glVertex3f(-2,2,6);	//porta malas
		glVertex3f(2,2,6);
		glVertex3f(2,2,8);
		glVertex3f(-2,2,8);
		glEnd();
		glPopMatrix();

		glPushMatrix();			//pneu dianteiro esquerdo
		glTranslatef(4.5, 1.5, 2);
		glTranslatef(xcarro,3,carro);
		glRotatef(90,0,0,1);
		glRotatef(90,1,0,0);
		glScalef(2,2,-2);
		glColor3ub(0,0,0);
		//gluCylinder(gluNewQuadric(), 1, 1, 1, 27, 27);
		glutSolidCylinder( 1, 1, 27, 27);
		glPopMatrix();

		glPushMatrix();		//roda dianteira esquerda
		glTranslatef(4.6,1.5,2);
		glTranslatef(xcarro,3,carro);
		glRotatef(90,0,1,0);
		glScalef(1,1,-2);
		//glScalef(2,2,-2);
		glColor3ub(32,32,32);
		gluDisk(gluNewQuadric(), 0, 1, 27, 27);
		glPopMatrix();
		
		glPushMatrix();		//pneu dianteiro direito
		glTranslatef(-2.5, 1.5, 2);
		glTranslatef(xcarro,3,carro);
		glRotatef(90,0,0,1);
		glRotatef(90,1,0,0);
		glScalef(2,2,-2);
		glColor3ub(0,0,0);
		glutSolidCylinder(1, 1, 27, 27);
		//gluCylinder(gluNewQuadric(), 1, 1, 1, 27, 27);
		glPopMatrix();

		glPushMatrix();		//roda dianteira direita
		glTranslatef(-4.6,1.5,2);
		glTranslatef(xcarro,3,carro);
		glRotatef(90,0,1,0);
		glScalef(1,1,-2);
		//glScalef(2,2,-2);
		glColor3ub(32,32,32);
		gluDisk(gluNewQuadric(), 0, 1, 27, 27);
		glPopMatrix();
		
		glPushMatrix();		//pneu traseiro esquerdo
		glTranslatef(4.5, 1.5, -12);
		glTranslatef(xcarro,3,carro);
		glRotatef(90,0,0,1);
		glRotatef(90,1,0,0);
		glScalef(2,2,-2);
		glColor3ub(0,0,0);
		glutSolidCylinder(1, 1, 27, 27);
		//gluCylinder(gluNewQuadric(), 1, 1, 1, 27, 27);
		glPopMatrix();
		
		glPushMatrix();		//roda traseira esquerda
		glTranslatef(4.6,1.5,-12);
		glTranslatef(xcarro,3,carro);
		glRotatef(90,0,1,0);
		glScalef(1,1,-2);
		//glScalef(2,2,-2);
		glColor3ub(32,32,32);
		gluDisk(gluNewQuadric(), 0, 1, 27, 27);
		glPopMatrix();

		glPushMatrix();		//pneu traseiro direito
		glTranslatef(-2.5, 1.5, -12);
		glTranslatef(xcarro,3,carro);
		glRotatef(90,0,0,1);
		glRotatef(90,1,0,0);
		glScalef(2,2,-2);
		glColor3ub(0,0,0);
		glutSolidCylinder(1, 1, 27, 27);
		//gluCylinder(gluNewQuadric(), 1, 1, 1, 27, 27);
		glPopMatrix();
		
		glPushMatrix();		//pneu traseiro direito
		glTranslatef(-4.6,1.5,-12);
		glTranslatef(xcarro,3,carro);
		glRotatef(90,0,1,0);
		glScalef(1,1,-2);
		//glScalef(2,2,-2);
		glColor3ub(32,32,32);
		gluDisk(gluNewQuadric(), 0, 1, 27, 27);
		glPopMatrix();
		

	}

}

void carControl() //funcao que controla os carro (cores, resets, etc)
{
	
	////// Controle de velocidade dos carros

	if(ativo) { //primeiramente verifica se o jogo esta ativo

		carro1-=0.8*passo-0.01*(rand()%20); 	//velocidade do carro1
		carro2-=passo-0.001*(rand()%20); 	//velocidade do carro2
		carro3-=0.3*passo-0.005*(rand()%20);	//velocidade do carro3

		//TODO: reinplementar o threshold (de forma aleatoria)

	}		

	////// Reset da posicao dos carros

	// Carro1
	if(carro1 < -100) { //passou de -100 em Z
		novaCor(&r1, &g1, &b1); //ganha uma nova cor
		xcarro1=novaPosicao();	//e uma nova posicao em X
		carro1=800; 		//vai para 600 em Z
	}

	// Carro2
	if(carro2 < -500) { //passou de -500 em Z
		novaCor(&r2, &g2, &b2);	//cor nova
		xcarro2=novaPosicao();	//posicao nova
		carro2=850;		//vai para 800 em Z
	}

	//Carro3
	if(carro3 < -500) { //passou de -500 em Z
		novaCor(&r3, &g3, &b3);	//cor nova
		xcarro3=novaPosicao();	//posicao nova
		carro3=800;		//vai para 500 em Z
	}

	/////// Controle das colisoes

	/// com os outros carros

	if(carro1 < carro+20 && carro1 > carro-20 && xcarro1 < xcarro+9 && xcarro1 > xcarro-9)
		fim(); //colisao com carro1
	else if(carro2 < carro+20 && carro2 > carro-20 && xcarro2 < xcarro+9 && xcarro2 > xcarro-9)
		fim(); //colisao com carro2
	else if(carro3 < carro+20 && carro3 > carro-20 && xcarro3 < xcarro+9 && xcarro3 > xcarro-9)
		fim(); //colisao com carro3

	// com as laterais
	if(xcarro > limiteDir-5) { //colisao lateral direita
		//xcarro-=10; //da um espaço da lateral
		fim();
	}
	else if(xcarro < limiteEsq+5) { //colisao lateral esquerda
		//xcarro+=10;
                fim();
	}
}

void novaCor(int *r, int *g, int *b){

		*r = rand() % 220 + 30; //cor nova para o carro
		*g = rand() % 200 + 50; //um pouco mais clara
		*b = rand() % 180 + 70; //para nao confundir com a pista
}

int novaPosicao(){
		
		int posicao;
		//srand(time(NULL)); //e sorteia uma posicao nova em X
		posicao=(rand()%(limiteDir-limiteEsq-10)+limiteEsq+10); 
			//sorteia uma posicao no meio dos limites
			//o "-10" e "+10" é para trazer mais para o meio da pista

		while( xcarro1 < posicao+10 && xcarro1 > posicao-10 && carro1 > 50 ||
		       xcarro2 < posicao+10 && xcarro2 > posicao-10 && carro2 > 50 ||
		       xcarro3 < posicao+10 && xcarro3 > posicao-10 && carro3 > 50) {
			//enquanto o carro estiver na reta de outro e o outro estiver > 50 em Z
			posicao+=10; //varia a posicao
			if(posicao > limiteDir-10)
				posicao=limiteEsq+10;
		}
		return(posicao);
}

/// Game Over

void fim()
{
	if(ativo) { //para fazer essa operacao somente uma vez
		//posiciona o letreiro e a camera
		letreiro=carro+50;
	
		posx=55; posy=50; posz=carro-100;
		oy=0;ox=0;oz=carro+50;
		lx=0; ly=1;  lz=0;
	}

	//para o jogo
	ativo=0;
	passo=0;

}

void Display()
{
   
   // Inicializa parâmetros de rendering
    // Define a cor de fundo da janela de visualização como azul (ceu)
   glClearColor(0.2, 0.2, 0.5, 0.0);

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LINE_SMOOTH);
   glEnable(GL_POLYGON_SMOOTH);
   glEnable(GL_SMOOTH);
   glEnable(GL_BLEND);

   glMatrixMode(GL_PROJECTION);/*glMatrixMode()- define qual matriz será alterada. SEMPRE defina o tipo de apresentação 
                              (Ortogonal ou Perspectiva) na matriz PROJECTION.*/
   glLoadIdentity();//"Limpa" ou "transforma" a matriz em identidade, reduzindo possíveis erros.
   gluPerspective(45,1,1,800); //Define a projeção como perspectiva
   glMatrixMode(GL_MODELVIEW);/*glMatrixMode()- define qual matriz será alterada. SEMPRE defina a câmera 
                              (Ortogonal ou Perspectiva) na matriz MODELVIEW (onde o desenho ocorrerá).*/
   glLoadIdentity(); ////"Limpa" ou "transforma" a matriz em identidade, reduzindo possíveis erros.

   gluLookAt(posx,posy,posz,ox,oy,oz,lx,ly,lz); //Define a pos da câmera, para onde olha e qual eixo está na vertical.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /* "limpa" um buffer particular ou combinações de buffers, 
                                                         onde buffer é uma área de armazenamento para informações da imagem. 

                                                        Nesse caso, está "limpando os buffers para suportarem animações */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	centro=(limiteDir+limiteEsq)/2; //Atualizacao do centro da pista (nao faz sentido sem curvas)

//Incremento da velocidade do jogo
//a cada execucao de Display() (tick) o valor de passo é incrementado até um certo limite	
//os outros elementos tomam esse "passo" como metrica para seus movimentos
	
	if(ativo) { //verifica se o jogo esta ativo
		score+=incremento/100; //pontuacao
		if(passo < limite ) 
			passo+=incremento;
	}


///////////// TERRENO VERDE //////////////////////

	// terreno verde 
	terrenoBuilder();

///////////// RUA /////////////////////////////

	// treixo de rua reta (sempre desenhada da mesma forma)
	ruaBuilder();

//////////// FAIXAS DA RUA ////////////////////

	// faixas amarelas da rua, sempre no centro da rua
	faixasBuilder();

////////// CERCA DAHORA! //////////////////////

	//cerca em um lado da pista
	cercaBuilder();

////////// LETREIRO //////////////////////

	//letreiro com a pontuação
	letreiroBuilder();

/////////// CARRO (o meu) ////////////////////
	
	//desenha o carro (o meu) nas posicoes xcarro (X) e carro (Z)
	carroBuilder(xcarro, carro, 0, 0, 0);

////////////// CARRO 1 ////////////////////
	
	//desenha o carro1 (inicialmente vermelho)
	carroBuilder(xcarro1, carro1, r1, g1, b1);

///////////// CARRO 2 //////////////////// ROXO
	
	//desenha o carro2 (inicialmente roxo)
	carroBuilder(xcarro2, carro2, r2, g2, b2);
	
///////////// CARRO 3 //////////////////// AZUL

	//desenha o carro3 (inicialmente azul)
	carroBuilder(xcarro3, carro3, r3, g3, b3);


/////////// Controle dos Carros (cor, velocidade, colisao, etc) ///////

	carControl();

	//printf("%.2f\n",passo);


	glutSwapBuffers(); //Executa a Cena. SwapBuffers dá suporte para mais de um buffer, permitindo execução de animações sem cintilações. 
        glutPostRedisplay();
}

void keyboard (unsigned char key, int x, int y)
{//Key - recebe o código ASCII da tecla
 //x, y - recebem as posições do mouse na tela (permite tratar os dois dispositivos)
	if (key=='\t')
	{
		if(ly==1 && posy==50) //se modo normal
		{
			//coloca visao de cima
			posx=0;posy=350;posz=60;
			oy=0;ox=0;oz=100;
			lx=0; ly=0;  lz=1;
		}
		else if(lz==1) //se visao de cima
		{
			//TODO: coloca em primeira pessoa
			posx=xcarro;posy=10;posz=carro;
			oy=10;ox=0;oz=800;
			lx=0; ly=1;  lz=0;

			//TODO: se for realmente fazer essa visao
			//colocar elementos adicionais no carro
			
		}
		else //se primeira pessoa
		{	
			//coloca visao normal
			posx=0;posy=50;posz=-100;
			oy=0;ox=0;oz=50;
			lx=0; ly=1;  lz=0;
		}
	}
	else if (key=='r') // reset do game
	{
		
		passo=0;	//reseta a velocidade
		ativo=1;	//volta o estado para ativo

		//reseta os carros
		//para evitar nova colisao ao reiniciar o jogo
		carro=-10;xcarro=0;
		carro1=60;carro2=200;carro3=-500;

		//reset da pontuacao
		score=0;
		
		//reset da camera
		posx=0; posy=50; posz=-100;
		oy=0;ox=0;oz=50;
		lx=0; ly=1;  lz=0;


	}	

	else if (key==' ')
	{
		passo+=incremento*10000;
	//TODO: solta nitro	  
	}
	else if (key==27)
	{         
		exit(0);
	}
	glutPostRedisplay();
}
void TeclasEspeciais (int key, int x, int y)
{//Key - recebe o código ASCII da tecla
 //x, y - recebem respectivamente as posições mouse na tela (permite tratar os dois dispositivos)
	
	if (key==GLUT_KEY_RIGHT && ativo)
	{
		if(xcarro > limiteEsq-10)
			xcarro-=5;
	}
	else if (key==GLUT_KEY_UP && ativo)
	{
		if(carro < 180)
			carro+=5;
	}
	else if (key==GLUT_KEY_LEFT && ativo)    
	{
		if(xcarro < limiteDir +10)
			xcarro+=5;
	}
	else if (key==GLUT_KEY_DOWN && ativo)
	{    
		if(carro > -10)
			carro-=5;
	}

	if(!lz && posy != 50) //está em primeira pessoa
	{
		 posx=xcarro;posy=10;posz=carro;
                 //oy=10;ox=0;oz=800;
                 //lx=0; ly=1;  lz=0;

	}
	glutPostRedisplay();
}
int main(int argc,char **argv)
{

   glutInit(&argc, argv); // Initializes glut
    
   
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); /*Define as características do espaço vetorial. 
                                                                           //  Nesse caso, permite animações (sem cintilações), cores compostas por Verm. Verde e Azul,
                                                                           //  Buffer que permite trablhar com profundidade e elimina faces escondidas.*/           
  
   glutInitWindowSize(1000, 1000);
   glutInitWindowPosition(400, 400);
   glutCreateWindow("carro feio");
   glutDisplayFunc(Display);
   //glutMouseFunc(Mouse);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(TeclasEspeciais);
   glutMainLoop();
   return 0; 
}
