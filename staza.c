#include "funkcije.h"

static void on_display(void);
static void on_reshape(int width, int height);
static void jump(void);
static void output(char *string);

GLuint LoadTexture(const char * filename, int width, int height);

void light_init(void);
void on_timer(int value);

float animation_parameter, animation_parameter2;
float laneCoord;
int lane;
int running, running2;
int ballSpeed;
int scoreMulti, noObstacles;
int score;
int boost_colected;
int window_h = 800, window_w = 1200;

float originalLaneCoord;

void initGL(int argc, char **argv){
	glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(window_w, window_h);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Color Runner");

	glClearColor(0.0, 0.0, 0.0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

GLuint texture[6];

int main(int argc, char **argv){
    
	initGL(argc, argv);
	
	// ucitavamo teksture skybox-a
    texture[0] = LoadTexture("skyb/down.dib", 512, 512);
	
    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);
    
    laneCoord = 0;
    originalLaneCoord = laneCoord;
    lane = 1; // pocinjemo u srednjem lane-u
	animation_parameter = 0;
	animation_parameter2 = 0;
	movement_parameter = 0;
    
    srand(time(NULL)); // seed za sve rand() pozive 
    listaBoja = malloc(sizeof(boje) * brStaza);
    pocetneBoje();
    pocetni_boost();
    boost_colected = 0;
        
    running = 1;
    score = 0;
    ballSpeed = 15;
    scoreMulti = 1;
    noObstacles = 0;
    glutTimerFunc(ballSpeed, on_timer, 0);
    lateral_movement = 0;
       
    glutMainLoop();
    return 0;
}

static void on_reshape(int width, int height){
	
	if(height == 0){
		height = 1;
	}
	
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
	glViewport(0, 0, width, height);

    gluPerspective(60.0, (float)width/height, 1.0, 1500.0);
    glMatrixMode(GL_MODELVIEW);
}

// funkcija za ucitavanje tekstura
GLuint LoadTexture(const char * filename, int width, int height){

    GLuint texture;
    unsigned char * data;
    FILE * file;

    // otvaramo lokaciju slike
    file = fopen(filename, "rb");
    if(file == NULL){
        return 0;
    }

    // alociramo memoriju i citamo
    data = (unsigned char *)malloc(width * height * 3);
    fread(data, width * height * 3, 1, file);

    // zatvaramo fajl
    fclose(file);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexParameterf(GL_TEXTURE_2D,
    				GL_TEXTURE_MIN_FILTER, 
    				GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,
    				GL_TEXTURE_MAG_FILTER, 
    				GL_LINEAR_MIPMAP_LINEAR);

    glTexParameterf(GL_TEXTURE_2D,
    				GL_TEXTURE_WRAP_S, 
    				GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, 
    				GL_TEXTURE_WRAP_T, 
    				GL_CLAMP_TO_EDGE);

    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height,
    				  GL_RGB, GL_UNSIGNED_BYTE, data);    
    free(data);

    return texture;     
}

void light_init(void){
	
	GLfloat light_position[] = { 0, 5, 0, 0};

	GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1 };
	GLfloat light_diffuse[] = { 0.9, 0.9, 0.9, 1 };
	GLfloat light_specular[] = { 0.1, 0.1, 0.1, 1 };
	
	// ukljucuje se osvjetljenje i podesavaju parametri svetla
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

static void on_display(void){
	// iscrtavanje 
    
    int i;
    int rBoostLane  = rand() % 3;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//svetlo
    light_init();
    
    //kamera
    glLoadIdentity();
    gluLookAt(0.0, 1.7, -2.5,
    		  0.0, 0.0, 0.0,
    		  0.0, 1.0, 0.0);
    //lopta
	lopta();
    
    //skidamo prvi i dodajemo poslednji segment
    if(animation_parameter == 0){
    	shift();
    }
    
    // iscrtavamo segmente i boostove
    // animation_parameter2 animira skok, a animation_parameter pomeranje lopte
    glTranslatef(0, -sin(animation_parameter2), -animation_parameter);
		for(i=0; i<brStaza; i++){
		    segment(listaBoja[i].pBoja[0], listaBoja[i].pBoja[1], listaBoja[i].pBoja[2]);
		    glTranslatef(0, 0, lStaza);
		    spawn_boost(boost_position[i]);
		}   
    glTranslatef(0, sin(animation_parameter2), animation_parameter);
    
    // pretvaranje score-a u string i ispisivanje
    char str_score[256];
    char str_score2[] = "Score: ";
    sprintf(str_score, "%d", score);
    strcat(str_score2, str_score);
    
    
    glDisable(GL_LIGHTING);
		output(str_score2);
    glEnable(GL_LIGHTING);
    
    
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
		drawSkybox(); // iscrtavamo skybox,
    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    
    glutSwapBuffers();     
}

