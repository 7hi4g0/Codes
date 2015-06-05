## == ATENCAO ==================================================================
##
## Este arquivo deve ser alterado para fazer o Trabalho Pratico de Computacao
## Grafica.
##
## O projeto usa a funcao desenhaAviao() para desenhar o aviao sempre que
## precisa. Os demais elementos da cena, como as fontes de luz e a configuracao
## do angulo da camera, sao automaticamente gerenciados pelo arquivo principal.
##
## Comandos de mouse e teclado:
## ----------------------------
##
## - A barra, "/", permite alternar a posicao da vista auxiliar que mostra os
##   tres eixos;
##
## - O angulo de visualizacao pode ser alterado clicando com o mouse e
##   arrastando.
##
## =============================================================================

from math import *

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

def desenhaAviao(angulo):

    glScale(0.35, 0.35, 0.35)
    materialMetalVermelho()
    desenhaCorpo()

    glPushMatrix()
    glTranslate(0.3, 0, -0.07)
    materialMetalBranco()
    desenhaAsa()

    glPushMatrix()
    glTranslate(0.3, 0.85, 0.1)
    glScale(0.45, 0.45, 0.45)
    desenhaMotor(angulo)
    glPopMatrix()

    glPushMatrix()
    glScale(1, -1, 1)
    glTranslate(0.3, 0.85, 0.1)
    glScale(0.45, 0.45, 0.45)
    desenhaMotor(angulo)
    glPopMatrix()

    glPopMatrix()

    glPushMatrix()
    glTranslate(-1.3, 0, 0)
    glScale(0.4, 0.2, 0.4)
    materialMetalAzul()
    desenhaAsa()
    glPopMatrix()

    glPushMatrix()
    glTranslate(0.7, 0, -0.28)
    glScale(0.25, 0.25, 0.25)
    desenhaRodaDianteira()
    glPopMatrix()

    glPushMatrix()
    glTranslate(-0.15, 0, -0.28)
    glScale(0.25, 0.25, 0.25)
    glTranslate(0, -0.6, 0)
    desenhaRodaTraseiraEsq()
    glPopMatrix()

    glPushMatrix()
    glScale(1, -1, 1)
    glTranslate(-0.15, 0, -0.28)
    glScale(0.25, 0.25, 0.25)
    glTranslate(0, -0.6, 0)
    desenhaRodaTraseiraEsq()
    glPopMatrix()


def desenhaCorpo():
    glPushMatrix()

    glRotate(90, 0, 1, 0)
    glTranslate(0, 0, -0.15)

    glPushMatrix()
    glutSolidCylinder(0.28, 1, 12, 2)
    glPopMatrix()

    glPushMatrix()
    glTranslate(0, 0, 1)
    glScale(1, 1, 2.5)
    glutSolidSphere(0.28, 12, 6)
    glPopMatrix()

    glPushMatrix()
    glScale(1, 1, 5)
    glutSolidSphere(0.28, 12, 12)
    glPopMatrix()

    glPopMatrix()

def desenhaAsa():
    glPushMatrix()

    glRotate(90, 1, 0, 0)
    glScale(0.5, 0.07, 3.75)
    glutSolidSphere(0.7, 36, 12)

    glPopMatrix()

def desenhaMotor(angulo):
    glPushMatrix()

    glScale(1, 1.5, 1.5)
    glRotate(90, 0, 1, 0)
    glTranslate(0, 0, -0.5)

    materialMetalAzul()
    glPushMatrix()
    glutSolidCylinder(0.28, 1, 12, 2)
    glPopMatrix()

    glPushMatrix()
    glTranslate(0, 0, 1)
    glutSolidSphere(0.28, 12, 6)
    glPopMatrix()

    glPushMatrix()
    glutSolidSphere(0.28, 12, 6)
    glPopMatrix()

    glPopMatrix()
    glPushMatrix()

    glRotate(90, 0, 1, 0)
    materialMetalEscovado()

    glPushMatrix()
    glScale(1, 1, 3.75)
    glutSolidSphere(0.28, 12, 6)
    glPopMatrix()

    glPopMatrix()

    glPushMatrix()

    glRotate(angulo, 1, 0, 0)
    glTranslate(0.9, 0, 0)
    for angle in range(0, 360, 120):
        glPushMatrix()

        glRotate(angle, 1, 0, 0)
        desenhaHelice()

        glPopMatrix()
    glPopMatrix()

def desenhaHelice():
    glPushMatrix()

    glTranslate(0, 0, 0.6)
    glRotate(45, 0, 0, 1)
    glScale(1, 0.25, 3)
    materialMetalPreto()
    glutSolidSphere(0.2, 12, 6)

    glPopMatrix()

def desenhaRodaDianteira():
    glPushMatrix()

    glTranslate(0, 0, -0.7)
    glRotate(90, 1, 0, 0)

    glPushMatrix()
    glTranslate(0, 0, -0.2)
    materialBorrachaPreta()
    glutSolidTorus(0.1, 0.2, 6, 12)
    materialMetalBranco()
    glutSolidCylinder(0.05, 0.4, 12, 6)
    glPopMatrix()

    glPushMatrix()
    glTranslate(0, 0, 0.2)
    materialBorrachaPreta()
    glutSolidTorus(0.1, 0.2, 6, 12)
    materialMetalBranco()
    glPopMatrix()

    glPushMatrix()
    glRotate(-90, 1, 0, 0)
    glutSolidCylinder(0.05, 0.7, 12, 6)
    glPopMatrix()

    glPopMatrix()

def desenhaRodaTraseiraEsq():
    glPushMatrix()

    glTranslate(0, 0, -0.5)
    glRotate(90, 1, 0, 0)

    glPushMatrix()
    glTranslate(0, 0, -0.2)
    materialBorrachaPreta()
    glutSolidTorus(0.1, 0.2, 6, 12)
    materialMetalBranco()
    glutSolidCylinder(0.05, 0.2, 12, 6)
    glPopMatrix()

    glPushMatrix()
    glTranslate(0, 0.4, 0)
    glScale(0.2, 0.8, 0.02)
    glutSolidCube(1)
    glPopMatrix()

    glPopMatrix()

def materialBorrachaPreta():
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, [0.02, 0.02, 0.02, 1])
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, [0.01, 0.01, 0.01, 1])
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, [0.04, 0.04, 0.04, 1])
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, [10])

def materialMetalEscovado():
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, [1.0, 1.0, 1.0, 1])
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, [0.163, 0.163, 0.163, 0.5])
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, [0, 0, 0, 0])
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, [0])

def materialMetalVermelho():
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, [1.0, 1.0, 1.0, 1])
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, [0.8, 0.032, 0.074, 0.8])
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, [1.0, 0.169, 0.354, 0.5])
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, [50])

def materialMetalBranco():
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, [1.0, 1.0, 1.0, 1])
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, [1.0, 1.0, 1.0, 1.0])
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, [0.376, 0.376, 0.376, 0.5])
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, [50])

def materialMetalAzul():
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, [1.0, 1.0, 1.0, 1])
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, [0.0, 0.0, 1.0, 0.5])
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, [0.153, 0.011, 0.761, 0.75])
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, [10])

def materialMetalPreto():
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, [0.02, 0.02, 0.02, 1])
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, [0.053, 0.053, 0.053, 0.5])
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, [0.42, 0.42, 0.42, 0.35])
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, [10])
