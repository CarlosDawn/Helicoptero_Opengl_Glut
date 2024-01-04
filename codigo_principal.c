#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "image.h"

#define PI 3.1415

#define COORD_TEXTURA_PLANO 1.0
#define COORD_TEXTURA_AVIAO 1.0
#define COR_DO_PLANO 0.52,0.52,0.78,1.0
#define COR_DO_AVIAO 0.3,0.52,0.18,1.0
#define TEXTURA_DO_PLANO "montanhas.rgb"
#define TEXTURA_DO_AVIAO "camuflagem.rgb"

GLint WIDTH =1000;
GLint HEIGHT=800;

GLfloat obs[3]={0.0,15.0,0.0};
GLfloat look[3]={0.0,5.0,0.0};
GLuint  textura_plano;
GLuint  textura_aviao;

GLshort texturas=1;
GLfloat tetaxz=0;
GLfloat raioxz=6;
GLuint  Helicoptero;

GLfloat HelicopteroLigado = 0;
GLfloat movePosicao = 1.0;
GLfloat posicaox; 
GLfloat posicaoy; 
GLfloat posicaoz;
GLfloat moveTorpedoCabeca = 12.0;
GLfloat moveTorpedoCorpo = 1.0;
GLfloat moveTorpedoCabecaDireito = 12.0;
GLfloat moveTorpedoCorpoDireito = 1.0;
GLfloat moveBala = 10.0;
GLfloat VerificaTorpedo = 0;
GLfloat VerificaTorpedoDireito = 0;
GLfloat VerificaMetralhadora = 0;

GLfloat t = 0.0;
GLfloat a = 0.0;

