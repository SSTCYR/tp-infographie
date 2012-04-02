/* IMN428 - Infographie 
 
 TP4: courbes parametriques
 
 Nom1:
 Nom2:
 Nom3:
 
*/

#define GLUT_DISABLE_ATEXIT_HACK

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>

using std::vector;

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <windows.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include "Glut/GLUT.h"
#endif

typedef struct{
	double x;	
	double y;
} vect2D;

#define UNSURSIX 0.1666666

/* Variables globales qui contiennent la dimension de la fenetres */
GLint windowWidth=500;
GLint windowHeight=500;

/* Constante/variables globale(s) concernant les points de controle */
#define NB_MAX_POINTS 1000
int nbControlPoints;
vect2D ControlPointArray[NB_MAX_POINTS];
int indexSelectedPoint=-1;

/*  commandes dans le menu */
enum
{
	Lines,
	Bezier,
	BSpline,
	Reset,
	Quit
};
int selectedCurve = Lines;

/* Etat de la souris */
int LeftButtonIsPressed = GL_FALSE;   /* Bouton gauche enfonce? */
int MiddleButtonIsPressed = GL_FALSE;   /* Bouton gauche enfonce? */
int RightButtonIsPressed = GL_FALSE;   /* Bouton gauche enfonce? */
int LastPosX, LastPosY;               /* Derniere position de souris */

/* nombre de segments de droite le long d'un parametre */
int curvePrecision = 0;

/* parametre K pour les b-splines */
int paramK = 3;

/*
 fonction qui multiplie un vecteur par un scalaire
 */
vect2D multScalaireVect(double scalaire, vect2D vec)
{
	vect2D pt;
	
	pt.x = scalaire * vec.x;
	pt.y = scalaire * vec.y;
	
	return pt;
}

/*
 fonction qui additionne deux vecteurs
 */
vect2D addVect(vect2D vec1, vect2D vec2)
{
	vect2D pt;
	
	pt.x = vec1.x + vec2.x;
	pt.y = vec1.y + vec2.y;
	
	return pt;
}

/*
 fonction qui soustrait deux vecteurs
 */
vect2D subVect(vect2D vec1, vect2D vec2)
{
	vect2D pt;
	
	pt.x = vec1.x - vec2.x;
	pt.y = vec1.y - vec2.y;
	
	return pt;
}

/*
 fonction qui normalise un vecteur
 */
vect2D normalizeVect(vect2D vec)
{
	vect2D pt;
	double length;
	
	length = sqrt(pow(vec.x,2.0)+pow(vec.y,2.0));
	pt.x = vec.x/length;
	pt.y = vec.y/length;
	
	return pt;
}

/*
 fonction qui calcule la distance euclidienne entre deux points
 */
double euclideanDistance(vect2D p1, vect2D p2)
{
	double dist;
	
	dist = pow(p1.x-p2.x,2.0) + pow(p1.y-p2.y,2.0);
	
	return sqrt(dist);
}

/* 
 fonction qui initialise les variables globales 
 */
void init(void)
{	
	nbControlPoints=0;
}

/*
 Fonction de selection d'un item dans le menu (standard glut)
 */
void menuSelection(int value)
{
	if( value == Reset )
	{
		init();
		glutPostRedisplay();
	}else if ( value == Quit )
		exit(0);
	else
		selectedCurve = value;
	glutPostRedisplay();
}

/*
 Fonction de redimensionnement de la fenetre
 */
void reshape(int width, int height)
{
	windowWidth=width;
	windowHeight=height;
}


void drawControlPoints()
{
	
	/* AJOUTER DU CODE ICI */
	// Couleur : vert
	// Taille : 4
	glColor3f(0.0, 1.0, 0.0);
	glPointSize(4.0);
	glBegin(GL_POINTS);
		for(int i = 0; i < nbControlPoints; i++)
		{
			glVertex2d(ControlPointArray[i].x, ControlPointArray[i].y);
		}
	glEnd();

}

void drawLines()
{
	// Caractéristiques visuelles de la ligne
	glLineWidth(1.5);
	glColor4f(1.0,0,0,1);
	
	/* AJOUTER DU CODE ICI */
	glBegin(GL_LINES);
		for(int i = 0; i < nbControlPoints - 1; i++)
		{
			glVertex2d(ControlPointArray[i].x, ControlPointArray[i].y);
			glVertex2d(ControlPointArray[i+1].x, ControlPointArray[i+1].y);
		}
	glEnd();
}

vect2D drawBezierCurvesImpl(vect2D points[], int nbPts, double precision)
{
	if(nbPts <= 1)
		return points[0];
	
	vect2D *newPts = new vect2D[--nbPts];
	for(int i = 0; i < nbPts; i++)
	{
		vect2D d = subVect(points[i+1], points[i]);
		vect2D v = multScalaireVect(precision, d);
		vect2D f = addVect(points[i], v);
		newPts[i] = f;
	}
	vect2D pt = drawBezierCurvesImpl(newPts, nbPts, precision);
	delete newPts;
	return pt;
}

void drawBezierCurves()
{
	// Caractéristiques visuelles de la ligne
	glLineWidth(1.5);
	glColor4f(1.0,0,0,1);

	/* AJOUTER DU CODE ICI */
	
	if(curvePrecision == 0)
		return;

	vector<vect2D> bezierPts;

	for(double i = 0; i <= 1; i += (double)1/curvePrecision)
	{
		bezierPts.push_back(drawBezierCurvesImpl(ControlPointArray, nbControlPoints, i));
	}

	glBegin(GL_LINES);
		for(int i = 0; i < bezierPts.size() - 1; i++)
		{
			glVertex2d(bezierPts[i].x, bezierPts[i].y);
			glVertex2d(bezierPts[i+1].x, bezierPts[i+1].y);
		}
	glEnd();
}

