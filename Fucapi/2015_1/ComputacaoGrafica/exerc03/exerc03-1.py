#!/usr/bin/env python2.7

#
# Aluno:
#   Thiago Dourado de Andrade
#

from math import *

from OpenGL.GL import *
from OpenGL.GLUT import *

from shapes import *

previous_time = 0
dx = 0
dy = 0
posx = 0
posy = 0

BODY_POINTS = [
    [-0.8, -0.4],
    [-0.7, -0.6],
    [-0.3, -0.6],
    [0, -0.3],
    [0.2, -0.3],
    [0.3, -0.2],
    [0.3, 0.45],
    [0.5, 0.5],
    [0.5, 0.6],
    [0.2, 0.65],
    [0.5, 0.7],
    [0.5, 0.8],
    [0.3, 0.9],
    [0, 0.9],
    [-0.1, 0.8],
    [-0.1, 0.6],
    [0, 0.5],
    [-0.1, 0.4],
    [-0.2, -0.1],
    [-0.4, -0.4],
    [-0.5, -0.5],
    [-0.7, -0.5],
    ]
ARM_POINTS = [
    [0, 0.3],
    [0.1, 0.2],
    [0.2, 0.2],
    [0.5, 0.1],
    [0.6, 0.2],
    [0.8, 0.2],
    [0.7, 0.25],
    [0.8, 0.3],
    [0.7, 0.3],
    [0.75, 0.4],
    [0.65, 0.3],
    [0.6, 0.4],
    [0.6, 0.3],
    [0.5, 0.2],
    [0.3, 0.4],
    [0.1, 0.4],
    ]
LEG_POINTS = [
    [0, -0.1],
    [0, -0.3],
    [0.1, -0.4],
    [0.1, -0.5],
    [0, -0.6],
    [0, -0.65],
    [0.1, -0.7],
    [0.4, -0.7],
    [0.2, -0.6],
    [0.2, -0.5],
    [0.4, -0.3],
    [0.3, -0.1],
    [0.2, 0],
    [0.1, 0],
    ]
EYE_POINTS = [
    [0.075, 0.8],
    [0.1, 0.77],
    [0.16, 0.77],
    [0.21, 0.8],
    [0.16, 0.825],
    [0.1, 0.825],
    ]


def desenhaQuadrado():
    glBegin(GL_LINE_LOOP)

    glVertex(0.05, 0.05)
    glVertex(-0.05, 0.05)
    glVertex(-0.05, -0.05)
    glVertex(0.05, -0.05)

    glEnd()


def desenhaBracoGodzilla():
    glPushMatrix()
    glTranslate(-0.1, -0.3, 0)

    glBegin(GL_LINE_LOOP)
    for point in ARM_POINTS:
        glVertex(point)
    glEnd()

    glPopMatrix()


def desenhaPernaGodzilla():
    glPushMatrix()
    glTranslate(-0.1, 0.1, 0)

    glBegin(GL_LINE_LOOP)
    for point in LEG_POINTS:
        glVertex(point)
    glEnd()

    glPopMatrix()


def desenhaCorpoGodzilla():
    for points in (BODY_POINTS, EYE_POINTS):
        glBegin(GL_LINE_LOOP)
        for point in points:
            glVertex(point)
        glEnd()


def desenhaGodzilla(angulo_braco, angulo_perna):
    desenhaCorpoGodzilla()

    glPushMatrix()
    glTranslate(0.1, 0.3, 0)
    glRotate(angulo_braco, 0, 0, 1)
    desenhaBracoGodzilla()
    glPopMatrix()

    glPushMatrix()
    glTranslate(0.1, -0.1, 0)
    glRotate(angulo_perna, 0, 0, 1)
    desenhaPernaGodzilla()
    glPopMatrix()


def draw():
    global previous_time, dx, dy, posx, posy

    # Quanto tempo passou desde que o programa
    # foi iniciado:
    current_time = glutGet(GLUT_ELAPSED_TIME)
    # Quanto tempo passou do quadro anterior
    # para o quadro atual:
    delta_time = current_time - previous_time
    # Guarda o current_time para ser usado
    # no proximo quadro
    previous_time = current_time

    # Limpeza da tela
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()

    glScale(0.1, 0.1, 1)
    desenhaGrade(-10, 10, -10, 10, unit=1)

    # --- INICIO DO DESENHO DA TELA ---
    posx = posx + (delta_time * dx) / 1000.0
    posy = posy + (delta_time * dy) / 1000.0

    glColor(1, 1, 1)
    glTranslate(posx, posy, 0.0)
    desenhaGodzilla(0, 0)

    # --- FIM DO DESENHO DA TELA ---

    # Exibicao da tela que acabou de ser construida
    glutSwapBuffers()
    glutPostRedisplay()


def keyboard(char, x, y):
    global dx, dy, posx, posy

    if char == 'w':
        dy = 1

    elif char == 's':
        dy = -1

    elif char == 'a':
        dx = -1

    elif char == 'd':
        dx = 1

    elif char == ' ':
        dx = 0
        dy = 0

    elif char == 'x':
        dx = 0
        dy = 0
        posx = 0
        posy = 0

    pass

if __name__ == '__main__':
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH)

    glutInitWindowPosition(0, 0)
    glutInitWindowSize(300, 300)
    glutCreateWindow("2a Avaliacao Parcial - 1")

    glutDisplayFunc(draw)
    glutKeyboardFunc(keyboard)

    glutMainLoop()
