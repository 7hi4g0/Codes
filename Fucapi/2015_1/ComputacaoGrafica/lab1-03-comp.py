#!/usr/bin/env python2.7

from math import *

from OpenGL.GL import *
from OpenGL.GLUT import *

try:
    from shapes import *
except ImportError:
    print >> sys.stderr, 'O arquivo "shapes.py" eh necessario neste diretorio.'
    print >> sys.stderr, 'Baixe a versao mais nova do site https://prof.vilarneto.com/cg .'
    sys.exit(1)


mostraDesenhoFinal = True


def draw():
    # Limpeza da tela
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()

    glScale(0.05, 0.05, 1)
    desenhaGrade(-20, 20, -20, 20)

    # --- Inicio do desenho da tela ---

    if mostraDesenhoFinal:
	glColor(1, 0, 0)   # Seta cor = vermelho
	glLineWidth(3)     # Seta linha com largura mais grossa
	desenhaCamerasDesejadas()

    glColor(0, 1, 0)   # Seta cor = verde
    glLineWidth(1)     # Seta linha com largura comum

    # === ALUNOS DEVEM ALTERAR O CODIGO A PARTIR DAQUI ===

    glTranslated(7, 2, 0)
    glRotated(60, 0, 0, 1)
    glTranslated(-7, -2, 0)
    desenhaCamera()

    # === ALUNOS DEVEM ALTERAR O CODIGO ATE' AQUI ===

    # --- Fim do desenho da tela ---

    # Exibicao da tela que acabou de ser construida
    glutSwapBuffers()


def keyboard(char, x, y):
    global mostraDesenhoFinal

    if char == '\x1b':
        sys.exit(0)

    if char == ' ':
	mostraDesenhoFinal = not mostraDesenhoFinal

    glutPostRedisplay()


def desenhaCamerasDesejadas():
    vertexes = [
        [6.020872, 7.184101],
        [5.835837, 6.313580],
        [6.197820, 5.500554],
        [6.968556, 5.055569],
        [7.853649, 5.148595],
        [8.515025, 5.744101],
        [8.700060, 6.614624],
        [8.338078, 7.427650],
        [7.567341, 7.872634],
        [6.682248, 7.779607],
        [3.762693, 4.792820],
        [4.162693, 5.485641],
        [3.416283, 4.992820],
        [3.816283, 5.685641],
        [7.000000, 2.000000],
        [10.500000, 8.062178],
        [3.535898, 4.000000],
        [7.035898, 10.062178],
        [5.169872, 8.830128],
        [4.169872, 7.098076],
        [6.335898, 8.849743],
        [4.735898, 6.078461],
        [5.709103, 7.364101],
        [5.477809, 6.275950],
        [5.930288, 5.259667],
        [6.893707, 4.703436],
        [8.000074, 4.819720],
        [8.826795, 5.564102],
        [9.058088, 6.652254],
        [8.605610, 7.668537],
        [7.642190, 8.224768],
        [6.535822, 8.108482],
	]
    edges = [
        [2, 1],
        [3, 2],
        [4, 3],
        [5, 4],
        [6, 5],
        [7, 6],
        [8, 7],
        [9, 8],
        [10, 9],
        [1, 10],
        [13, 11],
        [11, 12],
        [12, 14],
        [14, 13],
        [17, 15],
        [15, 16],
        [16, 18],
        [17, 22],
        [20, 22],
        [19, 20],
        [19, 21],
        [18, 21],
        [24, 23],
        [25, 24],
        [26, 25],
        [27, 26],
        [28, 27],
        [29, 28],
        [30, 29],
        [31, 30],
        [32, 31],
        [23, 32],
	]

    desenha(vertexes, edges)


if __name__ == '__main__':
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH)

    glutInitWindowPosition(0, 0)
    glutInitWindowSize(600, 600)
    glutCreateWindow("Exercicio de Computacao Grafica")

    glutKeyboardFunc(keyboard)
    glutDisplayFunc(draw)

    glutMainLoop()
