//
// Created by cain on 22/07/25.
//

#ifndef BUDGETBLOCKS_CAMERAVIEW_H
#define BUDGETBLOCKS_CAMERAVIEW_H

#include <glm/glm.hpp>

class CameraView {
private:
    int width;
    int height;
    glm::vec3 Position;
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
public:
    [[nodiscard]] std::pair<int, int> getResolution() const;

    CameraView(int width, int height, glm::vec3 position) : width(width), height(height), Position(position) {}

    [[nodiscard]] const glm::vec3 &getPosition() const;

    void setPosition(const glm::vec3 &position);

    [[nodiscard]] const glm::vec3 &getOrientation() const;

    void setOrientation(const glm::vec3 &orientation);

    [[nodiscard]] const glm::vec3 &getUp() const;

    void setUp(const glm::vec3 &up);

    void setResolution(int newWidth, int newHeight);

};
#endif

//BUDGETBLOCKS_CAMERAVIEW_H
