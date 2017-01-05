#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>
#include <GL/freeglut.h>

//Declaração de Variáveis Globais
//int projecao=0; //Variável Lógica para Definir o Tipo de Projeção (Perspectiva ou Ortogonal)
int posx=0, posy=50, posz=-80; //Variáveis que definem a posição da câmera
int oy=0,ox=0,oz=0;         //Variáveis que definem para onde a câmera olha
int lx=0, ly=1,  lz=0;         //Variáveis que definem qual eixo estará na vertical do monitor.

int xcarro1=0,xcarro2=25,xcarro3=-5;
float limiteEsq=-30, limiteDir=30;
float car=0,rua=-50,passo=1,cerca=0,carro1=80,carro2=100,carro3=-25;
//Protótipos das Funções
void Inicializa();
void Display();
void Mouse(int botao, int estado, int x, int y);
void keyboard (unsigned char key, int x, int y);
void TeclasEspeciais (int key, int x, int y);
	

void ruaReta()
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


void ruaCurva()
{
   int i;
   for(i=0; i<500; i++)
   {
	glPushMatrix();
	glTranslatef(0,.2,rua--);
	glColor3ub(50,50,50);
	glBegin(GL_QUADS);
	glVertex3f(limiteEsq-(i*.2), .2, i);
	glVertex3f(limiteDir-(i*.2), .2, i);
	glVertex3f(limiteDir-(i*.2), .2, i+5);
	glVertex3f(limiteEsq-(i*.2), .2, i+5);
	glEnd();
        glPopMatrix();
   }
}

void Display()
{
   
   // Inicializa parâmetros de rendering
    // Define a cor de fundo da janela de visualização como preta
   glClearColor(0.2, 0.2, 0.5, 0.0);

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LINE_SMOOTH);
   glEnable(GL_POLYGON_SMOOTH);


   glEnable(GL_SMOOTH);
   glEnable(GL_BLEND);

   glMatrixMode(GL_PROJECTION);/*glMatrixMode()- define qual matriz será alterada. SEMPRE defina o tipo de apresentação 
                              (Ortogonal ou Perspectiva) na matriz PROJECTION.*/
   glLoadIdentity();//"Limpa" ou "transforma" a matriz em identidade, reduzindo possíveis erros.

   //if (projecao==1)
   //   glOrtho(-150, 150, -150, 150, -150, 150); //Define a projeção como ortogonal
   //else
      gluPerspective(45,1,1,500); //Define a projeção como perspectiva
   
   glMatrixMode(GL_MODELVIEW);/*glMatrixMode()- define qual matriz será alterada. SEMPRE defina a câmera 
                              (Ortogonal ou Perspectiva) na matriz MODELVIEW (onde o desenho ocorrerá).*/
   glLoadIdentity(); ////"Limpa" ou "transforma" a matriz em identidade, reduzindo possíveis erros.

   gluLookAt(posx,posy,posz,ox,oy,oz,lx,ly,lz); //Define a pos da câmera, para onde olha e qual eixo está na vertical.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /* "limpa" um buffer particular ou combinações de buffers, 
                                                         onde buffer é uma área de armazenamento para informações da imagem. 
                                                        Nesse caso, está "limpando os buffers para suportarem animações */
   //Chamada para Função  ou funções para desenhar o objeto/cena...
   //----------------------------------------------------------------
   //glPushMatrix(); //Salva o estado atual da cena. O que for desenhado após o Push não influenciará o já representado


   int x,y,z;

      glColor3ub(70, 100, 40); //terreno verde
	glBegin(GL_QUADS);
	glVertex3f(-500, 0, -50);
	glVertex3f(500, 0, -50);
	glVertex3f(500, 0, 500);
	glVertex3f(-500, 0, 500);
	glEnd();
 

// treixo de rua reta

	ruaReta();
//ruaCurva();



    glColor3ub(217,217,25); // rua marcas
	for( z=550; z>-50; z=z-15)
	{
		glPushMatrix();
		glTranslatef(0,.3,rua);

		glBegin(GL_QUADS);
		glVertex3f(-1, 0.3, z-6);
		glVertex3f(-1, 0.3, z);
		glVertex3f(1, 0.3, z);
		glVertex3f(1, 0.3, z-6);
		glEnd();
        	
		glPopMatrix();
		
	}	
		if(passo < 50)
			passo+=.001;

		rua-=passo;
		if(rua<-100)rua=-10;

    /*  glColor3ub(56,176,222); //piscina legal
	glBegin(GL_QUADS);
	glVertex3f(-15, 0.1, 15);
	glVertex3f(10, 0.1, 15);
	glVertex3f(10, 0.1, 35);
	glVertex3f(-15, 0.1, 35);
	glEnd();
*/

