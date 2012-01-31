/* IMN428, Infographie 3D

 TP2: Introduction aux transformations 3D sous OpenGL

 Nom1: Jean-Philippe Ouellet 11057955
 Nom2: Felix-Antoine Ouellet
 Nom3: Francois Rheault
 Nom4: Alexandre Bizeau

*/

#define GLUT_DISABLE_ATEXIT_HACK

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <windows.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include "Glut/GLUT.h"
#endif


/* Variables globales pour contenir la dimension de la fenetre */
GLint windW, windH;

/* Variable globale indiquant si les axes doivent suivre le cube ou non */
GLboolean moveAxis = GL_FALSE;

/* Modes de transformations (commandes dans le menu) */
enum
{
    None,
    Cube,
    Cone,
    ModeTranslateX,
    ModeTranslateY,
    ModeTranslateZ,
    ModeRotateX,
    ModeRotateY,
    ModeRotateZ,
    ModeScaleX,
    ModeScaleY,
    ModeScaleZ,
    ModeScaleU,
    ModeShearX,
    ModeShearY,
    ModeShearZ,
    ActionReset,
    ActionQuit
};
int CurrentMode = None;    /* tranlation, rotation, changement d'echelle, ...*/
int SelectedObject = Cube; /* Cube ou Cone */


/* Etat de la souris */
int LeftButtonIsPressed = GL_FALSE;     /* Bouton gauche enfonce? */
int LastPosX, LastPosY;                 /* Derniere position de souris (en coordonnees pixel) */

GLfloat cubeModelviewMatrix[16];        /* Matrix de transformation du cube */
GLfloat coneModelviewMatrix[16];        /* Matrix de transformation du cone */


/*
   Fonction permettant de dessiner un tetrahedre centre en (0,0,0)
   Utilise la couleur definie par le dernier glColor
*/
void DrawTetrahedron()
{
    GLfloat V[][3] = {{ 3,  0,  0},{-3, -1,  1.73}, {-3, -1, -1.73}, {-3,  2,  0}};

    glBegin( GL_TRIANGLES );
    {
        glVertex3fv(V[0]);
        glVertex3fv(V[1]);
        glVertex3fv(V[2]);

        glVertex3fv(V[1]);
        glVertex3fv(V[2]);
        glVertex3fv(V[3]);

        glVertex3fv(V[0]);
        glVertex3fv(V[2]);
        glVertex3fv(V[3]);

        glVertex3fv(V[0]);
        glVertex3fv(V[1]);
        glVertex3fv(V[3]);
    }
    glEnd();

}

/*
    Fonction permettant d'initialiser la matrice de transformations
    du cone et du cube
*/
void initTransformations(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0,0,-80);  /* les objets sont initialement centree en (0,0,-80) */
    glGetFloatv(GL_MODELVIEW_MATRIX,cubeModelviewMatrix);
    glGetFloatv(GL_MODELVIEW_MATRIX,coneModelviewMatrix);
}

/*
    Fonction permettant de dessiner un cube centre en (0,0,0)
*/
void DrawCube()
{
    const int M = -10;
    const int P =  10;

    /* Contour du cube (avant, haut, arriere, bas) */
    glBegin( GL_TRIANGLE_STRIP );
    {
        glColor3f(1,0,0);
        glVertex3f(M,M,P);
        glVertex3f(P,M,P);

        glColor3f(1,1,0);
        glVertex3f(M,P,P);
        glVertex3f(P,P,P);

        glColor3f(0,1,0);
        glVertex3f(M,P,M);
        glVertex3f(P,P,M);

        glColor3f(0,0,1);
        glVertex3f(M,M,M);
        glVertex3f(P,M,M);

        glColor3f(1,0,0);
        glVertex3f(M,M,P);
        glVertex3f(P,M,P);
    }
    glEnd();

    /* Face gauche */
    glBegin( GL_TRIANGLE_FAN );
    {
        glColor3f(0,1,1);
        glVertex3f(M,M,P);
        glVertex3f(M,P,P);

        glColor3f(1,0,1);
        glVertex3f(M,P,M);
        glVertex3f(M,M,M);
    }
    glEnd();

    /* Face Droite */
    glBegin( GL_TRIANGLE_FAN );
    {
        glColor3f(0,1,1);
        glVertex3f(P,M,P);
        glVertex3f(P,P,P);

        glColor3f(1,0,1);
        glVertex3f(P,P,M);
        glVertex3f(P,M,M);
    }
    glEnd();
}


