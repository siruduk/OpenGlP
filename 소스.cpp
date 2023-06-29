#include <GL/glut.h>
#include<stdio.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

GLfloat r, g, b;
GLfloat size = -0.7;
bool start = false;
bool full = false;
bool enable = true;
bool light = false;
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void timer(int a);


void Keyboard(unsigned char key, int x, int y)
{
    if (key == 'o')
        light = true;
    if (key == 'p')
        light = false;
    // o,p로 조명 on/off
    if (key == 'g')
    {
        enable = true;
        if (start == false)
            glutTimerFunc(25, timer, 1);
        start = true;
    }//g키를 한번 누르면 애니메이션 실행 
    //키보드를 이용한 애니메이션 실행 중 우클릭 시 원래 상태로 돌아감

    glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        enable = true;
        if (start == false)
            glutTimerFunc(25, timer, 1);
        start = true;
    }
    else
    {
        enable = false;
        size = -0.7;
        start = false;
        full = false;
        glutPostRedisplay();
    }//마우스왼쪽 버튼을 꾹 누르면 애니메이션 실행 중간에 때면 원래 상태로 돌아감
}

void timer(int a)
{

    if (enable)
    {
        if (size < 0.69)
        {
            size += 0.01;
            glutTimerFunc(25, timer, 1);
        }// 게이지가 다안찼다면 계속 증가
        else if(size<0.7)
        {
            full = true;
            start = false;
            size += 0.3;
            glutTimerFunc(1, timer, 1);
        }// 게이지가 다찼으면 게이지를 끄고 음표 띄움
        else
        {
            size = -0.7;
            enable = false;
            start = false;
            full = false;
            PlaySound(TEXT("ost.wav"), NULL, SND_ASYNC);
            Sleep(1400);
        }//이후 사운드를 출력하고 처음상태로 돌아감
        glutPostRedisplay();
    }//주황색 네모 게이지 차오르게 하는 부분
}

void Reshape(GLsizei width, GLsizei height)

