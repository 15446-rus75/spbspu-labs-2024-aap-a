#include "complexquad.hpp"
#include <cmath>
#include <stdexcept>
#include "shape.hpp"
namespace
{
  double getLenghtSide(kiselev::point_t p1, kiselev::point_t p2)
  {
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
  }
  bool isTriangle(kiselev::point_t p1, kiselev::point_t p2, kiselev::point_t p3)
  {
    const double lenght1 = getLenghtSide(p1, p2);
    const double lenght2 = getLenghtSide(p1, p3);
    const double lenght3 = getLenghtSide(p3, p2);
    return lenght1 < lenght2 + lenght3 || lenght2 < lenght1 + lenght3 || lenght3 < lenght1 + lenght2;
  }
  kiselev::point_t findP(kiselev::point_t p1, kiselev::point_t p2, kiselev::point_t p3, kiselev::point_t p4, bool& isIntersect)
  {
    const double A1 = p2.y - p1.y;
    const double B1 = p2.x - p1.x;
    const double C1 = p1.x * A1 + p1.y * B1;
    const double A2 = p4.y - p3.y;
    const double B2 = p4.x - p3.x;
    const double C2 = p3.x * (A2) + p3.y * (B2);
    const double determiner = A1 * B2 - B1 * A2;
    if (determiner == 0)
    {
      isIntersect = false;
      return { 0, 0 };
    }
    isIntersect = true;
    const double x = (C1 * B2 - C2 * B1) / determiner;
    const double y = (C2 * A1 - A2 * C1) / determiner;
    return { x, y };
  }
}
kiselev::Complexquad::Complexquad(point_t p1, point_t p2, point_t p3, point_t p4):
  size(4),
  arr{ p1, p2, p3, p4 }
{
  bool isIntersect = true;
  point_t centre = findP(p1, p2, p3, p4, isIntersect);
  if (!isTriangle(p1, p4, centre) || !isTriangle(p2, p3, centre) || !isIntersect || (p4.x > p1.x && p3.x > p1.x))
  {
    throw std::invalid_argument("Incorrect coordinates");
  }
}
kiselev::rectangle_t kiselev::Complexquad::getFrameRect() const
{
  const double leftDownX = std::min(std::min(arr[0].x, arr[1].x), std::min(arr[2].x, arr[3].x));
  const double leftDownY = std::min(std::min(arr[0].y, arr[1].y), std::min(arr[2].y, arr[3].y));
  const double rightUpX = std::max(std::max(arr[0].x, arr[1].x), std::max(arr[2].x, arr[3].x));
  const double rightUpY = std::max(std::max(arr[0].y, arr[1].y), std::max(arr[2].y, arr[3].y));
  const point_t centre = { leftDownX + (rightUpX - leftDownX) / 2, leftDownY + (rightUpY - leftDownY) / 2 };
  return { rightUpX - leftDownX, rightUpY - leftDownY, centre };
}
double kiselev::Complexquad::getArea() const
{
  const point_t centre = getFrameRect().pos;
  const double lenghtP1p4 = getLenghtSide(arr[0], arr[3]);
  const double lenghtP1centre = getLenghtSide(arr[0], centre);
  const double lenghtP4centre = getLenghtSide(centre, arr[3]);
  const double semiPer1 = (lenghtP1p4 + lenghtP1centre + lenghtP4centre) / 2;
  const double area1 = std::sqrt(semiPer1 * (semiPer1 - lenghtP1p4) * (semiPer1 - lenghtP1centre) * (semiPer1 - lenghtP4centre));
  const double lenghtP2p3 = getLenghtSide(arr[2], arr[1]);
  const double lenghtP2centre = getLenghtSide(centre, arr[1]);
  const double lenghtP3centre = getLenghtSide(centre, arr[2]);
  const double semiPer2 = (lenghtP2p3 + lenghtP2centre + lenghtP3centre) / 2;
  const double area2 = std::sqrt(semiPer2 * (semiPer2 - lenghtP2p3) * (semiPer2 - lenghtP2centre) * (semiPer2 - lenghtP3centre));
  return area1 + area2;
}
void kiselev::Complexquad::move(point_t a)
{
  const point_t centre = getFrameRect().pos;
  const double moveForX = a.x - centre.x;
  const double moveForY = a.y - centre.y;
  move(moveForX, moveForY);
}
void kiselev::Complexquad::move(double dx, double dy)
{
  for (size_t i = 0; i < size; ++i)
  {
    arr[i] = movePoint(arr[i], dx, dy);
  }
}
void kiselev::Complexquad::scale(double k)
{
  const point_t centre = getFrameRect().pos;
  for (size_t i = 0; i < size; ++i)
  {
    arr[i] = scalePoint(arr[i], centre, k);
  }
}
kiselev::Shape* kiselev::Complexquad::clone() const
{
  return new Complexquad(*this);
}
