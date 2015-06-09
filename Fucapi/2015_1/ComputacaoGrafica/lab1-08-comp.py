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
    glScalef(0.5, 0.5, 1)
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
        [6.510436, 4.592051],
        [6.417918, 4.156790],
        [6.598910, 3.750277],
        [6.984278, 3.527785],
        [7.426825, 3.574298],
        [7.757513, 3.872051],
        [7.850030, 4.307312],
        [7.669039, 4.713825],
        [7.283670, 4.936317],
        [6.841124, 4.889804],
        [5.381347, 3.396410],
        [5.581347, 3.742821],
        [5.208141, 3.496410],
        [5.408141, 3.842820],
        [7.000000, 2.000000],
        [8.750000, 5.031089],
        [5.267949, 3.000000],
        [7.017949, 6.031089],
        [6.084936, 5.415064],
        [5.584936, 4.549038],
        [6.667949, 5.424871],
        [5.867949, 4.039230],
        [6.354551, 4.682051],
        [6.238904, 4.137975],
        [6.465144, 3.629833],
        [6.946854, 3.351718],
        [7.500037, 3.409860],
        [7.913397, 3.782051],
        [8.029044, 4.326127],
        [7.802805, 4.834269],
        [7.321095, 5.112384],
        [6.767911, 5.054241],
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
