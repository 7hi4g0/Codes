#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-

## == ATENCAO ==================================================================
##
## NAO ALTERAR O CONTEUDO DESTE ARQUIVO!
##
## =============================================================================

import sys
from math import *

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

import argparse

parser = argparse.ArgumentParser(
    description='Fase 1 do projeto final de Computacao Grafica.')
parser.add_argument('--dummy-draw-function', '-d', dest='use_dummy_draw_function',
                    action='store_true', default=False,
                    help='usa uma funcao padrao para o desenho do objeto')

options = parser.parse_args()

try:
    import aviao
except ImportError:
    print >> sys.stderr, '*** ERRO: Arquivo "aviao.py" nao foi encontrado.'
    print >> sys.stderr, '    Voce deve criar sua versao da funcao desenhaAviao()'
    print >> sys.stderr, '    e coloca-la em um arquivo chamado "aviao.py"'
    print >> sys.stderr, '    neste mesmo diretorio.'
    sys.exit(1)


class Scene(object):
    @staticmethod
    def draw_dummy_object(angulo_helice):
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, [0, 0.2, 0.9, 1])
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, [0, 0, 0, 1])
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, [0])

        glPushMatrix()
        glScale(1.4, 0.3, 0.1)
        glutSolidCube(1)
        glPopMatrix()

        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, [0.2, 0.8, 0.6, 1])
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, [.7, .7, .7, 1])
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, [127])

        glPushMatrix()
        glTranslate(0.8, 0, 0)
        glutSolidSphere(0.1, 32, 32)
        glPopMatrix()

        glPushMatrix()
        glTranslate(0, 0.25, 0)
        glutSolidSphere(0.1, 32, 32)
        glTranslate(0, -0.50, 0)
        glutSolidSphere(0.1, 32, 32)
        glPopMatrix()

        glPushMatrix()
        glTranslate(-0.6, 0, 0.15)
        glutSolidSphere(0.1, 32, 32)
        glPopMatrix()


    CAMERA_ROTATION_SPEED = 0.5
    AXES_VIEWPORT_SIZE = 48
    AXES_PADDING_FACTOR = 1.1
    AXES_WINDOW_BORDER = 4

    axes_position = 1
    current_time = 0.0
    delta_time = 0.0

    draw_object_function = None

    camera_alpha = 0.
    camera_beta = 0.
    window_width = 300
    window_height = 300


    def __init__(self):
        if self.draw_object_function is None:
            self.draw_object_function = Scene.draw_dummy_object

        self.enabled_lights = [True, True, True, True, False, False, False, False]

        self.arrow = glGenLists(1)
        glNewList(self.arrow, GL_COMPILE)

        glBegin(GL_LINES)
        glVertex(0, 0, 0)
        glVertex(1, 0, 0)
        glEnd()

        glPushMatrix()
        glTranslate(0.8, 0, 0)
        glRotate(90, 0, 1, 0)
        glutSolidCone(0.12, 0.25, 8, 2)
        glPopMatrix()

        glEndList()


    def configure_glut(self):
        glutDisplayFunc(self.draw)
        glutReshapeFunc(self.reshape)
        glutKeyboardFunc(self.keyboard)
        glutMouseFunc(self.mouse)
        glutMotionFunc(self.motion)


    def update_time(self):
        current_time = glutGet(GLUT_ELAPSED_TIME)
        self.delta_time = current_time - self.current_time
        self.current_time = current_time


    def get_axes_viewport_bounds(self):
        if self.axes_position == 1 or self.axes_position == 4:
            x = self.AXES_WINDOW_BORDER
        else:
            x = self.window_width - self.AXES_WINDOW_BORDER - self.AXES_VIEWPORT_SIZE

        if self.axes_position == 3 or self.axes_position == 4:
            y = self.AXES_WINDOW_BORDER
        else:
            y = self.window_height - self.AXES_WINDOW_BORDER - self.AXES_VIEWPORT_SIZE

        return (x, y, self.AXES_VIEWPORT_SIZE, self.AXES_VIEWPORT_SIZE)


    def get_axes_inner_viewport_bounds(self):
        viewport_bounds = self.get_axes_viewport_bounds()
        return (viewport_bounds[0] + 1, viewport_bounds[1] + 1,
                viewport_bounds[2] - 2, viewport_bounds[3] - 2)


    def switch_to_axes_viewport(self):
        viewport_bounds = self.get_axes_viewport_bounds()
        glViewport(*viewport_bounds)

        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        glOrtho(-self.AXES_PADDING_FACTOR, self.AXES_PADDING_FACTOR,
                -self.AXES_PADDING_FACTOR, self.AXES_PADDING_FACTOR,
                -self.AXES_PADDING_FACTOR, self.AXES_PADDING_FACTOR)

        glMatrixMode(GL_MODELVIEW)


    def draw_axes_viewport(self):
        glEnable(GL_COLOR_MATERIAL)
        glDisable(GL_LIGHTING)
        glEnable(GL_SCISSOR_TEST)

        glScissor(*self.get_axes_viewport_bounds())
        glClearColor(1, 1, 1, 1)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

        glScissor(*self.get_axes_inner_viewport_bounds())
        glClearColor(0, 0, 0, 1)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

        glLoadIdentity()

        glRotate(self.camera_beta, 1, 0, 0)
        glRotate(self.camera_alpha, 0, 0, 1)

        glColor(1, 0, 0)
        glCallList(self.arrow)

        glPushMatrix()
        glColor(0, 1, 0)
        glRotate(90, 0, 0, 1)
        glCallList(self.arrow)
        glPopMatrix()

        glPushMatrix()
        glColor(0, 0, 1)
        glRotate(-90, 0, 1, 0)
        glCallList(self.arrow)
        glPopMatrix()

        glColor(1, 1, 1)


    def switch_to_scene_viewport(self):
        glViewport(0, 0, self.window_width, self.window_height)

        if self.window_width >= self.window_height:
            x_range = float(self.window_width) / self.window_height
            y_range = 1.
        else:
            x_range = 1.
            y_range = float(self.window_height) / self.window_width

        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        glOrtho(-x_range, x_range, -y_range, y_range, -1, 1)

        glMatrixMode(GL_MODELVIEW)


    def draw_scene_viewport(self):
        glDisable(GL_COLOR_MATERIAL)
        glEnable(GL_LIGHTING)
        glDisable(GL_SCISSOR_TEST)

        glMaterial(GL_FRONT_AND_BACK, GL_AMBIENT, [0, 0, 0, 1])

        for light in range(len(self.enabled_lights)):
            if self.enabled_lights[light]:
                glEnable(GL_LIGHT0 + light)
            else:
                glDisable(GL_LIGHT0 + light)

        glClearColor(0, 0, 0.2, 1)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glLoadIdentity()

        glLightfv(GL_LIGHT1, GL_POSITION, [15, 3, 10, 1])
        glLightfv(GL_LIGHT2, GL_POSITION, [-5, -20, 10, 1])
        glLightfv(GL_LIGHT3, GL_POSITION, [-5, 20, 10, 1])
        glLightfv(GL_LIGHT4, GL_POSITION, [0, 0, 20, 1])

        glRotate(self.camera_beta, 1, 0, 0)
        glRotate(self.camera_alpha, 0, 0, 1)

        self.draw_object_function(0.8 * self.current_time)


    def draw(self):
        self.update_time()

        self.switch_to_scene_viewport()
        self.draw_scene_viewport()

        if self.axes_position != 0:
            self.switch_to_axes_viewport()
            self.draw_axes_viewport()

        glutSwapBuffers()
        glutPostRedisplay()


    def reshape(self, window_width, window_height):
        self.window_width = window_width
        self.window_height = window_height

        glViewport(0, 0, window_width, window_height)

        if window_width >= window_height:
            x_range = float(window_width) / window_height
            y_range = 1.
        else:
            x_range = 1.
            y_range = float(window_height) / window_width

        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        #glOrtho(-1, 1, -1, 1, -1, 1)
        glOrtho(-x_range, x_range, -y_range, y_range, -1, 1)

        glMatrixMode(GL_MODELVIEW)


    def keyboard(self, char, x, y):
        if char == '/':
            self.axes_position = (self.axes_position + 1) % 5
        elif char >= '0' and char <= '7':
            light = ord(char) - ord('0')
            self.enabled_lights[light] = not self.enabled_lights[light]


    def mouse(self, button, state, x, y):
        if button == GLUT_LEFT_BUTTON:
            if state == GLUT_DOWN:
                self.last_x = x
                self.last_y = y


    def motion(self, x, y):
        dx = x - self.last_x
        dy = y - self.last_y
        self.last_x = x
        self.last_y = y

        self.camera_alpha += self.CAMERA_ROTATION_SPEED * dx
        self.camera_beta += self.CAMERA_ROTATION_SPEED * dy


