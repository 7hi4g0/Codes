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
        [-0.979128, 5.184101],
        [-1.164163, 4.313580],
        [-0.802180, 3.500554],
        [-0.031444, 3.055569],
        [0.853649, 3.148595],
        [1.515025, 3.744101],
        [1.700060, 4.614624],
        [1.338077, 5.427650],
        [0.567341, 5.872634],
        [-0.317752, 5.779607],
        [-3.237307, 2.792820],
        [-2.837307, 3.485641],
        [-3.583717, 2.992820],
        [-3.183717, 3.685641],
        [-0.000000, 0.000000],
        [3.500000, 6.062178],
        [-3.464102, 2.000000],
        [0.035898, 8.062178],
        [-1.830128, 6.830127],
        [-2.830128, 5.098076],
        [-0.664102, 6.849742],
        [-2.264102, 4.078461],
        [-1.290897, 5.364101],
        [-1.522191, 4.275950],
        [-1.069712, 3.259667],
        [-0.106292, 2.703436],
        [1.000074, 2.819720],
        [1.826794, 3.564102],
        [2.058088, 4.652254],
        [1.605609, 5.668537],
        [0.642190, 6.224767],
        [-0.464178, 6.108483],
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
