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

    glTranslated(-11, -4, 0)
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
        [0.000000, 1.440000],
        [-0.846411, 1.164985],
        [-1.369521, 0.444984],
        [-1.369521, -0.444984],
        [-0.846411, -1.164984],
        [0.000000, -1.440000],
        [0.846411, -1.164984],
        [1.369521, -0.444985],
        [1.369521, 0.444984],
        [0.846411, 1.164985],
        [-3.200000, 2.200000],
        [-2.400000, 2.200000],
        [-3.200000, 2.600000],
        [-2.400000, 2.600000],
        [-4.000000, -2.000000],
        [3.000000, -2.000000],
        [-4.000000, 2.000000],
        [3.000000, 2.000000],
        [1.000000, 3.000000],
        [-1.000000, 3.000000],
        [1.600000, 2.000000],
        [-1.600000, 2.000000],
        [0.000000, 1.800000],
        [-1.058014, 1.456231],
        [-1.711902, 0.556231],
        [-1.711902, -0.556231],
        [-1.058014, -1.456231],
        [0.000000, -1.800000],
        [1.058014, -1.456230],
        [1.711902, -0.556231],
        [1.711902, 0.556231],
        [1.058013, 1.456231],
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