void output(char *string) {

	//funkcija iscrtava string score u gornjem levom uglu ekrana

	glColor3f( 1.0, 1.0, 1.0 );
	glMatrixMode( GL_PROJECTION );
	
	glPushMatrix();
		glLoadIdentity();
		gluOrtho2D( 0, window_w, 0, window_h );
		glMatrixMode( GL_MODELVIEW );
		
		glPushMatrix();
			glLoadIdentity();
			glRasterPos2i( 10, window_h-10-24 ); // wh - offset - fontsize
			int len = (int)strlen(string);
			for ( int i = 0; i<len; ++i ) {
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
			}
		glPopMatrix();

		glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	
	glMatrixMode( GL_MODELVIEW );

}

void on_timer(int value){
	float movement_duration = 4.0; // duzina animacije pokreta

	// timer koji kontrolise kretanje svih elemenata scene
    if(value == 0){  
		if(running && animation_parameter <= lStaza){
			animation_parameter += 0.05;
			glutPostRedisplay();
			glutTimerFunc(ballSpeed, on_timer, 0);
		}
			
		if (animation_parameter >= lStaza){
			animation_parameter = 0;
			running = 1;
		}
		
		// provera da li je aktivno pomeranje
		if (lateral_movement) {
			float move_amount = 
				(wStaza/laneOffset)*(ballSpeed/100.0) / 
				movement_duration;
			movement_parameter += move_amount;
			
			// ako je gotovo resetujemo
			if (movement_parameter > wStaza/laneOffset) {
				movement_parameter = 0;

				if (lateral_movement == 1)  { // desno
					lane += 1;
					originalLaneCoord = laneCoord;
				} else if (lateral_movement == 2) { // ili levo
					lane -= 1;
					originalLaneCoord = laneCoord;
				}
								
				lateral_movement = 0;
			// inace se malo pomeramo
			} else if (lateral_movement == 1)  { // desno
				laneCoord = originalLaneCoord - movement_parameter;
				
			} else if (lateral_movement == 2) { // ili levo
				laneCoord = originalLaneCoord + movement_parameter;
			}

		}

		/* 
		ako nije iste boje kao prepreka zavrsavamo igru, 
			prekidamo animaciju i ispisijemo score
		*/
		
		// Zaokruzujemo AP na 2 decimalna mesta
		if(roundf(animation_parameter*100)/100 == 5.75) {
			// ako nismo pokupili boost u ovom segmentu
			if(!running2){
				// hit detection
				if(	loptaR != listaBoja[1].pBoja[lane][0] 
					|| loptaG != listaBoja[1].pBoja[lane][1] 
					|| loptaB != listaBoja[1].pBoja[lane][2]
				){
					// kraj igre
					running = 0;
				} else {
					/* racunamo score i ubrzavamo animacju */
					score = score + scoreMulti;
					noObstacles++;
					//printf("%d, %d\n", noObstacles, score);
					if(noObstacles > 4 && noObstacles%5 == 0 && ballSpeed != 1){
						ballSpeed -= 1;
						scoreMulti += 1;
						//printf("Speedup\n");
					}
				}	
			} else {
				/* racunamo score i ubrzavamo animacju */
				score = score + scoreMulti;
				noObstacles++;
				//printf("%d, %d\n", noObstacles, score);
				if(noObstacles > 4 && noObstacles%5 == 0 && ballSpeed != 1){
					ballSpeed -= 1;
					scoreMulti += 1;
					//printf("Speedup\n");
				}
			}
		}
		
		// resetujemo mogucnost sakupljanja boost-a
		if(animation_parameter == 0){
			boost_colected = 0;
		}
		// detektujemo sakupljanje boosta preko pozicije
		// ako postoji boost u ovom segmentu
		if(boost_position[0] != -1){
			// ako smo na z-duzini boosta, u ispravnom lain-u i nismo taj
			// isti boost vec pokupili
			if(animation_parameter >= lStaza*boost_spawn_position - rLopte	
				&& animation_parameter <= lStaza*boost_spawn_position + rLopte	
				&& lane == boost_position[0]
				&& !boost_colected
			){
				boost_position[0] = -1; // sklanjanje boosta sa ekrana
				boost_colected = 1; // sprecava dalje detekcije u range-u
				jump(); // f-ja za skok
			}
		}
	} else if(value == 1){ // tajmer za skok, sin(0-pi)
	
		if(running2 && animation_parameter2 <= pi){
			animation_parameter2 += 0.05;
			glutPostRedisplay();
			glutTimerFunc(ballSpeed, on_timer, 1);
		}
			
		if (animation_parameter2 >= pi){
			animation_parameter2 = 0;
			running2 = 0;
		}
		
	} else {
		return;
	}
}

void jump(){
	// funkcija za skok, poziva novi tajmer (1)
	running2 = 1;
	glutTimerFunc(ballSpeed, on_timer, 1);
}

void moveRight() {
	if(lane != 2 && !lateral_movement) {
		originalLaneCoord = laneCoord;
		lateral_movement = 1;
    }
}

void moveLeft() {
	if(lane != 0 && !lateral_movement) {
		originalLaneCoord = laneCoord;
		lateral_movement = 2;
    }
}




