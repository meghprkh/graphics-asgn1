#include "basket.h"
#include "main.h"

Basket::Basket(brick_color_t color)
{
    this->color = color;
    // GL3 accepts only Triangles. Quads are not supported
    static const GLfloat vertex_buffer_data [] = {
      -0.5,-0.3,0, // vertex 1
      0.5,-0.3,0, // vertex 2
      0.5, 0.3,0, // vertex 3

      0.5, 0.3,0, // vertex 3
      -0.5, 0.3,0, // vertex 4
      -0.5,-0.3,0  // vertex 1
    };

    color_t color_s;
    if (color == BRICK_RED) color_s = COLOR_RED;
    else if (color == BRICK_GREEN) color_s = COLOR_GREEN;

    // create3DObject creates and returns a handle to a VAO that can be used later
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_s, GL_FILL);
}

void Basket::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translateRectangle = glm::translate (this->position);        // glTranslatef
    Matrices.model *= translateRectangle;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Basket::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Basket::move(direction_t dir) {
    if (dir == DIR_LEFT && this->position.x > -3.5) this->position.x -= BASKET_SPEED;
    else if (dir == DIR_RIGHT && this->position.x < 3.5) this->position.x += BASKET_SPEED;
}

bounding_box_t Basket::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 1, 0.6 };
    return bbox;
}