GLfloat ctp[4][2]={
  {-COORD_TEXTURA_PLANO,-COORD_TEXTURA_PLANO},
  {+COORD_TEXTURA_PLANO,-COORD_TEXTURA_PLANO},
  {+COORD_TEXTURA_PLANO,+COORD_TEXTURA_PLANO},
  {-COORD_TEXTURA_PLANO,+COORD_TEXTURA_PLANO}
};
void reshape(int width, int height){
  WIDTH=width;
  HEIGHT=height;
  glViewport(0,0,(GLint)width,(GLint)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(100.0,width/(float)height,0.1,100.0);
  glMatrixMode(GL_MODELVIEW);
}
void Bala(){
	  glPushMatrix();
	  glTranslatef(0.0f, 1.0f, moveBala);
	  glRotatef(90, 1.0f, 0.0f, 0.0f);
	  glScalef(0.1f, 4.0f, 0.1f);
	  glColor3f(1.0,1.0,0.0);
	  glutSolidCube(2.0f);
	  glPopMatrix();
}
void Torpedos(void){
	//Direito
	glPushMatrix();
    glTranslatef(5.3, 3.5f, moveTorpedoCabeca);
    glColor3f(1.0,0.0,0.0);
    glRotatef(180, 1.0f, 0.0f, 0.0f);
    glScalef(1.1f, 1.0f, 1.0f);
    gluCylinder(gluNewQuadric(), 0.0, 1.5, 4.0, 40, 40);
    glPopMatrix();
	
	glPushMatrix();
    glTranslatef(5.3, 3.5f, moveTorpedoCorpo);
    glColor3f(0.0,0.0,0.0);
    glScalef(1.1f, 1.0f, 1.0f);
    gluCylinder(gluNewQuadric(), 1.0f, 1.5f, 7.0f, 40, 40);
    glPopMatrix();
    
    //Pau ligando os dois 
    glPushMatrix();
    glTranslatef(0.0f, 3.0f, 4.0f);
    glRotatef(90, 0.0f, 0.0f, 1.0f);
    glScalef(0.1f, 1.7f, 0.10f);
    glutSolidCube(8.0f);
    glPopMatrix();
    
    //Esquerdo
    glPushMatrix();
    glTranslatef(-5.3, 3.5f, moveTorpedoCabecaDireito);
    glColor3f(1.0,0.0,0.0);
    glRotatef(180, 1.0f, 0.0f, 0.0f);
    glScalef(1.1f, 1.0f, 1.0f);
    gluCylinder(gluNewQuadric(), 0.0f, 1.5f, 4.0f, 40, 40);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-5.3, 3.5f, moveTorpedoCorpoDireito);
    glColor3f(0.0,0.0,0.0);
    glScalef(1.1f, 1.0f, 1.0f);
    gluCylinder(gluNewQuadric(), 1.0f, 1.5f, 7.0f, 40, 40);
    glPopMatrix();
}
void GiraHelice(){
  	  //helice 1	 
	  glPushMatrix();
	  glTranslatef(0.0f, 9.5f, 12.0f);
	  if (HelicopteroLigado==1){
	  glRotatef(a, 0.0f, 1.0f, 0.0f);
  	  }
	  glScalef(0.25f, 0.1f, 4.0f);
	  glColor3f(0.0,0.0,0.0);
	  glutSolidCube(4.5f);
	  glPopMatrix();

	  //helice 2	    
	  glPushMatrix();
	  glTranslatef(0.0f, 12.5f, -6.0f);
	  if (HelicopteroLigado==1){
	  glRotatef(a, 0.0f, 1.0f, 0.0f);
  	  }
	  glScalef(0.25f, 0.1f, 4.0f);
	  glColor3f(0.0,0.0,0.0);
	  glutSolidCube(4.5f);
	  glPopMatrix();
}
void PauHelices(void){
	  glPushMatrix();
	  glTranslatef(0.0f, 9.0f, 12.0f);
	  glScalef(0.1f, 0.7f, 0.10f);
	  glColor3f(0.8,0.8,0.8);
	  glutSolidCube(5.0f);
	  glPopMatrix();
	  
	  glPushMatrix();
	  glTranslatef(0.0f, 11.0f, -6.0f);
	  glScalef(0.1f, 0.7f, 0.10f);
	  glColor3f(0.8,0.8,0.8); 
	  glutSolidCube(5.0f);
	  glPopMatrix();
}
void Cabines(){
	GLUquadricObj *quadric;
	//Cabine 1
      glPushMatrix();
  	  glTranslatef(0,6.5,13.0);
  	  quadric=gluNewQuadric();
	  glScalef(8.0,2.5,6.0);
  	  glColor3f(0.0,0.0,0.0);
  	  glDisable(GL_TEXTURE_2D);
  	  gluSphere(quadric,0.5,12,12);
  	  glPopMatrix();
	  
	  //Cabine 2
      glPushMatrix();
  	  glTranslatef(0,5.0,13.0);
  	  quadric=gluNewQuadric();
	  glScalef(7.0,4.0,8.0);
  	  glColor3f(0.0,0.0,0.0);
  	  glDisable(GL_TEXTURE_2D);
  	  gluSphere(quadric,0.5,12,12);
  	  glPopMatrix();
}
void Metralhadora(){
	  glPushMatrix();
	  glTranslatef(0.0f, 1.0f, 8.0f);
	  glRotatef(90, 1.0f, 0.0f, 0.0f);
	  glScalef(0.7f, 4.0f, 0.7f);
	  glColor3f(0.0,0.0,0.0);
	  glutSolidCube(2.0f);
	  glPopMatrix();
	  
	  glPushMatrix();
	  glTranslatef(0.0f, 0.9f, 13.0f);
	  glRotatef(90, 1.0f, 0.0f, 0.0f);
	  glScalef(0.3f, 2.0f, 0.3f);
	  glColor3f(0.0,0.0,0.0);
	  glutSolidCube(2.0f);
	  glPopMatrix();
}
void tremDePouso(){
	//Esquerda
	  glPushMatrix();
	  glTranslatef(2.5f, -0.5f, 3.0f);
	  glRotatef(90, 1.0f, 0.0f, 0.0f);
	  glScalef(0.3f, 7.0f, 0.3f);
	  glColor3f(0.0,0.0,0.0);
	  glutSolidCube(2.0f);
	  glPopMatrix();
	  
	  glPushMatrix();
	  glTranslatef(1.5f, 1.0f, 0.5f);
	  glRotatef(50, 0.0f, 1.0f, 1.0f);
	  glScalef(0.2f, 2.0f, 0.3f);
	  glColor3f(0.0,0.0,0.0);
	  glutSolidCube(2.0f);
	  glPopMatrix();
	  glPushMatrix();
	  glTranslatef(1.7f, 1.0f, 7.5f);
	  glRotatef(35, 0.0f, 1.0f, 1.0f);
	  glScalef(0.2f, 2.0f, 0.3f);
	  glColor3f(0.0,0.0,0.0);
	  glutSolidCube(2.0f);
	  glPopMatrix();
	  
	  //Direita
	  glPushMatrix();
	  glTranslatef(-2.5f, -0.5f, 3.0f);
	  glRotatef(90, 1.0f, 0.0f, 0.0f);
	  glScalef(0.3f, 7.0f, 0.3f);
	  glColor3f(0.0,0.0,0.0);
	  glutSolidCube(2.0f);
	  glPopMatrix();
	  
	  glPushMatrix();
	  glTranslatef(-1.5f, 1.0f, 0.5f);
	  glRotatef(-50, 0.0f, 1.0f, 1.0f);
	  glScalef(0.2f, 2.0f, 0.3f);
	  glColor3f(0.0,0.0,0.0);
	  glutSolidCube(2.0f);
	  glPopMatrix();
	  glPushMatrix();
	  glTranslatef(-1.7f, 1.0f, 7.5f);
	  glRotatef(-35, 0.0f, 1.0f, 1.0f);
	  glScalef(0.2f, 2.0f, 0.3f);
	  glColor3f(0.0,0.0,0.0);
	  glutSolidCube(2.0f);
	  glPopMatrix();
}

