#include "funkcije.h"

float loptaR = 1.0, loptaG = 0.0, loptaB = 0.0;

/*pravimo objekat lopte, postavljamo*/

void lopta(){
	
	GLfloat ambient_ball[]  = {loptaR * 0.6, loptaG * 0.6, loptaB * 0.6, 1};
	GLfloat diffuse_ball[]  = {loptaR * 0.8, loptaG * 0.8, loptaB * 0.8, 1};
	GLfloat specular_ball[] = {loptaR * 0.9, loptaG * 0.9, loptaB * 0.9, 1};
	GLfloat shininess_ball  = 20;
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_ball);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_ball);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_ball);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess_ball);
	
	
	float lateralZ = 0;
	int deg = 40;
	
	if (lateral_movement == 1) {
		lateralZ = -deg;
	}
	if (lateral_movement == 2) {
		lateralZ = deg;
	}
	
	glPushMatrix();
		glTranslatef(laneCoord, 0.1 + rLopte, 0);
			glRotatef(animation_parameter*90, 1, 0, 0);
			
				glRotatef(lateralZ, 1, 1, 0);
				glutSolidSphere(rLopte, 20, 20);
				glDisable(GL_LIGHTING);
				glColor3f(0, 0, 0);
				glPushMatrix();
					glRotatef(90.0, 0, 1, 0);
    					glutWireSphere(rLopte, 10, 20);
    			glPopMatrix();
    			glEnable(GL_LIGHTING);

	glPopMatrix();
}

void boost(){
	// objekat boost treba da bude crven, intenzitet postavljamo preko materijala
	float boostR = 1.0, boostG = 0.0, boostB = 0.0;
	GLfloat ambient_boost[]  = {boostR * 0.6, boostG * 0.6, boostB * 0.6, 1};
	GLfloat diffuse_boost[]  = {boostR * 0.8, boostG * 0.8, boostB * 0.8, 1};
	GLfloat specular_boost[] = {boostR * 0.9, boostG * 0.9, boostB * 0.9, 1};
	GLfloat shininess_boost  = 20;
	
	// primenjujemo materijal
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_boost);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_boost);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_boost);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess_boost);
    
    //rotiramo 2 puta za 45 stepeni za zeljeni oblik
    glRotatef(45.0, 1, 0, 0);
	glRotatef(45.0, 0, 0, 1);
		glutSolidCube(0.2);
	glRotatef(-45.0, 0, 0, 1);
	glRotatef(-45.0, 1, 0, 0);
}

/* objekat jedne prepreke */
static void prepreka(){

	glTranslatef(0, (wZida+hZida)/2, 0);
		glScalef(wStaza/3, hZida, wZida);
			glutSolidCube(1);
		glScalef(1/(wStaza/3), 1/hZida, 1/wZida);
	glTranslatef(0, -(wZida+hZida)/2, 0);
	
}

/* postavljamo geometriju segmenta staze (bez prepreka) */
static void staza(){
    
    // braon
    float stazaR = 0.545;
    float stazaG = 0.271;
    float stazaB = 0.075;
    
    GLfloat ambient_staza[]  = {stazaR, stazaG, stazaB, 1};
	GLfloat diffuse_staza[]  = {stazaR * 0.1, stazaG * 0.1, stazaB * 0.1, 1};
	GLfloat specular_staza[] = {stazaR * 0.3, stazaG * 0.3, stazaB * 0.3, 1};
	GLfloat shininess_staza  = 0;
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_staza);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_staza);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_staza);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess_staza);
    
    // Donji deo
    
    glScalef(wStaza, wZida, lStaza);
    glutSolidCube(1);
    glScalef(1/wStaza, 1/wZida, 1/lStaza);
    
    // levi i desni zid
    
    float zidR = 0.3;
    float zidG = 0.3;
    float zidB = 0.3;
    
    GLfloat ambient_zid[]  = {0.4, 0.4, 0.4, 1};
	GLfloat diffuse_zid[]  = {zidR * 0.1, zidG * 0.1, zidB * 0.1, 1};
	GLfloat specular_zid[] = {0.2, 0.2, 0.2, 1};
	GLfloat shininess_zid  = 0;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_zid);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_zid);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_zid);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess_zid);
    
    glTranslatef(1+wZida/2, hZida/2-wZida/2, 0);
    glScalef(wZida, hZida, lStaza);
    glutSolidCube(1);
    glScalef(1/wZida, 1/hZida, 1/lStaza);
    glTranslatef(-1-wZida/2, -hZida/2+wZida/2, 0);
    
    glTranslatef(-1-wZida/2, hZida/2-wZida/2, 0);
    glScalef(wZida, hZida, lStaza);
    glutSolidCube(1);
    glScalef(1/wZida, 1/hZida, 1/lStaza);
    glTranslatef(1+wZida/2, -hZida/2+wZida/2, 0);
    
}

/* formiramo jedan segment iz predefinisanih random boja iz boje.c */
void segment(GLfloat* p1Boja, GLfloat* p2Boja, GLfloat* p3Boja){

	staza();
    
    // desna prepreka i boje
    
    GLfloat shininess_prepreke   = 0;
    
	GLfloat ambient_prepreka1[]  = {p1Boja[0], p1Boja[1], p1Boja[2], 1};
	GLfloat diffuse_prepreka1[]  = {p1Boja[0], p1Boja[1], p1Boja[2], 1};
	GLfloat specular_prepreka1[] = {p1Boja[0], p1Boja[1], p1Boja[2], 1};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_prepreka1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_prepreka1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_prepreka1);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess_prepreke);
    
    glTranslatef(wStaza/3, 0, 0);
    prepreka();
    glTranslatef(-wStaza/3, 0, 0);
 	
 	// centralna prepreka i boje
 	
 	GLfloat ambient_prepreka2[]  = {p2Boja[0], p2Boja[1], p2Boja[2], 1};
	GLfloat diffuse_prepreka2[]  = {p2Boja[0], p2Boja[1], p2Boja[2], 1};
	GLfloat specular_prepreka2[] = {p2Boja[0], p2Boja[1], p2Boja[2], 1};
	GLfloat shininess_prepreka2  = 0;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_prepreka2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_prepreka2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_prepreka2);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess_prepreke);
 	
    prepreka();
    
    // leva prepreka i boje
    
    GLfloat ambient_prepreka3[]  = {p3Boja[0], p3Boja[1], p3Boja[2], 1};
	GLfloat diffuse_prepreka3[]  = {p3Boja[0], p3Boja[1], p3Boja[2], 1};
	GLfloat specular_prepreka3[] = {p3Boja[0], p3Boja[1], p3Boja[2], 1};
	GLfloat shininess_prepreka3  = 0;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_prepreka3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_prepreka3);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_prepreka3);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess_prepreke);
    
    glTranslatef(-wStaza/3, 0, 0);
    prepreka();
    glTranslatef(wStaza/3, 0, 0);
 	
}
