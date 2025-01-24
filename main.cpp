
#include <windows.h>
#include <cmath>
#include <GL/gl.h>
#include <GL/glut.h>
#include<iostream>;

const float PI = 3.14159265358979323846;
void drawHollowCircle(float centerX, float centerY, float radius, int segments) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * PI * i / segments; // Angle for each segment
        float x = radius * cosf(theta);        // X-coordinate
        float y = radius * sinf(theta);        // Y-coordinate
        glVertex2f(centerX + x, centerY + y); // Add vertex on the circle
    }
    glEnd();
}
void drawRightHollowSemiCircle(float centerX, float centerY, float radius, float angle, int segments) {
    glPushMatrix();
    glTranslatef(centerX, centerY, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= segments; i++) {
        float theta = (-PI / 2.0f) + (PI * i / segments); // Angle from -PI/2 to +PI/2
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();

    glPopMatrix();
}
void drawTiltedUpperHollowEllipse(float centerX, float centerY, float radiusX, float radiusY, float angle, int segments) {
    glPushMatrix();
    glTranslatef(centerX, centerY, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= segments / 2; i++) {
        float theta = PI * i / (segments / 2);
        float x = radiusX * cosf(theta);
        float y = radiusY * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
}
void drawTiltedHollowEllipse(float centerX, float centerY, float radiusX, float radiusY, float angle, int segments) {
    glPushMatrix();
    glTranslatef(centerX, centerY, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * PI * i / segments;
        float x = radiusX * cosf(theta);
        float y = radiusY * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
}
void drawTiltedFilledEllipse(float centerX, float centerY, float radiusX, float radiusY, float angle, int segments) {
    glPushMatrix();
    glTranslatef(centerX, centerY, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * PI * i / segments;
        float x = radiusX * cosf(theta);
        float y = radiusY * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
}
void drawFilledCircle(float x, float y, float radius, int segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float angle = 2.0f * PI * i / segments;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}
void drawFilledEllipse(float centerX, float centerY, float a, float b) {
    const int segments = 200;
    const float step = 2 * M_PI / segments;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY);
    for (float theta = 0.0f; theta <= 2 * M_PI; theta += step) {
        float x = centerX + a * cos(theta);
        float y = centerY + b * sin(theta);
        glVertex2f(x, y);
    }
    glVertex2f(centerX + a * cos(0.0f), centerY + b * sin(0.0f));
    glEnd();
}
void drawHollowEllipse(float centerX, float centerY, float a, float b, int segments) {
    const float step = 2 * M_PI / segments;
    glBegin(GL_LINE_LOOP);
    for (float theta = 0.0f; theta < 2 * M_PI; theta += step) {
        float x = centerX + a * cos(theta);
        float y = centerY + b * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}
void drawLowerHollowTiltedEllipse(float centerX, float centerY, float radiusX, float radiusY, float angle, int segments) {
    glPushMatrix();
    glTranslatef(centerX, centerY, 0.0f); // Move to the center
    glRotatef(angle, 0.0f, 0.0f, 1.0f);  // Apply tilt

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= segments; i++) {
        float theta = PI + (PI * i / segments); // Angles from PI to 2PI (lower half)
        float x = radiusX * cosf(theta);       // X-coordinate
        float y = radiusY * sinf(theta);       // Y-coordinate
        glVertex2f(x, y);
    }
    glEnd();

    glPopMatrix();

}
void drawTiltedHollowSemiCircle(float centerX, float centerY, float radius, float tiltAngle, int isUpper) {
    glPushMatrix();
    glTranslatef(centerX, centerY, 0.0f);
    glRotatef(tiltAngle, 0.0f, 0.0f, 1.0f);
    glBegin(GL_LINE_STRIP);

    if (isUpper) {
        for (int i = 0; i <= 180; i++) {
            float theta = i * 3.14159f / 180.0f; // Convert degrees to radians
            float x = radius * cosf(theta);
            float y = radius * sinf(theta);
            glVertex2f(x, y);
        }
    } else {

        for (int i = 180; i <= 360; i++) {
            float theta = i * 3.14159f / 180.0f; // Convert degrees to radians
            float x = radius * cosf(theta);
            float y = radius * sinf(theta);
            glVertex2f(x, y);
        }
    }

    glEnd();
    glPopMatrix();
}
float randomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}


// Enum to track current scene
enum Scene {
    MOUNTAIN_SCENE,
    RIVER_SCENE,
    CITY_SCENE
};

// Current active scene
Scene currentScene = MOUNTAIN_SCENE;

// Function prototypes for each scene's display and initialization
void initMountainScene();
void displayMountainScene();
void initRiverScene();
void displayRiverScene();
void initCityScene();
void displayCityScene();

// Common display function to switch between scenes
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    switch(currentScene) {
        case MOUNTAIN_SCENE:
            displayMountainScene();
            break;
        case RIVER_SCENE:
            displayRiverScene();
            break;
        case CITY_SCENE:
            displayCityScene();
            break;
    }

    glutSwapBuffers();
}

// Keyboard function to switch scenes
void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case '1':
            currentScene = MOUNTAIN_SCENE;
            glutPostRedisplay();
            break;
        case '2':
            currentScene = RIVER_SCENE;
            glutPostRedisplay();
            break;
        case '3':
            currentScene = CITY_SCENE;
            glutPostRedisplay();
            break;
        case 27:  // ESC key
            exit(0);
    }
}

// Reshape function to handle window resizing
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 30, 0, 15);
    glMatrixMode(GL_MODELVIEW);
      glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
}
void path() {
glBegin(GL_POLYGON);
glColor3f(0.953, 0.973, 0.796); // Light yellow

// Adjusting y-coordinates by -0.27 to move the path down
glVertex2f(0, 3 );
glVertex2f(2.9250602877645, 2.8330532768222);
glVertex2f(4.8119528655895, 3.0656838686088);
glVertex2f(7.3191936881789, 3.039836025077);
glVertex2f(7.3191936881789, 3.039836025077);
glVertex2f(12.049, 2.911 - 0.27);
glVertex2f(14.686, 2.885 - 0.27);
glVertex2f(16.547, 3.092 - 0.27);
glVertex2f(18.4932652432189, 2.7162342411408 - 0.27);
glVertex2f(21.1278714208712, 2.6179738708787 - 0.27);
glVertex2f(23.3244942806265, 2.6637754859671 - 0.27);
glVertex2f(25.4497432639327, 2.8272561769907 - 0.27);
glVertex2f(26.705, 3.428 - 0.27);
glVertex2f(28.230, 3.143 - 0.27);
glVertex2f(29.961, 3.416 - 0.27);
glVertex2f(30, 2 - 0.27);
glVertex2f(27.44, 1.865 - 0.27);
glVertex2f(25.244, 2.054 - 0.27);
glVertex2f(23.143, 1.818 - 0.27);
glVertex2f(20.594, 1.983 - 0.27);
glVertex2f(18, 2 - 0.27);
glVertex2f(15.070, 1.865 - 0.27);
glVertex2f(12, 2 - 0.27);
glVertex2f(9.428, 1.983 - 0.27);
glVertex2f(6.407, 2.054 - 0.27);
glVertex2f(3.102, 1.865 - 0.27);
glVertex2f(0, 2 - 0.27);

glEnd();
}



void path_down_ground()
{
  glBegin(GL_POLYGON);
glColor3f(0.451f, 0.863f, 0.447f);

glVertex2f(30, 2);
glVertex2f(27.44, 1.865);
glVertex2f(25.244, 2.054);
glVertex2f(23.143, 1.818);
glVertex2f(20.594, 1.983);
glVertex2f(18, 2);
glVertex2f(15.070, 1.865);
glVertex2f(12, 2);
glVertex2f(9.428, 1.983);
glVertex2f(6.407, 2.054);
glVertex2f(3.102, 1.865);
glVertex2f(0, 2);
glVertex2f(0,0);
  glVertex2f(30, 0);



glEnd();

}

void house() {

glLineWidth(1.0f);
// roof
glBegin(GL_POLYGON);
glColor3f(0.992f, 0.224f, 0.231f); // Steel blue
glVertex2f(19.9954352043112, 6.7002585126804);
glVertex2f(22.7200571286011, 6.7076363257484);
glVertex2f(21.5, 5.5);
glVertex2f(19, 5.5);

glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(19.9954352043112, 6.7002585126804);
glVertex2f(22.7200571286011, 6.7076363257484);
glVertex2f(21.5, 5.5);
glVertex2f(19, 5.5);
glEnd();


   // chimni front
glBegin(GL_POLYGON);
glColor3f(0.0, 0.5, 0.7); // Steel blue
glVertex2f(20.4, 7.2);
glVertex2f(21, 7.2);
glVertex2f(21, 6);
glVertex2f(20.4, 6);

glEnd();


    // Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(20.4, 7.2);
glVertex2f(21, 7.2);
glVertex2f(21, 6);
glVertex2f(20.4, 6);
glEnd();

    // chimni back
glBegin(GL_POLYGON);
glColor3f (0.647f, 0.812f, 0.855f); // Steel blue
glVertex2f(21, 7.2);
glVertex2f(21.2, 7.2);
glVertex2f(21.2, 6.4);
glVertex2f(21, 6);

glEnd();

        // Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
 glVertex2f(21, 7.2);
glVertex2f(21.2, 7.2);
glVertex2f(21.2, 6.4);
glVertex2f(21, 6);
glEnd();




   // chimni top front
glBegin(GL_POLYGON);
glColor3f(0.969f, 0.965f, 0.831f);

glVertex2f(20.4, 7.4);
glVertex2f(21, 7.4);
glVertex2f(21, 7.2);
glVertex2f(20.4, 7.2);

glEnd();

        // Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
  glVertex2f(20.4, 7.4);
glVertex2f(21, 7.4);
glVertex2f(21, 7.2);
glVertex2f(20.4, 7.2);
glEnd();




    // chimni top back
glBegin(GL_POLYGON);
glColor3f(0.169f, 0.529f, 0.635f);

glVertex2f(21, 7.4);
glVertex2f(21.2, 7.4);
glVertex2f(21.2, 7.2);
glVertex2f(21, 7.2);

glEnd();

        // Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
   glVertex2f(21, 7.4);
glVertex2f(21.2, 7.4);
glVertex2f(21.2, 7.2);
glVertex2f(21, 7.2);
glEnd();




    //house front
glBegin(GL_POLYGON);
glColor3f(0.267f, 0.592f, 0.749f);

glVertex2f(21.5, 5.5);
glVertex2f(22.7200571286011, 6.7076363257484);
glVertex2f(24, 5.5);
glVertex2f(24.001, 3.12);
 glVertex2f(21.5, 3.1);

glEnd();

        // Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
 glVertex2f(21.5, 5.5);
glVertex2f(22.7200571286011, 6.7076363257484);
glVertex2f(24, 5.5);
glVertex2f(24.001, 3.12);
 glVertex2f(21.5, 3.1);
glEnd();


      //house front top corner
glBegin(GL_POLYGON);
glColor3f(0.161f, 0.157f, 0.404f);

glVertex2f(22.7200571286011, 6.7076363257484);
glVertex2f(24, 5.5);
glVertex2f(24, 5.2);
glVertex2f(22.6, 6.6);
glEnd();

        // Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(22.7200571286011, 6.7076363257484);
glVertex2f(24, 5.5);
glVertex2f(24, 5.2);
glVertex2f(22.6, 6.6);
glEnd();
    //house front downpart
glBegin(GL_POLYGON);
glColor3f(0.161f, 0.157f, 0.404f);
glVertex2f(21.4865306841878, 3.3985742055293);
glVertex2f(24, 3.4);
glVertex2f(24.001, 3.12);
glVertex2f(21.5, 3.1);


glEnd();


glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(21.4865306841878, 3.3985742055293);
glVertex2f(24, 3.4);
glVertex2f(24.001, 3.12);
glVertex2f(21.5, 3.1);
glEnd();

    //house front top window
glBegin(GL_POLYGON);
glColor3f(0.576f, 0.776f, 0.839f);

glVertex2f(22.6, 6);
glVertex2f(23, 6);
glVertex2f(23, 5.6);
glVertex2f(22.6, 5.6);


glEnd();



    glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color

glVertex2f(22.6, 6);
glVertex2f(23, 6);
glVertex2f(23, 5.6);
glVertex2f(22.6, 5.6);

glEnd();

// house front down 2nd window 1st block with black border
glBegin(GL_POLYGON);
glColor3f(0.373f, 0.694f, 0.847f);  // Window color
glVertex2f(23, 4.8);
glVertex2f(23.2, 4.8);
glVertex2f(23.2, 4.3);
glVertex2f(23, 4.3);
glEnd();


// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(23, 4.8);
glVertex2f(23.2, 4.8);
glVertex2f(23.2, 4.3);
glVertex2f(23, 4.3);
glEnd();


// house front down 2nd window 2nd block with black border
glBegin(GL_POLYGON);
glColor3f(0.373f, 0.694f, 0.847f);  // Window color
glVertex2f(23.2, 4.8);
glVertex2f(23.4, 4.8);
glVertex2f(23.4, 4.3);
glVertex2f(23.2, 4.3);
glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(23.2, 4.8);
glVertex2f(23.4, 4.8);
glVertex2f(23.4, 4.3);
glVertex2f(23.2, 4.3);
glEnd();


// house front down 2nd window 3rd block with black border
glBegin(GL_POLYGON);
glColor3f(0.373f, 0.694f, 0.847f);  // Window color
glVertex2f(23.2, 4.3);
glVertex2f(23.4, 4.3);
glVertex2f(23.4, 3.8);
glVertex2f(23.2, 3.8);
glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(23.2, 4.3);
glVertex2f(23.4, 4.3);
glVertex2f(23.4, 3.8);
glVertex2f(23.2, 3.8);
glEnd();


// house front down 2nd window 4th block with black border
glBegin(GL_POLYGON);
glColor3f(0.373f, 0.694f, 0.847f);  // Window color
glVertex2f(23, 4.3);
glVertex2f(23.2, 4.3);
glVertex2f(23.2, 3.8);
glVertex2f(23, 3.8);
glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(23, 4.3);
glVertex2f(23.2, 4.3);
glVertex2f(23.2, 3.8);
glVertex2f(23, 3.8);
glEnd();


// house front down 1st window 1st h block with black border
glBegin(GL_POLYGON);
glColor3f(0.373f, 0.694f, 0.847f);  // Window color
glVertex2f(22, 4.8);
glVertex2f(22.2, 4.8);
glVertex2f(22.2, 4.3);
glVertex2f(22, 4.3);
glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(22, 4.8);
glVertex2f(22.2, 4.8);
glVertex2f(22.2, 4.3);
glVertex2f(22, 4.3);
glEnd();


// house front down 1st window 2nd h block with black border
glBegin(GL_POLYGON);
glColor3f(0.373f, 0.694f, 0.847f);  // Window color
glVertex2f(22.2, 4.8);
glVertex2f(22.4, 4.8);
glVertex2f(22.4, 4.3);
glVertex2f(22.2, 4.3);
glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(22.2, 4.8);
glVertex2f(22.4, 4.8);
glVertex2f(22.4, 4.3);
glVertex2f(22.2, 4.3);
glEnd();


// house front down 1st window 3rd h block with black border
glBegin(GL_POLYGON);
glColor3f(0.373f, 0.694f, 0.847f);  // Window color
glVertex2f(22.2, 4.3);
glVertex2f(22.4, 4.3);
glVertex2f(22.4, 3.8);
glVertex2f(22.2, 3.8);
glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(22.2, 4.3);
glVertex2f(22.4, 4.3);
glVertex2f(22.4, 3.8);
glVertex2f(22.2, 3.8);
glEnd();


// house front down 1st window 4th h block with black border
glBegin(GL_POLYGON);
glColor3f(0.373f, 0.694f, 0.847f);  // Window color
glVertex2f(22, 4.3);
glVertex2f(22.2, 4.3);
glVertex2f(22.2, 3.8);
glVertex2f(22, 3.8);
glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(22, 4.3);
glVertex2f(22.2, 4.3);
glVertex2f(22.2, 3.8);
glVertex2f(22, 3.8);
glEnd();


//house back
glBegin(GL_POLYGON);
glColor3f(0.639f, 0.933f, 0.898f);

glVertex2f(19, 5.5);
glVertex2f(21.5, 5.5);
glVertex2f(21.5, 3.1);
glVertex2f(19.0021721018923, 3.0574066348317);


glEnd();

        glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color

glVertex2f(19, 5.5);
glVertex2f(21.5, 5.5);
glVertex2f(21.5, 3.1);
glVertex2f(19.0021721018923, 3.0574066348317);

glEnd();


    //house back top part
glBegin(GL_POLYGON);
glColor3f(0.122f, 0.259f, 0.667f);

glVertex2f(19, 5.5);
glVertex2f(21.5, 5.5);
glVertex2f(21.5, 5.3);
glVertex2f(19.1, 5.3);


glEnd();
            glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color

glVertex2f(19, 5.5);
glVertex2f(21.5, 5.5);
glVertex2f(21.5, 5.3);
glVertex2f(19.1, 5.3);


glEnd();



    //house back downpart
glBegin(GL_POLYGON);
glColor3f(0.282f, 0.518f, 0.753f);

glVertex2f(18.9908057372809, 3.3998093343432);
glVertex2f(21.4979108378192, 3.3998041597796);
glVertex2f(21.5, 3.1);
glVertex2f(19.0021721018923, 3.0574066348317);


glEnd();

                glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color


glVertex2f(18.9908057372809, 3.3998093343432);
glVertex2f(21.4979108378192, 3.3998041597796);
glVertex2f(21.5, 3.1);
glVertex2f(19.0021721018923, 3.0574066348317);


glEnd();

       //house back door down
glBegin(GL_POLYGON);
glColor3f(0.929f, 0.965f, 0.831f);

glVertex2f(19.1, 3.6);
glVertex2f(20.2, 3.6);
glVertex2f(20.2, 3.4);
glVertex2f(19.1, 3.4);


glEnd();
                    glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color


glVertex2f(19.1, 3.6);
glVertex2f(20.2, 3.6);
glVertex2f(20.2, 3.4);
glVertex2f(19.1, 3.4);


glEnd();


         //house back door
glBegin(GL_POLYGON);
glColor3f(0.263f, 0.263f, 0.490f);

glVertex2f(19.3, 4.3);
glVertex2f(20,4.3);
glVertex2f(20,3.6);
glVertex2f(19.3, 3.6);


glEnd();

                        glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color


glVertex2f(19.3, 4.3);
glVertex2f(20,4.3);
glVertex2f(20,3.6);
glVertex2f(19.3, 3.6);



glEnd();

          //house back door top
glBegin(GL_POLYGON);
glColor3f(0.337f, 0.400f, 0.620f);

glVertex2f(19.3, 4.5);
glVertex2f(20, 4.5);
glVertex2f(20,4.3);
glVertex2f(19.3, 4.3);


glEnd();


glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(19.3, 4.5);
glVertex2f(20, 4.5);
glVertex2f(20,4.3);
glVertex2f(19.3, 4.3);
glEnd();

//house back window 1st block
glBegin(GL_POLYGON);
glColor3f(0.373f, 0.694f, 0.847f);
glVertex2f(20.7, 4.8);
glVertex2f(20.9, 4.8);
glVertex2f(20.9, 4.4);
glVertex2f(20.7, 4.4);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(20.7, 4.8);
glVertex2f(20.9, 4.8);
glVertex2f(20.9, 4.4);
glVertex2f(20.7, 4.4);
glEnd();


//house back window 2nd block
glBegin(GL_POLYGON);
glColor3f(0.373f, 0.694f, 0.847f);
glVertex2f(20.9, 4.8);
glVertex2f(21.1, 4.8);
glVertex2f(21.1, 4.4);
glVertex2f(20.9, 4.4);
glEnd();


glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(20.9, 4.8);
glVertex2f(21.1, 4.8);
glVertex2f(21.1, 4.4);
glVertex2f(20.9, 4.4);
glEnd();

//house back window 3rd block
glBegin(GL_POLYGON);
glColor3f(0.373f, 0.694f, 0.847f);
glVertex2f(20.9, 4.4);
glVertex2f(21.1, 4.4);
glVertex2f(21.1, 4);
glVertex2f(20.9, 4);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(20.9, 4.4);
glVertex2f(21.1, 4.4);
glVertex2f(21.1, 4);
glVertex2f(20.9, 4);
glEnd();


    //house back window 4th block
glBegin(GL_POLYGON);
glColor3f(0.373f, 0.694f, 0.847f);
glVertex2f(20.7, 4.4);
glVertex2f(20.9, 4.4);
glVertex2f(20.9, 4);
glVertex2f(20.7, 4);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(20.7, 4.4);
glVertex2f(20.9, 4.4);
glVertex2f(20.9, 4);
glVertex2f(20.7, 4);
glEnd();


}

