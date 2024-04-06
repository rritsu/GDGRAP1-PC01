/*
GDGRAP1 - MP
Date: 03-22-24
Group 5 Members:
    Austria, Joshua Angelo E.
    Legaspi, Andrea Maxene F.
*/

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

//class header
#include "Model3D.h"
#include "Light/Light.h"
#include "Light/PointLight.h"
#include "Light/DirectionLight.h"
#include "Camera/MyCamera.h"
#include "Camera/OrthoCamera.h"
#include "Camera/PerspectiveCamera.h"


//openGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//obj loader
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float width = 800.0f;
float height = 800.0f;

//timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool firstMouse = true;
std::string projectionType = "Perspective";

//Model3D* model;
Model3D* psub = new Model3D();
Model3D* esub1 = new Model3D();
Model3D* esub2 = new Model3D();
Model3D* esub3 = new Model3D();
Model3D* esub4 = new Model3D();
Model3D* esub5 = new Model3D();
Model3D* esub6 = new Model3D();
Model3D* lightSource = new Model3D();
Model3D* activeModel = new Model3D();

MyCamera* Camera = new MyCamera();

PointLight* lightsource = new PointLight();

std::vector<Model3D*> vecModels;
//glm::vec3 lastCameraPos = glm::vec3(1.0f);
// glm::vec3 lastCameraFront = glm::vec3(1.0f);
//glm::vec3 lastCameraUp = glm::vec3(1.0f);

int i = 1;
double last_xpos = 0.0f;
double last_ypos = 0.0f;


int modelInt = 1;  //1 for the model, 2 for the lightsource
int modelLP = 2;


//this function handles the mouse control for the camera
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    /*
    Camera->initialize(&firstMouse, xpos, ypos);
    if (projectionType == "Perspective") {
        if (i == 0) {
            xpos = last_xpos;
            ypos = last_ypos;
            std::cout << "hello" << std::endl;
        }
        i++;
        Camera->updateMouse(xpos, ypos);
        std::cout << "wah" << std::endl;
    }
    else {
        if (i == 1) {
            last_xpos = xpos;
            last_ypos = ypos;
        }
        i++;
    }
    */
    Camera->initialize(&firstMouse, xpos, ypos);
    if (projectionType == "Perspective") {
        Camera->updateMouse(xpos, ypos);
    }
    else {
        if (i == 1) {
            last_xpos = xpos;
            last_ypos = ypos;
        }
        i++;
    }

}



void processInput(GLFWwindow* window)
{
    //float cameraSpeed = 2.5 * deltaTime;

    switch (modelInt) {
    case 1:
        activeModel = psub;
        break;
    case 2:
        activeModel = lightSource;
        break;
    }


  //  float theta_x = activeModel->getTheta_X();
   // float theta_y = activeModel->getTheta_Y();
   // float theta_z = activeModel->getTheta_Z();

    //float pos_x = activeModel->getPos_X();
    //float pos_y = activeModel->getPos_Y();
   // float pos_z = activeModel->getPos_Z();
     

    //---------ROTATION----------
    //x-axis
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
      //  activeModel->setPos_Y(pos_y - 0.03f);
      //  std::cout << "Depth at: " << pos_y << std::endl;

    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
      //  activeModel->setPos_Y(pos_y + 0.03f);
   //     std::cout << "Depth at: " << pos_y << std::endl;
    }

    //y-axis
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
     //   activeModel->setPos_X(pos_x -= 0.00003f);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
       // activeModel->setPos_X(pos_x += 0.00003f);
    }

    //z-axis
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
      //  activeModel->setTheta_Z(theta_z + 0.03f);
     //   activeModel->setPos_X(pos_x - 0.003f);
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
      //  activeModel->setTheta_Z(theta_z - 0.03f);
      //  activeModel->setTheta_Z(theta_z + 0.03f);
      / // activeModel->setPos_X(pos_y + 0.003f);
    }

 //   if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
   //     activeModel->setTheta_Z(theta_z + 0.03f);
  //  }

   // if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
    //    activeModel->setTheta_Z(theta_z - 0.03f);
  //  }

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
      //  activeModel->setTheta_X(theta_x + 0.03f);
    }

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
       // activeModel->setTheta_X(theta_x - 0.03f);
    }

}