// cerca dahora

     	glColor3ub(235,199,158); // cerca
	for( z=150; z<800; z=z+3)
	{
		
		glPushMatrix();
		glTranslatef(0,0,cerca);
		
		glBegin(GL_QUADS);
		glVertex3f(-35, 0, z);
		glVertex3f(-35, 6, z);
		glVertex3f(-35, 6, z+2);
		glVertex3f(-35, 0, z+2);
		glEnd();
		
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(0,0,cerca);
		glBegin(GL_QUADS); //divisoria
		glVertex3f(-35, 3, z+2);
		glVertex3f(-35, 4, z+2);
		glVertex3f(-35, 4, z+3);
		glVertex3f(-35, 3, z+3);
		glEnd();
		glPopMatrix();
		
	}
	cerca-=passo;
	if(cerca < -1000) cerca=400;

/*      glColor3ub(216,216,191); //fundacao casa cinza
	glBegin(GL_QUADS);
	glVertex3f(-20, 0.2, -10);
	glVertex3f(20, 0.2, -10);
	glVertex3f(20, 0.2, 10);
	glVertex3f(-20, 0.2, 10);
	glEnd();
 
    glColor3ub(255,28,174); // chaleira rosa
    glutWireTeapot(2.0);
    
      glColor3ub(165,128,100); // parede esquerda
	glBegin(GL_QUADS);
	glVertex3f(-20, 0, -10);
	glVertex3f(-20, 0, 10);
	glVertex3f(-20, 10, 10);
	glVertex3f(-20, 10, -10);
	glEnd();

     //glColor3ub(168,168,168); // parede direita
	glBegin(GL_QUADS);
	glVertex3f(20, 0, -10);
	glVertex3f(20, 0, 10);
	glVertex3f(20, 10, 10);
	glVertex3f(20, 10, -10);
	glEnd();

     //glColor3ub(112,147,219); // parede frente A
	glBegin(GL_QUADS);
	glVertex3f(-20, 0, -10);
	glVertex3f(-20, 8, -10);
	glVertex3f(10, 8, -10);
	glVertex3f(10, 0, -10);
	glEnd();

     //glColor3ub(168,168,168); // parede frente B
	glBegin(GL_QUADS);
	glVertex3f(15, 0, -10);
	glVertex3f(15, 8, -10);
	glVertex3f(20, 8, -10);
	glVertex3f(20, 0, -10);
	glEnd();

     //glColor3ub(168,168,168); // parede frente C
	glBegin(GL_QUADS);
	glVertex3f(-20, 8, -10);
	glVertex3f(-20, 10, -10);
	glVertex3f(20, 10, -10);
	glVertex3f(20, 8, -10);
	glEnd();


     //glColor3ub(168,168,168); // parede fundo A
	glBegin(GL_QUADS);
	glVertex3f(-20, 0, 10);
	glVertex3f(-20, 3, 10);
	glVertex3f(20, 3, 10);
	glVertex3f(20, 0, 10);
	glEnd();

     //glColor3ub(168,168,168); // parede fundo B
	glBegin(GL_QUADS);
	glVertex3f(-20, 7, 10);
	glVertex3f(-20, 10, 10);
	glVertex3f(20, 10, 10);
	glVertex3f(20, 7, 10);
	glEnd();

     //glColor3ub(168,168,168); // parede fundo C
	glBegin(GL_QUADS);
	glVertex3f(-20, 3, 10);
	glVertex3f(-20, 7, 10);
	glVertex3f(-10, 7, 10);
	glVertex3f(-10, 3, 10);
	glEnd();

     //glColor3ub(168,168,168); // parede fundo C
	glBegin(GL_QUADS);
	glVertex3f(-5, 3, 10);
	glVertex3f(-5, 7, 10);
	glVertex3f(20, 7, 10);
	glVertex3f(20, 3, 10);
	glEnd();
*/	
	
	glPushMatrix();
        glColor3ub(23,234,23); //carro
        glTranslatef(car,3,-10);
        glScalef(8, 3, 6);
        glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
        glColor3ub(232,23,56); //carro2
        glTranslatef(xcarro1,3,carro1);
        glScalef(8, 3, 6);
        glutSolidCube(1);
	glPopMatrix();

	carro1-=passo-0.01*(rand()%20);
	if(carro1<-100)
	{
		carro1=600;
		srand(time(NULL));
		xcarro1=(rand()%(int)(limiteDir-limiteEsq)+limiteEsq);
	}

	glPushMatrix();
        glColor3ub(100,50,100); //carro3
        glTranslatef(xcarro2,3,carro2);
        glScalef(8, 3, 6);
        glutSolidCube(1);
	glPopMatrix();

	carro2-=passo-0.001*(rand()%20);
	if(carro2<-500)
	{
		carro2=800;
		srand(time(NULL));
		xcarro2=(rand()%(int)(limiteDir-limiteEsq)+limiteEsq);
	}

	glPushMatrix();
        glColor3ub(25,25,90); //carro4
        glTranslatef(xcarro3,3,carro3);
        glScalef(8, 3, 6);
        glutSolidCube(1);
	glPopMatrix();

	carro3-=0.3*passo-0.005*(rand()%20);
	if(carro3<-500)
	{
		carro3=500;
		srand(time(NULL));
		xcarro3=(rand()%(int)(limiteDir-limiteEsq)+limiteEsq);
	}
