import sys
from OpenGL.GL import *


SHAPES_VERSION = 1

def requer_versao(versao):
    if SHAPES_VERSION < versao:
        print >> sys.stderr, 'Seu arquivo "shapes.py" esta desatualizado.'
        print >> sys.stderr, 'Baixe a versao mais nova do site https://prof.vilarneto.com/cg .'
        sys.exit(1)


def desenhaGrade(xmin, xmax, ymin, ymax, unit=1):
    glBegin(GL_LINES)

    for y in range(ymin, ymax + 1, unit):
        if y == 0:
            glColor(.6, .2, .2)
        elif y % 5 == 0:
            glColor(.3, .3, .3)
        else:
            glColor(.2, .2, .2)

        glVertex(xmin, y)
        glVertex(xmax, y)

    for x in range(xmin, xmax + 1, unit):
        if x == 0:
            glColor(.2, .6, .2)
        elif x % 5 == 0:
            glColor(.3, .3, .3)
        else:
            glColor(.2, .2, .2)

        glVertex(x, ymin)
        glVertex(x, ymax)

    glEnd()


def desenha(vertexes, edges):
    glBegin(GL_LINES)

    for edge in edges:
        index1, index2 = edge
        glVertex(*vertexes[index1 - 1])
        glVertex(*vertexes[index2 - 1])

    glEnd()


def desenhaCamera():
    vertexes = [
        [11.000000, 5.440000],
        [10.153589, 5.164985],
        [9.630479, 4.444984],
        [9.630479, 3.555016],
        [10.153589, 2.835016],
        [11.000000, 2.560000],
        [11.846411, 2.835016],
        [12.369521, 3.555015],
        [12.369521, 4.444984],
        [11.846411, 5.164985],
        [7.800000, 6.200000],
        [8.600000, 6.200000],
        [7.800000, 6.600000],
        [8.600000, 6.600000],
        [7.000000, 2.000000],
        [14.000000, 2.000000],
        [7.000000, 6.000000],
        [14.000000, 6.000000],
        [12.000000, 7.000000],
        [10.000000, 7.000000],
        [12.600000, 6.000000],
        [9.400000, 6.000000],
        [11.000000, 5.800000],
        [9.941986, 5.456231],
        [9.288098, 4.556231],
        [9.288098, 3.443769],
        [9.941986, 2.543769],
        [11.000000, 2.200000],
        [12.058014, 2.543770],
        [12.711902, 3.443769],
        [12.711902, 4.556231],
        [12.058013, 5.456231],
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