void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode) {

    //  glm::vec3 lasCameraPos = Camera.getCameraPos();
    //  glm::vec3 lastCameraFront = Camera.getCameraFront();
     // glm::vec3 lastCameraUp = Camera.getCameraUp();

      //-------EXIT BUTTON-----------
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    //-------SWAP OBJECTS----------
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        if (modelInt == 1) {  //change to light source
            modelInt = 2;
            lightSource->setModelColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)); //color green
            lightsource->setLightColor(glm::vec3(0.0f, 1.0f, 0.0f));
        }

        else {              //change to model
            modelInt = 1;
            lightSource->setModelColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));   //color white
            lightsource->setLightColor(glm::vec3(1.0f, 1.0f, 1.0f));
        }

        std::cout << "Swapped active model" << std::endl;
    }

    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        if (projectionType == "Perspective")
            std::cout << "Already using perspective projection" << std::endl;
        else {
            //Camera->setCameraPos(lastCameraPos);
            //Camera->setCameraFront(lastCameraFront);
            projectionType = "Perspective";
            i = 0;
            std::cout << "Changed projection type" << std::endl;
        }
    }

    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        if (projectionType == "Ortho")
            std::cout << "Already using ortho projection" << std::endl;
        else {
            //lastCameraPos = Camera->getCameraPos();
            //lastCameraFront = Camera->getCameraFront();
            //lastCameraUp = Camera.getCameraUp();
            projectionType = "Ortho";
            i = 1;
            std::cout << "Changed projection type" << std::endl;
        }
    }
}


