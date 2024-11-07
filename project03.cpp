#include <GL/freeglut.h>

float translateX = 0.0f, translateY = 0.0f, translateZ = -2.0f;
float rotateX = 0.0f, rotateY = 0.0f;
float scale = 1.0f;
float cameraX = 0.0f, cameraY = 2.0f, cameraZ = 5.0f;

int lastX = -1, lastY = -1;  // 마지막 마우스 위치

void drawPyramid() {
    glBegin(GL_TRIANGLES);

    // 정면 삼각형
    glColor3f(1.0f, 0.0f, 0.0f);  // 빨간색
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // 왼쪽 삼각형
    glColor3f(1.0f, 0.0f, 0.0f);  // 빨간색
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // 오른쪽 삼각형
    glColor3f(1.0f, 0.0f, 0.0f);  // 빨간색
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // 뒷면 삼각형
    glColor3f(1.0f, 0.0f, 0.0f);  // 빨간색
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);



    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // 카메라 위치 지정 (시점 변환)
    gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // 모델 변환 (이동, 회전, 크기 조정)
    glTranslatef(translateX, translateY, translateZ);  // 이동
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f);  // X축 회전
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f);  // Y축 회전
    glScalef(scale, scale, scale);  // 크기 조정

    // 피라미드 그리기
    drawPyramid();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'w') translateY += 0.1f;  // 위로 이동
    if (key == 's') translateY -= 0.1f;  // 아래로 이동
    if (key == 'a') translateX -= 0.1f;  // 왼쪽으로 이동
    if (key == 'd') translateX += 0.1f;  // 오른쪽으로 이동
    if (key == 'q') translateZ += 0.1f;  // 뒤로 이동
    if (key == 'e') translateZ -= 0.1f;  // 앞으로 이동

    if (key == 'r') rotateX += 5.0f;  // X축 회전
    if (key == 'f') rotateX -= 5.0f;  // X축 반대방향 회전
    if (key == 't') rotateY += 5.0f;  // Y축 회전
    if (key == 'g') rotateY -= 5.0f;  // Y축 반대방향 회전

    if (key == 27) exit(0);  // ESC 키로 종료

    if (key == ']') scale += 0.1f;  // ]: 크기 증가
    if (key == '[') scale -= 0.1f;  // [: 크기 감소

    glutPostRedisplay();
}

// 마우스 움직임을 통한 시점 조정
void mouseMotion(int x, int y) {
    if (lastX != -1 && lastY != -1) {
        // 마우스 드래그에 따른 카메라 위치 변경
        cameraX += (x - lastX) * 0.01f;  // X축 방향
        cameraY -= (y - lastY) * 0.01f;  // Y축 방향
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
    glEnable(GL_DEPTH_TEST);  // 깊이 테스트 활성화

    // 원근 투영 설정
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
    glutMotionFunc(mouseMotion);  // 마우스 드래그 이벤트 처리
    glutMouseFunc(mouse);  // 마우스 클릭 이벤트 처리

    glutMainLoop();
    return 0;
}
