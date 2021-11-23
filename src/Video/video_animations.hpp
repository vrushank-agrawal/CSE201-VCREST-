#ifndef VIDEO_ANIMATIONS_H
#define VIDEO_ANIMATIONS_H

#endif // VIDEO_ANIMATIONS_H

#include<opencv2/opencv.hpp>
#include<iostream>

class Coordinate {
public:
  Coordinate(double x_other, double y_other);
  Coordinate();
  Coordinate(const Coordinate &other);
  ~Coordinate();

  double get_x() const;
  double get_y() const;
  void set_x(const double x);
  void set_y(const double y);
  double get_distance(Coordinate other);

  Coordinate operator+(const Coordinate& other);
  Coordinate operator-();
  Coordinate operator-(const Coordinate& other);

  bool operator==(const Coordinate& other);
  bool operator!=(const Coordinate& other);
  bool operator>(const Coordinate& other);
  bool operator<(const Coordinate& other);

  static int get_num_instances();

  friend std::ostream& operator<<(std::ostream& os, const Coordinate& c);

private:
  double x;
  double y;
  static int num_instances;
};

void zoom_img(img, coordinate, ratio);