int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Legaspi,Andrea and Austria,Joshua", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    //mouse callbacks
    glfwSetCursorPosCallback(window, mouse_callback);
    // glfwSetKeyCallback(window, Key_Callback);
    // glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //shaders
    std::fstream vertSrc("Shaders/sample.vert");
    std::stringstream vertBuff;
    vertBuff << vertSrc.rdbuf();
    std::string vertS = vertBuff.str();
    const char* v = vertS.c_str();

    std::fstream fragSrc("Shaders/sample.frag");
    std::stringstream fragBuff;
    fragBuff << fragSrc.rdbuf();
    std::string fragS = fragBuff.str();
    const char* f = fragS.c_str();

    std::fstream lvertSrc("Shaders/lightsample.vert");
    std::stringstream lvertBuff;
    lvertBuff << lvertSrc.rdbuf();
    std::string lvertS = lvertBuff.str();
    const char* lv = lvertS.c_str();

    std::fstream lfragSrc("Shaders/lightsample.frag");
    std::stringstream lfragBuff;
    lfragBuff << lfragSrc.rdbuf();
    std::string lfragS = lfragBuff.str();
    const char* lf = lfragS.c_str();

    glfwMakeContextCurrent(window);
    gladLoadGL();

    glViewport(0, 0, width, height);

    //create and links shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &v, NULL);
    glCompileShader(vertexShader);

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &f, NULL);
    glCompileShader(fragShader);

    GLuint shaderProg = glCreateProgram();
    glAttachShader(shaderProg, vertexShader);
    glAttachShader(shaderProg, fragShader);

    glLinkProgram(shaderProg);

    GLuint lvertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(lvertexShader, 1, &lv, NULL);
    glCompileShader(lvertexShader);

    GLuint lfragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(lfragShader, 1, &lf, NULL);
    glCompileShader(lfragShader);

    GLuint lshaderProg = glCreateProgram();
    glAttachShader(lshaderProg, lvertexShader);
    glAttachShader(lshaderProg, lfragShader);

    glLinkProgram(lshaderProg);

    //load texture
    int img_width, img_height, colorChannels;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* tex_bytes = stbi_load("3D/pshipT.png", &img_width, &img_height, &colorChannels, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_bytes);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(tex_bytes);

    glEnable(GL_DEPTH_TEST);


    //loads the 3D model
    //source: https://free3d.com/3d-model/gun-54829.html
    std::string path = "3D/pship.obj";
    std::vector <tinyobj::shape_t> shapes;
    std::vector <tinyobj::material_t> material;
    std::string warning, error;

    tinyobj::attrib_t attributes;

    bool success = tinyobj::LoadObj(&attributes, &shapes, &material, &warning, &error, path.c_str());

    std::vector<GLfloat> fullVertexData;
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        tinyobj::index_t vData = shapes[0].mesh.indices[i];

        //vertices
        fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3)]);
        fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3 + 1)]);
        fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3 + 2)]);

        //normals
        fullVertexData.push_back(attributes.normals[(vData.normal_index * 3)]);
        fullVertexData.push_back(attributes.normals[(vData.normal_index * 3 + 1)]);
        fullVertexData.push_back(attributes.normals[(vData.normal_index * 3 + 2)]);

        //UVs
        fullVertexData.push_back(attributes.texcoords[(vData.texcoord_index * 2)]);
        fullVertexData.push_back(attributes.texcoords[(vData.texcoord_index * 2 + 1)]);
    }
    //OLD
        /*
        std::vector<GLuint> mesh_indices;
        for (int i = 0; i < shapes[0].mesh.indices.size(); i++)
        {
            mesh_indices.push_back(shapes[0].mesh.indices[i].vertex_index);
        }
        */
        //buffers
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * fullVertexData.size(), fullVertexData.data(), GL_DYNAMIC_DRAW);

    //vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //normals
    GLintptr normalPtr = 3 * sizeof(float);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)normalPtr);
    glEnableVertexAttribArray(1);

    GLintptr uvPtr = 6 * sizeof(float);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)uvPtr);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh_indices.size(), &mesh_indices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    /*int img_width1, img_height1, colorChannels1;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* tex_bytes1 = stbi_load("3D/enemy1T.jpg", &img_width1, &img_height1, &colorChannels1, 0);

    GLuint texture1;
    glGenTextures(1, &texture1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width1, img_height1, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_bytes1);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(tex_bytes1);

    glEnable(GL_DEPTH_TEST);
    */

    //loads the 3D model
    //source: https://free3d.com/3d-model/gun-54829.html
    std::string path1 = "3D/enemy1.obj";
    std::vector <tinyobj::shape_t> shapes1;
    std::vector <tinyobj::material_t> material1;
    std::string warning1, error1;

    tinyobj::attrib_t attributes1;

    bool success1 = tinyobj::LoadObj(&attributes1, &shapes1, &material1, &warning1, &error1, path1.c_str());

    std::vector<GLfloat> fullVertexData1;
    for (int i = 0; i < shapes1[0].mesh.indices.size(); i++) {
        tinyobj::index_t vData1 = shapes1[0].mesh.indices[i];

        //vertices
        fullVertexData1.push_back(attributes1.vertices[(vData1.vertex_index * 3)]);
        fullVertexData1.push_back(attributes1.vertices[(vData1.vertex_index * 3 + 1)]);
        fullVertexData1.push_back(attributes1.vertices[(vData1.vertex_index * 3 + 2)]);

        //normals
        fullVertexData1.push_back(attributes1.normals[(vData1.normal_index * 3)]);
        fullVertexData1.push_back(attributes1.normals[(vData1.normal_index * 3 + 1)]);
        fullVertexData1.push_back(attributes1.normals[(vData1.normal_index * 3 + 2)]);

        //UVs
        fullVertexData1.push_back(attributes1.texcoords[(vData1.texcoord_index * 2)]);
        fullVertexData1.push_back(attributes1.texcoords[(vData1.texcoord_index * 2 + 1)]);
    }

    GLuint e1VAO, e1VBO, e1EBO;
    glGenVertexArrays(1, &e1VAO);
    glGenBuffers(1, &e1VBO);
    glGenBuffers(1, &e1EBO);

    glBindVertexArray(e1VAO);
    glBindBuffer(GL_ARRAY_BUFFER, e1VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * fullVertexData1.size(), fullVertexData1.data(), GL_DYNAMIC_DRAW);

    //vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //normals
    GLintptr normalPtre1 = 3 * sizeof(float);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)normalPtre1);
    glEnableVertexAttribArray(1);

    GLintptr uvPtre1 = 6 * sizeof(float);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)uvPtre1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e1EBO);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    /*int img_width1, img_height1, colorChannels1;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* tex_bytes1 = stbi_load("3D/enemy1T.jpg", &img_width1, &img_height1, &colorChannels1, 0);

    GLuint texture1;
    glGenTextures(1, &texture1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width1, img_height1, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_bytes1);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(tex_bytes1);

    glEnable(GL_DEPTH_TEST);
    */

    //loads the 3D model
    //source: https://free3d.com/3d-model/gun-54829.html
    std::string path2 = "3D/enemy2.obj";
    std::vector <tinyobj::shape_t> shapes2;
    std::vector <tinyobj::material_t> material2;
    std::string warning2, error2;

    tinyobj::attrib_t attributes2;

    bool success2 = tinyobj::LoadObj(&attributes2, &shapes2, &material2, &warning2, &error2, path2.c_str());

    std::vector<GLfloat> fullVertexData2;
    for (int i = 0; i < shapes2[0].mesh.indices.size(); i++) {
        tinyobj::index_t vData2 = shapes2[0].mesh.indices[i];

        //vertices
        fullVertexData2.push_back(attributes2.vertices[(vData2.vertex_index * 3)]);
        fullVertexData2.push_back(attributes2.vertices[(vData2.vertex_index * 3 + 1)]);
        fullVertexData2.push_back(attributes2.vertices[(vData2.vertex_index * 3 + 2)]);

        //normals
        fullVertexData2.push_back(attributes2.normals[(vData2.normal_index * 3)]);
        fullVertexData2.push_back(attributes2.normals[(vData2.normal_index * 3 + 1)]);
        fullVertexData2.push_back(attributes2.normals[(vData2.normal_index * 3 + 2)]);

        //UVs
        fullVertexData2.push_back(attributes2.texcoords[(vData2.texcoord_index * 2)]);
        fullVertexData2.push_back(attributes2.texcoords[(vData2.texcoord_index * 2 + 1)]);
    }

    GLuint e2VAO, e2VBO, e2EBO;
    glGenVertexArrays(1, &e2VAO);
    glGenBuffers(1, &e2VBO);
    glGenBuffers(1, &e2EBO);

    glBindVertexArray(e2VAO);
    glBindBuffer(GL_ARRAY_BUFFER, e2VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * fullVertexData2.size(), fullVertexData2.data(), GL_DYNAMIC_DRAW);

    //vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //normals
    GLintptr normalPtre2 = 3 * sizeof(float);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)normalPtre2);
    glEnableVertexAttribArray(1);

    GLintptr uvPtre2 = 6 * sizeof(float);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)uvPtre2);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e2EBO);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    /*int img_width1, img_height1, colorChannels1;

 stbi_set_flip_vertically_on_load(true);
 unsigned char* tex_bytes1 = stbi_load("3D/enemy1T.jpg", &img_width1, &img_height1, &colorChannels1, 0);

 GLuint texture1;
 glGenTextures(1, &texture1);
 glActiveTexture(GL_TEXTURE0);
 glBindTexture(GL_TEXTURE_2D, texture1);

 glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width1, img_height1, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_bytes1);
 glGenerateMipmap(GL_TEXTURE_2D);
 stbi_image_free(tex_bytes1);

 glEnable(GL_DEPTH_TEST);
 */

 //loads the 3D model
 //source: https://free3d.com/3d-model/gun-54829.html
    std::string path3 = "3D/enemy3.obj";
    std::vector <tinyobj::shape_t> shapes3;
    std::vector <tinyobj::material_t> material3;
    std::string warning3, error3;

    tinyobj::attrib_t attributes3;

    bool success3 = tinyobj::LoadObj(&attributes3, &shapes3, &material3, &warning3, &error3, path3.c_str());

    std::vector<GLfloat> fullVertexData3;
    for (int i = 0; i < shapes3[0].mesh.indices.size(); i++) {
        tinyobj::index_t vData3 = shapes3[0].mesh.indices[i];

        //vertices
        fullVertexData3.push_back(attributes3.vertices[(vData3.vertex_index * 3)]);
        fullVertexData3.push_back(attributes3.vertices[(vData3.vertex_index * 3 + 1)]);
        fullVertexData3.push_back(attributes3.vertices[(vData3.vertex_index * 3 + 2)]);

        //normals
        fullVertexData3.push_back(attributes3.normals[(vData3.normal_index * 3)]);
        fullVertexData3.push_back(attributes3.normals[(vData3.normal_index * 3 + 1)]);
        fullVertexData3.push_back(attributes3.normals[(vData3.normal_index * 3 + 2)]);

        //UVs
        fullVertexData3.push_back(attributes3.texcoords[(vData3.texcoord_index * 2)]);
        fullVertexData3.push_back(attributes3.texcoords[(vData3.texcoord_index * 2 + 1)]);
    }

    GLuint e3VAO, e3VBO, e3EBO;
    glGenVertexArrays(1, &e3VAO);
    glGenBuffers(1, &e3VBO);
    glGenBuffers(1, &e3EBO);

    glBindVertexArray(e3VAO);
    glBindBuffer(GL_ARRAY_BUFFER, e3VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * fullVertexData3.size(), fullVertexData3.data(), GL_DYNAMIC_DRAW);

    //vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //normals
    GLintptr normalPtre3 = 3 * sizeof(float);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)normalPtre3);
    glEnableVertexAttribArray(1);

    GLintptr uvPtre3 = 6 * sizeof(float);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)uvPtre3);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e3EBO);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    /*int img_width1, img_height1, colorChannels1;

stbi_set_flip_vertically_on_load(true);
unsigned char* tex_bytes1 = stbi_load("3D/enemy1T.jpg", &img_width1, &img_height1, &colorChannels1, 0);

GLuint texture1;
glGenTextures(1, &texture1);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, texture1);

glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width1, img_height1, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_bytes1);
glGenerateMipmap(GL_TEXTURE_2D);
stbi_image_free(tex_bytes1);

glEnable(GL_DEPTH_TEST);
*/

