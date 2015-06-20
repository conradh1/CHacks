/*
 *          File: main1.cpp
 * Last Modified: January 31, 2000
 *         Topic: Modules, Separate Compilation, Using Make Files
 * ----------------------------------------------------------------
 */

#include <iostream.h>


class Point
{
public:
  Point();
  Point(int xval, int yval);
  void move(int dx, int dy);
  int get_x() const;
  int get_y() const;

private:
  int x;
  int y;
};

Point::Point()
{
  x = 0;
  y = 0;
}

Point::Point(int xval, int yval)
{
  x = xval;
  y = yval;
}

void Point::move(int dx, int dy)
{
  x += dx;
  y += dy;
}

int Point::get_x() const
{
  return x;
}

int Point::get_y() const
{
  return y;
}


class Rectangle
{
public:
  Rectangle();
  Rectangle(Point bl, Point tr);
  void move(int dx, int dy);
  Point get_bottom_left() const;
  Point get_top_right() const;
  int width() const;
  int height() const;
  int area() const;

private:
  Point bottom_left;
  Point top_right;
};

Rectangle::Rectangle()
{
  // Do nothing since the 2 Points will initialize themselves.
}

Rectangle::Rectangle(Point bl, Point tr)
{
  bottom_left = bl;
  top_right = tr;
}

void Rectangle::move(int dx, int dy)
{
  bottom_left.move(dx, dy);
  top_right.move(dx, dy);
}

Point Rectangle::get_bottom_left() const
{
  return bottom_left;
}

Point Rectangle::get_top_right() const
{
  return top_right;
}

int Rectangle::width() const
{
  return top_right.get_x() - bottom_left.get_x();
}

int Rectangle::height() const
{
  return top_right.get_y() - bottom_left.get_y();
}

int Rectangle::area() const
{
  int w = top_right.get_x() - bottom_left.get_x();
  int h = top_right.get_y() - bottom_left.get_y();
  return w * h;
}


int main()
{
  int x, y;

  cout << "Please enter x and y value for point p1: ";
  cin >> x >> y;

  Point p1(x, y);

  p1.move(3, 5);
  cout << "\nMoved p1 by 3, 5--p1 now at "
       << p1.get_x() << ", " << p1.get_y() << endl;

  cout << "\nWe'll use p1 point for the bottom left point of" << endl
       << "rectangle r1, please enter the x and y value for" << endl
       << "top right point: ";
  cin >> x >> y;

  Point p2(x, y);
  Rectangle r1(p1, p2);
  cout << "\nRectangle r1 area is: " << r1.area() << endl;

  return 0;
}

