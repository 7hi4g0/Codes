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

    glRotated(180, 0, 1, 0)
    glTranslatef(-10.5, 0, 0)
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
        [-0.500000, 5.440000],
        [0.346411, 5.164985],
        [0.869521, 4.444984],
        [0.869521, 3.555016],
        [0.346411, 2.835016],
        [-0.500000, 2.560000],
        [-1.346411, 2.835016],
        [-1.869521, 3.555015],
        [-1.869521, 4.444984],
        [-1.346411, 5.164985],
        [2.700000, 6.200000],
        [1.900000, 6.200000],
        [2.700000, 6.600000],
        [1.900000, 6.600000],
        [3.500000, 2.000000],
        [-3.500000, 2.000000],
        [3.500000, 6.000000],
        [-3.500000, 6.000000],
        [-1.500000, 7.000000],
        [0.500000, 7.000000],
        [-2.100000, 6.000000],
        [1.100000, 6.000000],
        [-0.500000, 5.800000],
        [0.558014, 5.456231],
        [1.211902, 4.556231],
        [1.211902, 3.443769],
        [0.558014, 2.543769],
        [-0.500000, 2.200000],
        [-1.558014, 2.543770],
        [-2.211902, 3.443769],
        [-2.211902, 4.556231],
        [-1.558013, 5.456231],
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
