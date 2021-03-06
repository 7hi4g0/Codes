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

    for angulo in range(0, 360, 60):
	glPushMatrix()  # Salva transformacoes atuais

        glRotate(angulo, 0, 0, 1)
        glTranslated(1, -4, 0)
	desenhaCamera()

	glPopMatrix()   # Recupera transformacoes salvas

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
        [-12.000001, -1.439998],
        [-11.153590, -1.164983],
        [-10.630479, -0.444983],
        [-10.630479, 0.444986],
        [-11.153588, 1.164986],
        [-12.000000, 1.440001],
        [-12.846411, 1.164987],
        [-13.369522, 0.444987],
        [-13.369521, -0.444982],
        [-12.846412, -1.164982],
        [-8.800001, -2.199998],
        [-9.600000, -2.199998],
        [-8.800001, -2.599998],
        [-9.600001, -2.599998],
        [-8.000000, 2.000001],
        [-15.000000, 2.000002],
        [-8.000001, -1.999999],
        [-15.000000, -1.999998],
        [-13.000001, -2.999998],
        [-11.000001, -2.999998],
        [-13.600000, -1.999998],
        [-10.400000, -1.999999],
        [-12.000001, -1.799998],
        [-10.941986, -1.456229],
        [-10.288099, -0.556229],
        [-10.288099, 0.556232],
        [-10.941986, 1.456232],
        [-12.000000, 1.800002],
        [-13.058014, 1.456233],
        [-13.711902, 0.556233],
        [-13.711902, -0.556229],
        [-13.058014, -1.456229],
        [-4.752922, -11.112306],
        [-4.567887, -10.241784],
        [-4.929871, -9.428758],
        [-5.700606, -8.983773],
        [-6.585700, -9.076800],
        [-7.247076, -9.672305],
        [-7.432110, -10.542827],
        [-7.070127, -11.355853],
        [-6.299391, -11.800838],
        [-5.414298, -11.707810],
        [-2.494743, -8.721024],
        [-2.894743, -9.413844],
        [-2.148333, -8.921024],
        [-2.548333, -9.613844],
        [-5.732050, -5.928204],
        [-9.232050, -11.990381],
        [-2.267948, -7.928204],
        [-5.767948, -13.990381],
        [-3.901923, -12.758331],
        [-2.901923, -11.026279],
        [-5.067948, -12.777946],
        [-3.467948, -10.006664],
        [-4.441153, -11.292305],
        [-4.209859, -10.204153],
        [-4.662338, -9.187870],
        [-5.625758, -8.631639],
        [-6.732125, -8.747923],
        [-7.558845, -9.492306],
        [-7.790139, -10.580458],
        [-7.337659, -11.596741],
        [-6.374239, -12.152971],
        [-5.267872, -12.036687],
        [7.247076, -9.672304],
        [6.585702, -9.076799],
        [5.700606, -8.983772],
        [4.929871, -9.428757],
        [4.567888, -10.241783],
        [4.752923, -11.112305],
        [5.414298, -11.707809],
        [6.299393, -11.800838],
        [7.070128, -11.355853],
        [7.432112, -10.542826],
        [6.305256, -6.521024],
        [6.705256, -7.213844],
        [6.651666, -6.321024],
        [7.051666, -7.013844],
        [2.267949, -7.928203],
        [5.767949, -13.990381],
        [5.732050, -5.928204],
        [9.232051, -11.990382],
        [9.098077, -9.758331],
        [8.098076, -8.026280],
        [8.532049, -10.777946],
        [6.932051, -8.006664],
        [7.558846, -9.492305],
        [6.732126, -8.747923],
        [5.625758, -8.631639],
        [4.662339, -9.187870],
        [4.209859, -10.204153],
        [4.441154, -11.292305],
        [5.267874, -12.036687],
        [6.374240, -12.152971],
        [7.337659, -11.596741],
        [7.790139, -10.580456],
        [-7.247079, 9.672304],
        [-6.585702, 9.076799],
        [-5.700609, 8.983772],
        [-4.929873, 9.428757],
        [-4.567890, 10.241784],
        [-4.752924, 11.112305],
        [-5.414301, 11.707809],
        [-6.299394, 11.800837],
        [-7.070130, 11.355852],
        [-7.432113, 10.542826],
        [-6.305257, 6.521023],
        [-6.705258, 7.213844],
        [-6.651667, 6.321023],
        [-7.051667, 7.013844],
        [-2.267950, 7.928203],
        [-5.767951, 13.990381],
        [-5.732052, 5.928203],
        [-9.232052, 11.990379],
        [-9.098078, 9.758330],
        [-8.098077, 8.026278],
        [-8.532053, 10.777946],
        [-6.932052, 8.006663],
        [-7.558848, 9.492304],
        [-6.732126, 8.747922],
        [-5.625760, 8.631639],
        [-4.662340, 9.187870],
        [-4.209862, 10.204153],
        [-4.441156, 11.292305],
        [-5.267877, 12.036687],
        [-6.374243, 12.152970],
        [-7.337662, 11.596739],
        [-7.790142, 10.580456],
        [4.752923, 11.112305],
        [4.567888, 10.241784],
        [4.929872, 9.428757],
        [5.700607, 8.983773],
        [6.585701, 9.076799],
        [7.247077, 9.672305],
        [7.432111, 10.542826],
        [7.070128, 11.355852],
        [6.299392, 11.800837],
        [5.414299, 11.707810],
        [2.494744, 8.721024],
        [2.894744, 9.413844],
        [2.148334, 8.921023],
        [2.548334, 9.613844],
        [5.732051, 5.928204],
        [9.232051, 11.990381],
        [2.267949, 7.928203],
        [5.767949, 13.990380],
        [3.901924, 12.758330],
        [2.901923, 11.026278],
        [5.067949, 12.777946],
        [3.467949, 10.006663],
        [4.441154, 11.292305],
        [4.209860, 10.204153],
        [4.662339, 9.187869],
        [5.625759, 8.631639],
        [6.732126, 8.747922],
        [7.558846, 9.492305],
        [7.790140, 10.580457],
        [7.337660, 11.596740],
        [6.374241, 12.152970],
        [5.267873, 12.036687],
        [12.000000, 1.440000],
        [11.153591, 1.164984],
        [10.630479, 0.444984],
        [10.630480, -0.444984],
        [11.153589, -1.164985],
        [12.000000, -1.440001],
        [12.846411, -1.164984],
        [13.369522, -0.444985],
        [13.369521, 0.444984],
        [12.846412, 1.164984],
        [8.800000, 2.199999],
        [9.600001, 2.199999],
        [8.800000, 2.599999],
        [9.600001, 2.599999],
        [8.000000, -2.000000],
        [15.000000, -2.000000],
        [8.000000, 2.000000],
        [15.000000, 2.000000],
        [13.000000, 3.000000],
        [11.000000, 3.000000],
        [13.600000, 1.999999],
        [10.400000, 2.000000],
        [12.000001, 1.800000],
        [10.941986, 1.456231],
        [10.288099, 0.556231],
        [10.288099, -0.556231],
        [10.941986, -1.456231],
        [12.000001, -1.800000],
        [13.058014, -1.456231],
        [13.711903, -0.556231],
        [13.711903, 0.556230],
        [13.058014, 1.456231],
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
        [34, 33],
        [35, 34],
        [36, 35],
        [37, 36],
        [38, 37],
        [39, 38],
        [40, 39],
        [41, 40],
        [42, 41],
        [33, 42],
        [45, 43],
        [43, 44],
        [44, 46],
        [46, 45],
        [49, 47],
        [47, 48],
        [48, 50],
        [49, 54],
        [52, 54],
        [51, 52],
        [51, 53],
        [50, 53],
        [56, 55],
        [57, 56],
        [58, 57],
        [59, 58],
        [60, 59],
        [61, 60],
        [62, 61],
        [63, 62],
        [64, 63],
        [55, 64],
        [66, 65],
        [67, 66],
        [68, 67],
        [69, 68],
        [70, 69],
        [71, 70],
        [72, 71],
        [73, 72],
        [74, 73],
        [65, 74],
        [77, 75],
        [75, 76],
        [76, 78],
        [78, 77],
        [81, 79],
        [79, 80],
        [80, 82],
        [81, 86],
        [84, 86],
        [83, 84],
        [83, 85],
        [82, 85],
        [88, 87],
        [89, 88],
        [90, 89],
        [91, 90],
        [92, 91],
        [93, 92],
        [94, 93],
        [95, 94],
        [96, 95],
        [87, 96],
        [98, 97],
        [99, 98],
        [100, 99],
        [101, 100],
        [102, 101],
        [103, 102],
        [104, 103],
        [105, 104],
        [106, 105],
        [97, 106],
        [109, 107],
        [107, 108],
        [108, 110],
        [110, 109],
        [113, 111],
        [111, 112],
        [112, 114],
        [113, 118],
        [116, 118],
        [115, 116],
        [115, 117],
        [114, 117],
        [120, 119],
        [121, 120],
        [122, 121],
        [123, 122],
        [124, 123],
        [125, 124],
        [126, 125],
        [127, 126],
        [128, 127],
        [119, 128],
        [130, 129],
        [131, 130],
        [132, 131],
        [133, 132],
        [134, 133],
        [135, 134],
        [136, 135],
        [137, 136],
        [138, 137],
        [129, 138],
        [141, 139],
        [139, 140],
        [140, 142],
        [142, 141],
        [145, 143],
        [143, 144],
        [144, 146],
        [145, 150],
        [148, 150],
        [147, 148],
        [147, 149],
        [146, 149],
        [152, 151],
        [153, 152],
        [154, 153],
        [155, 154],
        [156, 155],
        [157, 156],
        [158, 157],
        [159, 158],
        [160, 159],
        [151, 160],
        [162, 161],
        [163, 162],
        [164, 163],
        [165, 164],
        [166, 165],
        [167, 166],
        [168, 167],
        [169, 168],
        [170, 169],
        [161, 170],
        [173, 171],
        [171, 172],
        [172, 174],
        [174, 173],
        [177, 175],
        [175, 176],
        [176, 178],
        [177, 182],
        [180, 182],
        [179, 180],
        [179, 181],
        [178, 181],
        [184, 183],
        [185, 184],
        [186, 185],
        [187, 186],
        [188, 187],
        [189, 188],
        [190, 189],
        [191, 190],
        [192, 191],
        [183, 192],
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