{
    if (width > height) {
         glViewport((width - height)/2, 0, height, height);
    } else {
         glViewport(0, (height - width)/2, width, width);
    }
    //뷰포트 변환
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1, 1, 1, 1); //배경 흰색
    if (light)
        glEnable(GL_LIGHTING);
    else
        glDisable(GL_LIGHTING);
    GLfloat arLight[] = { 1, 1, 1, 1 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, arLight);
    //조명 on off

    //음표
    if (full)
    {
        //오른쪽 음표
        glColor3f(0, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(0.9, 0.7);
        glVertex2f(0.8, 0.68);
        glVertex2f(0.91, 0.65);
        glVertex2f(0.81, 0.63);
        glVertex2f(0.8, 0.68);
        glVertex2f(0.83, 0.53);
        glEnd();

        glBegin(GL_QUADS);
        glVertex2f(0.82, 0.58);
        glVertex2f(0.78, 0.57);
        glVertex2f(0.79, 0.52);
        glVertex2f(0.83, 0.53);
        glEnd();
        
        //왼쪽 음표
        glBegin(GL_LINES);
        glVertex2f(-0.8, 0.7);
        glVertex2f(-0.7, 0.68);
        glVertex2f(-0.81, 0.65);
        glVertex2f(-0.71, 0.63);
        glVertex2f(-0.7, 0.68);
        glVertex2f(-0.73, 0.53);
        glVertex2f(-0.8, 0.7);
        glVertex2f(-0.83, 0.55);
        glEnd();

        glBegin(GL_QUADS);
        glVertex2f(-0.76, 0.58);
        glVertex2f(-0.72, 0.57);
        glVertex2f(-0.73, 0.52);
        glVertex2f(-0.77, 0.53);

        glVertex2f(-0.86, 0.6);
        glVertex2f(-0.82, 0.59);
        glVertex2f(-0.83, 0.54);
        glVertex2f(-0.87, 0.55);
        glEnd();
    }

    //네모 게이지
    if (start)
    {
        r = 245;
        g = 170;
        b = 64;

        r = r / 255;
        g = g / 255;
        b = b / 255;
        glColor3f(r, g, b);
        //네모 테두리
        glBegin(GL_LINE_LOOP);
        glVertex2f(-0.7, -0.55);
        glVertex2f(-0.7, -0.68);
        glVertex2f(0.7, -0.68);
        glVertex2f(0.7, -0.55);
        glEnd();
        //색 채우기
        glBegin(GL_QUADS);
        glVertex2f(-0.7, -0.55);
        glVertex2f(-0.7, -0.68);
        glVertex2f(size, -0.68);
        glVertex2f(size, -0.55);
        glEnd();
    }

    //잎

    r = 95;
    g = 181;
    b = 9;

    r = r / 255;
    g = g / 255;
    b = b / 255;
    glColor3f(r,g,b);

    //왼쪽
    glBegin(GL_POLYGON);
    glVertex2f(-0.2, 0.2);
    glVertex2f(0, 0.2);
    glVertex2f(0.05, 0.25);
    glVertex2f(0, 0.35);
    glVertex2f(-0.1, 0.45);
    glVertex2f(-0.2, 0.5);
    glVertex2f(-0.25, 0.49);
    glVertex2f(-0.3, 0.485);
    glVertex2f(-0.35, 0.48);
    glVertex2f(-0.4, 0.45);
    glVertex2f(-0.5, 0.35);
    glEnd();
    //오른쪽
    glBegin(GL_POLYGON);
    glVertex2f(0,0.2);
    glVertex2f(0.05, 0.21);
    glVertex2f(0.1, 0.22);
    glVertex2f(0.15, 0.225);
    glVertex2f(0.2, 0.25);
    glVertex2f(0.4, 0.35);
    glVertex2f(0.46, 0.4);
    glVertex2f(0.6, 0.55);
    glVertex2f(0.4, 0.58);
    glVertex2f(0.3, 0.58);
    glVertex2f(0.25, 0.57);
    glVertex2f(0.2, 0.55);
    glVertex2f(0.15, 0.525);
    glVertex2f(0.1, 0.48);
    glVertex2f(0.05, 0.4);
    glVertex2f(0, 0.2);
    glEnd();

    //무 Y축 방향으로 분할해서 그림

    r = 195;
    g = 222;
    b = 163;

    r = r / 255;
    g = g / 255;
    b = b / 255;
    glColor3f(r, g, b);

    glBegin(GL_POLYGON);
    glVertex2f(0.13, 0.03);
    glVertex2f(0.125, 0.05);
    glVertex2f(0.125, -0.2);
    glVertex2f(0.14, -0.1);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.125, 0.05);
    glVertex2f(0.1, 0.15);
    glVertex2f(0.1, -0.3);
    glVertex2f(0.125, -0.2);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.1, 0.15);
    glVertex2f(0.05, 0.21);
    glVertex2f(0.05, -0.35);
    glVertex2f(0.1, -0.3);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.05, 0.21);
    glVertex2f(0, 0.2);
    glVertex2f(0, -0.4);
    glVertex2f(0.05, -0.35);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0, 0.2);
    glVertex2f(-0.05, 0.05);
    glVertex2f(-0.05, -0.43);
    glVertex2f(0, -0.4);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.05, 0.05);
    glVertex2f(-0.1, 0);
    glVertex2f(-0.1, -0.44);
    glVertex2f(-0.05, -0.43);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.1, 0);
    glVertex2f(-0.15, -0.04);
    glVertex2f(-0.15, -0.45);
    glVertex2f(-0.1, -0.44);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.15, -0.04);
    glVertex2f(-0.2, -0.06);
    glVertex2f(-0.2, -0.47);
    glVertex2f(-0.15, -0.45);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.2, -0.06);
    glVertex2f(-0.25, -0.08);
    glVertex2f(-0.25, -0.48);
    glVertex2f(-0.2, -0.47);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.25, -0.08);
    glVertex2f(-0.3, -0.1);
    glVertex2f(-0.3, -0.46);
    glVertex2f(-0.25, -0.48);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.3, -0.1);    
    glVertex2f(-0.35, -0.11);
    glVertex2f(-0.35, -0.45);
    glVertex2f(-0.3, -0.46);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.35, -0.11);
    glVertex2f(-0.4, -0.13);
    glVertex2f(-0.4, -0.43);
    glVertex2f(-0.35, -0.45);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.4, -0.13);
    glVertex2f(-0.42, -0.18);
    glVertex2f(-0.42, -0.4);
    glVertex2f(-0.4, -0.43);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.42, -0.18);
    glVertex2f(-0.45, -0.38);
    glVertex2f(-0.42, -0.4);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.42, -0.18);
    glVertex2f(-0.47, -0.25);
    glVertex2f(-0.45, -0.38);
    glEnd();

    //잎맥


    r = 166;
    g = 255;
    b = 77;

    r = r / 255;
    g = g / 255;
    b = b / 255;

    glColor3f(r, g, b);

    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.5, 0.35);
    glVertex2f(-0.4, 0.375);
    glVertex2f(-0.3, 0.39);
    glVertex2f(-0.25, 0.375);
    glVertex2f(-0.175, 0.35);
    glVertex2f(-0.1, 0.325);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(0.15, 0.35);
    glVertex2f(0.2, 0.4);
    glVertex2f(0.25, 0.425);
    glVertex2f(0.3, 0.45);
    glVertex2f(0.4, 0.48);
    glVertex2f(0.6, 0.55);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-0.25, 0.375);
    glVertex2f(-0.3, 0.45);
    glVertex2f(-0.175, 0.35);
    glVertex2f(-0.188, 0.3);
    glVertex2f(0.2, 0.4);
    glVertex2f(0.22, 0.5);
    glVertex2f(0.4, 0.48);
    glVertex2f(0.43, 0.44);
    glEnd();

    //무 줄기?

    r = 18;
    g = 111;
    b = 15;

    r = r / 255;
    g = g / 255;
    b = b / 255;
    glColor3f(r, g, b);


    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.2, -0.06);
    glVertex2f(-0.15, -0.2);
    glVertex2f(-0.05, -0.43);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.3, -0.1);
    glVertex2f(-0.15, -0.2);
    glVertex2f(0.1, -0.3);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.45, -0.38);
    glVertex2f(-0.38, -0.33);
    glVertex2f(-0.2, -0.3);
    glVertex2f(-0.09, -0.33);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.47, -0.25);
    glVertex2f(-0.43, -0.28);
    glVertex2f(-0.38, -0.33);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-0.25,-0.13);   
    glVertex2f(-0.32, -0.16);
    glVertex2f(-0.2, -0.3);
    glVertex2f(-0.17, -0.4);
    glVertex2f(-0.19, -0.35);   
    glVertex2f(-0.25, -0.42);
    glVertex2f(0.13, -0.15);
    glVertex2f(-0.08, -0.23);
    glEnd();

    glFlush();
    glutSwapBuffers();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize(800, 800);
    glutCreateWindow("");
    glutDisplayFunc(display);
    glutMouseFunc(Mouse);
    glutKeyboardFunc(Keyboard);
    glutReshapeFunc(Reshape);
    glutMainLoop();
    return 0;
}
