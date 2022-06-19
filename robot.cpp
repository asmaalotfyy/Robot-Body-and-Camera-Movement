#include <GL\glut.h>
#include <iostream>
#include <math.h>
using namespace std;
//The distance from the camera to the object
float G_fDistance = 3.6f;
//Rotation angle of the robot 
float G_fAngle_horizon = 0.0;
float G_fAngle_vertical = 0.0f;

int G_left_upper_arm1 = 0.0;//Motion angle of upper left arm (left and right movement)
int G_left_upper_arm2 = 0.0;//Motion angle of upper left arm (forward and backward movement)
int G_left_lower_arm1 = 0.0f;//Motion angle of left lower arm (left and right movement)
int G_left_lower_arm2 = 0.0f;//Motion angle of left lower arm (forward and backward movement)
int G_right_upper_arm1 = 0.0;//Motion angle of upper right arm (left and right movement)
int G_right_upper_arm2 = 0.0;//Motion angle of upper right arm (forward and backward movement)
int G_right_lower_arm1 = 0.0f;//Motion angle of right lower arm (left and right movement)
int G_right_lower_arm2 = 0.0f;//Motion angle of right lower arm (forward and backward movement)

int G_left_upper_leg = 0.0;//Left thigh movement angle (forward and backward movement)
int G_left_lower_leg = 0.0f;//Left calf movement angle (forward and backward movement)
int G_right_upper_leg = 0.0;//Right thigh movement angle (forward and backward movement)
int G_right_lower_leg = 0.0f;//Right calf movement angle (forward and backward movement)
int moving, startx, starty;
GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */
void myinit(void);
void myReshape(GLsizei w, GLsizei h);
void display(void);
void processSpecialKeys(int key, int x, int y);
void processNormalKeys(unsigned char key, int x, int y);
void timer(int value);
static void motion(int x, int y)
{
	if (moving) {
		angle = angle + (x - startx);
		angle2 = angle2 + (y - starty);
		startx = x;
		starty = y;
		glutPostRedisplay();
	}
}
//Main function
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	//Initialize OPENGL display mode
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	//Set the position and size of the OPENGL window
	glutInitWindowSize(500, 800);
	glutInitWindowPosition(100, 100);

	//Open the window
	glutCreateWindow("Simple Robot");
	cout << "w, s, a, d control the robot's upper right arm front, back, left, and right" << "\n";
	cout << "5, 2, 1, 3 control the left and right upper arm of the robot" << "\n";
	cout << "t, g, f, h control the right lower arm of the robot front, back, left, and right" << "\n";
	cout << "i, k, j, l control the left and right lower arm of the robot" << "\n";
	cout << "6, 7 control the front and back of the right thigh of the robot" << "\n";
	cout << "8, 9 control the front and back of the left thigh of the robot" << "\n";
	cout << "z, x control the front and rear of the right calf of the robot" << "\n";
	cout << "c, v control the front and rear of the left leg of the robot" << "\n";
	cout << "‘[’,‘]’ are used to control the distance of the robot from the screen" << "\n";
	cout << "The up, down, left, and right keys on the keyboard can rotate the robot" << "\n";
	//Call the initialization function
	myinit();

	//Set the callback function of the window size change
	glutReshapeFunc(myReshape);

	//Set the callback function of keyboard control
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(processNormalKeys);

	//Start the OPENGL cycle
	glutDisplayFunc(display);
	glutMainLoop();
	glutMotionFunc(motion);
	return 0;
}

void myinit(void)//initialization
{
	glEnable(GL_DEPTH);
}
void myReshape(GLsizei w, GLsizei h)//Set the callback function of the window size change
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1, 30);
}

