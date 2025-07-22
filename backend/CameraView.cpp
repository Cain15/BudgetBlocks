//
// Created by cain on 22/07/25.
//

#include "CameraView.h"

std::pair<int, int> CameraView::getResolution() const {
    return {width, height};
}

const glm::vec3 &CameraView::getPosition() const {
    return Position;
}

void CameraView::setPosition(const glm::vec3 &position) {
    Position = position;
}

const glm::vec3 &CameraView::getOrientation() const {
    return Orientation;
}

void CameraView::setOrientation(const glm::vec3 &orientation) {
    Orientation = orientation;
}

const glm::vec3 &CameraView::getUp() const {
    return Up;
}

void CameraView::setUp(const glm::vec3 &up) {
    Up = up;
}

void CameraView::setResolution(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;
}
