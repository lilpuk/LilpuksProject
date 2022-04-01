#include <stdio.h> // подключаем заголовки:
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "math_3d.h"

GLuint VBO; // назначаем GLuint в качестве глобальной переменной для хранения указателя на буфер вершин

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT); // функция рендера - очистка буфера кадра

    glEnableVertexAttribArray(0); // включаем массив атрибутов вершин с индексом 0
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3); // отрисовываем
    glDisableVertexAttribArray(0); // отключаем атрибут каждой вершины
    glutSwapBuffers();
}

static void GlutCall()
{
    glutDisplayFunc(RenderSceneCB); // функция обратного вызова
}

static void VerBuffer()
{
    Vector3f Vertices[3]; // массив, который содержит 3 вершины
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
    Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
    Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

int main(int argc, char** argv)
{

    glutInit(&argc, argv); // инициализируем GLUT

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //настраиваем опции GLUT

    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Треугольник"); // Задают параметры окна и создают его
    GlutCall();

    GLenum res = glewInit(); // инициализируем GLEW и проверяем на ошибки
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    glClearColor(1.0f, 0.8f, 1.0f, 0.0f); // устанавливаем розовый цвет

    VerBuffer();
    glutMainLoop(); // вызов передаёт контроль GLUT'у

    return 0;
}