/*
    Fonction permettant de dessiner les axes du cube
*/
void DrawAxis()
{

    /* AJOUTER DU CODE ICI!

     (Il faut dessiner la pointe des axes avec des
      tetrahedres. Ne pas oublier de bien specifier les couleurs,
      les translations et les rotations. Le tetrahedre
      original pointe dans la direction des X positifs.) */

	glLineWidth(4);
	glBegin(GL_LINES);
	{
		glColor3f(1,0,0);
		glVertex3f(0,0,0);
        glVertex3f(20,0,0);

		glColor3f(0,1,0);
		glVertex3f(0,0,0);
        glVertex3f(0,20,0);

		glColor3f(0,0,1);
		glVertex3f(0,0,0);
        glVertex3f(0,0,20);
	}
	glEnd();

	glColor3f(1,0,0);
	glPushMatrix();
	glTranslated(20,0,0);
	DrawTetrahedron();
	glPopMatrix();

	glColor3f(0,1,0);
	glPushMatrix();
	glTranslated(0,20,0);
	glRotated(90, 0, 0, 1);
	DrawTetrahedron();
	glPopMatrix();

	glColor3f(0,0,1);
	glPushMatrix();
	glPushMatrix();
	glTranslated(0,0,20);
	glRotated(-90, 0, 1, 0);
	DrawTetrahedron();
	glPopMatrix();
}


/*
    Fonction de selection d'un item dans le menu (standard glut)
*/
void MenuSelection(int value)
{

    switch(value){

    case Cube:
        /* AJOUTER DU CODE ICI!
        l'object selectionne est le cube
        */
		SelectedObject = Cube;
    break;

    case Cone:
        /* AJOUTER DU CODE ICI!
        l'object selectionne est le cube
        */
		SelectedObject = Cone;
    break;

    case ActionReset:

        /* AJOUTER DU CODE ICI!

        Il faut ici re-initialiser les coordonnees des
        transformations affines. */
		Display();
		
    break;
    case ActionQuit:
        exit(0);
    break;
    }

    CurrentMode = value;
}



/*
    Fonction de redimensionnement de la fenetre (standard glut)
*/
void Reshape(int width, int height)
{
    windW = (GLint)width;
    windH = (GLint)height;
}


/*
    Fonction de rafraichissement de la fenetre (standard glut)
*/
void Display(void)
{
    /* Configurer le "viewport" OpenGL.
       Les dimensions de la fenetre sont contenues dans windW et windH */
    glViewport(0, 0, windW, windH);

    /* Configurer une camera tres simple (projection perspective) */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLdouble)windW / (GLdouble)windH, 1, 300);

    /* AJOUTER DU CODE ICI!
       Il faut ici afficher le cube, le cone et les axes avec LES BONNES
       TRANSFORMATIONS AFFINES.  */

    /* Selectionner la pile de transformations attachee au modele (MODELVIEW) */
	glMatrixMode(GL_MODELVIEW);

    /* Effacer l'ecran */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    /* Afficher le cube */
	DrawCube();

    /* Afficher le cone de couleur blanche */


    /* Afficher les axes du systeme centres sur l'objet selectionne */
	DrawAxis();

    glutSwapBuffers();
}


