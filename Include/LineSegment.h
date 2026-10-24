#pragma once
#include "Point2D.h"

class PrimitiveRenderer;

class LineSegment
{
public:
    LineSegment();
    LineSegment(const Point2D& start, const Point2D& end);
    LineSegment(float x0, float y0, float x1, float y1);

    Point2D getStart() const;
    Point2D getEnd() const;
    void setStart(const Point2D& start);
    void setEnd(const Point2D& end);

    void draw(PrimitiveRenderer& renderer, bool useIncremental = false, sf::Color color = sf::Color::White) const;

private:
    Point2D m_start;
    Point2D m_end;
};