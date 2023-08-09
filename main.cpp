//Tema: Transformaciones Geometricas: Sistema de poleas
#include<iostream>
#include <stdlib.h>
#include<conio.h>
#include <gl/glut.h>
#include<math.h>
using namespace std;
void cuerdaesfera(void);
void girar_objeto_geometrico (void);
// declaracion de variables
// theta[] me indica los ángulos iniciales en los ejes
GLfloat theta[4] = {0.0,0.0,0.0};
GLint eje = -1;
float a=0; //dato que modifica la posicion de los cuerpos que presentan movimiento
float distancia=0.05; //modifica el valor de 'a' y define cuanto se movera el cuerpo al apretar M/N
//ejes coordenados
void ejes(int longitud)
{
 glBegin(GL_LINES);
 glVertex3d(0,0,longitud);
 glVertex3d(0,0,0);
 glEnd();
 glBegin(GL_LINES);
 glVertex3d(0,0,0);
 glVertex3d(0,longitud,0);
 glEnd();
 glBegin(GL_LINES);
 glVertex3d(0,0,0);
 glVertex3d(longitud,0,0);
 glEnd();
}

//cuerda horizontal(junto al prisma)
void cuerda_horizontal(int longitud){
glBegin(GL_LINES);
 glVertex3d(0,0.2,0);
 glVertex3d(longitud,0.2,0);
 glEnd();
}

//cuerda vertical(junto al cilindro)
void cuerda_vertical(int longitud){
glBegin(GL_LINES);
 glVertex3d(-1.3,0.3,0);
 glVertex3d(-1.3,longitud,0);
 glEnd();
}

//cuerda diagonal(une ambas poleas)
void cuerda_diagonal(){
glBegin(GL_LINES);
 glVertex3f(-0.05,0.21,0);
 glVertex3f(-1.11,1.05,0);
 glEnd();
}

//cilindro alambrico
void mi_cilindro(int Nverticales,int Ncortes)
{
    float ang=0,dang,hz,x,y,z,radio=0.5;
    int i,j;
    hz=1/float(Ncortes-1);

    for(i=0;i<Ncortes;i++)
    {
        glBegin(GL_LINE_LOOP);
        for (ang = 0.0f; ang < 2 * M_PI; ang += 2*M_PI/Nverticales)
        {
            x = radio * cos(ang);
            y=-0.5+i*hz;
            z = radio * sin(ang);
            glVertex3f(x,y,z);
        }
        glEnd();
    }
}

//cilindro solido
void mi_cilindro_solido (float Nverticales, float Ncortes)
{

    float ang, hz, x, y, z, radio=0.5;
    float xFinal,yFinal,zFinal;
    int i,j;
    hz=1/float(Ncortes-1);
    for(i=0;i<Ncortes-1;i++){
        glBegin(GL_QUAD_STRIP);
        for(ang=2*M_PI; ang >=-2*M_PI ; ang -= 2*M_PI/(float)Nverticales){
            x=radio*cos(ang);
            y=0.25-i*hz;
            z = radio*sin(ang);

            glVertex3f(x, y, z);
            glVertex3f(x, y+hz, z);
        }
        glEnd();
    }

    //tapas
    for(i=0;i<Ncortes;i++)
    {
        glBegin(GL_POLYGON);
        for (ang = 0.0f; ang < 2 * M_PI; ang += 2*M_PI/Nverticales)
        {
            x = radio * cos(ang);
            y=-0.5+i*hz;
            z = radio * sin(ang);
            glVertex3f(x,y,z);
        }
        glEnd();
    }
}

//prisma achatado
void soporte_prismal(void){
    glPushMatrix();
    glScalef(4,0.2,3);
    glColor3f(1,1,1);
    glutWireCube(1);
    glColor3f(0,1,1);
    glutSolidCube(1);
    glPopMatrix();
}

//un prisma de la polea
void palo_polea(void){
    glPushMatrix();
    glScalef(0.2,1,0.2);
    glColor3f(1,0,0);
    glutSolidCube(1);
    glColor3f(1,1,0);
    glutWireCube(1);
    glPopMatrix();
}

//cilindro de la polea
void cilindro_polea(){
    glPushMatrix();
    glRotated(90,0,0,1);
    glScalef(1,0.2,1);
    mi_cilindro_solido(50,5);
    glColor3f(1,0,0);
    mi_cilindro(50,2);
    glPopMatrix();
}

//polea(conformado por 2 palos de polea y un cilindro de polea)
void polea(void){
    glPushMatrix();
    glRotated(90,0,1,0);
    glPushMatrix();
    glRotated(90,0,1,0);
    glTranslatef(0,0.5,0);
    glTranslatef(0,0,0.2);
    palo_polea();
    glTranslatef(0,0,-0.4);
    palo_polea();
    glPopMatrix();
    cilindro_polea();//cilindro de la polea
    glPopMatrix();
}