/*
    Fonction appelee lorsqu'un bouton de la souris est presse (standard glut)
*/
void MouseButton( int button, int state, int x, int y )
{
    /* On s'assure que LeftButtonIsPressed a la bonne valeur */
    if( button == GLUT_LEFT_BUTTON )
        LeftButtonIsPressed = (state == GLUT_DOWN);

    if( LeftButtonIsPressed )
    {
        LastPosX = x;
        LastPosY = y;
    }
}



/*
   Fonction appelee lorsque la souris est deplacee (standard glut)
*/
void MouseMove(int x, int y)
{
    GLfloat delta;
    GLfloat translate, rotate, scale, shear;

    /* On s'interesse seulement aux deplacements avec le bouton gauche enfonce */
    if( !LeftButtonIsPressed )
        return;

    delta = (y - LastPosY);
    rotate = delta * 0.33;
    translate = delta;
    scale = delta;
    shear = delta/50.0;
    if( scale > -0.5 && scale < 0.5 )
        scale = 0;
    else
        scale *= -0.01;
    scale+=1;

    glMatrixMode(GL_MODELVIEW);

    /*  AJOUTER DU CODE ICI!
     remplacer la matrice MODELVIEW courante
     par celle du cube ou du cone
     (cubeModelviewMatrix ou coneModelviewMatrix) */
	glLoadMatrixf(SelectedObject == Cube ? cubeModelviewMatrix : coneModelviewMatrix);

    /* AJOUTER DU CODE ICI!
       effectuer les bonnes operations affines. */
    switch(CurrentMode)
    {
        case ModeTranslateX:
        /* Effectuer une translation en X */
        break;

        case ModeTranslateY:
        /* Effectuer une translation en Y */
        break;

        case ModeTranslateZ:
        /* Effectuer une translation en Z */
        break;

        case ModeRotateX:
        /* Effectuer une rotation relative a l'axe X */
        break;

        case ModeRotateY:
        /* Effectuer une rotation relative a l'axe X */
        break;

        case ModeRotateZ:
        /* Effectuer une rotation relative a l'axe Z */
        break;

        case ModeScaleX:
        /* Effectuer un changement d'echelle relatif a l'axe X */
        break;

        case ModeScaleY:
        /* Effectuer un changement d'echelle relatif a l'axe Y */
        break;

        case ModeScaleZ:
        /* Effectuer un changement d'echelle relatif a l'axe Z */
        break;

        case ModeScaleU:
        /* Effectuer un changement d'echelle uniforme */
        break;
        case ModeShearX:
        /* Effectuer un cisaillement relatif a l'axe X */
        break;
        case ModeShearY:
        /* Effectuer un cisaillement relatif a l'axe Y */
        break;
        case ModeShearZ:
        /* Effectuer un cisaillement relatif a l'axe Z */
        break;
    }

    /*AJOUTER DU CODE ICI!
     copier la matrice MODELVIEW courante dans
     le buffer du cube ou du cone
     (cubeModelviewMatrix ou coneModelviewMatrix)  */
	


    glutPostRedisplay();

    LastPosX = x;
    LastPosY = y;
}

