#include <GL/glut.h>

float translateX = 0.0f, translateY = 0.0f, translateZ = -2.0f;
float rotateX = 0.0f, rotateY = 0.0f;
float scale = 1.0f;
float cameraX = 0.0f, cameraY = 2.0f, cameraZ = 5.0f;

int lastX = -1, lastY = -1;  // ������ ���콺 ��ġ

void drawPyramid() {
    glBegin(GL_TRIANGLES);

    // ���� �ﰢ��
    glColor3f(1.0f, 0.0f, 0.0f);  // ������
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // ���� �ﰢ��
    glColor3f(1.0f, 0.0f, 0.0f);  // ������
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // ������ �ﰢ��
    glColor3f(1.0f, 0.0f, 0.0f);  // ������
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // �޸� �ﰢ��
    glColor3f(1.0f, 0.0f, 0.0f);  // ������
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);



    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // ī�޶� ��ġ ���� (���� ��ȯ)
    gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // �� ��ȯ (�̵�, ȸ��, ũ�� ����)
    glTranslatef(translateX, translateY, translateZ);  // �̵�
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f);  // X�� ȸ��
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f);  // Y�� ȸ��
    glScalef(scale, scale, scale);  // ũ�� ����

    // �Ƕ�̵� �׸���
    drawPyramid();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'w') translateY += 0.1f;  // ���� �̵�
    if (key == 's') translateY -= 0.1f;  // �Ʒ��� �̵�
    if (key == 'a') translateX -= 0.1f;  // �������� �̵�
    if (key == 'd') translateX += 0.1f;  // ���������� �̵�
    if (key == 'q') translateZ += 0.1f;  // �ڷ� �̵�
    if (key == 'e') translateZ -= 0.1f;  // ������ �̵�

    if (key == 'r') rotateX += 5.0f;  // X�� ȸ��
    if (key == 'f') rotateX -= 5.0f;  // X�� �ݴ���� ȸ��
    if (key == 't') rotateY += 5.0f;  // Y�� ȸ��
    if (key == 'g') rotateY -= 5.0f;  // Y�� �ݴ���� ȸ��

    if (key == 27) exit(0);  // ESC Ű�� ����

    if (key == ']') scale += 0.1f;  // ]: ũ�� ����
    if (key == '[') scale -= 0.1f;  // [: ũ�� ����

    glutPostRedisplay();
}

// ���콺 �������� ���� ���� ����
void mouseMotion(int x, int y) {
    if (lastX != -1 && lastY != -1) {
        // ���콺 �巡�׿� ���� ī�޶� ��ġ ����
        cameraX += (x - lastX) * 0.01f;  // X�� ����
        cameraY -= (y - lastY) * 0.01f;  // Y�� ����
    }
    lastX = x;
    lastY = y;

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_UP) {
        lastX = -1;
        lastY = -1;
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);  // ���� �׽�Ʈ Ȱ��ȭ

    // ���� ���� ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 10.0);  // FOV, aspect ratio, near, far plane
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Pyramid");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMotionFunc(mouseMotion);  // ���콺 �巡�� �̺�Ʈ ó��
    glutMouseFunc(mouse);  // ���콺 Ŭ�� �̺�Ʈ ó��

    glutMainLoop();
    return 0;
}