//loads the 3D model
//source: https://free3d.com/3d-model/gun-54829.html
    std::string path4 = "3D/enemy4.obj";
    std::vector <tinyobj::shape_t> shapes4;
    std::vector <tinyobj::material_t> material4;
    std::string warning4, error4;

    tinyobj::attrib_t attributes4;

    bool success4 = tinyobj::LoadObj(&attributes4, &shapes4, &material4, &warning4, &error4, path4.c_str());

    std::vector<GLfloat> fullVertexData4;
    for (int i = 0; i < shapes4[0].mesh.indices.size(); i++) {
        tinyobj::index_t vData4 = shapes4[0].mesh.indices[i];

        //vertices
        fullVertexData4.push_back(attributes4.vertices[(vData4.vertex_index * 3)]);
        fullVertexData4.push_back(attributes4.vertices[(vData4.vertex_index * 3 + 1)]);
        fullVertexData4.push_back(attributes4.vertices[(vData4.vertex_index * 3 + 2)]);

        //normals
        fullVertexData4.push_back(attributes4.normals[(vData4.normal_index * 3)]);
        fullVertexData4.push_back(attributes4.normals[(vData4.normal_index * 3 + 1)]);
        fullVertexData4.push_back(attributes4.normals[(vData4.normal_index * 3 + 2)]);

        //UVs
        fullVertexData4.push_back(attributes4.texcoords[(vData4.texcoord_index * 2)]);
        fullVertexData4.push_back(attributes4.texcoords[(vData4.texcoord_index * 2 + 1)]);
    }

    GLuint e4VAO, e4VBO, e4EBO;
    glGenVertexArrays(1, &e4VAO);
    glGenBuffers(1, &e4VBO);
    glGenBuffers(1, &e4EBO);

    glBindVertexArray(e4VAO);
    glBindBuffer(GL_ARRAY_BUFFER, e4VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * fullVertexData4.size(), fullVertexData4.data(), GL_DYNAMIC_DRAW);

    //vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //normals
    GLintptr normalPtre4 = 3 * sizeof(float);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)normalPtre4);
    glEnableVertexAttribArray(1);

    GLintptr uvPtre4 = 6 * sizeof(float);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)uvPtre4);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e4EBO);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    /*int img_width1, img_height1, colorChannels1;

stbi_set_flip_vertically_on_load(true);
unsigned char* tex_bytes1 = stbi_load("3D/enemy1T.jpg", &img_width1, &img_height1, &colorChannels1, 0);

GLuint texture1;
glGenTextures(1, &texture1);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, texture1);

glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width1, img_height1, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_bytes1);
glGenerateMipmap(GL_TEXTURE_2D);
stbi_image_free(tex_bytes1);

glEnable(GL_DEPTH_TEST);
*/  

