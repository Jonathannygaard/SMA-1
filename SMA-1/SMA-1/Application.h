//
// Created by jonat on 08/04/2024.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include "Camera/Camera.h"
#include "Mesh/Mesh.h"


class VertexBuffer;
class ElementBuffer;
struct GLFWwindow;

class Application {

public:
    GLFWwindow *mWindow;
    static Camera mCamera;
    static float DeltaTime;
    Mesh mMesh;

    Application() = default;

    void init();
    void create();
    void update();
    void run();

    virtual ~Application() = default;

private:
    VertexBuffer* VBO = nullptr;
    ElementBuffer* EBO = nullptr;
};



#endif //APPLICATION_H