void house_beside_forest()
{


glBegin(GL_POLYGON);
glColor3f(0.451f, 0.863f, 0.447f);
 glVertex2f(0, 3 );
glVertex2f(2.9250602877645, 2.8330532768222);
glVertex2f(4.8119528655895, 3.0656838686088);
glVertex2f(7.3191936881789, 3.039836025077);
glVertex2f(7.3191936881789, 3.039836025077);
glVertex2f(9.9039780413638, 2.9622924944814);
glVertex2f(12.0493490545073, 2.9105968074177);
glVertex2f(14.6858290947559, 2.8847489638859);
glVertex2f(19, 3);
     glVertex2f(18.9952735886179, 4.1502603619579);

             glVertex2f(0,4);

glEnd();

    glBegin(GL_POLYGON);
glColor3f(0.451f, 0.863f, 0.447f);


glVertex2f(24, 3.1 );
glVertex2f(26.705, 3.428 - 0.27);
glVertex2f(28.230, 3.143 - 0.27);
glVertex2f(29.961, 3.416 - 0.27);
    glVertex2f(29.9801699332932, 4.1868556413432);
        glVertex2f(24.004, 4.198);


glEnd();



}
void first_house()
{

glLineWidth(1.0f);
// roof
glBegin(GL_POLYGON);
glColor3f(0.992f, 0.224f, 0.231f); // Steel blue
glVertex2f(6, 8);
glVertex2f(9, 8);
glVertex2f(10.4, 6.8);
glVertex2f(7, 6.8);
glEnd();


glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(6, 8);
glVertex2f(9, 8);
glVertex2f(10.4, 6.8);
glVertex2f(7, 6.8);
glEnd();



    //house front
glBegin(GL_POLYGON);
glColor3f(0.267f, 0.592f, 0.749f);
glVertex2f(6, 8);
glVertex2f(7, 6.8);
glVertex2f(7, 4.06);
glVertex2f(5, 4.045);
 glVertex2f(5, 6.8);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(6, 8);
glVertex2f(7, 6.8);
glVertex2f(7, 4.06);
glVertex2f(5, 4.045);
 glVertex2f(5, 6.8);
glEnd();


      //house front top corner
glBegin(GL_POLYGON);
glColor3f(0.161f, 0.157f, 0.404f);
glVertex2f(6, 8);
glVertex2f(6.065, 7.92);
glVertex2f(5.002, 6.64);
glVertex2f(5, 6.8);
glEnd();


glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(6, 8);
glVertex2f(6.065, 7.92);
glVertex2f(5.002, 6.64);
glVertex2f(5, 6.8);
glEnd();


    //house front downpart
glBegin(GL_POLYGON);
glColor3f(0.161f, 0.157f, 0.404f);
glVertex2f(7.002, 4.4);
glVertex2f(5.8, 4.4);
glVertex2f(5.8, 4.2001);
glVertex2f(5.9, 4.2);
glVertex2f(5.9, 4.048);
glVertex2f(7, 4.06);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(7.002, 4.4);
glVertex2f(5.8, 4.4);
glVertex2f(5.8, 4.2001);
glVertex2f(5.9, 4.2);
glVertex2f(5.9, 4.048);
glVertex2f(7, 4.06);
glEnd();


    //house front top window
glBegin(GL_POLYGON);
glColor3f(0.576f, 0.776f, 0.839f);
glVertex2f(5.8, 7);
glVertex2f(6.2, 7);
glVertex2f(6.2, 6.6);
glVertex2f(5.8, 6.6);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(5.8, 7);
glVertex2f(6.2, 7);
glVertex2f(6.2, 6.6);
glVertex2f(5.8, 6.6);
glEnd();

// house front down 2nd window 1st block with black border
glBegin(GL_POLYGON);
glColor3f(0.576f, 0.776f, 0.839f);
glVertex2f(9, 6);
glVertex2f(9.4, 6);
glVertex2f(9.4, 5.4);
glVertex2f(9, 5.4);
glEnd();



// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(9, 6);
glVertex2f(9.4, 6);
glVertex2f(9.4, 5.4);
glVertex2f(9, 5.4);
glEnd();

//house back window 2nd block
glBegin(GL_POLYGON);
glColor3f(0.373f, 0.694f, 0.847f);
glVertex2f(6.4, 6.2);
glVertex2f(6.6, 6.2);
glVertex2f(6.6, 5.6);
glVertex2f(6.4, 5.6);


glEnd();


    // Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
 glVertex2f(6.4, 6.2);
glVertex2f(6.6, 6.2);
glVertex2f(6.6, 5.6);
glVertex2f(6.4, 5.6);
glEnd();

//house back
glBegin(GL_POLYGON);
glColor3f(0.639f, 0.933f, 0.898f);
glVertex2f(7, 6.8);
glVertex2f(10.4, 6.8);
glVertex2f(10.4, 4.084);
glVertex2f(7, 4.06);
glEnd();

    // Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(7, 6.8);
glVertex2f(10.4, 6.8);
glVertex2f(10.4, 4.084);
glVertex2f(7, 4.06);
glEnd();


    //house back top part
glBegin(GL_POLYGON);
glColor3f(0.122f, 0.259f, 0.667f);
glVertex2f(7, 6.8);
glVertex2f(10.4, 6.8);
glVertex2f(10.4, 6.6);
glVertex2f(7.001, 6.602);
glEnd();


    // Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(7, 6.8);
glVertex2f(10.4, 6.8);
glVertex2f(10.4, 6.6);
glVertex2f(7.001, 6.602);
glEnd();



    //house back downpart
glBegin(GL_POLYGON);
glColor3f(0.282f, 0.518f, 0.753f);
glVertex2f(7.002, 4.4);
glVertex2f(10.4, 4.4);
glVertex2f(10.4, 4.084);
glVertex2f(7, 4.06);
glEnd();

    // Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(7.002, 4.4);
glVertex2f(10.4, 4.4);
glVertex2f(10.4, 4.084);
glVertex2f(7, 4.06);
glEnd();


       //house back door down
glBegin(GL_POLYGON);
glColor3f(0.929f, 0.965f, 0.831f);
glVertex2f(5, 4.2);
glVertex2f(5.9, 4.2);
glVertex2f(5.9, 4.048);
glVertex2f(5, 4.045);
glEnd();


    // Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(5, 4.2);
glVertex2f(5.9, 4.2);
glVertex2f(5.9, 4.048);
glVertex2f(5, 4.045);
glEnd();

     //house back door down upppp
glBegin(GL_POLYGON);
glColor3f(0.929f, 0.965f, 0.831f);
glVertex2f(5.2, 4.4);
glVertex2f(5.8, 4.4);
glVertex2f(5.8, 4.2001);
glVertex2f(5.2, 4.2001);
glEnd();

    // Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(5.2, 4.4);
glVertex2f(5.8, 4.4);
glVertex2f(5.8, 4.2001);
glVertex2f(5.2, 4.2001);
glEnd();

         //house back door
glBegin(GL_POLYGON);
glColor3f(0.263f, 0.263f, 0.490f);
glVertex2f(5.3, 5.4);
glVertex2f(5.8, 5.4);
glVertex2f(5.8, 4.4);
glVertex2f(5.3, 4.4005);
glEnd();


    // Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(5.3, 5.4);
glVertex2f(5.8, 5.4);
glVertex2f(5.8, 4.4);
glVertex2f(5.3, 4.4005);
glEnd();


//house back window 1st block
glBegin(GL_POLYGON);
glColor3f(0.373f, 0.694f, 0.847f);
glVertex2f(6.2, 6.2);
glVertex2f(6.4, 6.2);
glVertex2f(6.4, 5.6);
glVertex2f(6.2, 5.6);
glEnd();



// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(6.2, 6.2);
glVertex2f(6.4, 6.2);
glVertex2f(6.4, 5.6);
glVertex2f(6.2, 5.6);
glEnd();



//house front window 2nd 1st block
glBegin(GL_POLYGON);
glColor3f(0.373f, 0.694f, 0.847f);
glVertex2f(9, 6);
glVertex2f(9.4, 6);
glVertex2f(9.4, 5.4);
glVertex2f(9, 5.4);


glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
  glVertex2f(9, 6);
glVertex2f(9.4, 6);
glVertex2f(9.4, 5.4);
glVertex2f(9, 5.4);

glEnd();

//house front window 2nd 2nd block
glBegin(GL_POLYGON);
glColor3f(0.373f, 0.694f, 0.847f);
glVertex2f(9.4, 6);
glVertex2f(9.8, 6);
glVertex2f(9.8, 5.4);
glVertex2f(9.4, 5.4);


glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(9.4, 6);
glVertex2f(9.8, 6);
glVertex2f(9.8, 5.4);
glVertex2f(9.4, 5.4);
glEnd();



//house front window 2nd 3rd block
glBegin(GL_POLYGON);
glColor3f(0.373f, 0.694f, 0.847f);
glVertex2f(9.4, 5.4);
glVertex2f(9.8, 5.4);
glVertex2f(9.8, 4.8);
glVertex2f(9.4, 4.8);


glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(9.4, 5.4);
glVertex2f(9.8, 5.4);
glVertex2f(9.8, 4.8);
glVertex2f(9.4, 4.8);

glEnd();


//house front window 2nd 4th block
glBegin(GL_POLYGON);
glColor3f(0.373f, 0.694f, 0.847f);
glVertex2f(9, 5.4);
glVertex2f(9.4, 5.4);
glVertex2f(9.4, 4.8);
glVertex2f(9, 4.8);


glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(9, 5.4);
glVertex2f(9.4, 5.4);
glVertex2f(9.4, 4.8);
glVertex2f(9, 4.8);

glEnd();



//house front window 1st 1st block
glBegin(GL_POLYGON);
glColor3f(0.373f, 0.694f, 0.847f);
glVertex2f(7.6, 6);
glVertex2f(8, 6);
glVertex2f(8, 5.4);
glVertex2f(7.6, 5.4);


glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(7.6, 6);
glVertex2f(8, 6);
glVertex2f(8, 5.4);
glVertex2f(7.6, 5.4);

glEnd();

//house front window 1st 2nd block
glBegin(GL_POLYGON);
glColor3f(0.373f, 0.694f, 0.847f);
glVertex2f(8, 6);
glVertex2f(8.4, 6);
glVertex2f(8.4, 5.4);
glVertex2f(8, 5.4);


glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(8, 6);
glVertex2f(8.4, 6);
glVertex2f(8.4, 5.4);
glVertex2f(8, 5.4);
glEnd();



//house front window 2nd 3rd block
glBegin(GL_POLYGON);
glColor3f(0.373f, 0.694f, 0.847f);
glVertex2f(8, 5.4);
glVertex2f(8.4, 5.4);
glVertex2f(8.4, 4.8);
glVertex2f(8, 4.8);


glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(8, 5.4);
glVertex2f(8.4, 5.4);
glVertex2f(8.4, 4.8);
glVertex2f(8, 4.8);
glEnd();


//house front window 1st 4th block
glBegin(GL_POLYGON);
glColor3f(0.373f, 0.694f, 0.847f);
glVertex2f(7.6, 5.4);
glVertex2f(8, 5.4);
glVertex2f(8, 4.8);
glVertex2f(7.6, 4.8);


glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
 glVertex2f(7.6, 5.4);
glVertex2f(8, 5.4);
glVertex2f(8, 4.8);
glVertex2f(7.6, 4.8);


glEnd();

}