/*
    Fonction appelee a chaque fois qu'une touche du clavier est enfoncee
*/
void keyboard( unsigned char key, int x, int y )
{
    GLfloat buf[16];

    switch(key)
    {
        case 'p':/* Afficher la matrice de transformation de l'objet selectionne. */
        case 'P':
        if(SelectedObject == Cube)
        {
            printf("%f %f %f %f\n",cubeModelviewMatrix[0],cubeModelviewMatrix[4],cubeModelviewMatrix[8],cubeModelviewMatrix[12]);
            printf("%f %f %f %f\n",cubeModelviewMatrix[1],cubeModelviewMatrix[5],cubeModelviewMatrix[9],cubeModelviewMatrix[13]);
            printf("%f %f %f %f\n",cubeModelviewMatrix[2],cubeModelviewMatrix[6],cubeModelviewMatrix[10],cubeModelviewMatrix[14]);
            printf("%f %f %f %f\n",cubeModelviewMatrix[3],cubeModelviewMatrix[7],cubeModelviewMatrix[11],cubeModelviewMatrix[15]);
        }
        else
        {
            printf("%f %f %f %f\n",coneModelviewMatrix[0],coneModelviewMatrix[4],coneModelviewMatrix[8],coneModelviewMatrix[12]);
            printf("%f %f %f %f\n",coneModelviewMatrix[1],coneModelviewMatrix[5],coneModelviewMatrix[9],coneModelviewMatrix[13]);
            printf("%f %f %f %f\n",coneModelviewMatrix[2],coneModelviewMatrix[6],coneModelviewMatrix[10],coneModelviewMatrix[14]);
            printf("%f %f %f %f\n",coneModelviewMatrix[3],coneModelviewMatrix[7],coneModelviewMatrix[11],coneModelviewMatrix[15]);
        }
        break;

        case 'q':/* quit*/
        case 'Q':
        exit(0);
        break;
    }

    glutPostRedisplay(); /* appel la fonction 'display'*/
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
	
	/* Variable locale pour la configuration de la fenetre graphique OpenGL */
    int MenuId;

    /* DEBUT: Initialisation standard de la fenetre graphique OpenGL */
    windW = 600;
    windH = 400;
    glutInitWindowPosition(0, 0);
    glutInitWindowSize( windW, windH);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    if (glutCreateWindow("Transform") == GL_FALSE)
        exit(1);

    /* Configuration de la couleur de fond (noir) */
    glClearColor(0.0, 0.0, 0.0, 0.0);

    /* Activer le Z-buffer */
    glDepthFunc( GL_LESS );
    glEnable( GL_DEPTH_TEST );

    /*  Initialiser a zero les transformations de base */
    initTransformations();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Creation d'un menu GLUT */
    MenuId = glutCreateMenu(MenuSelection);
    glutSetMenu( MenuId );
    glutAddMenuEntry( "Move Cube", Cube );
    glutAddMenuEntry( "Move Cone", Cone );
    glutAddMenuEntry( "Translation X", ModeTranslateX );
    glutAddMenuEntry( "Translation Y", ModeTranslateY );
    glutAddMenuEntry( "Translation Z", ModeTranslateZ );
    glutAddMenuEntry( "Rotation X", ModeRotateX );
    glutAddMenuEntry( "Rotation Y", ModeRotateY );
    glutAddMenuEntry( "Rotation Z", ModeRotateZ );
    glutAddMenuEntry( "Changement d'echelle X", ModeScaleX );
    glutAddMenuEntry( "Changement d'echelle Y", ModeScaleY );
    glutAddMenuEntry( "Changement d'echelle Z", ModeScaleZ );
    glutAddMenuEntry( "Changement d'echelle uniforme", ModeScaleU );
    glutAddMenuEntry( "Cisaillement d'echelle X", ModeShearX );
    glutAddMenuEntry( "Cisaillement d'echelle Y", ModeShearY  );
    glutAddMenuEntry( "Cisaillement d'echelle Z", ModeShearZ  );
    glutAddMenuEntry( "Retour a l'origine", ActionReset );
    glutAddMenuEntry( "Quitter", ActionQuit );
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    /* Fonctions de rappel (callback) pour glut */
    glutMouseFunc(MouseButton);     /* Fonctions appelee lorsqu'un bouton de la souris est enfonce */
    glutMotionFunc(MouseMove);      /* Fonctions appelee lorsque la souris bouge et qu'un de ses boutons est enfonce */
    glutReshapeFunc(Reshape);       /* Fonctions appelee lorsque la taille de la fenetre est modifiee */
    glutDisplayFunc(Display);       /* Fonctions appelee lorsque la scene doit etre affichee. */
    glutKeyboardFunc( keyboard );   /* Fonctions appelee lorsqu'une touche du clavier est enfoncee. */
    glutMainLoop();

    return( 0 );
}







