/**
 * position.h
 */
#ifndef POSITION_H
#define POSITION_H

/**
 * @brief Position class
 * @details [long description]
 */
class CPosition
{
public:
  CPosition();
  virtual ~CPosition();

private:
  float x_;
  float y_;
  float z_;

  float x_rot_;
  float y_rot_;
  float z_rot_;
};

#endif
