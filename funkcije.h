#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

static float rLopte = 0.15;
static float wZida = 0.1;
static float hZida = 0.5;
static float lStaza = 6.0;
static float wStaza = 2.0;
static int brStaza = 8;
static float laneOffset = 3.5;
static int boost_spawn_chance = 4;
static float boost_spawn_position = 0.75;
static float jumpTranslateAmount = 0;
static float jumpTranslateIncrement = 0.005;

static int brBoja = 8; // 8 max
extern GLfloat bojeRgb[3][3];
extern GLfloat bojeOstalo[8][3];
extern int *boost_position;
extern int running, running2;
extern int boost_colected;

extern GLuint texture[];

extern float laneCoord;
extern int lane;
extern int ballSpeed;
float movement_duration; // duzina animacije pokreta

int lateral_movement;
float movement_parameter;

float move_amount;

extern int scoreMulti, noObstacles, score;;

extern float loptaR, loptaG, loptaB;

typedef struct{
	GLfloat pBoja[3][3];
} boje;

boje *listaBoja;

static float pi = 3.141592653589793;

float animation_parameter;
float animation_parameter2;

extern void on_keyboard(unsigned char key, int x, int y);
extern void lopta();
extern void boost();
extern void pocetni_boost();
extern void spawn_boost();
extern void segment(GLfloat* p1Boja, GLfloat* p2Boja, GLfloat* p3Boja);
extern void pocetneBoje();
extern void shift();
extern void on_timer(int value);
extern void drawSkybox(void);

extern void moveLeft();
extern void moveRight();