//loads the 3D model
//source: https://free3d.com/3d-model/gun-54829.html
    std::string path5 = "3D/enemy5.obj";
    std::vector <tinyobj::shape_t> shapes5;
    std::vector <tinyobj::material_t> material5;
    std::string warning5, error5;

    tinyobj::attrib_t attributes5;

    bool success5 = tinyobj::LoadObj(&attributes5, &shapes5, &material5, &warning5, &error5, path5.c_str());

    std::vector<GLfloat> fullVertexData5;
    for (int i = 0; i < shapes5[0].mesh.indices.size(); i++) {
        tinyobj::index_t vData5 = shapes5[0].mesh.indices[i];

        //vertices
        fullVertexData5.push_back(attributes5.vertices[(vData5.vertex_index * 3)]);
        fullVertexData5.push_back(attributes5.vertices[(vData5.vertex_index * 3 + 1)]);
        fullVertexData5.push_back(attributes5.vertices[(vData5.vertex_index * 3 + 2)]);

        //normals
        fullVertexData5.push_back(attributes5.normals[(vData5.normal_index * 3)]);
        fullVertexData5.push_back(attributes5.normals[(vData5.normal_index * 3 + 1)]);
        fullVertexData5.push_back(attributes5.normals[(vData5.normal_index * 3 + 2)]);

        //UVs
        fullVertexData5.push_back(attributes5.texcoords[(vData5.texcoord_index * 2)]);
        fullVertexData5.push_back(attributes5.texcoords[(vData5.texcoord_index * 2 + 1)]);
    }

    GLuint e5VAO, e5VBO, e5EBO;
    glGenVertexArrays(1, &e5VAO);
    glGenBuffers(1, &e5VBO);
    glGenBuffers(1, &e5EBO);

    glBindVertexArray(e5VAO);
    glBindBuffer(GL_ARRAY_BUFFER, e5VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * fullVertexData5.size(), fullVertexData5.data(), GL_DYNAMIC_DRAW);

    //vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //normals
    GLintptr normalPtre5 = 3 * sizeof(float);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)normalPtre5);
    glEnableVertexAttribArray(1);

    GLintptr uvPtre5 = 6 * sizeof(float);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)uvPtre5);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e5EBO);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    /*int img_width1, img_height1, colorChannels1;

stbi_set_flip_vertically_on_load(true);
unsigned char* tex_bytes1 = stbi_load("3D/enemy1T.jpg", &img_width1, &img_height1, &colorChannels1, 0);

GLuint texture1;
glGenTextures(1, &texture1);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, texture1);

glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width1, img_height1, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_bytes1);
glGenerateMipmap(GL_TEXTURE_2D);
stbi_image_free(tex_bytes1);

glEnable(GL_DEPTH_TEST);
*/

