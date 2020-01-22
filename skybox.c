#include <GL/glut.h>
#include "funkcije.h"

// f-ja za iscrtavanje zemlje

void drawSkybox(void){
	int width = 256;
    int height = 256;
    int length = 256; // daljina od centra

    // centar
    int x = 0;
    int y = 0;
    int z = 0;

    // centriramo kocku,
    x = x - width / 2;
    y = y - height / 2;
    z = z - length / 2;

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBegin(GL_QUADS);      
        glTexCoord2f(8.0f, 0.0f); glVertex3f(x, y - 10 + height/2, z);
        glTexCoord2f(8.0f, 8.0f); glVertex3f(x, y - 10 + height/2, z + length);
        glTexCoord2f(0.0f, 8.0f); glVertex3f(x + width, y - 10 + height/2, z + length); 
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y - 10 + height/2, z);
    glEnd();

}

