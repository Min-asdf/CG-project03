#include <GL/freeglut.h>
#include <cmath>

// �ʱ� �� ����
float ballY = 3.0f;        // ���� �ʱ� ����
float velocity = 0.0f;     // �ʱ� �ӵ�
float gravity = -0.8f;     // �߷� ���ӵ�
float elasticity = 0.8f;   // ź�� ���
float timeStep = 0.016f;   // ���� �ð�

// Flatshading�� Wireframe�� ��۸��ϱ� ���� �ο� ����
int FlatShaded = 0;
int Wireframed = 0;

float squash = 1.0f;       // Ȯ��/��� ���� (1.0�� ���� ũ��)
bool isSquashing = false;  // �ٴڿ� ��Ҵ��� ����

void MyKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'q': case 'Q': case '\033':
        exit(0);
        break;
    case 's':
        if (FlatShaded) {
            FlatShaded = 0;
            glShadeModel(GL_SMOOTH);
        }
        else {
            FlatShaded = 1;
            glShadeModel(GL_FLAT);
        }
        glutPostRedisplay();
        break;

        // ���̾� ������ ��۸�
    case 'w':
        if (Wireframed) {
            Wireframed = 0;
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        else {
            Wireframed = 1;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        glutPostRedisplay();
        break;
    }
}

void Floor() {
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f); // ȸ�� �ٴ�
    glBegin(GL_QUADS);
    glVertex3f(-5.0f, 0.0f, -5.0f);
    glVertex3f(5.0f, 0.0f, -5.0f);
    glVertex3f(5.0f, 0.0f, 5.0f);
    glVertex3f(-5.0f, 0.0f, 5.0f);
    glEnd();
    glPopMatrix();
}

void Ball() {
    glPushMatrix();
    glTranslatef(0.0f, ballY, 0.0f);
    if (isSquashing) {
        glScalef(1.0f + squash, 1.0f - squash, 1.0f);
    }
    else {
        glScalef(1.0f - squash, 1.0f + squash, 1.0f);
    }
    glColor3f(1.0f, 0.0f, 0.0f); // ������ ��
    glutSolidSphere(0.2, 50, 50);
    glPopMatrix();
}

void update() {
    velocity += gravity * timeStep;
    ballY += velocity * timeStep;

    if (ballY <= 0.5f) {
        ballY = 0.5f;
        velocity = -velocity * elasticity;
        isSquashing = true;
    }
    else {
        isSquashing = false;
    }

    squash = std::abs(velocity) / 10.0f;
    if (squash > 0.3f) squash = 0.3f;

    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // ī�޶� ���� - �� ����� ��ġ���� ��ü�� ���� ���� ����
    gluLookAt(0.0, 2.5, 5.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0);

    Floor();
    Ball();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // ������ ���
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ball Animation");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(MyKeyboard);
    glutIdleFunc(update);
    glutMainLoop();
    return 0;
}
