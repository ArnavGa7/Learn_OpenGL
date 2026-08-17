#include "Object.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

// Object Function 
Object::Object(GLfloat* vertices, GLsizeiptr vertexSize, GLuint* indices, GLsizeiptr indexSize, const char* vertexShader, const char* fragmentShader) : shader(vertexShader, fragmentShader)
{
    Position = glm::vec3(0.0f);
    Rotation = glm::vec3(0.0f);
    Scale = glm::vec3(1.0f);
    Color = glm::vec3(1.0f, 1.0f, 1.0f);
    angle = 0.0f;
    vao.Bind();
    
    vbo = new VBO(vertices, vertexSize);
    ebo = new EBO(indices, indexSize);

    // Link VBO, VAO and Attributes;
    vao.LinkAttrib(*vbo, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
    vao.LinkAttrib(*vbo, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.LinkAttrib(*vbo, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    vao.LinkAttrib(*vbo, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    vao.Unbind();

    IndexCount = indexSize / sizeof(GLuint);
}

// Draw Function 
void Object::Draw(glm::mat4 view, glm::mat4 projection,glm::vec3 light_Color, glm::vec3 Light_Position1,glm::vec3 camera_Position, glm::vec3 cube_Color){

        shader.Active();

  
        // Create the Model Matrix
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, Position);
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        model = glm::scale(model, Scale);


        //Draw the Object in the 3D World
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));


        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "Meshmodel"),1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "Meshview"),1,GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "Meshprojection"),1,GL_FALSE, glm::value_ptr(projection));
        glUniform3fv(glGetUniformLocation(shader.ID, "Color"), 1, glm::value_ptr(cube_Color));

        // This is from light.frag
        glUniform3fv(glGetUniformLocation(shader.ID, "light_Color"), 1, glm::value_ptr(light_Color));

        vao.Bind();


        // Draw the World
        glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_INT, 0);
    
   
}
