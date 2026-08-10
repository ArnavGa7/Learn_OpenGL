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
void Object::Draw(glm::mat4 view, glm::mat4 projection,glm::vec3 light_Color, glm::vec3 Light_Position,glm::vec3 camera_Position){

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

        // 
      
        glUniform3fv(glGetUniformLocation(shader.ID, "view_Position"), 1, glm::value_ptr(camera_Position));

        // This is from light.frag
        glUniform3fv(glGetUniformLocation(shader.ID, "light_Color"), 1, glm::value_ptr(light_Color));


        // For the Light Struct
        glUniform3f(glGetUniformLocation(shader.ID, "light.ambient"), 0.3f, 0.3f, 0.3f);
        glUniform3f(glGetUniformLocation(shader.ID, "light.diffuse"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(shader.ID, "light.specular"), 1.0f, 1.0f, 1.0f);

        glUniform1f(glGetUniformLocation(shader.ID, "light.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(shader.ID, "light.linear"),  0.00018f);
        glUniform1f(glGetUniformLocation(shader.ID, "light.quadratic"), 0.009f);


        glUniform3fv(glGetUniformLocation(shader.ID, "light.Position"), 1, glm::value_ptr(Light_Position));
        glUniform1f(glGetUniformLocation(shader.ID,  "light.innercutoff"), glm::cos(glm::radians(12.5f)));
        glUniform1f(glGetUniformLocation(shader.ID, "light.outercutoff"), glm::cos(glm::radians(17.5f)));

        // Light Maps and Texture
        /* Diffuse Texture is for the whole cube But specluar texture is the Metle part of the Texture so the onlt Matel part shines!*/
        glUniform1i(glGetUniformLocation(shader.ID, "material.diffuse"), 0);
        glUniform1i(glGetUniformLocation(shader.ID, "material.specular"), 1);
        glUniform1f(glGetUniformLocation(shader.ID, "material.shininess"), 32.0f);
        vao.Bind();


        // Draw the World
        glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_INT, 0);
    
   
}
