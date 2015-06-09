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
    glRotated(60, 0, 0, 1)
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
        [9.752923, 4.719999],
        [9.567888, 3.849479],
        [9.929871, 3.036452],
        [10.700607, 2.591468],
        [11.585700, 2.684494],
        [12.247076, 3.280000],
        [12.432111, 4.150522],
        [12.070128, 4.963549],
        [11.299393, 5.408533],
        [10.414299, 5.315506],
        [7.494744, 2.328719],
        [7.894744, 3.021540],
        [7.148334, 2.528719],
        [7.548334, 3.221539],
        [10.732051, -0.464101],
        [14.232050, 5.598077],
        [7.267949, 1.535898],
        [10.767948, 7.598077],
        [8.901923, 6.366026],
        [7.901923, 4.633975],
        [10.067949, 6.385641],
        [8.467949, 3.614360],
        [9.441154, 4.900000],
        [9.209860, 3.811849],
        [9.662339, 2.795566],
        [10.625758, 2.239335],
        [11.732125, 2.355618],
        [12.558846, 3.100000],
        [12.790139, 4.188152],
        [12.337660, 5.204435],
        [11.374241, 5.760666],
        [10.267873, 5.644382],
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