void second_house()
{

glLineWidth(1.0f);
// roof
glBegin(GL_POLYGON);
glColor3f(0.9843f, 0.2431f, 0.2549f);
glVertex2f(11.9, 8.1);
glVertex2f(14.8, 8.1);
glVertex2f(16, 6.8);
glVertex2f(12.8, 6.8);

glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(11.9, 8.1);
glVertex2f(14.8, 8.1);
glVertex2f(16, 6.8);
glVertex2f(12.8, 6.8);
glEnd();


// roof down part
glBegin(GL_POLYGON);
glColor3f(0.1373f, 0.2392f, 0.4980f);
glVertex2f(12.8, 6.8);
glVertex2f(16, 6.8);
glVertex2f(16.1, 6.65);
glVertex2f(12.9, 6.65);

glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(12.8, 6.8);
glVertex2f(16, 6.8);
glVertex2f(16.1, 6.65);
glVertex2f(12.9, 6.65);
glEnd();



// house chimni front part
glBegin(GL_POLYGON);
glColor3f(0.6353f, 0.8235f, 0.8471f);
glVertex2f(13.6, 8.6);
glVertex2f(14, 8.6);
glVertex2f(14, 7.4);
glVertex2f(13.6, 7.4);

glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(13.6, 8.6);
glVertex2f(14, 8.6);
glVertex2f(14, 7.4);
glVertex2f(13.6, 7.4);
glEnd();


// house chimni back part
glBegin(GL_POLYGON);
glColor3f(0.2196f, 0.2039f, 0.3961f);
glVertex2f(14, 8.6);
glVertex2f(14.2, 8.6);
glVertex2f(14.2, 7.6);
glVertex2f(14, 7.4);

glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(14, 8.6);
glVertex2f(14.2, 8.6);
glVertex2f(14.2, 7.6);
glVertex2f(14, 7.4);
glEnd();



// house chimni front upper part
glBegin(GL_POLYGON);
glColor3f(0.9569f, 0.9608f, 0.8157f);
glVertex2f(13.6, 8.8);
glVertex2f(14, 8.8);
glVertex2f(14, 8.6);
glVertex2f(13.6, 8.6);

glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(13.6, 8.8);
glVertex2f(14, 8.8);
glVertex2f(14, 8.6);
glVertex2f(13.6, 8.6);
glEnd();


// house chimni back upper part
glBegin(GL_POLYGON);
glColor3f(0.5451f, 0.6471f, 0.6314f);
glVertex2f(14, 8.8);
glVertex2f(14.2, 8.7);
glVertex2f(14.2, 8.6);
glVertex2f(14, 8.6);

glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(14, 8.8);
glVertex2f(14.2, 8.7);
glVertex2f(14.2, 8.6);
glVertex2f(14, 8.6);
glEnd();



// house back part
glBegin(GL_POLYGON);
glColor3f(0.2235f, 0.5843f, 0.7529f);
glVertex2f(12.8, 6.8);
glVertex2f(16, 6.8);
glVertex2f(16, 4.3);
glVertex2f(12.8, 4.3);

glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(12.8, 6.8);
glVertex2f(16, 6.8);
glVertex2f(16, 4.3);
glVertex2f(12.8, 4.3);
glEnd();




// back part window 1st 1st block
glBegin(GL_POLYGON);
glColor3f(0.5647f, 0.7804f, 0.9255f);
glVertex2f(13.4, 5.8);
glVertex2f(13.6, 5.8);
glVertex2f(13.6, 5.4);
glVertex2f(13.4, 5.4);

glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(13.4, 5.8);
glVertex2f(13.6, 5.8);
glVertex2f(13.6, 5.4);
glVertex2f(13.4, 5.4);
glEnd();



// back part window 1st 2nd block
glBegin(GL_POLYGON);
glColor3f(0.5647f, 0.7804f, 0.9255f);
glVertex2f(13.6, 5.8);
glVertex2f(13.8, 5.8);
glVertex2f(13.8, 5.4);
glVertex2f(13.6, 5.4);

glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0,0,0);
glVertex2f(13.6, 5.8);
glVertex2f(13.8, 5.8);
glVertex2f(13.8, 5.4);
glVertex2f(13.6, 5.4);
glEnd();


// back part window 1st 3rd block
glBegin(GL_POLYGON);
glColor3f(0.5647f, 0.7804f, 0.9255f);
glVertex2f(13.6, 5.4);
glVertex2f(13.8, 5.4);
glVertex2f(13.8, 5);
glVertex2f(13.6, 5);

glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(13.6, 5.4);
glVertex2f(13.8, 5.4);
glVertex2f(13.8, 5);
glVertex2f(13.6, 5);
glEnd();


// back part window 1st 4th block
glBegin(GL_POLYGON);
glColor3f(0.5647f, 0.7804f, 0.9255f);
glVertex2f(13.4, 5.4);
glVertex2f(13.6, 5.4);
glVertex2f(13.6, 5);
glVertex2f(13.4, 5);

glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(13.4, 5.4);
glVertex2f(13.6, 5.4);
glVertex2f(13.6, 5);
glVertex2f(13.4, 5);
glEnd();


// back part window 2nd 1st block
glBegin(GL_POLYGON);
glColor3f(0.5647f, 0.7804f, 0.9255f);
glVertex2f(14.8, 5.8);
glVertex2f(15, 5.8);
glVertex2f(15, 5.4);
glVertex2f(14.8, 5.4);

glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(14.8, 5.8);
glVertex2f(15, 5.8);
glVertex2f(15, 5.4);
glVertex2f(14.8, 5.4);
glEnd();



// back part window 2nd 2nd block
glBegin(GL_POLYGON);
glColor3f(0.5647f, 0.7804f, 0.9255f);
glVertex2f(15, 5.8);
glVertex2f(15.2, 5.8);
glVertex2f(15.2, 5.4);
glVertex2f(15, 5.4);

glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(15, 5.8);
glVertex2f(15.2, 5.8);
glVertex2f(15.2, 5.4);
glVertex2f(15, 5.4);
glEnd();

// back part window 2nd 3rd block
glBegin(GL_POLYGON);
glColor3f(0.5647f, 0.7804f, 0.9255f);
glVertex2f(15, 5.4);
glVertex2f(15.2, 5.4);
glVertex2f(15.2, 5);
glVertex2f(15, 5);

glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(15, 5.4);
glVertex2f(15.2, 5.4);
glVertex2f(15.2, 5);
glVertex2f(15, 5);
glEnd();



// back part window 2nd 4th block
glBegin(GL_POLYGON);
glColor3f(0.5647f, 0.7804f, 0.9255f);
glVertex2f(14.8, 5.4);
glVertex2f(15, 5.4);
glVertex2f(15, 5);
glVertex2f(14.8, 5);

glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(14.8, 5.4);
glVertex2f(15, 5.4);
glVertex2f(15, 5);
glVertex2f(14.8, 5);
glEnd();



// back part down
glBegin(GL_POLYGON);
glColor3f(0.282f, 0.518f, 0.753f);
glVertex2f(12.8, 4.3);
glVertex2f(16, 4.3);
glVertex2f(15.9991, 4.126);
glVertex2f(12.8, 4.1015);

glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(12.8, 4.3);
glVertex2f(16, 4.3);
glVertex2f(15.9991, 4.126);
glVertex2f(12.8, 4.1015);
glEnd();

//front
glBegin(GL_POLYGON);
glColor3f(0.6118f, 0.9059f, 0.8549f);
glVertex2f(11, 6.8);
glVertex2f(11.9, 8.1);
glVertex2f(12.8, 6.8);
glVertex2f(12.8, 4.1015);
glVertex2f(11.0012876337854, 4.0952324079706);

glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(11, 6.8);
glVertex2f(11.9, 8.1);
glVertex2f(12.8, 6.8);
glVertex2f(12.8, 4.1015);
glVertex2f(11.0012876337854, 4.0952324079706);
glEnd();


//front upper part
glBegin(GL_POLYGON);
glColor3f(0.1020f, 0.1882f, 0.5176f);
glVertex2f(11, 6.8);
glVertex2f(11.9, 8.1);
glVertex2f(11.948, 8.03);
glVertex2f(11.000052,6.69);


glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(11, 6.8);
glVertex2f(11.9, 8.1);
glVertex2f(11.948, 8.03);
glVertex2f(11.000052,6.69);
glEnd();


//front window
glBegin(GL_POLYGON);
glColor3f(0.4667f, 0.8000f, 0.8627f);
glVertex2f(11.6, 7);
glVertex2f(12, 7);
glVertex2f(12, 6.6);
glVertex2f(11.6, 6.6);


glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(11.6, 7);
glVertex2f(12, 7);
glVertex2f(12, 6.6);
glVertex2f(11.6, 6.6);
glEnd();


//front door
glBegin(GL_POLYGON);
glColor3f(0.2667f, 0.2627f, 0.5020f);
glVertex2f(11.2, 5.4);
glVertex2f(11.6, 5.4);
glVertex2f(11.6,4.3);
glVertex2f(11.2, 4.3);


glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(11.2, 5.4);
glVertex2f(11.6, 5.4);
glVertex2f(11.6,4.3);
glVertex2f(11.2, 4.3);
glEnd();


//front door down part
glBegin(GL_POLYGON);
glColor3f(0.9255f, 0.9569f, 0.8157f);
glVertex2f(11.001,4.2);
glVertex2f(11.75, 4.2);
glVertex2f(11.7515559278993, 4.0885646145288);
glVertex2f(11.0012876337854, 4.0952324079706);


glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(11.001,4.2);
glVertex2f(11.75, 4.2);
glVertex2f(11.7515559278993, 4.0885646145288);
glVertex2f(11.0012876337854, 4.0952324079706);
glEnd();




//front door down upper part
glBegin(GL_POLYGON);
glColor3f(0.9255f, 0.9569f, 0.8157f);
glVertex2f(11.1, 4.3);
glVertex2f(11.7, 4.3);
glVertex2f(11.7, 4.2);
glVertex2f(11.1, 4.2);


glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(11.1, 4.3);
glVertex2f(11.7, 4.3);
glVertex2f(11.7, 4.2);
glVertex2f(11.1, 4.2);
glEnd();


//front down part
glBegin(GL_POLYGON);
glColor3f(0.2000f, 0.2627f, 0.4196f);
glVertex2f(11.7, 4.3);
glVertex2f(12.8, 4.3);
glVertex2f(12.8, 4.1015);
glVertex2f(11.7515559278993, 4.0885646145288);
glVertex2f(11.75, 4.2);
glVertex2f(11.7, 4.2);

glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(11.001,4.2);
glVertex2f(11.75, 4.2);
glVertex2f(11.7515559278993, 4.0885646145288);
glVertex2f(11.0012876337854, 4.0952324079706);
glEnd();

//back upper part
glBegin(GL_POLYGON);
glColor3f(0.1255f, 0.2431f, 0.6588f);
glVertex2f(12.8, 6.8);
glVertex2f(16, 6.8);
glVertex2f(16.1, 6.65);
glVertex2f(12.9, 6.65);
glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(12.8, 6.8);
glVertex2f(16, 6.8);
glVertex2f(16.1, 6.65);
glVertex2f(12.9, 6.65);
glEnd();

}


void background_gradient()
{
     glBegin(GL_QUADS);
    glColor3f(0.678f, 0.847f, 0.902f); // Light blue at the bottom-left corner
    glVertex2f(0.0f, 0.0f);  // Bottom-left corner
    glColor3f(1.0f, 1.0f, 1.0f); // White at the top-left corner
    glVertex2f(0.0f, 15.0f);  // Top-left corner
    glColor3f(1.0f, 1.0f, 1.0f); // White at the top-right corner
    glVertex2f(30.0f, 15.0f);  // Top-right corner
    glColor3f(0.678f, 0.847f, 0.902f); // Light blue at the bottom-right corner
    glVertex2f(30.0f, 0.0f);  // Bottom-right corner
    glEnd();
}


// Mountain Scene Implementation (Placeholder - replace with your actual implementation)
void initMountainScene() {
    // Initialize mountain scene-specific settings
    //glClearColor(0.5f, 0.7f, 1.0f, 1.0f);  // Sky blue background
}

void displayMountainScene() {
     background_gradient();
    path();
    house();
    path_down_ground();
    house_beside_forest();
    first_house();
    second_house();
}




























//Animation variables
float RightBallonX = 0.0f;
float RightBallonSpeed = .03;
float LeftBallonX = 0.0f;
float LeftBallonSpeed = .03;
float LeftLeafAngle= 0.0f;
float LeftLeafRotSpeed=1.0f;
float BallPositionX = 0.0f;
float BallAngle = 0.0f;

//
const float ballRadius = 1.0f; // Radius of the ball
const float BallSpeed = 0.05f;     // Speed of movement

bool  JuiceSignVisible=true;
int   JuiceSignelapsedTime=0;
//stars vars
const int numStars = 100;
float starX[numStars];
float starY[numStars];
float starBrightness[numStars];
bool starVisible[numStars];

//Waves
float Wave1X= 0.0f;
float Wave1Speed=0.015f;
float Wave2X= 0.0f;
float Wave2Speed=0.020f;
float Wave3X= 0.0f;
float Wave3Speed=0.01f;


