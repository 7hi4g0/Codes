from math import *

from OpenGL.GL import *


def drawCylinder(radius, height, slices, stacks, is_solid):
    angle_delta = pi * 2 / slices
    angles = [i * angle_delta for i in range(slices)]
    xs = [cos(angle) for angle in angles]
    ys = [sin(angle) for angle in angles]
    xs.append(xs[0])
    ys.append(ys[0])

    # Draw bottom cap
    glNormal(0, 0, -1)

    if is_solid:
        glBegin(GL_TRIANGLE_FAN)

        glVertex(0, 0, 0)
        for x, y in zip(xs, ys):
            glVertex(radius * x, radius * y, 0)

        glEnd()

    else:
        glBegin(GL_LINES)

        for i in range(slices):
            glVertex(0, 0, 0)
            glVertex(radius * xs[i], radius * ys[i], 0)

            glVertex(0, 0, 0)
            glVertex(radius * xs[i + 1], radius * ys[i + 1], 0)

            glVertex(radius * xs[i], radius * ys[i], 0)
            glVertex(radius * xs[i + 1], radius * ys[i + 1], 0)

        glEnd()

    # Draw top cap
    glNormal(0, 0, 1)

    if is_solid:
        glBegin(GL_TRIANGLE_FAN)

        glVertex(0, 0, height)
        for x, y in zip(xs, ys):
            glVertex(radius * x, radius * y, height)

        glEnd()

    else:
        glBegin(GL_LINES)

        for i in range(slices):
            glVertex(0, 0, height)
            glVertex(radius * xs[i], radius * ys[i], height)

            glVertex(0, 0, height)
            glVertex(radius * xs[i + 1], radius * ys[i + 1], height)

            glVertex(radius * xs[i], radius * ys[i], height)
            glVertex(radius * xs[i + 1], radius * ys[i + 1], height)

        glEnd()

    # Draw walls

    glBegin(GL_QUADS if is_solid else GL_LINE_LOOP)

    for j in range(slices):
        h1 = float(height) * j / slices
        h2 = float(height) * (j + 1) / slices

        for i in range(stacks):
            glNormal(xs[i], ys[i], 0)
            glVertex(radius * xs[i], radius * ys[i], h1)
            glVertex(radius * xs[i], radius * ys[i], h2)
            glNormal(xs[i + 1], ys[i + 1], 0)
            glVertex(radius * xs[i + 1], radius * ys[i + 1], h2)
            glVertex(radius * xs[i + 1], radius * ys[i + 1], h1)

    glEnd()


def glutSolidCylinder(radius, height, slices, stacks):
    drawCylinder(radius, height, slices, stacks, True)


def glutWireCylinder(radius, height, slices, stacks):
    drawCylinder(radius, height, slices, stacks, False)