if __name__ == '__main__':
    if not options.use_dummy_draw_function:
        try:
            Scene.draw_object_function = staticmethod(aviao.desenhaAviao)
        except AttributeError:
            print >> sys.stderr, '*** ERRO: Nao existe uma funcao chamada desenhaAviao()'
            print >> sys.stderr, '    dentro do arquivo "aviao.py".'
            print >> sys.stderr, '    Voce deve criar sua versao da funcao desenhaAviao()'
            print >> sys.stderr, '    e coloca-la em um arquivo chamado "aviao.py"'
            print >> sys.stderr, '    neste mesmo diretorio.'
            sys.exit(1)

    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH)

    glutInitWindowPosition(0, 0)
    glutInitWindowSize(300, 300)
    glutCreateWindow("Aula 12")

    glEnable(GL_DEPTH_TEST)

    # Cor da fonte de luz 0
    glLight(GL_LIGHT0, GL_AMBIENT, [0.02, 0.02, 0.02]);
    glLight(GL_LIGHT0, GL_DIFFUSE, [0, 0, 0]);
    glLight(GL_LIGHT0, GL_SPECULAR, [0, 0, 0]);
    glEnable(GL_LIGHT0)
    # Cor da fonte de luz 1
    glLight(GL_LIGHT1, GL_AMBIENT, [0, 0, 0]);
    glLight(GL_LIGHT1, GL_DIFFUSE, [0.8, 0.8, 0.8]);
    # Cor da fonte de luz 2
    glLight(GL_LIGHT2, GL_AMBIENT, [0, 0, 0]);
    glLight(GL_LIGHT2, GL_DIFFUSE, [0.1, 0.1, 0.1]);
    # Cor da fonte de luz 3
    glLight(GL_LIGHT3, GL_AMBIENT, [0, 0, 0]);
    glLight(GL_LIGHT3, GL_DIFFUSE, [0.1, 0.1, 0.1]);
    # Cor da fonte de luz 4
    glLight(GL_LIGHT4, GL_AMBIENT, [0, 0, 0]);
    glLight(GL_LIGHT4, GL_DIFFUSE, [0.6, 0.4, 0.1]);

    scene = Scene()
    scene.configure_glut()

    glutMainLoop()
