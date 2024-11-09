#include <GL/freeglut.h>
#include <cmath>

// 초기 값 설정
float ballY = 3.0f;        // 공의 초기 높이
float velocity = 0.0f;     // 초기 속도
float gravity = -0.8f;     // 중력 가속도
float elasticity = 0.8f;   // 탄성 계수
float timeStep = 0.016f;   // 단위 시간

// Flatshading과 Wireframe을 토글링하기 위한 부울 변수
int FlatShaded = 0;
int Wireframed = 0;

float squash = 1.0f;       // 확대/축소 비율 (1.0은 원래 크기)
bool isSquashing = false;  // 바닥에 닿았는지 여부

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

        // 와이어 프레임 토글링
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
    glColor3f(0.3f, 0.3f, 0.3f); // 회색 바닥
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
    glColor3f(1.0f, 0.0f, 0.0f); // 빨간색 공
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

    // 카메라 설정 - 더 가까운 위치에서 객체를 보기 위해 조정
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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 검은색 배경
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