void drawfinger(GLfloat x, GLfloat y, GLfloat z)//Draw fingers
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glPushMatrix();
	glScalef(0.025, 0.05, 0.025);
	glutWireCube(1.0);
	glPopMatrix();
	glPopMatrix();
}
void drawfoot(GLfloat x, GLfloat y, GLfloat z)//Draw feet
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glPushMatrix();
	glScalef(0.25, 0.05, 0.25);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();
}
void display(void)
{
	//Clear color and depth buffer
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Change of perspective
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -G_fDistance);
	glRotatef(G_fAngle_horizon, 0.0f, 1.0f, 0.0f);
	glRotatef(G_fAngle_vertical, 1.0f, 0.0f, 0.0f);
	//body
	glPushMatrix();
	glScalef(1.0, 0.75, 0.5);
	glutWireCube(1.0);
	glPopMatrix();
	glPushMatrix();
	//head
	glTranslatef(0.0, 0.625, 0.0);
	glutWireSphere(0.25, 20, 20);
	//Left arm
	glPushMatrix();
	//Upper left arm
	glTranslatef(-0.575, -0.375, 0.0);
	glRotatef(G_left_upper_arm1, 0.0, 0.0, 1.0);
	glRotatef(G_left_upper_arm2, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.225, 0.0);
	glPushMatrix();
	glScalef(0.125, 0.45, 0.3);
	glutWireCube(1.0);
	glPopMatrix();
	//Left elbow
	glTranslatef(0.0, -0.25625, 0.0);
	glutWireSphere(0.0625, 20, 20);
	//Lower left arm
	glTranslatef(0.0, -0.03125, 0.0);
	glRotatef(G_left_lower_arm1, 0.0, 0.0, 1.0);
	glRotatef(G_left_lower_arm2, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.225, 0.0);
	glPushMatrix();
	glScalef(0.125, 0.45, 0.15);
	glutWireCube(1.0);
	glPopMatrix();
	//Draw fingers
	drawfinger(-0.0675, -0.25, 0.075);
	drawfinger(0.0675, -0.25, 0.075);
	drawfinger(0, -0.25, -0.075);
	glPopMatrix();
	//Right arm
	glPushMatrix();
	//Upper right arm
	glTranslatef(0.575, 0.375, 0.0);
	glRotatef(G_right_upper_arm1, 0.0, 0.0, 1.0);
	glRotatef(G_right_upper_arm2, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.225, 0.0);
	glPushMatrix();
	glScalef(0.125, 0.45, 0.3);
	glutWireCube(1.0);
	glPopMatrix();
	//Right elbow
	glTranslatef(0.0, -0.25625, 0.0);
	glutWireSphere(0.0625, 20, 20);
	//Lower right arm
	glTranslatef(0.0, -0.03125, 0.0);
	glRotatef(G_right_lower_arm1, 0.0, 0.0, 1.0);
	glRotatef(G_right_lower_arm2, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.225, 0.0);
	glPushMatrix();
	glScalef(0.125, 0.45, 0.15);
	glutWireCube(1.0);
	glPopMatrix();
	//Draw fingers
	drawfinger(-0.0675, -0.25, 0.075);
	drawfinger(0.0675, -0.25, 0.075);
	drawfinger(0, -0.25, -0.075);
	glPopMatrix();
	//Left leg
	glPushMatrix();
	//Left thigh
	glTranslatef(0.15, -0.375, 0.0);
	glRotatef(G_left_upper_leg, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.225, 0.0);
	glPushMatrix();
	glScalef(0.25, 0.45, 0.3);
	glutWireCube(1.0);
	glPopMatrix();
	//Left knee
	glTranslatef(0.0, -0.25625, 0.0);
	glutWireSphere(0.0625, 20, 20);
	//Left calf
	glTranslatef(0.0, -0.0625, 0.0);
	glRotatef(G_left_lower_leg, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.225, 0.0);
	glPushMatrix();
	glScalef(0.125, 0.45, 0.3);
	glutWireCube(1.0);
	glPopMatrix();
	drawfoot(0.0, -0.25, 0.0);
	glPopMatrix();
	//Right leg
	glPushMatrix();
	//Right thigh
	glTranslatef(-0.15, -0.375, 0.0);
	glRotatef(G_right_upper_leg, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.225, 0.0);
	glPushMatrix();
	glScalef(0.25, 0.45, 0.3);
	glutWireCube(1.0);
	glPopMatrix();
	//Right knee
	glTranslatef(0.0, -0.25625, 0.0);
	glutWireSphere(0.0625, 20, 20);
	//Right calf
	glTranslatef(0.0, -0.0625, 0.0);
	glRotatef(G_right_lower_leg, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.225, 0.0);
	glPushMatrix();
	glScalef(0.125, 0.45, 0.3);
	glutWireCube(1.0);
	glPopMatrix();
	drawfoot(0.0, -0.25, 0.0);
	glPopMatrix();
	//Exchange the front and back buffer
	glutSwapBuffers();
}