//dibuja todos los solidos que se mantienen estaticos
void sistema_estatico(void){
    glPushMatrix();

    //soporte de la polea suspendida
    glPushMatrix();
    glScalef(0.1,0.1,0.1);
    glTranslatef(-12,12.1,0);
    soporte_prismal();
    glPopMatrix();

    //mesa del sistema
    soporte_prismal();

    //polea suspendida
    glPushMatrix();
    glScalef(0.2,0.2,0.2);
    glTranslatef(-6,5,0);
    polea();
    glPopMatrix();

    //polea invertida(sobre la mesa)
    glPushMatrix();
    glScalef(0.2,0.2,0.2);
    glTranslatef(0,1.5,0);
    glRotated(180,0,0,1);
    polea();
    glPopMatrix();
    glPopMatrix();

    //cuerda que une ambas poleas
    cuerda_diagonal();

}

//dibuja todos los solidos que se transforman
void sistema_movimiento(void){
//lo que se mueve HORIZONTAL
glPushMatrix();

//cuerda horizontal y su deformacion
glPushMatrix();
glScaled(1.0+a,1.0,1.0);
cuerda_horizontal(1);
glPopMatrix();

glTranslated(a,0.0,0.0);//movimiento horizontal del prisma sobre la mesa

//prisma sobre la mesa
glScalef(0.1,0.1,0.1);
glColor3f(1,1,0);
glTranslated(11,2,0);
glutWireCube(2);
glColor3f(1,0,0);
glutSolidCube(2);
glPopMatrix();


 //lo que se mueve VERTICAL
glPushMatrix();

glTranslated(0.0,a,0.0);//movimiento vertical del cilinro suspendido

//cuerda vertical y su deformacion
glPushMatrix();
glScaled(1.0,1.0-a,1.0);
cuerda_vertical(1);
glPopMatrix();

//prisma suspendido
glScalef(0.2,0.2,0.2);
glTranslated(-6.5,1,0);
glColor3f(1,1,0);
mi_cilindro(50,2);//
glColor3f(1,0,0);
mi_cilindro_solido(50,5);

 glPopMatrix();
}

// dibujamos nuestra escena
void display(void)
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glLoadIdentity();
 glScalef(1.5,1.5,1.5);//aumentar tamaño del sistema completo
 glPushMatrix();

 //glColor3f(1,1,1);
 //ejes(1);

glPopMatrix();
// composicion de rotaciones
 glRotatef(theta[0],1.0,0.0,0.0);//eje x positivo
 glRotatef(theta[1],0.0,1.0,0.0);//eje y positivo
 glRotatef(theta[2],-1.0,0.0,0.0);//eje x negativo
 glRotatef(theta[3],0.0,-1.0,0.0);//eje y negatico

 //solidos que se mantienen estaticos
 sistema_estatico();

 //solidos que se mueven o cambian al apretar M/N
 sistema_movimiento();

 glFlush();
// intercambiamos los buffers, el que se muestra y el que esta oculto
 glutSwapBuffers();
}

//funcion para las rotaciones
void sistema_rota()
{
    float aumento=0.25; //aumento del angulo
    theta[eje] += aumento;
    if(theta[eje]>360) theta[eje] -= 360.0;
    display();
}

//aumenta el valor de movimiento de los cuerpos
void aumento(){
if(a<0.6){
    a+=distancia; //variacion de la distancia
    }
}
//disminuye el valor de movimiento de los cuerpos
void decremento(){
if(a>=distancia){
    a-=distancia; //variacion de la distancia
    }
}

//acciones del teclado
void teclado(unsigned char tecla,int x,int y)
{
switch(tecla){
//rotaciones
case 'L' : eje = 0; break;
case 'D' : eje = 1; break;
case 'P' : eje = 2; break;
case 'A' : eje = 3; break;
//movimientos
case 'M' :  aumento(); break;
case 'N' :  decremento(); break;
case 'F' : exit(0) ; break;
    }
}

// control de ventana
void myReshape(int w, int h)
{
 glViewport(0,0,w,h);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 if(w <=h)
glOrtho(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w,
 2.0*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
 else
glOrtho(-2.0*(GLfloat)w/(GLfloat)h,
 2.0*(GLfloat)w/(GLfloat)h, -2.0,2.0,-10.0,10.0);
 glMatrixMode(GL_MODELVIEW);
}

//funcion principal
int main(int argc, char **argv)
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize(800,500);
 glutCreateWindow("PC02_MooreSalazar");
 glutReshapeFunc(myReshape);
 // invocamos a display() para dibujar nuestra escena
 glutDisplayFunc(display);
 glutKeyboardFunc(teclado);
 glutIdleFunc(sistema_rota);
 glEnable(GL_DEPTH_TEST);
 glutMainLoop();
 return 0;
}