//loads the 3D model
//source: https://free3d.com/3d-model/gun-54829.html
    std::string path6 = "3D/enemy6.obj";
    std::vector <tinyobj::shape_t> shapes6;
    std::vector <tinyobj::material_t> material6;
    std::string warning6, error6;

    tinyobj::attrib_t attributes6;

    bool success6 = tinyobj::LoadObj(&attributes6, &shapes6, &material6, &warning6, &error6, path6.c_str());

    std::vector<GLfloat> fullVertexData6;
    for (int i = 0; i < shapes6[0].mesh.indices.size(); i++) {
        tinyobj::index_t vData6 = shapes6[0].mesh.indices[i];

        //vertices
        fullVertexData6.push_back(attributes6.vertices[(vData6.vertex_index * 3)]);
        fullVertexData6.push_back(attributes6.vertices[(vData6.vertex_index * 3 + 1)]);
        fullVertexData6.push_back(attributes6.vertices[(vData6.vertex_index * 3 + 2)]);

        //normals
        fullVertexData6.push_back(attributes6.normals[(vData6.normal_index * 3)]);
        fullVertexData6.push_back(attributes6.normals[(vData6.normal_index * 3 + 1)]);
        fullVertexData6.push_back(attributes6.normals[(vData6.normal_index * 3 + 2)]);

        //UVs
        fullVertexData6.push_back(attributes6.texcoords[(vData6.texcoord_index * 2)]);
        fullVertexData6.push_back(attributes6.texcoords[(vData6.texcoord_index * 2 + 1)]);
    }

    GLuint e6VAO, e6VBO, e6EBO;
    glGenVertexArrays(1, &e6VAO);
    glGenBuffers(1, &e6VBO);
    glGenBuffers(1, &e6EBO);

    glBindVertexArray(e6VAO);
    glBindBuffer(GL_ARRAY_BUFFER, e6VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * fullVertexData6.size(), fullVertexData6.data(), GL_DYNAMIC_DRAW);

    //vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //normals
    GLintptr normalPtre6 = 3 * sizeof(float);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)normalPtre6);
    glEnableVertexAttribArray(1);

    GLintptr uvPtre6 = 6 * sizeof(float);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)uvPtre6);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e6EBO);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  /* //loads the 3D model
//source: https://free3d.com/3d-model/gun-54829.html
    std::string path1 = "3D/smallball.obj";
    std::vector <tinyobj::shape_t> shapes1;
    std::vector <tinyobj::material_t> material1;
    std::string warning1, error1;

    tinyobj::attrib_t attributes1;

    bool success1 = tinyobj::LoadObj(&attributes1, &shapes1, &material1, &warning1, &error1, path1.c_str());

    std::vector<GLuint> mesh_indices1;
    for (int i = 0; i < shapes1[0].mesh.indices.size(); i++)
    {
        mesh_indices1.push_back(shapes1[0].mesh.indices[i].vertex_index);
    }
    //OLD
        /*
        std::vector<GLuint> mesh_indices;
        for (int i = 0; i < shapes[0].mesh.indices.size(); i++)
        {
            mesh_indices.push_back(shapes[0].mesh.indices[i].vertex_index);
        }*/

        //buffers
   /* GLuint sphereVAO, sphereVBO, sphereEBO;
    glGenVertexArrays(1, &sphereVAO);
    glGenBuffers(1, &sphereVBO);
    glGenBuffers(1, &sphereEBO);

    glBindVertexArray(sphereVAO);
    glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * attributes1.vertices.size(), &attributes1.vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh_indices1.size(), &mesh_indices1[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    std::cout << "Press [ESCAPE] key to exit" << std::endl/*/


    //------------SKYBOX RELATED--------------
    //LOAD VERTEX AND FRAGMENT SHADER
    std::fstream skyboxVertSrc("Shaders/sky.vert");
    std::stringstream skyboxVertBuff;
    skyboxVertBuff << skyboxVertSrc.rdbuf();
    std::string skyboxVertS = skyboxVertBuff.str();
    const char* sky_v = skyboxVertS.c_str();

    std::fstream skyboxFragSrc("Shaders/sky.frag");
    std::stringstream skyboxFragBuff;
    skyboxFragBuff << skyboxFragSrc.rdbuf();

    std::string sky_fragS = skyboxFragBuff.str();
    const char* sky_f = sky_fragS.c_str();

    //COMPILE SHADERS
    GLuint vertexShaderSkybox = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderSkybox, 1, &sky_v, NULL);
    glCompileShader(vertexShaderSkybox);

    GLuint fragShaderSkybox = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShaderSkybox, 1, &sky_f, NULL);
    glCompileShader(fragShaderSkybox);

    //CREATE SHADER AND ATTACH FRAG AND VERTEX SHADERS
    GLuint skyboxShaderProg = glCreateProgram();
    glAttachShader(skyboxShaderProg, vertexShaderSkybox);
    glAttachShader(skyboxShaderProg, fragShaderSkybox);

    //COMPILATION
    glLinkProgram(skyboxShaderProg);

    //CLEANUP
    glDeleteShader(vertexShaderSkybox);
    glDeleteShader(fragShaderSkybox);

    //SKYBOX