//Respond to keyboard input, so as to set the callback function of moving the object closer and farther and rotating
void processSpecialKeys(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		G_fAngle_horizon -= 5.0f;
		break;
	case GLUT_KEY_RIGHT:
		G_fAngle_horizon += 5.0f;
		break;
	case GLUT_KEY_UP:
		G_fAngle_vertical -= 5.0f;
		break;
	case GLUT_KEY_DOWN:
		G_fAngle_vertical += 5.0f;
		break;
	}
	glutPostRedisplay();
}
void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case 91:	//"["
		G_fDistance -= 0.3f;
		break;
	case 93:		//"]"
		G_fDistance += 0.3f;
		break;
	case 49:	//1
		G_left_upper_arm1 -= 15.0;
		break;
	case 51:	//3
		G_left_upper_arm1 += 15.0;
		break;
	case 50:	//2
		G_left_upper_arm2 -= 15.0;
		break;
	case 53:	//5
		G_left_upper_arm2 += 15.0;
		break;
		//i, k, j, l control the lower arm of the left arm of the robot
	//case 106:	//j
		//G_left_lower_arm1 -= 15.0;
		//break;
	//case 108:	//l
	//	G_left_lower_arm1 += 15.0;
		//break;
	case 105:	//i
		if (G_left_lower_arm2 > 0)
			G_left_lower_arm2 = (G_left_lower_arm2 - 5) % 360;
				//G_left_lower_arm2 -= 15.0;
		break;
	case 107:	//k
		if (G_left_lower_arm2 < 180)
			G_left_lower_arm2 = (G_left_lower_arm2 + 5) % 360;
				//G_left_lower_arm2 += 15.0;
		break;
	case  97:	//a
		G_right_upper_arm1 -= 15.0;
		break;
	case  100:	//d
		G_right_upper_arm1 += 15.0;
		break;
	case  119:	//w
		G_right_upper_arm2 -= 15.0;
		break;
	case  115:	//s
		G_right_upper_arm2 += 15.0;
		break;
	//case  102:	//f
		//G_right_lower_arm1 -= 15.0;
		//break;
	//case  104:	//h
		//G_right_lower_arm1 += 15.0;
		//break;
	case  116:	//t
		if (G_right_lower_arm2 > 0)
			G_right_lower_arm2 = (G_right_lower_arm2 - 5) % 360;
				//G_right_lower_arm2 -= 15.0;
		break;
	case  103:	//g
		if (G_right_lower_arm2 < 180)
			G_right_lower_arm2 = (G_right_lower_arm2 + 5) % 360;
				//G_right_lower_arm2 += 15.0;
		break;
	case 56://8
		if (G_left_upper_leg > 0)
			G_left_upper_leg = (G_left_upper_leg - 5) % 360;
			//G_left_upper_leg -= 15.0;
		break;
	case 57://9
		if (G_left_upper_leg < 180)
			G_left_upper_leg = (G_left_upper_leg + 5) % 360;
	//G_left_upper_leg += 15.0;
		break;
	case 99://c
		if (G_left_lower_leg > 0)
			G_left_lower_leg = (G_left_lower_leg - 5) % 360;
	//G_left_lower_leg -= 15.0;
		break;
	case 118://v
		if (G_left_lower_leg < 90)
			G_left_lower_leg = (G_left_lower_leg + 5) % 360;
			 //G_left_lower_leg += 15.0;
		break;
	case 54://6
		if (G_right_upper_leg > 0)
			G_right_upper_leg = (G_right_upper_leg - 5) % 360;
		//G_right_upper_leg -= 15.0;
		break;
	case 55://7
		if (G_right_upper_leg < 180)
			G_right_upper_leg = (G_left_upper_leg + 5) % 360;
			//G_right_upper_leg += 15.0;
		break;
	case 122://z
		if (G_right_lower_leg > 0)
			G_right_lower_leg = (G_right_lower_leg - 5) % 360;
		//G_right_lower_leg -= 15.0;
		break;
	case 120://x
		if (G_right_lower_leg < 90)
			G_right_lower_leg = (G_left_lower_leg + 5) % 360;
			 //G_right_lower_leg += 15.0;
		break;
	case 27:	//"esc"
		exit(0);
	}
	glutPostRedisplay();
}