void Compoe_Helicoptero(void){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    Helicoptero = glGenLists(1);
    glNewList(Helicoptero, GL_COMPILE);
	glTranslatef(posicaox,posicaoy,posicaoz);
	
	GLUquadricObj *quadric;
	quadric=gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    
	// Desenha o corpo do helicóptero com helice 1
	  glPushMatrix();
		glEnable(GL_TEXTURE_GEN_S);
	    glTranslatef(0.0f, 5.0f, 12.0f);
	    glRotatef(90, 1.0f, 0.0f, 0.0f);
	    glutSolidTorus(4, 0.6f, 6.0f, 8.0f);
	    glDisable(GL_TEXTURE_GEN_S);
	  glPopMatrix();
	  
    //Desenha corpo do helicoptero com helice 2
 	  glPushMatrix();
	  glTranslatef(0.0f, 6.0f, -6.0f);
	  glRotatef(90, 1.0f, 0.0f, 0.0f);
	  glEnable(GL_TEXTURE_GEN_S);
	  glutSolidTorus(5.0f, 0.5f, 6.0f, 8.0f);
	  glDisable(GL_TEXTURE_GEN_S);
	  glPopMatrix();
	  
	  //Corpo que liga as helices
	  glPushMatrix();
      glTranslatef(0.0f, 4.0f, 3.0f);
      glRotatef(90, 0.0f, 1.0f, 0.0f);
      glScalef(0.4f, 0.1f, 0.1f);
      glColor3f(0.5,0.5,0.5);
      glEnable(GL_TEXTURE_GEN_S);
      glutSolidCube(45.0f);
      glDisable(GL_TEXTURE_GEN_S);
      glPopMatrix();
      
      glPushMatrix();
  	  glTranslatef(0,5.5,2.0);
  	  quadric=gluNewQuadric();
	  glScalef(4.0,4.0,15.0);
	  glColor3f(0.0,0.0,0.0);
  	  glDisable(GL_TEXTURE_2D);
  	  gluSphere(quadric,0.56,22,12);
  	  glPopMatrix();
	  
	Cabines();
	GiraHelice();
	PauHelices();
	Torpedos();
	tremDePouso();
	Bala();
	Metralhadora();
	glutSwapBuffers();
	glEndList();
}
void carregar_texturas(void){
  IMAGE *img;
  GLenum gluerr;

  /* textura do plano */
  glGenTextures(1, &textura_plano);
  glBindTexture(GL_TEXTURE_2D, textura_plano);
  
  if(!(img=ImageLoad((char*)TEXTURA_DO_PLANO))) {
    fprintf(stderr,"Error reading a texture.\n");
    exit(-1);
  }
  
  gluerr=gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 
			   img->sizeX, img->sizeY, 
			   GL_RGB, GL_UNSIGNED_BYTE, 
			   (GLvoid *)(img->data));
  if(gluerr){
    fprintf(stderr,"GLULib%s\n",gluErrorString(gluerr));
    exit(-1);
  }

  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

  /* textura do aviao */
  glGenTextures(1, &textura_aviao);
  glBindTexture(GL_TEXTURE_2D, textura_aviao);

  
  if(!(img=ImageLoad((char*)TEXTURA_DO_AVIAO))) {
    fprintf(stderr,"Error reading a texture.\n");
    exit(-1);
  }

  gluerr=gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 
			   img->sizeX, img->sizeY, 
			   GL_RGB, GL_UNSIGNED_BYTE, 
			   (GLvoid *)(img->data));
  if(gluerr){
    fprintf(stderr,"GLULib%s\n",gluErrorString(gluerr));
    exit(-1);
  }

  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
  
}