void drawBSplineCurves()
{
	// Caractéristiques visuelles de la ligne
	glLineWidth(1.5);
	glColor4f(1.0,0,0,1);
	
	/* AJOUTER DU CODE ICI */
	if(nbControlPoints < paramK || curvePrecision < 1)
		return;

	//int u = nbControlPoints + 1 - paramK;
	vector<vect2D> nodes;
	if(paramK == 3)
	{
		for(int i = 0; i < nbControlPoints - 2; i++)
		{
			for(double j = 0; j <= 1; j += (double)1/curvePrecision)
			{
				vect2D p1 = multScalaireVect(pow(1-j,2.0),ControlPointArray[i]);
				vect2D p2 = multScalaireVect(-2*pow(j,2.0)+2*j+1,ControlPointArray[i+1]);
				vect2D p3 = multScalaireVect(pow(j,2.0), ControlPointArray[i+2]);

				nodes.push_back(multScalaireVect(0.5, addVect(addVect(p1, p2),p3)));
			}
		}
	}
	else
	{
		for(int i = 1; i < nbControlPoints - 2; i++)
		{
			for(double j = 0; j <= 1; j += (double)1/curvePrecision)
			{
				vect2D p1 = multScalaireVect(-pow(j,3.0) + 3*pow(j,2.0)-3*j+1, ControlPointArray[i-1]);
				vect2D p2 = multScalaireVect(3*pow(j,3.0)-6*pow(j,2.0)+4, ControlPointArray[i]);
				vect2D p3 = multScalaireVect(-3*pow(j,3.0) + 3*pow(j,2.0)+3*j+1, ControlPointArray[i+1]);
				vect2D p4 = multScalaireVect(pow(j,3.0), ControlPointArray[i+2]);

				nodes.push_back(multScalaireVect((double)1/6, addVect(addVect(p1,p2), addVect(p3,p4))));
			}
		}
	}
	

	glBegin(GL_LINES);
		for(int i = 0; i < nodes.size() - 1; i++)
		{
			glVertex2d(nodes[i].x, nodes[i].y);
			glVertex2d(nodes[i+1].x, nodes[i+1].y);
		}
	glEnd();
}

/*
 affichage de la courbe
 */
void display(void)
{
	int i;
	char buf[40];
	
	/* Configurer le "viewport" OpenGL. */
	glViewport(0, 0, windowWidth, windowHeight);
	
	/* Configurer une camera (projection perspective) */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-windowWidth/2.0,windowWidth/2.0,-windowHeight/2.0,windowHeight/2.0);
	
	/* Selectionner la pile de transformations attachee au modele (MODELVIEW) */
	glMatrixMode(GL_MODELVIEW);
	
	/* Effacer l'ecran */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();

	drawControlPoints();
	
	switch(selectedCurve){
			
		case Lines:
			drawLines();
			break;
			
		case Bezier:
			drawBezierCurves();
			break;
			
		case BSpline:
			drawBSplineCurves();
			break;
	}
	
	glPushAttrib( GL_ALL_ATTRIB_BITS );
	
	sprintf(buf,"   Precision %d",curvePrecision);
	for (i = 0; i < (int) strlen(buf); i++) 
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buf[i]);
	
	sprintf(buf,"   K = %d",paramK);
	for (i = 0; i < (int) strlen(buf); i++) 
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buf[i]);
	
	glPopAttrib();
	
	glutSwapBuffers();
}


/*
 Fonction de rappel: un bouton de la souris a ete appuye
 */
void mouseButton( int button, int state, int x, int y )
{
	/* Enregistrer le point de controle (x,y) */
	if(nbControlPoints<NB_MAX_POINTS && state==GLUT_DOWN)
	{
		ControlPointArray[nbControlPoints].x=x-windowWidth/2.0;
		ControlPointArray[nbControlPoints].y=windowHeight-y-windowHeight/2.0;
		nbControlPoints++;
	}
	glutPostRedisplay();
}

/*
 fonction qui permet de reagir aux entrees de touches au clavier
 */
void keyboard(unsigned char key, int x, int y)
{
	
	switch(key){
			
		case 'p':
			curvePrecision--;
			if(curvePrecision<0)
				curvePrecision=0;
			break;
		case 'P':
			curvePrecision++;
			break;
		
		case 'k':
			if(paramK==3)
				paramK=4;
			else
				paramK=3;
			break;
			
		case 'q':
			exit(0);
			break;
			
	}
	glutPostRedisplay();
	
}

int main(int argc, char* argv[])
{
    /* Variable locale pour la configuration de la fenetre graphique OpenGL */
    int MenuId;
	glutInit(&argc,argv);
	
	init();
    glutInitWindowPosition(0, 0);
    glutInitWindowSize( windowWidth, windowHeight);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("IMN428 -- TP4");
	
    /* Configuration de la couleur de fond (noir) */
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glDepthFunc( GL_LESS );
    glEnable( GL_DEPTH_TEST );
	
	/* Creation du menu */
    MenuId = glutCreateMenu(menuSelection);
    glutSetMenu( MenuId );
    glutAddMenuEntry( "Lignes", Lines );
    glutAddMenuEntry( "Bezier", Bezier );
	glutAddMenuEntry( "B-Spline", BSpline);
    glutAddMenuEntry( "Reset", Reset );
    glutAddMenuEntry( "Quitter", Quit );
    glutAttachMenu(GLUT_RIGHT_BUTTON);
	
    /* Fonctions de rappel (callback) de glut  */
    glutMouseFunc(mouseButton);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
	
	glutMainLoop();
	
    return( 0 );
}
