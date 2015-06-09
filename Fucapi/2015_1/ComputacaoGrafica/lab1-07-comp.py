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

    glTranslated(11, 4, 0)
    glRotated(180, 1, 0, 0)
    glRotated(90, 0, 0, 1)
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
        [9.560001, 4.000000],
        [9.835016, 4.846411],
        [10.555017, 5.369521],
        [11.444985, 5.369521],
        [12.164986, 4.846411],
        [12.440001, 4.000000],
        [12.164986, 3.153589],
        [11.444985, 2.630479],
        [10.555017, 2.630479],
        [9.835016, 3.153589],
        [8.800001, 7.200000],
        [8.800001, 6.400000],
        [8.400002, 7.200000],
        [8.400002, 6.400001],
        [13.000002, 8.000000],
        [13.000001, 1.000000],
        [9.000002, 8.000000],
        [9.000001, 1.000000],
        [8.000001, 3.000001],
        [8.000001, 5.000001],
        [9.000001, 2.400000],
        [9.000002, 5.600000],
        [9.200001, 4.000000],
        [9.543770, 5.058014],
        [10.443771, 5.711902],
        [11.556231, 5.711902],
        [12.456232, 5.058014],
        [12.800001, 4.000000],
        [12.456231, 2.941986],
        [11.556231, 2.288098],
        [10.443770, 2.288098],
        [9.543770, 2.941987],
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