/*
  7--------6
 /|       /|
4--------5 |
| |      | |
| 3------|-2
|/       |/
0--------1
*/
//Vertices for the cube
    float skyboxVertices[]{
        -1.f, -1.f, 1.f, //0
        1.f, -1.f, 1.f,  //1
        1.f, -1.f, -1.f, //2
        -1.f, -1.f, -1.f,//3
        -1.f, 1.f, 1.f,  //4
        1.f, 1.f, 1.f,   //5
        1.f, 1.f, -1.f,  //6
        -1.f, 1.f, -1.f  //7
    };

    //Skybox Indices
    unsigned int skyboxIndices[]{
        1,2,6,
        6,5,1,

        0,4,7,
        7,3,0,

        4,5,6,
        6,7,4,

        0,3,2,
        2,1,0,

        0,1,5,
        5,4,0,

        3,7,6,
        6,2,3
    };

    //-----------SKYBOX BUFFERS------------------
    //CREATE VAO, VBO, AND EBO
    unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glGenBuffers(1, &skyboxEBO);

    //ADD SKYBOX DATA TO THE BUFFERS
    //VAO AND VBO
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_INT) * 36, &skyboxIndices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);

    std::string facesSkybox[]{
        "Skybox/px.png",
        "Skybox/nx.png",
        "Skybox/py.png",
        "Skybox/ny.png",
        "Skybox/pz.png",
        "Skybox/nz.png"
    };

    std::string facesSkyboxaa[]{
        "Skybox/rainbow_rt.png",    //right
        "Skybox/rainbow_lf.png",    //left
        "Skybox/rainbow_up.png",    //up
        "Skybox/rainbow_dn.png",    //down
        "Skybox/rainbow_ft.png",    //front
        "Skybox/rainbow_bk.png",    //back
    };

    //------------INITIALIZATION OF CUBEMAP------------
    unsigned int skyboxTex;
    glGenTextures(1, &skyboxTex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    for (unsigned int i = 0; i < 6; i++) {
        int w, h, skyCChannel;

        stbi_set_flip_vertically_on_load(false);

        unsigned char* data = stbi_load(facesSkybox[i].c_str(), &w, &h, &skyCChannel, 0);

        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            
            stbi_image_free(data);
        }
    }

    stbi_set_flip_vertically_on_load(true);




    PointLight pointLight;
    //spawn model on run
 //   spawnModel();a

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //input
        processInput(window);
        glfwSetKeyCallback(window, Key_Callback);

     //   glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 viewMatrix = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        //this->cameraPos, this->cameraPos + this->cameraFront, this->cameraUp


        if (projectionType == "Perspective") {
            PerspectiveCamera perspective;
            projection = perspective.giveProjection(width, height);
            Camera->bindProjection(shaderProg, projection);
            Camera->bindProjection(lshaderProg, projection);
            viewMatrix = Camera->bindView(shaderProg);
            viewMatrix = Camera->bindView(lshaderProg);
        }
        else if (projectionType == "Ortho") {
            OrthoCamera ortho;
            projection = ortho.giveProjection();
            Camera->bindProjection(shaderProg, projection);
            Camera->bindProjection(lshaderProg, projection);
            viewMatrix = ortho.bindView(shaderProg);
            viewMatrix = ortho.bindView(lshaderProg);
;            //implement smth that will retain old mouse's position when changing back to perspective
        }

        //---------SKYBOX RELATED ------
        glDepthMask(GL_FALSE);
        glDepthFunc(GL_LEQUAL);
        glUseProgram(skyboxShaderProg);

        //CAST CAMERA
        glm::mat4 sky_view = glm::mat4(1.0f);
        sky_view = glm::mat4(glm::mat3(viewMatrix));

        unsigned int skyvoxViewLoc = glGetUniformLocation(skyboxShaderProg, "view");
        glUniformMatrix4fv(skyvoxViewLoc, 1, GL_FALSE, glm::value_ptr(sky_view));

        unsigned int skyboxProjLoc = glGetUniformLocation(skyboxShaderProg, "projection");
        glUniformMatrix4fv(skyboxProjLoc, 1, GL_FALSE, glm::value_ptr(projection));

        //DRAW SKYBOX
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);




        glm::vec3 lightPosition = lightSource->getPosition();
        pointLight.setLightPoint(lightPosition);


        DirectionLight dirLight;
        dirLight.bindLightDirection(shaderProg);

        Light light;
        light.bindLighting(shaderProg);

        pointLight.bindLightPoint(lshaderProg);

        //draw the models
        psub->drawModel(fullVertexData, texture, shaderProg, &VAO, 8);

        esub1->setScale(glm::vec3(.05f, .05f, .05f));
        esub1->setPosition(glm::vec3(.3f, .3f, .3f));
        esub1->drawModel(fullVertexData1, texture, shaderProg, &e1VAO, 8);

        esub2->setScale(glm::vec3(.05f, .05f, .05f));
        esub2->setPosition(glm::vec3(-0.5f, -0.5f, .5f));
        esub2->drawModel(fullVertexData2, texture, shaderProg, &e2VAO, 8);

        esub3->setScale(glm::vec3(.007f, .007f, .007f));
        esub3->setPosition(glm::vec3(-0.2f, -0.2f, .2f));
        esub3->drawModel(fullVertexData3, texture, shaderProg, &e3VAO, 8);

        esub4->setScale(glm::vec3(.07f, .07f, .07f));
        esub4->setPosition(glm::vec3(-0.8f, -0.8f, .8f));
        esub4->drawModel(fullVertexData4, texture, shaderProg, &e4VAO, 8);

        esub5->setScale(glm::vec3(.09f, .09f, .09f));
        esub5->setPosition(glm::vec3(-0.8f, 0.8f, .7f));
        esub5->drawModel(fullVertexData5, texture, shaderProg, &e5VAO, 8);

        esub6->setScale(glm::vec3(.09f, .09f, .09f));
        esub6->setPosition(glm::vec3(0.4f, -0.4f, .2f));
        esub6->drawModel(fullVertexData6, texture, shaderProg, &e6VAO, 8);



        //draw(?) lightsource below 
        //swap front and back buffers 
        glfwSwapBuffers(window);

        // Poll for and process events 
        glfwPollEvents();
    }

    //delete buffers
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &e1VAO);
    glDeleteBuffers(1, &e1VBO);
    glDeleteVertexArrays(1, &e2VAO);
    glDeleteBuffers(1, &e2VBO);
    glDeleteVertexArrays(1, &e3VAO);
    glDeleteBuffers(1, &e3VBO);
    glDeleteVertexArrays(1, &e4VAO);
    glDeleteBuffers(1, &e4VBO);
    glDeleteVertexArrays(1, &e5VAO);
    glDeleteBuffers(1, &e5VBO);
    glDeleteVertexArrays(1, &e6VAO);
    glDeleteBuffers(1, &e6VBO);
    // glDeleteBuffers(1, &EBO);

    glfwTerminate();

    return 0;
}