//glPushMatrix(); //roda 1
	//glColor3ub(0,0,0);
	//glTranslatef(car-3,2,-34);
	//glScalef(3, 3, 8);
        //glutSolidCylinder(.5,1,50,50);	
        //glPopMatrix();

	//glPushMatrix(); //roda 2
	//glColor3ub(0,0,0);
	//glTranslatef(car+3,2,-34);
	//glScalef(3, 3, 8);
        //glutSolidCylinder(.5,1,50,50);	
        //glPopMatrix();
	
	//glPushMatrix();
        //glColor3ub(220,220,220); //cubo
        //glTranslatef(10,3,-30);
        //glScalef(8, 8, 8);
        //glutSolidCube(1);
	//glPopMatrix();

	//glPushMatrix();
        //glColor3ub(200,5,70); //carro 2
        //glTranslatef(10,3,-30);
        //glScalef(6, 3, 8);
        //glutSolidCube(1);
	//glPopMatrix();

	//glPushMatrix(); //roda 1
	//glColor3ub(0,0,0);
	//glTranslatef(10,2,-30);
	//glScalef(8, 3, 3);
        //glutSolidCylinder(.5,1,50,50);	
        //glPopMatrix();

	//glPushMatrix(); //roda 2
	//glColor3ub(0,0,0);
	//glTranslatef(10,2,-35);
	//glScalef(8, 3, 3);
        //glutSolidCylinder(.5,1,50,50);	
        //glPopMatrix();

	if(car > limiteDir || car < limiteEsq)
		puts("bateu");
        

         // glPopMatrix();  //Retorna ao estado anterior da cena. O que for desenhado após o Push não influenciou o já representado
   //----------------------------------------------------------------   
   
   
   glutSwapBuffers(); //Executa a Cena. SwapBuffers dá suporte para mais de um buffer, permitindo execução de animações sem cintilações. 

        glutPostRedisplay();
}

void Mouse(int botao, int estado, int x, int y)
{  //botão - recebe o código do botão pressionado
   //estado - recebe se está pressionado ou não
   //x, y - recebem respectivamente as posições do mouse na tela
   switch (botao)
   {
      case GLUT_LEFT_BUTTON:
      if (estado == GLUT_DOWN)
      {
	      
      
      printf("pos:  x: %d  y: %d  z: %d\nolho:  x: %d  y: %d  z: %d\n",posx,posy,posz,ox,oy,oz);

		      
         //projecao=1;
         //posx=0; posy=10; posz=20;
         //ox=0,oy=0,oz=0;
         //lx=0, ly=1,lz=0;
        glutPostRedisplay();
      }
      break;

      case GLUT_RIGHT_BUTTON:
      if(estado == GLUT_DOWN)
      {
         //projecao=0;
         //posx=0; posy=10; posz=20;
         //oy=0; ox=0;  oz=0;
         //lx=0, ly=1, lz=0;
         //glutPostRedisplay();
      }
      break;
   }
}

void keyboard (unsigned char key, int x, int y)
{//Key - recebe o código ASCII da tecla
 //x, y - recebem as posições do mouse na tela (permite tratar os dois dispositivos)
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
	      car-=5;
              }
      else if (key==27)
      {         
         exit(0);
      }
      printf("pos:  x: %d  y: %d  z: %d\nolho:  x: %d  y: %d  z: %d\n",posx,posy,posz,ox,oy,oz);
      glutPostRedisplay();
}
void TeclasEspeciais (int key, int x, int y)
{//Key - recebe o código ASCII da tecla
 //x, y - recebem respectivamente as posições mouse na tela (permite tratar os dois dispositivos)
      if (key==GLUT_KEY_RIGHT)
      {
	car-=5;
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
	 oz+=3;
	 //oy+=3;
         //posz-=5; oz-=5;
      }
      else if (key==GLUT_KEY_LEFT)    
      { 
	 car+=5;
         //posx-=5; ox-=5;
      }
      else if (key==GLUT_KEY_PAGE_DOWN)
      {
	 posy-=3;
         //posy-=5; oy-=5;
      }
      else if (key==GLUT_KEY_DOWN)
      {    
	 oz-=3;
	 //oy-=3;  
         //posz+=5; oz+=5;
      }
      
      printf("pos:  x: %d  y: %d  z: %d\nolho:  x: %d  y: %d  z: %d\n",posx,posy,posz,ox,oy,oz);
      
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
   glutCreateWindow("Estrutura para uma Aplicação 3D");
   glutDisplayFunc(Display);
   glutMouseFunc(Mouse);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(TeclasEspeciais);
   glutMainLoop();
   return 0; 
}