SoilAndDetails(){
glBegin(GL_POLYGON);
        glColor3ub(240,214,138);
        glVertex2f(0.0,0.0);
        glVertex2f(30.0,0.0);
        glVertex2f(30.0,5.0);
        glVertex2f(10.0202451819864, 7.7104130643092);
        glVertex2f(0.0,6.0);
    glEnd();
    glLineWidth(2.3);
    glBegin(GL_LINE_LOOP);
        glColor3ub(0,0,0);
        glVertex2f(0.0,0.0);
        glVertex2f(30.0,0.0);
        glVertex2f(30.0,5.0);
        glVertex2f(10.0202451819864, 7.7104130643092);
        glVertex2f(0.0,6.0);
    glEnd();
    glColor3ub(240,214,138);
    drawTiltedFilledEllipse(4.6510528439121, 6.778886816893,5.3,0.13,10.0,200);
    glColor3ub(0,0,0);
    drawTiltedUpperHollowEllipse(4.6510528439121, 6.778886816893,5.3,0.13,10.0,200);


}
SoilStrip(){
 //Strip
    glBegin(GL_POLYGON);
        glColor3ub(240,214,138);
        glVertex2f(12.7607151034867, 2.4001033496419);
        glVertex2f(22.0099054874694, 2.3264621314034);
        glVertex2f(22.0169767339404, 2.7370957014211);
        glVertex2f(12.9587100046729, 2.7158819620083);
        glVertex2f(0.0,6.0);
    glEnd();
    glColor3ub(0,0,0);
    glLineWidth(2.3);
    glBegin(GL_LINES);
    glVertex2f(12.9587100046729, 2.7158819620083);
        glVertex2f(13.3,2.71);
        glEnd();
        drawTiltedHollowSemiCircle(13.4610549178167, 2.7297831661403,0.18,0.0,true);
        glBegin(GL_LINES);
    glVertex2f(13.6537605775349, 2.734697529998);
        glVertex2f(15.6446411561796, 2.7409779103723);
        glEnd();
        glBegin(GL_LINES);
    glVertex2f(14.8048058090687, 2.5557550454622);
        glVertex2f(15.4198850956766, 2.5557550454622);
        glEnd();
        drawTiltedHollowSemiCircle(15.5751194351604, 2.5377106522981,0.18,170.0,false);
        glBegin(GL_LINES);
    glVertex2f(15.7005752380506, 2.5251709925369);
        glVertex2f(15.9542742399106, 2.5251709925369);
        glEnd();
        drawTiltedHollowSemiCircle(16.1001875433592, 2.5289278494811,0.18,0.0,true);
        glBegin(GL_LINES);
    glVertex2f(17.3926731328713, 2.4214562426168);
        glVertex2f(17.6188444410086, 2.4261195685577);
        glEnd();
        drawHollowEllipse(17.735427589533, 2.4774161539085,0.16,0.05,200);
        glBegin(GL_LINES);
    glVertex2f(17.7657392081493, 2.3724913202365);
        glVertex2f(18.2507251060107, 2.3771546461775);
        glEnd();

        glBegin(GL_LINES);
    glVertex2f(18.5996720186478, 2.4149529291167);
        glVertex2f(19.1610561032512, 2.4197924470874);
        glEnd();
        drawHollowEllipse(19.4159054996686, 2.4132785469701,0.31,0.05,200);
        drawTiltedHollowSemiCircle(19.8756893899823, 2.427706648643,0.18,2.0,true);
        glBegin(GL_LINES);
    glVertex2f(19.99995849591, 2.4143110009995);
        glVertex2f(21.125900399363, 2.410113411146);
        glEnd();

}
SkyAndClouds(){
glBegin(GL_POLYGON);
        glColor3ub(0,7,60);
        glVertex2f(0.0,10.0);
        glVertex2f(15.2798174002007, 11.7817611608872);
        glVertex2f(30.0,10.0);
        glVertex2f(30.0,15.0);
        glVertex2f(0.0,15.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3ub(40, 36, 66);
    glVertex2f(0.0,10.0);
        glVertex2f(30.0,10.0);
        glVertex2f(15.2798174002007, 11.7817611608872);
        glEnd();
    //Border clouds
    glColor3ub(0,7,60);
drawFilledCircle(28.0532136084675, 10.1660269945496,3.1,100);
drawFilledCircle(24.3511674505249, 10.7549888833132,1.46,100);
drawFilledCircle(21.9953198954705, 9.7948574835388,1.42,100);
drawFilledCircle(19.38,11.28,1.9,100);
drawFilledCircle(16.19,11.67,1.8,100);
drawFilledCircle(13.9839692884568, 11.6864296905942,0.67,100);
drawFilledCircle(12.52,11.46,0.9,100);
drawFilledCircle(10.38,11.21,1.4,100);
drawFilledCircle(7.17,10.83,1.9,100);
drawFilledCircle(5.2249926647529, 9.530373906298,1.13,100);
drawFilledCircle(4.0,10.46,0.9,100);
drawFilledCircle(1.5376472609278, 10.228641972803,1.7,100);
}
void Stars() {
    glPointSize(4.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < numStars; i++) {
        if (starBrightness[i] == 0) {
            starBrightness[i] = randomFloat(0.5, 1.0);
            starVisible[i] = true;
        }

        if (starVisible[i]) {
            glColor3f(starBrightness[i], starBrightness[i], starBrightness[i]);
            float x = randomFloat(0.0,30.0);
            float y = randomFloat(10.0,30.0);
            glVertex2f(x, y);
        }
    }
    glEnd();
}
Cloud1(){
    glColor3ub(255,255,255);
    glLineWidth(3.0);
    drawTiltedHollowSemiCircle(3.2882887823755, 13.2989546744021,0.96,0,true);
    drawTiltedHollowSemiCircle(4.4254240391536, 13.6101110879483,1.24,0,true);
    glColor3ub(11,11,84);
    drawFilledCircle(3.2882887823755, 13.2989546744021,0.96,100);
    drawFilledCircle(4.4254240391536, 13.6101110879483,1.24,100);
   /* glColor3ub(255,255,255);
    glLineWidth(1.5);
    drawTiltedHollowSemiCircle(3.2882887823755, 13.2989546744021,0.96,0,true);
    drawTiltedHollowSemiCircle(4.4254240391536, 13.6101110879483,1.24,0,true);*/
    glBegin(GL_POLYGON);
        glColor3ub(3,37,108);
        //glColor3ub(17,16,122);
       // glColor3ub(0,0,0);
        glVertex2f(3.0,12.0);
        glVertex2f(6.0,12.0);
        glVertex2f(6.0075306509456, 13.1900535852944);
        glVertex2f(2.9918000596263, 13.1814924598916);
    glEnd();


    drawFilledCircle(5.760442341656, 12.9569400811648,0.96,100);
    drawFilledCircle(4.2610292824076, 13.6609790551645,0.96,100);
    drawFilledCircle(3.2597484511024, 12.9417491622551,0.96,100);
    glColor3ub(255,255,255);
    glLineWidth(1.5);
    glBegin(GL_LINES);
    glVertex2f(3.0,12.0);
        glVertex2f(6.0,12.0);
        glEnd();



}
SeaWater(){
glBegin(GL_POLYGON);
        glColor3ub(14,49,119);
       // glColor3ub(0,0,0);
        glVertex2f(22.6855606826301, 2.0214219028557);
        glVertex2f(30.0, 0.0);
        glVertex2f(30.0,7.26);
        glVertex2f(23.5,5.87);
    glEnd();
drawTiltedFilledEllipse(23.9939891124046, 2.3289818018727,1.86,0.78,150,200);
drawTiltedFilledEllipse(23.8562703425279, 3.6248601739538,1.86,0.78,160,200);
drawTiltedFilledEllipse(24.453942398449637, 5.226398521455826,1.86,0.78,30,200);
drawTiltedFilledEllipse(26.72,6.45,3.20,0.58,10,200);

}
Wave1(){
    glPushMatrix();
    glTranslatef(Wave1X,0.0,0.0);
glColor3ub(14,49,119);
drawTiltedFilledEllipse(23.5836825899908, 3.0533863656836,1.79,0.58,0,200);
glPopMatrix();
}
Wave2(){
    glPushMatrix();
    glTranslatef(Wave2X,0.0,0.0);
glColor3ub(14,49,119);
drawTiltedFilledEllipse(23.6655352338137, 3.4970129185738,1.79,0.78,0,200);
glPopMatrix();
}
Wave3(){
    glPushMatrix();
    glTranslatef(Wave3X,0.0,0.0);
glColor3ub(14,49,119);
drawTiltedFilledEllipse(23.6655352338137, 4.1170129185738,1.79,0.78,170,200);
glPopMatrix();
}
//#S4_busstand
BusStand(){
    glBegin(GL_POLYGON);
        glColor3ub(170,170,170);
       // glColor3ub(0,0,0);
        glVertex2f(1.0,0.0);
        glVertex2f(1.4, 0.0);
        glVertex2f(1.4,6.0);
        glVertex2f(1.0, 6.0);
    glEnd();
glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glColor3ub(0,0,0);
        glVertex2f(1.0,0.0);
        glVertex2f(1.4, 0.0);
        glVertex2f(1.4,6.0);
        glVertex2f(1.0, 6.0);
    glEnd();
    glBegin(GL_QUADS);
        glColor3ub(170,170,170);
        glVertex2f(7.0,0.0);
        glVertex2f(7.4, 0.0);
        glVertex2f(7.4,6.0);
        glVertex2f(7.0, 6.0);
    glEnd();
glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glColor3ub(0,0,0);
        glVertex2f(7.0,0.0);
        glVertex2f(7.4, 0.0);
        glVertex2f(7.4,6.0);
        glVertex2f(7.0, 6.0);
    glEnd();
    //roof
glBegin(GL_QUADS);
        glColor3ub(70,130,180);
        glVertex2f(0.6,6.0);
        glVertex2f(7.9, 6.0);
        glVertex2f(7.0,7.0);
        glVertex2f(1.6, 7.0);
    glEnd();
glColor3ub(70,130,180);
drawTiltedFilledEllipse(1.10,6.49,0.67,0.17,48,100);
drawTiltedFilledEllipse(7.44,6.49,0.67,0.17,360-48,100);
    //Bus Stop Board
glBegin(GL_QUADS);
        glColor3ub(166,102,65);
        glVertex2f(1.7,7.0);
        glVertex2f(6.8, 7.0);
        glVertex2f(6.8,8.0);
        glVertex2f(1.7, 8.0);
    glEnd();
glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glColor3ub(0,0,0);
        glVertex2f(1.7,7.0);
        glVertex2f(6.8, 7.0);
        glVertex2f(6.8,8.0);
        glVertex2f(1.7, 8.0);
    glEnd();
    //BUS STOP logo
    //B
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(2.44,7.18);
    glVertex2f(2.44, 7.79);
    glEnd();
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(2.44, 7.79);
    glVertex2f(2.65, 7.79);
    glEnd();
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(2.44, 7.5);
    glVertex2f(2.70, 7.5);
    glEnd();
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(2.44, 7.18);
    glVertex2f(2.63, 7.18);
    glEnd();
glColor3ub(0,0,0);
drawRightHollowSemiCircle(2.64,7.66,0.14,0,100);
drawRightHollowSemiCircle(2.6,7.34,0.17,0,100);
    //U
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(2.9, 7.8);
    glVertex2f(2.9, 7.3);
    glEnd();
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(3.2, 7.8);
    glVertex2f(3.2, 7.3);
    glEnd();
drawRightHollowSemiCircle(3.05,7.32,0.16,270,100);
    //S
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(3.4, 7.7);
    glVertex2f(3.4, 7.4);
    glEnd();
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(3.6, 7.5);
    glVertex2f(3.6, 7.3);
    glEnd();
drawRightHollowSemiCircle(3.5,7.4,0.11,90,100);
drawRightHollowSemiCircle(3.5,7.64,0.11,90,100);
drawRightHollowSemiCircle(3.5,7.3,0.11,270,100);
    //S
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(4.15, 7.7);
    glVertex2f(4.15, 7.5);
    glEnd();
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(4.5, 7.45);
    glVertex2f(4.5, 7.3);
    glEnd();
drawRightHollowSemiCircle(4.32,7.64,0.17,90,200);
drawRightHollowSemiCircle(4.32,7.45,0.17,90,100);
drawRightHollowSemiCircle(4.33,7.32,0.16,270,100);
    //T
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(4.75, 7.2);
    glVertex2f(4.75, 7.82);
    glEnd();
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(4.54, 7.82);
    glVertex2f(4.94, 7.82);
    glEnd();
    //O
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(5.11, 7.4);
    glVertex2f(5.11, 7.6);
    glEnd();
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(5.51, 7.4);
    glVertex2f(5.51, 7.6);
    glEnd();
drawRightHollowSemiCircle(5.3,7.6,0.19,90,100);
drawRightHollowSemiCircle(5.3,7.4,0.19,270,100);
    //P
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(5.76, 7.2);
    glVertex2f(5.76, 7.8);
    glEnd();
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(5.95, 7.8);
    glVertex2f(5.76, 7.8);
    glEnd();
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(5.76, 7.5);
    glVertex2f(5.95, 7.5);
    glEnd();
drawRightHollowSemiCircle(5.95,7.64,0.15,0,100);
    //Body windows
    glLineWidth(7.0f);
    glBegin(GL_LINES);
    glColor3ub(170,170,170);
    glVertex2f(1.4, 5.0);
    glVertex2f(7.0, 5.0);
    glEnd();
    glLineWidth(7.0f);
    glBegin(GL_LINES);
    glColor3ub(170,170,170);
    glVertex2f(1.4, 1.0);
    glVertex2f(7.0, 1.0);
    glEnd();
    glBegin(GL_QUADS);
        glColor3ub(208,223,242);
        glVertex2f(2.0,1.19);
        glVertex2f(3.90, 1.19);
        glVertex2f(3.90,4.77);
        glVertex2f(2.0,4.77);
    glEnd();
    glBegin(GL_QUADS);
        glColor3ub(208,223,242);
        glVertex2f(4.4,1.19);
        glVertex2f(6.4, 1.19);
        glVertex2f(6.4,4.77);
        glVertex2f(4.4,4.77);
    glEnd();
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glColor3ub(0,0,0);
        glVertex2f(2.0,1.19);
        glVertex2f(3.90, 1.19);
        glVertex2f(3.90,4.77);
        glVertex2f(2.0,4.77);
    glEnd();
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glColor3ub(0,0,0);
        glVertex2f(4.4,1.19);
        glVertex2f(6.4, 1.19);
        glVertex2f(6.4,4.77);
        glVertex2f(4.4,4.77);
    glEnd();
    //White shade Win-1
    glBegin(GL_QUADS);
    glColor3ub(255,255,255);
    glVertex2f(2.0,3.88);
    glVertex2f(3.90, 1.9);
    glVertex2f(3.9,2.5);
    glVertex2f(2.0, 4.4);
    glEnd();
    //White shade Win-2
    glBegin(GL_QUADS);
    glColor3ub(255,255,255);
    glVertex2f(4.9,4.77);
    glVertex2f(6.4,3.4);
    glVertex2f(6.4,3.9);
    glVertex2f(5.4, 4.77);
    glEnd();
}
//S4_JuiceShop
void BeachJuiceShop(){
glBegin(GL_QUADS);
    glColor3ub(145,67,81);
    glVertex2f(16.0,2.6);
    glVertex2f(16.3,2.6);
    glVertex2f(16.3,4.2);
    glVertex2f(16.0,4.2);
    glEnd();
glLineWidth(2.0f);
glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2f(16.0,2.6);
    glVertex2f(16.3,2.6);
    glVertex2f(16.3,4.2);
    glVertex2f(16.0,4.2);
    glEnd();
glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(16.15, 4.2);
    glVertex2f(16.15, 2.6);
    glEnd();
glBegin(GL_QUADS);
    glColor3ub(145,67,81);
    glVertex2f(15.4,4.2);
    glVertex2f(18.4,4.2);
    glVertex2f(18.4,4.4);
    glVertex2f(15.4,4.4);
    glEnd();
glLineWidth(2.0f);
glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2f(15.4,4.2);
    glVertex2f(18.4,4.2);
    glVertex2f(18.4,4.4);
    glVertex2f(15.4,4.4);
    glEnd();
glBegin(GL_QUADS);
    glColor3ub(94,44,71);
    glVertex2f(18.4,4.2);
    glVertex2f(20.0,4.2);
    glVertex2f(20.0,4.4);
    glVertex2f(18.4,4.4);
    glEnd();
glLineWidth(2.0f);
glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2f(18.4,4.2);
    glVertex2f(20.0,4.2);
    glVertex2f(20.0,4.4);
    glVertex2f(18.4,4.4);
    glEnd();

glBegin(GL_QUADS);
    glColor3ub(94,44,71);
    glVertex2f(18.7,2.6);
    glVertex2f(19.5,2.6);
    glVertex2f(19.5,4.2);
    glVertex2f(18.7,4.2);
    glEnd();
glLineWidth(2.5f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(18.7,2.6);
    glVertex2f(18.7,4.2);
    glEnd();
glBegin(GL_QUADS);
    glColor3ub(45,21,45);
    glVertex2f(19.5,2.6);
    glVertex2f(19.6,2.6);
    glVertex2f(19.6,4.2);
    glVertex2f(19.5,4.2);
    glEnd();
glLineWidth(2.0f);
glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2f(19.5,2.6);
    glVertex2f(19.6,2.6);
    glVertex2f(19.6,4.2);
    glVertex2f(19.5,4.2);
    glEnd();
glBegin(GL_QUADS);
    glColor3ub(145,67,81);
    glVertex2f(16.0,4.4);
    glVertex2f(16.3,4.4);
    glVertex2f(16.3,5.5);
    glVertex2f(16.0,5.5);
    glEnd();
glLineWidth(2.0f);
glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2f(16.0,4.4);
    glVertex2f(16.3,4.4);
    glVertex2f(16.3,5.5);
    glVertex2f(16.0,5.5);
    glEnd();
glLineWidth(2.5f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(16.2,4.2);
    glVertex2f(16.2,5.5);
    glEnd();
glBegin(GL_QUADS);
    glColor3ub(145,67,81);
    glVertex2f(17.0,4.4);
    glVertex2f(17.2,4.4);
    glVertex2f(17.2,5.5);
    glVertex2f(17.0,5.5);
    glEnd();
glLineWidth(2.0f);
glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2f(17.0,4.4);
    glVertex2f(17.2,4.4);
    glVertex2f(17.2,5.5);
    glVertex2f(17.0,5.5);
    glEnd();
glBegin(GL_QUADS);
    glColor3ub(145,67,81);
    glVertex2f(18.5,4.4);
    glVertex2f(18.8,4.4);
    glVertex2f(18.8,5.5);
    glVertex2f(18.5,5.5);
    glEnd();
glLineWidth(2.0f);
glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2f(18.5,4.4);
    glVertex2f(18.8,4.4);
    glVertex2f(18.8,5.5);
    glVertex2f(18.5,5.5);
    glEnd();
glLineWidth(2.5f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(18.7,4.2);
    glVertex2f(18.7,5.5);
    glEnd();
glBegin(GL_QUADS);
    glColor3ub(145,67,81);
    glVertex2f(19.4,4.4);
    glVertex2f(19.7,4.4);
    glVertex2f(19.7,5.5);
    glVertex2f(19.4,5.5);
    glEnd();
glLineWidth(2.0f);
glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2f(19.4,4.4);
    glVertex2f(19.7,4.4);
    glVertex2f(19.7,5.5);
    glVertex2f(19.4,5.5);
    glEnd();
glLineWidth(2.5f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(19.5,4.2);
    glVertex2f(19.5,5.5);
    glEnd();
//shoproof
    glBegin(GL_POLYGON);
    glColor3ub(240,189,55);
    glVertex2f(15.3,5.5);
    glVertex2f(20.4,5.5);
    glVertex2f(18.0,7.5);
    glEnd();
glLineWidth(2.0f);
glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2f(15.3,5.5);
    glVertex2f(20.4,5.5);
    glVertex2f(18.0,7.5);
    glEnd();
glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(18.0,7.5);
    glVertex2f(17.4,5.5);
    glEnd();
glBegin(GL_POLYGON);
    glColor3ub(255,162,69);
    glVertex2f(18.0,7.5);
    glVertex2f(18.6,6.78);
    glVertex2f(18.56,6.73);
    glVertex2f(19.2,6.3);
    glVertex2f(19.18,6.18);
    glVertex2f(20.4,5.5);
    glEnd();
glBegin(GL_POLYGON);
    glColor3ub(255,162,69);
    glVertex2f(16.5,5.5);
    glVertex2f(17.4,5.5);
    glVertex2f(18.0,7.5);
    glVertex2f(16.93,6.3);
    glVertex2f(17.25,6.27);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(145,67,81);
    glVertex2f(16.3,2.6);
    glVertex2f(18.7,2.6);
    glVertex2f(18.7,4.2);
    glVertex2f(16.3,4.2);
    glEnd();
glBegin(GL_POLYGON);
    glColor3ub(94,44,71);
    glVertex2f(16.3,3.9);
    glVertex2f(18.7,3.5);
    glVertex2f(18.7,4.2);
    glVertex2f(16.3,4.2);
    glEnd();
glLineWidth(2.5f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(16.8,3.9);
    glVertex2f(18.5,3.9);
    glEnd();
glLineWidth(2.5f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(16.3,3.7);
    glVertex2f(18.5,3.7);
    glEnd();
glLineWidth(2.5f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(16.3,3.4);
    glVertex2f(16.9,3.4);
    glEnd();
glLineWidth(2.5f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(16.6,3.2);
    glVertex2f(18.4,3.2);
    glEnd();



    }
void BoardLighted(){
            //board
    glBegin(GL_POLYGON);
    glColor3ub(148,89,78);
    glVertex2f(15.5, 7);
    glVertex2f(15.9994284432612, 7.2448951300453);
    glVertex2f(15.5, 7.5);
    glVertex2f(20, 7.5);
    glVertex2f(19.5063925100027, 7.2507400701565);
    glVertex2f(20, 7);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(40,36,66);
    glVertex2f(15.5, 7);
    glVertex2f(15.9994284432612, 7.2448951300453);
    glVertex2f(15.5, 7.5);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3ub(1,31,75);
    glVertex2f(15.5, 7);
    glVertex2f(20.0,7.0);
    glVertex2f(19.5063925100027, 7.2507400701565);
    glVertex2f(20.0,7.5);
    glVertex2f(15.5,7.5);
    glVertex2f(15.9994284432612, 7.2448951300453);
    glEnd();

    //J
    glColor3ub(118,165,175);
    glLineWidth(2.5f);
    glBegin(GL_LINES);
    //glColor3ub(10,117,173);
    glVertex2f(16.6, 7.4);
    glVertex2f(16.8952361438692, 7.3999108642741);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(10,117,173);
    glVertex2f(16.79, 7.4);
    glVertex2f(16.7930362584353, 7.1280055342436);
    glEnd();
    drawTiltedHollowSemiCircle(16.6928682149093, 7.1268464103162,0.094,0,false);

    //U
    glBegin(GL_LINES);
    //glColor3ub(10,117,173);
    glVertex2f(17.1101901960062, 7.389376724065);
    glVertex2f(17.1111035674595, 7.1723551347304);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(10,117,173);
    glVertex2f(17.4032373611813, 7.3829552257626);
    glVertex2f(17.4038160747662, 7.1723551347304);
    glEnd();
    drawTiltedHollowSemiCircle(17.25000001212, 7.1713417437256,0.136,0,false);

    //I
    glBegin(GL_LINES);
    //glColor3ub(10,117,173);
    glVertex2f(17.7440680569499, 7.0593799462696);
    glVertex2f(17.7468819698948, 7.4001974609834);
    glEnd();

    //C
    drawTiltedHollowSemiCircle(18.214610197932, 7.2409438074779,0.15,90,true);

    //E
    glBegin(GL_LINES);
    //glColor3ub(10,117,173);
    glVertex2f(18.6037154343155, 7.0956740391545);
    glVertex2f(18.6037123826749, 7.4178389132929);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(10,117,173);
    glVertex2f(18.6037123826749, 7.4178389132929);
    glVertex2f(18.8684100399316, 7.4161715155384);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(10,117,173);
    glVertex2f(18.6,7.3);
    glVertex2f(18.7929831658903, 7.3);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(10,117,173);
    glVertex2f(18.6037154343155, 7.0956740391545);
    glVertex2f(18.8774919210494, 7.0937733372579);
    glEnd();

    //Middle juicebox
    glColor3ub(32,155,56);
    drawTiltedHollowSemiCircle(17.8845747302662, 7.7358241081472,0.20,75.68,false);
    drawTiltedHollowSemiCircle(17.415006140826, 7.7292104660425,0.20,284.32,false);
    glColor3ub(223,0,80);
    drawHollowEllipse(17.6410082807829, 7.9809895131394,0.28,0.09,200);
    glColor3ub(255,190,0);
    glBegin(GL_LINES);
    //glColor3ub(10,117,173);
    glVertex2f(17.7604018291005, 7.88084897367);
    glVertex2f(17.982767272757, 8.4830308250124);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(10,117,173);
    glVertex2f(18.1263472166237, 8.5255143042144);
    glVertex2f(17.982767272757, 8.4830308250124);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(0,200,244);
    glVertex2f(17.6119793380043, 7.9461199278198);
    glVertex2f(17.4, 8.4);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255,229,155);
    glVertex2f(17.4026641732678, 8.1516293622883);
    glVertex2f(17.6140551908777, 8.2398531094087);
    glEnd();
    glBegin(GL_LINES);
    glColor3ub(255,229,155);
    glVertex2f(17.44,8.3);
    glVertex2f(17.6140551908777, 8.2398531094087);
    glEnd();
    glBegin(GL_LINES);
    glColor3ub(255,229,155);
    glVertex2f(17.44,8.3);
    glVertex2f(17.4026641732678, 8.1516293622883);
    glEnd();

    //Left Juicebox
    glLineWidth(2.0);
    glColor3ub(240,105,105);
    glBegin(GL_LINES);
    //glColor3ub(255,229,155);
    glVertex2f(16.9,7.5);
    glVertex2f(16.7271061170485, 7.8207220715546);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(255,229,155);
    glVertex2f(16.76980729577967, 8.05483720488847);
    glVertex2f(16.7271061170485, 7.8207220715546);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(255,229,155);
    glVertex2f(16.76980729577967, 8.05483720488847);
    glVertex2f(16.4884384315571, 7.9266890093019);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(255,229,155);
    glVertex2f(16.6764869601934, 7.7990281471881);
    glVertex2f(16.4884384315571, 7.9266890093019);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(255,229,155);
    glVertex2f(16.6764869601934, 7.7990281471881);
    glVertex2f(16.8051177632278, 7.4991236613211);
    glEnd();
    glLineWidth(1.7);
    glColor3ub(254,198,1);
    drawHollowCircle(16.4884384315571, 7.9266890093019,0.077,200);
    glBegin(GL_LINES);
    //glColor3ub(255,229,155);
    glVertex2f(16.4884384315571, 7.9266890093019);
    glVertex2f(16.5,8.00);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(255,229,155);
    glVertex2f(16.4884384315571, 7.9266890093019);
    glVertex2f(16.45,8.00);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(255,229,155);
    glVertex2f(16.4884384315571, 7.9266890093019);
    glVertex2f(16.41,8.00);
    glEnd();
     glBegin(GL_LINES);
    //glColor3ub(255,229,155);
    glVertex2f(16.4884384315571, 7.9266890093019);
    glVertex2f(16.435,8.00);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(255,229,155);
    glVertex2f(16.4884384315571, 7.9266890093019);
    glVertex2f(16.435,7.86);
    glEnd();
    //Right JuiceBox
}
void BoardNotLighted(){
        glBegin(GL_POLYGON);
    glColor3ub(148,89,78);
    glVertex2f(15.5, 7);
    glVertex2f(15.9994284432612, 7.2448951300453);
    glVertex2f(15.5, 7.5);
    glVertex2f(20, 7.5);
    glVertex2f(19.5063925100027, 7.2507400701565);
    glVertex2f(20, 7);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(40,36,66);
    glVertex2f(15.5, 7);
    glVertex2f(15.9994284432612, 7.2448951300453);
    glVertex2f(15.5, 7.5);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3ub(1,31,75);
    glVertex2f(15.5, 7);
    glVertex2f(20.0,7.0);
    glVertex2f(19.5063925100027, 7.2507400701565);
    glVertex2f(20.0,7.5);
    glVertex2f(15.5,7.5);
    glVertex2f(15.9994284432612, 7.2448951300453);
    glEnd();

    //J
    glColor3ub(255,255,255);
    glLineWidth(2.5f);
    glBegin(GL_LINES);
    //glColor3ub(10,117,173);
    glVertex2f(16.6, 7.4);
    glVertex2f(16.8952361438692, 7.3999108642741);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(10,117,173);
    glVertex2f(16.79, 7.4);
    glVertex2f(16.7930362584353, 7.1280055342436);
    glEnd();
    drawTiltedHollowSemiCircle(16.6928682149093, 7.1268464103162,0.094,0,false);

    //U
    glBegin(GL_LINES);
    //glColor3ub(10,117,173);
    glVertex2f(17.1101901960062, 7.389376724065);
    glVertex2f(17.1111035674595, 7.1723551347304);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(10,117,173);
    glVertex2f(17.4032373611813, 7.3829552257626);
    glVertex2f(17.4038160747662, 7.1723551347304);
    glEnd();
    drawTiltedHollowSemiCircle(17.25000001212, 7.1713417437256,0.136,0,false);

    //I
    glBegin(GL_LINES);
    //glColor3ub(10,117,173);
    glVertex2f(17.7440680569499, 7.0593799462696);
    glVertex2f(17.7468819698948, 7.4001974609834);
    glEnd();

    //C
    drawTiltedHollowSemiCircle(18.214610197932, 7.2409438074779,0.15,90,true);

    //E
    glBegin(GL_LINES);
    //glColor3ub(10,117,173);
    glVertex2f(18.6037154343155, 7.0956740391545);
    glVertex2f(18.6037123826749, 7.4178389132929);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(10,117,173);
    glVertex2f(18.6037123826749, 7.4178389132929);
    glVertex2f(18.8684100399316, 7.4161715155384);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(10,117,173);
    glVertex2f(18.6,7.3);
    glVertex2f(18.7929831658903, 7.3);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(10,117,173);
    glVertex2f(18.6037154343155, 7.0956740391545);
    glVertex2f(18.8774919210494, 7.0937733372579);
    glEnd();

    //Middle juicebox
    //glColor3ub(32,155,56);
    drawTiltedHollowSemiCircle(17.8845747302662, 7.7358241081472,0.20,75.68,false);
    drawTiltedHollowSemiCircle(17.415006140826, 7.7292104660425,0.20,284.32,false);
    //glColor3ub(223,0,80);
    drawHollowEllipse(17.6410082807829, 7.9809895131394,0.28,0.09,200);
    //glColor3ub(255,190,0);
    glBegin(GL_LINES);
    //glColor3ub(10,117,173);
    glVertex2f(17.7604018291005, 7.88084897367);
    glVertex2f(17.982767272757, 8.4830308250124);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(10,117,173);
    glVertex2f(18.1263472166237, 8.5255143042144);
    glVertex2f(17.982767272757, 8.4830308250124);
    glEnd();

    glBegin(GL_LINES);
    //glColor3ub(0,200,244);
    glVertex2f(17.6119793380043, 7.9461199278198);
    glVertex2f(17.4, 8.4);
    glEnd();

    glBegin(GL_LINES);
   // glColor3ub(255,229,155);
    glVertex2f(17.4026641732678, 8.1516293622883);
    glVertex2f(17.6140551908777, 8.2398531094087);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(255,229,155);
    glVertex2f(17.44,8.3);
    glVertex2f(17.6140551908777, 8.2398531094087);
    glEnd();
    glBegin(GL_LINES);
   // glColor3ub(255,229,155);
    glVertex2f(17.44,8.3);
    glVertex2f(17.4026641732678, 8.1516293622883);
    glEnd();

    //Left Juicebox
    glLineWidth(2.0);
    //glColor3ub(240,105,105);
    glBegin(GL_LINES);
    //glColor3ub(255,229,155);
    glVertex2f(16.9,7.5);
    glVertex2f(16.7271061170485, 7.8207220715546);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(255,229,155);
    glVertex2f(16.76980729577967, 8.05483720488847);
    glVertex2f(16.7271061170485, 7.8207220715546);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(255,229,155);
    glVertex2f(16.76980729577967, 8.05483720488847);
    glVertex2f(16.4884384315571, 7.9266890093019);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(255,229,155);
    glVertex2f(16.6764869601934, 7.7990281471881);
    glVertex2f(16.4884384315571, 7.9266890093019);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(255,229,155);
    glVertex2f(16.6764869601934, 7.7990281471881);
    glVertex2f(16.8051177632278, 7.4991236613211);
    glEnd();
    glLineWidth(1.7);
    //glColor3ub(254,198,1);
    drawHollowCircle(16.4884384315571, 7.9266890093019,0.077,200);
    glBegin(GL_LINES);
    //glColor3ub(255,229,155);
    glVertex2f(16.4884384315571, 7.9266890093019);
    glVertex2f(16.5,8.00);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(255,229,155);
    glVertex2f(16.4884384315571, 7.9266890093019);
    glVertex2f(16.45,8.00);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(255,229,155);
    glVertex2f(16.4884384315571, 7.9266890093019);
    glVertex2f(16.41,8.00);
    glEnd();
     glBegin(GL_LINES);
    //glColor3ub(255,229,155);
    glVertex2f(16.4884384315571, 7.9266890093019);
    glVertex2f(16.435,8.00);
    glEnd();
    glBegin(GL_LINES);
    //glColor3ub(255,229,155);
    glVertex2f(16.4884384315571, 7.9266890093019);
    glVertex2f(16.435,7.86);
    glEnd();

}

//#S4_2SurfBoards
void SurfBoard(){
    //Board1
glColor3ub(135,206,235);
drawTiltedFilledEllipse(14.6,3.8,1.39,0.33,92,100);
glColor3ub(0,0,0);
glLineWidth(2.0f);
drawTiltedHollowEllipse(14.6,3.8,1.39,0.33,92,100);
glLineWidth(5.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(14.23,3.8);
    glVertex2f(14.60,4.2);
    glEnd();
glLineWidth(5.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(14.95,3.8);
    glVertex2f(14.55,4.2);
    glEnd();
    //Board2
glColor3ub(106,139,65);
drawTiltedFilledEllipse(15.5,3.8,1.37,0.34,73,100);
glColor3ub(0,0,0);
glLineWidth(2.0f);
drawTiltedHollowEllipse(15.5,3.8,1.37,0.34,73,100);
glLineWidth(8.5f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(15.9,5.1);
    glVertex2f(15.1,2.5);
    glEnd();
}

void three_Leaves(){
    //Leaf1
    glPushMatrix();
     glTranslatef(0.0f, 0.0f, 0.0f);
     glRotatef(LeftLeafAngle, 0.0f, 0.0f, 1.0f);
glBegin(GL_POLYGON);
glColor3ub(21,71,52);
    glVertex2f(19.8772635553422, 2.7727674976646);
    glVertex2f(19.825507402781, 3.1932862372247);
    glVertex2f(19.7381688953339, 3.1997557562948);
    glVertex2f(19.7844026539455, 3.2667253842175);
    glVertex2f(19.6837674348399, 3.4194133028604);
    glVertex2f(19.5206689762895, 3.3482746134927);
    glVertex2f(19.6473305451638, 3.4662607324441);
    glVertex2f(19.609158565503, 3.5148432520123);
    glVertex2f(19.5067882564129, 3.5165783419968);
    glVertex2f(19.5224040662741, 3.598127571272);
    glVertex2f(19.4460601069526, 3.6692662606398);
    glVertex2f(19.3454248878471, 3.598127571272);
    glVertex2f(19.3436897978625, 3.7386698600229);
    glVertex2f(19.00,3.9);
    glVertex2f(19.0088174308388, 3.7143786002388);
    glVertex2f(19.0868964801449, 3.6744715305935);
    glVertex2f(19.045254320515, 3.5998626612566);
    glVertex2f(19.1424193596514, 3.3812413231997);
    glVertex2f(19.2750441386974, 3.4136477763378);
    glVertex2f(19.1875316992504, 3.3343938936161);
    glVertex2f(19.3679810576466, 3.067190035991);
    glVertex2f(19.4634110067984, 3.0446338661914);
    glVertex2f(19.4946426265208, 2.9422635571013);
    glEnd();
    glLineWidth(1.5);
glBegin(GL_LINE_LOOP);
glColor3ub(0,0,0);
    glVertex2f(19.8772635553422, 2.7727674976646);
    glVertex2f(19.825507402781, 3.1932862372247);
    glVertex2f(19.7381688953339, 3.1997557562948);
    glVertex2f(19.7844026539455, 3.2667253842175);
    glVertex2f(19.6837674348399, 3.4194133028604);
    glVertex2f(19.5206689762895, 3.3482746134927);
    glVertex2f(19.6473305451638, 3.4662607324441);
    glVertex2f(19.609158565503, 3.5148432520123);
    glVertex2f(19.5067882564129, 3.5165783419968);
    glVertex2f(19.5224040662741, 3.598127571272);
    glVertex2f(19.4460601069526, 3.6692662606398);
    glVertex2f(19.3454248878471, 3.598127571272);
    glVertex2f(19.3436897978625, 3.7386698600229);
    glVertex2f(19.00,3.9);
    glVertex2f(19.0088174308388, 3.7143786002388);
    glVertex2f(19.0868964801449, 3.6744715305935);
    glVertex2f(19.045254320515, 3.5998626612566);
    glVertex2f(19.1424193596514, 3.3812413231997);
    glVertex2f(19.2750441386974, 3.4136477763378);
    glVertex2f(19.1875316992504, 3.3343938936161);
    glVertex2f(19.3679810576466, 3.067190035991);
    glVertex2f(19.4634110067984, 3.0446338661914);
    glVertex2f(19.4946426265208, 2.9422635571013);
    glEnd();
glLineWidth(1.5);
drawTiltedUpperHollowEllipse(19.493365139957, 3.2562580268776,0.62,0.04,130,100);
    glPopMatrix();
    //Leaf2

    glBegin(GL_POLYGON);
glColor3ub(107,148,100);
    glVertex2f(19.8772635553422, 2.7727674976646);
    glVertex2f(20.1919980965359, 3.2896706652112);
    glVertex2f(20.104815036604, 3.3735005305303);
    glVertex2f(20.2959471295316, 3.3399685844027);
    glVertex2f(20.3563046325614, 3.5713390126835);
    glVertex2f(20.1685257342465, 3.678641240292);
    glVertex2f(20.3797769948507, 3.6384029049388);
    glVertex2f(20.3965429679145, 3.7289391594834);
    glVertex2f(20.3261258810465, 3.8228286086409);
    glVertex2f(20.4367813032677, 3.8697733332196);
    glVertex2f(20.4501940817188, 3.9904883392791);
    glVertex2f(20.2959471295316, 4.0441394530834);
    glVertex2f(20.4535472763316, 4.1547948753046);
    glVertex2f(20.3428918541103, 4.6275953157045);
    glVertex2f(20.1651725396337, 4.449876001228);
    glVertex2f(20.1783002816226, 4.3565283126194);
    glVertex2f(20.082040167697, 4.3417190643232);
    glVertex2f(20.016986236501, 4.2453763066778);
    glVertex2f(20.040166207312, 4.12368145992);
    glVertex2f(19.9340472419433, 4.0652950252052);
    glVertex2f(20.0510736574186, 3.9748655223379);
    glVertex2f(19.9, 4);
    glVertex2f(19.7638270012519, 3.6042818733327);
    glVertex2f(19.8117014439463, 3.4677510552781);
    glVertex2f(19.72, 3.36);
    glEnd();
    glLineWidth(1.5);
glBegin(GL_LINE_LOOP);
glColor3ub(0,0,0);
    glVertex2f(19.8772635553422, 2.7727674976646);
    glVertex2f(20.1919980965359, 3.2896706652112);
    glVertex2f(20.104815036604, 3.3735005305303);
    glVertex2f(20.2959471295316, 3.3399685844027);
    glVertex2f(20.3563046325614, 3.5713390126835);
    glVertex2f(20.1685257342465, 3.678641240292);
    glVertex2f(20.3797769948507, 3.6384029049388);
    glVertex2f(20.3965429679145, 3.7289391594834);
    glVertex2f(20.3261258810465, 3.8228286086409);
    glVertex2f(20.4367813032677, 3.8697733332196);
    glVertex2f(20.4501940817188, 3.9904883392791);
    glVertex2f(20.2959471295316, 4.0441394530834);
    glVertex2f(20.4535472763316, 4.1547948753046);
    glVertex2f(20.3428918541103, 4.6275953157045);
    glVertex2f(20.1651725396337, 4.449876001228);
    glVertex2f(20.1783002816226, 4.3565283126194);
    glVertex2f(20.082040167697, 4.3417190643232);
    glVertex2f(20.016986236501, 4.2453763066778);
    glVertex2f(20.040166207312, 4.12368145992);
    glVertex2f(19.9340472419433, 4.0652950252052);
    glVertex2f(20.0510736574186, 3.9748655223379);
    glVertex2f(19.9, 4);
    glVertex2f(19.7638270012519, 3.6042818733327);
    glVertex2f(19.8117014439463, 3.4677510552781);
    glVertex2f(19.72, 3.36);
    glEnd();
glLineWidth(1.5);
drawTiltedUpperHollowEllipse(20.07, 3.76,0.67,0.034,73,100);
    //Leaf3
    glPushMatrix();
    glTranslatef(0.0,0.0,0.0);
    glRotatef(LeftLeafAngle,0.0,0.0,1.0);


    glBegin(GL_POLYGON);
glColor3ub(31,134,70);
    glVertex2f(19.8772635553422, 2.7727674976646);
    glVertex2f(20.3276649238026, 2.9034306362164);
    glVertex2f(20.3276649238026, 2.9881965317617);
    glVertex2f(20.3990150012817, 2.9451315910073);
    glVertex2f(20.5506855410139, 3.0406278567646);
    glVertex2f(20.4817143522996, 3.2179710775231);
    glVertex2f(20.6030499560738, 3.0779975115735);
    glVertex2f(20.6585305690028, 3.1214823163016);
    glVertex2f(20.6570310929777, 3.239940922285);
    glVertex2f(20.7544970346097, 3.2219472099838);
    glVertex2f(20.8129765995889, 3.2924225831638);
    glVertex2f(20.7290059421829, 3.4093817131222);
    glVertex2f(20.9, 3.4);
    glVertex2f(21.0738854279576, 3.7857501954241);
    glVertex2f(20.8639587844425, 3.7602591029973);
    glVertex2f(20.8249724077897, 3.6702905414908);
    glVertex2f(20.7604949387101, 3.7272706304449);
    glVertex2f(20.5085829664921, 3.6133104525368);
    glVertex2f(20.5505682951951, 3.490353418478);
    glVertex2f(20.4635986857388, 3.5848204080597);
    glVertex2f(20.2, 3.4);
    glVertex2f(20.144210292391, 3.2759283468876);
    glVertex2f(20.0302501144828, 3.239940922285);
    //glVertex2f()
    glEnd();
glLineWidth(1.5);
glBegin(GL_LINE_LOOP);
glColor3ub(0,0,0);
    glVertex2f(19.8772635553422, 2.7727674976646);
    glVertex2f(20.3276649238026, 2.9034306362164);
    glVertex2f(20.3276649238026, 2.9881965317617);
    glVertex2f(20.3990150012817, 2.9451315910073);
    glVertex2f(20.5506855410139, 3.0406278567646);
    glVertex2f(20.4817143522996, 3.2179710775231);
    glVertex2f(20.6030499560738, 3.0779975115735);
    glVertex2f(20.6585305690028, 3.1214823163016);
    glVertex2f(20.6570310929777, 3.239940922285);
    glVertex2f(20.7544970346097, 3.2219472099838);
    glVertex2f(20.8129765995889, 3.2924225831638);
    glVertex2f(20.7290059421829, 3.4093817131222);
    glVertex2f(20.9, 3.4);
    glVertex2f(21.0738854279576, 3.7857501954241);
    glVertex2f(20.8639587844425, 3.7602591029973);
    glVertex2f(20.8249724077897, 3.6702905414908);
    glVertex2f(20.7604949387101, 3.7272706304449);
    glVertex2f(20.5085829664921, 3.6133104525368);
    glVertex2f(20.5505682951951, 3.490353418478);
    glVertex2f(20.4635986857388, 3.5848204080597);
    glVertex2f(20.2, 3.4);
    glVertex2f(20.144210292391, 3.2759283468876);
    glVertex2f(20.0302501144828, 3.239940922285);
    glEnd();
drawLowerHollowTiltedEllipse(20.46,3.32,0.53,0.03,40,200);
glPopMatrix();

}
void RightBallon(){

    glPushMatrix();
    glTranslatef(RightBallonX,0.0f, 0.0f);
    glColor3ub(148,0,0);
drawFilledCircle(25.6,14.06,0.93,200);
    glColor3ub(0,0,0);
    glLineWidth(2.0);
drawHollowCircle(25.6,14.06,0.93,200);
drawLowerHollowTiltedEllipse(25.6,14.06,0.915,0.15,720,200);
//strings
glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(25.9,13.9);
    glVertex2f(25.73,12.49);
    glEnd();
glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(25.26,13.9);
    glVertex2f(25.47,12.50);
    glEnd();
glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(24.93,13.95);
    glVertex2f(25.32,12.49);
    glEnd();
glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(24.65,14.1);
    glVertex2f(25.22,12.5);
    glEnd();
glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(26.25,13.95);
    glVertex2f(25.90,12.49);
    glEnd();
glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(26.50,14.01);
    glVertex2f(26.01,12.49);
    glEnd();
    //body
glBegin(GL_QUADS);
    glColor3ub(109,77,43);
    glVertex2f(25.2,11.9);
    glVertex2f(26.01,11.9);
    glVertex2f(26.01,12.5);
    glVertex2f(25.2,12.5);
    glEnd();
drawFilledEllipse(25.62,11.9,0.38,0.06);
glColor3ub(0,0,0);
    glLineWidth(2.0);
drawLowerHollowTiltedEllipse(25.62,11.9,0.38,0.06,0,200);
glColor3ub(109,77,43);
drawFilledEllipse(25.6,12.5,0.38,0.06);
glColor3ub(0,0,0);
glLineWidth(2.0);
drawHollowEllipse(25.6,12.5,0.38,0.06,200);
glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(25.22,11.9);
    glVertex2f(25.22,12.5);
    glEnd();
glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(26.01,12.5);
    glVertex2f(26.01,11.9);
    glEnd();
    glPopMatrix();

}
void LeftBallon(){
glPushMatrix();
    glTranslatef(LeftBallonX,0.0f, 0.0f);
    glColor3ub(115,56,160);
drawFilledCircle(15.2,12.7,0.86,200);
    glColor3ub(0,0,0);
    glLineWidth(2.0);
drawHollowCircle(15.2,12.7,0.86,200);
drawLowerHollowTiltedEllipse(15.2,12.6,0.85,0.21,0,200);
glBegin(GL_LINES);
    glVertex2f(14.9,12.4);
    glVertex2f(15.1,11.2);
    glEnd();
glBegin(GL_LINES);
    glVertex2f(14.6,12.45);
    glVertex2f(15.0,11.2);
    glEnd();
glBegin(GL_LINES);
    glVertex2f(14.34,12.6);
    glVertex2f(14.9,11.2);
    glEnd();
glBegin(GL_LINES);
    glVertex2f(15.3,11.2);
    glVertex2f(15.5,12.4);
    glEnd();
glBegin(GL_LINES);
    glVertex2f(15.8,12.46);
    glVertex2f(15.5,11.2);
    glEnd();
glBegin(GL_LINES);
    glVertex2f(16.06,12.6);
    glVertex2f(15.6,11.2);
    glEnd();
//body
glBegin(GL_QUADS);
    glColor3ub(109,77,43);
    glVertex2f(14.85,10.5);
    glVertex2f(15.65,10.5);
    glVertex2f(15.65,11.2);
    glVertex2f(14.85,11.2);
    glEnd();
drawFilledEllipse(15.25,10.5,0.38,0.07);
glColor3ub(0,0,0);
drawLowerHollowTiltedEllipse(15.25,10.5,0.38,0.07,0,200);
glColor3ub(109,77,43);
drawFilledEllipse(15.25,11.2,0.38,0.07);
glColor3ub(0,0,0);
drawHollowEllipse(15.25,11.2,0.38,0.07,200);
glBegin(GL_LINES);
    glVertex2f(14.85,11.2);
    glVertex2f(14.85,10.5);
    glEnd();
glBegin(GL_LINES);
    glVertex2f(15.65,11.2);
    glVertex2f(15.65,10.5);
    glEnd();

    glPopMatrix();
}
void Stones(){
    //Stone1
glBegin(GL_POLYGON);
    glColor3ub(123,79,68);
    glVertex2f(28.7,0.0);
    glVertex2f(30.0,0.0);
    glVertex2f(30.0,1.0);
    glVertex2f(29.6,1.2);
    glVertex2f(29.3,0.99);
    glVertex2f(29.3,0.66);
    glEnd();
    glLineWidth(2.0);
/*glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2f(28.7,0.0);
    glVertex2f(30.0,0.0);
    glVertex2f(30.0,1.0);
    glVertex2f(29.6,1.2);
    glVertex2f(29.3,0.99);
    glVertex2f(29.3,0.66);
    glEnd();*/
    //Stone2
    glBegin(GL_POLYGON);
    glColor3ub(123,79,68);
    glVertex2f(29.6,1.2);
    glVertex2f(29.3,1.2);
    glVertex2f(29.1,1.3);
    glVertex2f(28.4654195020674, 1.0733558197022);
    glVertex2f(27.7981680049524, 0.2967430523521);
    glVertex2f(28.1985784777704, 0.0872975742627);
    glVertex2f(28.7098718507534, 0.0235853259022);
    glVertex2f(29.3092963170291, 0.9962416950204);
    glVertex2f(29.1,1.3);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(62,39,35);
    glVertex2f(27.7981680049524, 0.2967430523521);
    glVertex2f(28.1985784777704, 0.0872975742627);
    glVertex2f(28.6428328880332, 0.9001054380701);
    glVertex2f(29.6123001680084, 1.250764929843);
    glVertex2f(29.3521346120808, 1.2237118600958);
    glVertex2f(29.1169623437729, 1.3085280880101);
    glVertex2f(28.4654195020674, 1.0733558197022);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2f(29.6,1.2);
    glVertex2f(29.3,1.2);
    glVertex2f(29.1,1.3);
    glVertex2f(28.4654195020674, 1.0733558197022);
    glVertex2f(27.7981680049524, 0.2967430523521);
    glVertex2f(28.1985784777704, 0.0872975742627);
    glVertex2f(28.7098718507534, 0.0235853259022);
    glVertex2f(29.3092963170291, 0.9962416950204);
    glVertex2f(29.1,1.3);
    glEnd();
    //Stone3
    glBegin(GL_POLYGON);
    glColor3ub(123,79,68);
    glVertex2f(27.4901599489385, 0.6601925584484);
    glVertex2f(27.5825623657427, 0.4630674025996);
    glVertex2f(27.7981680049524, 0.2967430523521);
    glVertex2f(28.4654195020674, 1.0733558197022);
    glVertex2f(28.2416996056123, 1.1899664147922);
    glVertex2f(27.9028907439971, 1.0852436757475);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2f(27.4901599489385, 0.6601925584484);
    glVertex2f(27.5825623657427, 0.4630674025996);
    glVertex2f(27.7981680049524, 0.2967430523521);
    glVertex2f(28.4654195020674, 1.0733558197022);
    glVertex2f(28.2416996056123, 1.1899664147922);
    glVertex2f(27.9028907439971, 1.0852436757475);
    glEnd();
    //Stone4
    glBegin(GL_POLYGON);
    glColor3ub(62,39,35);
    glVertex2f(25.7374752257486, 0.7204284547293);
    glVertex2f(27.0629417379546, 0.4343145379976);
    glVertex2f(27.5825623657427, 0.4630674025996);
    glVertex2f(27.4901599489385, 0.6601925584484);
    glVertex2f(27.4366415475633, 0.8839221214331);
    glVertex2f(26.4673576663907, 1.5904483239746);
    glVertex2f(26.5315873211672, 1.4094374786954);
    glVertex2f(26.0177500829552, 1.1291626214888);
    glVertex2f(27.5825623657427, 0.4630674025996);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2f(25.7374752257486, 0.7204284547293);
    glVertex2f(27.0629417379546, 0.4343145379976);
    glVertex2f(27.5825623657427, 0.4630674025996);
    glVertex2f(27.4901599489385, 0.6601925584484);
    glVertex2f(27.4366415475633, 0.8839221214331);
    glVertex2f(26.4673576663907, 1.5904483239746);
    glVertex2f(26.5315873211672, 1.4094374786954);
    glVertex2f(26.0177500829552, 1.1291626214888);
    glVertex2f(27.5825623657427, 0.4630674025996);
    glEnd();
    //Stone5
    glBegin(GL_POLYGON);
    glColor3ub(123,79,68);
    glVertex2f(24.2717032220415, 1.405672267292);
    glVertex2f(24.8072660737938, 0.9724079377846);
    glVertex2f(25.7374752257486, 0.7204284547293);
    glVertex2f(26.0177500829552, 1.1291626214888);
    glVertex2f(26.5315873211672, 1.4094374786954);
    glVertex2f(26.4673576663907, 1.5904483239746);
    glVertex2f(26.3056385466738, 1.6764624732341);
    glVertex2f(25.6798122929408, 1.532041030065);
    glVertex2f(25.2826533242256, 1.6824800333662);
    glVertex2f(24.9938104378873, 1.4237249476881);
    glVertex2f(24.9035470359066, 1.6704449131021);
    glVertex2f(24.4763002665312, 1.6283219921778);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2f(24.2717032220415, 1.405672267292);
    glVertex2f(24.8072660737938, 0.9724079377846);
    glVertex2f(25.7374752257486, 0.7204284547293);
    glVertex2f(26.0177500829552, 1.1291626214888);
    glVertex2f(26.5315873211672, 1.4094374786954);
    glVertex2f(26.4673576663907, 1.5904483239746);
    glVertex2f(26.3056385466738, 1.6764624732341);
    glVertex2f(25.6798122929408, 1.532041030065);
    glVertex2f(25.2826533242256, 1.6824800333662);
    glVertex2f(24.9938104378873, 1.4237249476881);
    glVertex2f(24.9035470359066, 1.6704449131021);
    glVertex2f(24.4763002665312, 1.6283219921778);
    glEnd();
    //Stone6
    glBegin(GL_POLYGON);
    glColor3ub(123,79,68);
    glVertex2f(22.8888679036969, 1.6734536931681);
    glVertex2f(23, 1.4);
    glVertex2f(23.5626744243839, 1.10702935074);
    glVertex2f(24.0961198318958, 1.3247621701325);
    glVertex2f(24.4763002665312, 1.6283219921778);
    glVertex2f(24.0671061775519, 1.7859820676374);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(62,39,35);
    glVertex2f(22.8888679036969, 1.6734536931681);
    glVertex2f(23, 1.4);
    glVertex2f(23.3304260836985, 1.2449268030219);
    glVertex2f(24.0671061775519, 1.7859820676374);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2f(22.8888679036969, 1.6734536931681);
    glVertex2f(23, 1.4);
    glVertex2f(23.5626744243839, 1.10702935074);
    glVertex2f(24.0961198318958, 1.3247621701325);
    glVertex2f(24.4763002665312, 1.6283219921778);
    glVertex2f(24.0671061775519, 1.7859820676374);
    glEnd();
    //Stone7
    glBegin(GL_POLYGON);
    glColor3ub(123,79,68);
    glVertex2f(22.8888679036969, 1.6734536931681);
    glVertex2f(24.0671061775519, 1.7859820676374);
    glVertex2f(23.5882908756111, 2.7599952300084);
    glVertex2f(22.6413160145788, 2.3833575011887);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(62,39,35);
    glVertex2f(22.8888679036969, 1.6734536931681);
    glVertex2f(23.0400572812497, 2.1862852006721);
    glVertex2f(23.5882908756111, 2.7599952300084);
    glVertex2f(22.6413160145788, 2.3833575011887);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2f(22.8888679036969, 1.6734536931681);
    glVertex2f(24.0671061775519, 1.7859820676374);
    glVertex2f(23.5882908756111, 2.7599952300084);
    glVertex2f(22.6413160145788, 2.3833575011887);
    glEnd();
    //Stone8
    glBegin(GL_POLYGON);
    glColor3ub(62,39,35);
    glVertex2f(27.104200522918, 1.8292441759069);
    glVertex2f(27.8705126881371, 1.5629831693477);
    glVertex2f(27.5912633397946, 3.6735887091462);
    glVertex2f(27.3250023332354, 3.4917519241789);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2f(27.104200522918, 1.8292441759069);
    glVertex2f(27.8705126881371, 1.5629831693477);
    glVertex2f(27.5912633397946, 3.6735887091462);
    glVertex2f(27.3250023332354, 3.4917519241789);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(123,79,68);
    glVertex2f(27.8705126881371, 1.5629831693477);
    glVertex2f(28.4160230430389, 1.7578082960984);
    glVertex2f(27.5912633397946, 3.6735887091462);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2f(27.8705126881371, 1.5629831693477);
    glVertex2f(28.4160230430389, 1.7578082960984);
    glVertex2f(27.5912633397946, 3.6735887091462);
    glEnd();

}
void BeachBall(){
glPushMatrix();
glTranslatef(BallPositionX,3.0f,0.0f);
glRotatef(BallAngle,0.0f,0.0f,1.0f);
glColor3ub(218,248,227);
drawFilledCircle(0.0,0.0,ballRadius,200);
glColor3ub(0,0,0);
drawHollowCircle(0.0,0.0,ballRadius,200);
glColor3ub(0,0,0);
drawFilledCircle(0.13,0.18,0.05,200);
drawHollowCircle(0.13,0.18,0.05,200);

//semi-circle stripes
drawTiltedHollowSemiCircle(0.29,0.5,0.4,45,true);
drawTiltedHollowSemiCircle(0.55,0.63,0.7,80,true);
glPopMatrix();
}

//Update functions
UpdateRightBallonPos(){
 RightBallonX -= RightBallonSpeed;
    if (RightBallonX >4 || RightBallonX <-4) {
        RightBallonSpeed = -RightBallonSpeed;
    }
}
UpdateLeftBallonPos(){
LeftBallonX+=LeftBallonSpeed;
if(LeftBallonX>2 || LeftBallonX<-2){
    LeftBallonSpeed= - LeftBallonSpeed;
}
}
UpdateLeftLeaf(){
LeftLeafAngle+=LeftLeafRotSpeed;
if (LeftLeafAngle >15.0 || LeftLeafAngle <-15.0){
    LeftLeafRotSpeed=-LeftLeafRotSpeed;
}
}

UpdateBallpos(){
    BallPositionX += BallSpeed;
    if(BallPositionX >=180.0){
    BallPositionX =- ballRadius*2;
    }

    float circumference = 2 * PI * ballRadius;
    BallAngle -= (360.0f * BallSpeed) / circumference;

}

void UpdateJuiceSign(int value){
    JuiceSignelapsedTime+=value;
    if (JuiceSignelapsedTime>=1000){
        JuiceSignVisible = !JuiceSignVisible;
        JuiceSignelapsedTime = 0;
    }
}
void updateStars(int value) {
    static int elapsedTime = 0;
    elapsedTime += value;

    if (elapsedTime >= 1000) {
        for (int i = 0; i < numStars; i++) {
            starVisible[i] = rand() % 4;
        }
        elapsedTime = 0;
    }
    for (int i = 0; i < numStars; i++) {
        if (starVisible[i]) {
            starBrightness[i] += randomFloat(-0.05, 0.05);
            if (starBrightness[i] > 1.0) starBrightness[i] = 1.0;
            if (starBrightness[i] < 0.5) starBrightness[i] = 0.5;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(50, updateStars, 0);
}
void UpdateWave1(){
Wave1X-=Wave1Speed;
if (Wave1X>0.4 || Wave1X<-0.4){
    Wave1Speed= - Wave1Speed;
}
}
void UpdateWave2(){
Wave2X-=Wave2Speed;
if (Wave2X>0.4 || Wave2X<-0.4){
    Wave2Speed= - Wave2Speed;
}
}
void UpdateWave3(){
Wave3X-=Wave3Speed;
if (Wave2X>0.4 || Wave2X<-0.4){
    Wave3Speed= - Wave3Speed;
}
}

//main update
void update(int value) {
    UpdateRightBallonPos();
    UpdateLeftBallonPos();
    // UpdateLeftLeaf();
   // UpdateBallpos();


    UpdateJuiceSign(value);
    updateStars(value);
    UpdateWave1();
    UpdateWave2();
    UpdateWave3();


    glutPostRedisplay();
    glutTimerFunc(50, update, 50);
}








// River Scene Implementation (Placeholder - replace with your friend's actual implementation)
void initRiverScene() {
    // Initialize river scene-specific settings
    glClearColor(0.0f, 0.5f, 0.8f, 1.0f);  // Water blue background
}

void displayRiverScene() {
     SoilAndDetails();
    SurfBoard();
    SoilStrip();
    SkyAndClouds();
    Stars();
    Cloud1();
    SeaWater();
    Wave1();
    Wave2();
    Wave3();
    BeachJuiceShop();
    if(JuiceSignVisible==true){
        BoardLighted();
    }else{
     BoardNotLighted();
     }
    three_Leaves();
    RightBallon();
    LeftBallon();
    Stones();
    //BeachBall();
    BusStand();

}

































void first_road() {

glLineWidth(1.0f);
// 1st road down 1st part
glBegin(GL_POLYGON);
glColor3f(1, 1, 1);
glVertex2f(0,0.5);
glVertex2f(14, 0.5);
glVertex2f(14, 0);
glVertex2f(0,0);


glEnd();




// 1st road down 2nd part
glBegin(GL_POLYGON);
glColor3f(1, 1, 1);
glVertex2f(18, 0.5);
glVertex2f(30, 0.5);
glVertex2f(30, 0);
glVertex2f(18,0);
glEnd();


}

void first_left_middle_road()
{
    glLineWidth(1.0f);
    glBegin(GL_POLYGON);
glColor3f(0.2667f, 0.3059f, 0.3529f);

glVertex2f(0,3);
glVertex2f(30,3);
glVertex2f(30, 0.5);
glVertex2f(0,0.5);
glEnd();

// midline of the road
   glBegin(GL_POLYGON);
glColor3f(1, 1, 1);
glVertex2f(1, 1.8);
glVertex2f(3, 1.8);
glVertex2f(3, 1.6);
glVertex2f(1, 1.6);
glEnd();


// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(1, 1.8);
glVertex2f(3, 1.8);
glVertex2f(3, 1.6);
glVertex2f(1, 1.6);
glEnd();

//2
   glBegin(GL_POLYGON);
glColor3f(1, 1, 1);
glVertex2f(5.6, 1.8);
glVertex2f(7.4, 1.8);
glVertex2f(7.4, 1.6);
glVertex2f(5.6, 1.6);
glEnd();


// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(5.6, 1.8);
glVertex2f(7.4, 1.8);
glVertex2f(7.4, 1.6);
glVertex2f(5.6, 1.6);
glEnd();

//3
   glBegin(GL_POLYGON);
glColor3f(1, 1, 1);
glVertex2f(10.2, 1.8);
glVertex2f(12, 1.8);
glVertex2f(12, 1.6);
glVertex2f(10.2, 1.6);
glEnd();


// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(10.2, 1.8);
glVertex2f(12, 1.8);
glVertex2f(12, 1.6);
glVertex2f(10.2, 1.6);
glEnd();


//4

   glBegin(GL_POLYGON);
glColor3f(1, 1, 1);
glVertex2f(14.6, 1.8);
glVertex2f(16.8, 1.8);
glVertex2f(16.8, 1.6);
glVertex2f(14.6, 1.6);
glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(14.6, 1.8);
glVertex2f(16.8, 1.8);
glVertex2f(16.8, 1.6);
glVertex2f(14.6, 1.6);
glEnd();


//5
   glBegin(GL_POLYGON);
glColor3f(1, 1, 1);
glVertex2f(19.6, 1.8);
glVertex2f(21.8, 1.8);
glVertex2f(21.8, 1.6);
glVertex2f(19.6, 1.6);
glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(19.6, 1.8);
glVertex2f(21.8, 1.8);
glVertex2f(21.8, 1.6);
glVertex2f(19.6, 1.6);
glEnd();


//6
   glBegin(GL_POLYGON);
glColor3f(1, 1, 1);
glVertex2f(24.2, 1.8);
glVertex2f(26, 1.8);
glVertex2f(26, 1.6);
glVertex2f(24.2, 1.6);
glEnd();


// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(24.2, 1.8);
glVertex2f(26, 1.8);
glVertex2f(26, 1.6);
glVertex2f(24.2, 1.6);
glEnd();



//7
   glBegin(GL_POLYGON);
glColor3f(1, 1, 1);
glVertex2f(28, 1.8);
glVertex2f(29.4, 1.8);
glVertex2f(29.4, 1.6);
glVertex2f(28, 1.6);
glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(28, 1.8);
glVertex2f(29.4, 1.8);
glVertex2f(29.4, 1.6);
glVertex2f(28, 1.6);
glEnd();





//second middle road between the house

        glBegin(GL_POLYGON);
glColor3f(0.2667f, 0.3059f, 0.3529f);

glVertex2f(14,15);
glVertex2f(17.99,15);
glVertex2f(18,0);
glVertex2f(14, 0);

glEnd();


// second middle road between the house middle line
//1
glBegin(GL_POLYGON);
glColor3f(1, 1, 1);
glVertex2f(15.9, 14.6);
glVertex2f(16.1, 14.6);
glVertex2f(16.1, 13.6);
glVertex2f(15.9, 13.6);
glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(15.9, 14.6);
glVertex2f(16.1, 14.6);
glVertex2f(16.1, 13.6);
glVertex2f(15.9, 13.6);
glEnd();


//2
glBegin(GL_POLYGON);
glColor3f(1, 1, 1);
glVertex2f(15.9, 12.4);
glVertex2f(16.1, 12.4);
glVertex2f(16.1, 11.4);
glVertex2f(15.9, 11.4);
glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(15.9, 12.4);
glVertex2f(16.1, 12.4);
glVertex2f(16.1, 11.4);
glVertex2f(15.9, 11.4);
glEnd();

//3
glBegin(GL_POLYGON);
glColor3f(1, 1, 1);
glVertex2f(15.9, 10.2);
glVertex2f(16.1, 10.2);
glVertex2f(16.1, 9.2);
glVertex2f(15.9, 9.2);
glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(15.9, 10.2);
glVertex2f(16.1, 10.2);
glVertex2f(16.1, 9.2);
glVertex2f(15.9, 9.2);
glEnd();



//4
glBegin(GL_POLYGON);
glColor3f(1, 1, 1);
glVertex2f(15.9, 8);
glVertex2f(16.1, 8);
glVertex2f(16.1, 7);
glVertex2f(15.9, 7);
glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(15.9, 8);
glVertex2f(16.1, 8);
glVertex2f(16.1, 7);
glVertex2f(15.9, 7);
glEnd();

//5
glBegin(GL_POLYGON);
glColor3f(1, 1, 1);
glVertex2f(15.9, 5.2);
glVertex2f(16.1, 5.2);
glVertex2f(16.1, 4);
glVertex2f(15.9, 4);
glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(15.9, 5.2);
glVertex2f(16.1, 5.2);
glVertex2f(16.1, 4);
glVertex2f(15.9, 4);
glEnd();




}
void first_box()
{
    //1st box fll color with white
glBegin(GL_POLYGON);
glColor3f(1, 1, 1);
glVertex2f(0, 15);
glVertex2f(14,15);
glVertex2f(14, 3);
glVertex2f(0, 3);

glEnd();

//2nd box fill with white
glBegin(GL_POLYGON);
glColor3f(1, 1, 1);
glVertex2f(17.99, 15);
glVertex2f(30, 15);
glVertex2f(30, 3);
glVertex2f(18, 3);

glEnd();

}
void first_housee()
{
    glLineWidth(1);
    //body
glBegin(GL_POLYGON);
glColor3f(0.9922f, 0.3529f, 0.4667f);
glVertex2f(0,10);
glVertex2f(3.5, 10);
glVertex2f(3.5, 5);
glVertex2f(0,5);

glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(0,10);
glVertex2f(3.5, 10);
glVertex2f(3.5, 5);
glVertex2f(0,5);
glEnd();

    //door up
    //1st
    glBegin(GL_POLYGON);
glColor3f(0.0980f, 0.2706f, 0.4039f);
glVertex2f(0.25, 6.2);
glVertex2f(0.9997, 6.2);
glVertex2f(1, 5.95);
glVertex2f(0.25, 5.95);
glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(0.25, 6.2);
glVertex2f(0.9997, 6.2);
glVertex2f(1, 5.95);
glVertex2f(0.25, 5.95);
glEnd();

    //2nd
    glBegin(GL_POLYGON);
glColor3f(1.0f, 0.4706f, 0.4000f);
glVertex2f(0.9997, 6.2);
glVertex2f(1.6,6.2);
glVertex2f(1.6,5.95);
glVertex2f(1, 5.95);
glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(0.9997, 6.2);
glVertex2f(1.6,6.2);
glVertex2f(1.6,5.95);
glVertex2f(1, 5.95);
glEnd();

    //3rd
    glBegin(GL_POLYGON);
glColor3f(0.9961f, 0.4078f, 0.4706f);
glVertex2f(1.6,6.2);
glVertex2f(2.5,6.2);
glVertex2f(2.5,5.95);
glVertex2f(1.6,5.95);
glEnd();


// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(1.6,6.2);
glVertex2f(2.5,6.2);
glVertex2f(2.5,5.95);
glVertex2f(1.6,5.95);
glEnd();
        //4th
    glBegin(GL_POLYGON);
glColor3f(0.0980f, 0.2706f, 0.4039f);
glVertex2f(2.5,6.2);
glVertex2f(3.1, 6.2);
glVertex2f(3.1, 5.95);
glVertex2f(2.5,5.95);
glEnd();



// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(2.5,6.2);
glVertex2f(3.1, 6.2);
glVertex2f(3.1, 5.95);
glVertex2f(2.5,5.95);
glEnd();

        //door down 1st
    glBegin(GL_POLYGON);
glColor3f(0.1765f, 0.5373f, 0.7294f);

glVertex2f(0.40003,5.95);
glVertex2f(1, 5.95);
glVertex2f(1,5);
glVertex2f(0.40013,5.0028);
glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(0.40003,5.95);
glVertex2f(1, 5.95);
glVertex2f(1,5);
glVertex2f(0.40013,5.0028);
glEnd();

       //door down 2nd
    glBegin(GL_POLYGON);
glColor3f(0.8275f, 0.9961f, 0.9725f);
glVertex2f(1, 5.95);
glVertex2f(1.5, 5.95);
glVertex2f(1.5, 5);
glVertex2f(1,5);
glEnd();


// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(1, 5.95);
glVertex2f(1.5, 5.95);
glVertex2f(1.5, 5);
glVertex2f(1,5);
glEnd();

//door handle

    glBegin(GL_POLYGON);
glColor3f(1, 1, 1);
glVertex2f(1.35, 5.6);
glVertex2f(1.45, 5.6);
glVertex2f(1.45, 5.25);
glVertex2f(1.35, 5.25);
glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(1.35, 5.6);
glVertex2f(1.45, 5.6);
glVertex2f(1.45, 5.25);
glVertex2f(1.35, 5.25);
glEnd();

//second door handle

    glBegin(GL_POLYGON);
glColor3f(0, 1, 1);
glVertex2f(1.55, 5.6);
glVertex2f(1.65, 5.6);
glVertex2f(1.65, 5.25);
glVertex2f(1.55, 5.25);
glEnd();

//door down third

    glBegin(GL_POLYGON);
glColor3f(0.6824f, 0.8706f, 0.8706f);
glVertex2f(1.5, 5.95);
glVertex2f(2.2,5.95);
glVertex2f(2.2,5);
glVertex2f(1.5,5);
glEnd();

// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(1.5, 5.95);
glVertex2f(2.2,5.95);
glVertex2f(2.2,5);
glVertex2f(1.5,5);
glEnd();

//door down 4th

    glBegin(GL_POLYGON);
glColor3f(0.6118f, 0.9451f, 0.9608f);
glVertex2f(2.2, 5.95);
glVertex2f(3,5.949);
glVertex2f(3, 5.0005);
glVertex2f(2.2,5);
glEnd();


// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(2.2, 5.95);
glVertex2f(3,5.949);
glVertex2f(3, 5.0005);
glVertex2f(2.2,5);
glEnd();


//door upper shadow

    glBegin(GL_POLYGON);
glColor3f(0.0980f, 0.2706f, 0.4039f);
glVertex2f(0.25,5.95);
glVertex2f(3.1,5.95);
glVertex2f(3.2, 5.8);
glVertex2f(0.45, 5.8);
glEnd();


// Black border
glBegin(GL_LINE_LOOP);
glColor3f(0.0f, 0.0f, 0.0f);  // Black color
glVertex2f(0.25,5.95);
glVertex2f(3.1,5.95);
glVertex2f(3.2, 5.8);
glVertex2f(0.45, 5.8);
glEnd();


//1st window 1st part

    glBegin(GL_POLYGON);
glColor3f(0.1451, 0.4745, 0.7529);

glVertex2f(0.8, 9.4);
glVertex2f(1.4, 9.4);
glVertex2f(1.4, 8.6);

glEnd();

//2nd wnodow second part
    glBegin(GL_POLYGON);
glColor3f(0.5294, 0.9608, 0.9922);
glVertex2f(0.8, 9.4);
glVertex2f(1.4, 8.6);
glVertex2f(0.8, 8.6);

glEnd();

//1st window border

    glBegin(GL_POLYGON);
glColor3f(1, 1, 1);
glVertex2f(0.75, 9.45);
glVertex2f(1.4, 9.4);
glVertex2f(1.4, 9.4);
glVertex2f(0.8, 9.4);
glEnd();


    glBegin(GL_POLYGON);
glColor3f(1, 1, 1);
glVertex2f(1.4, 9.4);
glVertex2f(1.42, 8.58);
glVertex2f(1.4, 8.6);
glVertex2f(1.4, 9.4);
glEnd();
}





















// City Scene Implementation (Placeholder - replace with your friend's actual implementation)
void initCityScene() {
    // Initialize city scene-specific settings
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);  // Gray background
}

void displayCityScene() {
    first_road();
 first_left_middle_road();
first_box();
first_housee();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Multi-Scene GLUT Project");

    // Initialize each scene
    initMountainScene();
    initRiverScene();
    initCityScene();

    // Set up GLUT callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    // Print instructions
    std::cout << "Scene Selection:" << std::endl;
    std::cout << "1 - Mountain Scene" << std::endl;
    std::cout << "2 - River Scene" << std::endl;
    std::cout << "3 - City Scene" << std::endl;
    std::cout << "ESC - Exit" << std::endl;
   glutTimerFunc(16, update, 0);
    glutMainLoop();
    return 0;
}
