#include "rectangle.hpp"
#include <stdexcept>
#include "base-types.hpp"

double maslov::Rectangle::getArea() const
{
  return (upperRightCorner_.x - lowerLeftCorner_.x) * (upperRightCorner_.y - lowerLeftCorner_.y);
}
maslov::rectangle_t maslov::Rectangle::getFrameRect() const
{
  double centreForX = lowerLeftCorner_.x + (upperRightCorner_.x - lowerLeftCorner_.x) / 2;
  double centreForY = lowerLeftCorner_.y + (upperRightCorner_.y - lowerLeftCorner_.y) / 2;
  return { upperRightCorner_.x - lowerLeftCorner_.x, upperRightCorner_.y - lowerLeftCorner_.y, { centreForX, centreForY } };
}
void maslov::Rectangle::move(point_t s)
{
  point_t centre = this->getFrameRect().pos;
  double moveX = s.x - centre.x;
  double moveY = s.y - centre.y;
  lowerLeftCorner_.x += moveX;
  lowerLeftCorner_.y += moveY;
  upperRightCorner_.x += moveX;
  upperRightCorner_.y += moveY;
}
void maslov::Rectangle::move(double dx, double dy)
{
  lowerLeftCorner_.x += dx;
  lowerLeftCorner_.y += dy;
  upperRightCorner_.x += dx;
  upperRightCorner_.y += dy;
}

void maslov::Rectangle::scale(double k)
{
  point_t centre = this->getFrameRect().pos;
  lowerLeftCorner_.x = centre.x + (lowerLeftCorner_.x - centre.x) * k;
  upperRightCorner_.y = centre.y + (lowerLeftCorner_.y - centre.y) * k;
  upperRightCorner_.x = centre.x + (upperRightCorner_.x - centre.x) * k;
  upperRightCorner_.y = centre.y + (upperRightCorner_.y - centre.y) * k;
}
