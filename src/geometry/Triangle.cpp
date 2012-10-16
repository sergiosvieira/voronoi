#include <geometry/Triangle.h>
#include <geometry/Line.h>

using namespace geometry;

Triangle::Triangle(const Point& a, const Point& b, const Point& c) : a(a), b(b), c(c)
{
}

Circle Triangle::circumcircle() const
{
	Point ab = b-a;
	Point bc = c-b;
	
	if (ab.x()*bc.y()-ab.y()*bc.x()==0) return Circle(); // all points on a line
	
	Point center = Line::forNormal((a+b)/2, ab).intersection(Line::forNormal((b+c)/2,bc));
	real r = 0;
	if (center.isValid()) r = (center-a).length();
	
	return Circle(center, r);
}

bool Triangle::contains(const Point& p) const
{
	return Line::segment(b, c).sameSide(p, a) && Line::segment(a, c).sameSide(p, b) && Line::segment(a, b).sameSide(p, c);
}

bool Triangle::isClockwise() const
{
	Point ab(b-a);
	Point bc(c-b);
	return ab.x()*bc.y()-ab.y()*bc.x()<0;
}