void display(void){
  carregar_texturas();
  Compoe_Helicoptero();
  glEnable(GL_DEPTH_TEST);
  
  glDepthMask(GL_TRUE);
  glClearColor(1.0,1.0,1.0,1.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
  glPushMatrix();

  /* calcula a posicao do observador */
  obs[0]=raioxz*cos(2*PI*tetaxz/360);
  obs[2]=raioxz*sin(2*PI*tetaxz/360);
  gluLookAt(obs[0],obs[1],obs[2],look[0],look[1],look[2],0.0,1.0,0.0);

  /* habilita/desabilita uso de texturas*/
  if(texturas){
    glEnable(GL_TEXTURE_2D);  
  }
  else{
    glDisable(GL_TEXTURE_2D);
  }

  glColor4f(COR_DO_PLANO);
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
  glBindTexture(GL_TEXTURE_2D,textura_plano);
   
  glBegin(GL_QUADS);
  glTexCoord2fv(ctp[0]);  glVertex3f(-60,0,60);
  glTexCoord2fv(ctp[1]);  glVertex3f(60,0,60);
  glTexCoord2fv(ctp[2]);  glVertex3f(60,0,-60);
  glTexCoord2fv(ctp[3]);  glVertex3f(-60,0,-60);
  glEnd();
  glTranslatef(0.0,0.0,-3.0);

  glColor4f(COR_DO_AVIAO);
  glBindTexture(GL_TEXTURE_2D,textura_aviao);
  glCallList(Helicoptero);

  glPopMatrix();
  glutSwapBuffers();
}


void special(int key, int x, int y){
  switch (key) {
  case GLUT_KEY_UP:
  	if(HelicopteroLigado==1){
		posicaoz+=movePosicao;	  
	  }
    break;
  case GLUT_KEY_DOWN:
  	if(HelicopteroLigado==1){
		posicaoz-=movePosicao;		  
	  }
    break;
  case GLUT_KEY_LEFT:
  	if(HelicopteroLigado==1){
	   	posicaox+=movePosicao;	  
	  }
    break;
  case GLUT_KEY_RIGHT:
  	if(HelicopteroLigado==1){
		posicaox-=movePosicao;	  
	  }
    break;
  }
  glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
  		//Parte que move o angulo de observação;
	  case 'w':
	  	obs[1]=obs[1]+1;
	  	glutPostRedisplay();
	  	break;
	  case 's':
	  	obs[1] =obs[1]-1;
	  	glutPostRedisplay();
	  	break;
	  case 'a':
	  	tetaxz=tetaxz+2;
	  	glutPostRedisplay();
	  	break;
	  case 'd':
	  	tetaxz=tetaxz-2;
	  	glutPostRedisplay();
	  	break;
	  
	  //Sobe e desce o jato;
	  case 'Y':
	  	if (HelicopteroLigado==1){
			posicaoy+=movePosicao;
		}
	  	break;
	  case 'y':
	  	if (HelicopteroLigado==1){
			if(posicaoy>=2){
				posicaoy-=movePosicao;
			}
		}
	  	break;
	  
	  //Ligar ou desliga o jato;
	  case 'i':
			HelicopteroLigado=1;
			glutPostRedisplay();
		break;
	  case 'I':
  	    if(posicaoy==1){
			HelicopteroLigado=0;
			VerificaTorpedo = 0;
			glutPostRedisplay();	   
		}
	  	break;
	  
	  case 'T':
	  	if(HelicopteroLigado==1){
			VerificaTorpedo=1;  
		  }
	  	break;
	  case 't':
	  	if(HelicopteroLigado==1){
			  VerificaTorpedoDireito=1;
		  }
  		break;
  	  case 'M':
  	  	if(HelicopteroLigado==1){
				VerificaMetralhadora = 1;
			}
  	  	break;
  	  case 'm':
  	  	if(HelicopteroLigado==1){
				VerificaMetralhadora = 0;
				moveBala=10;
			}
  	  	break;
	  
	  case 27:
	    exit(0);
	    break;
	  case 'n':
	    texturas = !texturas;
	    glutPostRedisplay();
	    break;
	  case 'r':
	    raioxz=raioxz+1;
	    glutPostRedisplay();
	    break;
	  case 'R':
	    raioxz=raioxz-1;
	    if(raioxz==0){
	      raioxz=1;
	    }
	    glutPostRedisplay();
	    break;
  }
}

