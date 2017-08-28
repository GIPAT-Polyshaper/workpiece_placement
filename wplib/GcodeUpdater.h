
#ifndef WORKPIECE_PLACEMENT_GCODE_UPDATER_H
#define WORKPIECE_PLACEMENT_GCODE_UPDATER_H

#include <iostream>
#include <array>

class GcodeUpdater {

public:
  /**
   * @brief A point
   *
   * Each point is X, Y, Z, E. E is the angular position of the end effector
   */
  using Point = std::array<double, 4>;

private:
  void findNextPoint();
  bool extractPoint(const std::string& str);
  void printPoint();

  std::istream& m_input;
  std::ostream& m_output;
  bool m_hasNextPoint;
  Point m_originalNextPoint;
  Point m_nextPoint;
  std::string m_nextCommand;
  bool m_firstPointFound;

public:

  /**
   * @brief constructor
   * @param input the stream from which the gcode is read
   * @param output the stream to which the gcode is written
   * NOTE: keep streams valid for the lifetime of this object!
   */
  GcodeUpdater(std::istream& input, std::ostream& output);

  /**
   * @brief Returns true if more points are available
   * @return true if more points are available
   */
  bool hasNextPoint();

  /**
   * @brief Returns the next point
   * @return the next point
   * Always check the next point is available with hasNextPoint() before calling this
   */
  const Point& nextPoint() const;

  /**
   * @brief Changes the value of the point to store
   * @param point the new point to store
   */
  void updatePoint(const Point& p);

  /**
   * @brief Changes the value of the point to store
   * @param point the new point to store
   */
  void updatePoint(Point&& p);
};


#endif //WORKPIECE_PLACEMENT_IMAGECUTTER_H
