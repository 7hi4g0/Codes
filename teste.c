#include <GL/glut.h>

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitWindowSize(480, 600);
	//glutInitWindow
	glutCreateWindow("Teste");
	glutFullScreen();
	sleep(10);
	return 0;
}