void init(){
  posicaox = 0; 
  posicaoy = 1; 
  posicaoz = 0;
  HelicopteroLigado = 0;
}
void GiraAtira(int valor){
	if (HelicopteroLigado==1){
		 t = glutGet(GLUT_ELAPSED_TIME) / 10000.0;
 	 	 a = t*10000.0;
		 if (VerificaTorpedo==1){
			 moveTorpedoCabeca+=8;
		  	 moveTorpedoCorpo+=8;
	   	      if (moveTorpedoCabeca==140||moveTorpedoCorpo==140){
				VerificaTorpedo=0;
				moveTorpedoCabeca=12;
 	 	  	    moveTorpedoCorpo=1;
	          }
	     }
		 if(VerificaTorpedoDireito==1){
			 moveTorpedoCabecaDireito+=8;
		  	 moveTorpedoCorpoDireito+=8;
	   	      if (moveTorpedoCabecaDireito==140||moveTorpedoCorpoDireito==140){
				VerificaTorpedoDireito=0;
				moveTorpedoCabecaDireito=12;
		  	    moveTorpedoCorpoDireito=1;
	          }
		 }
		 if(VerificaMetralhadora==1){
			 moveBala+=15;
			 if(moveBala==70){
				 moveBala=10;
			 }
		 }	
	}
 glutPostRedisplay();
 glutTimerFunc(33,GiraAtira, 1);
}

int main(int argc,char **argv){
  glutInitWindowPosition(0,0);
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);

  if(!glutCreateWindow("Helicoptero do Exercito")) {
    fprintf(stderr,"Error opening a window.\n");
    exit(-1);
  }
  glutTimerFunc(33,GiraAtira, 1);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  init();
  glutMainLoop();

  return(0);
}
