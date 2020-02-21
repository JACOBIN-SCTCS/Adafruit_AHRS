//=============================================================================================
// Adafruit_AHRS_Mahony.h
//=============================================================================================
//
// Madgwick's implementation of Mayhony's AHRS algorithm.
// See: http://www.x-io.co.uk/open-source-imu-and-ahrs-algorithms/
//
// Date			Author			Notes
// 29/09/2011	SOH Madgwick    Initial release
// 02/10/2011	SOH Madgwick	Optimised for reduced CPU load
//
//=============================================================================================
#ifndef __Adafruit_Mahony_h__
#define __Adafruit_Mahony_h__

#include "Adafruit_AHRS_FusionInterface.h"
#include <math.h>

//--------------------------------------------------------------------------------------------
// Variable declaration

class Adafruit_Mahony : public Adafruit_AHRS_FusionInterface {
private:
  float twoKp; // 2 * proportional gain (Kp)
  float twoKi; // 2 * integral gain (Ki)
  float q0, q1, q2,
      q3; // quaternion of sensor frame relative to auxiliary frame
  float integralFBx, integralFBy,
      integralFBz; // integral error terms scaled by Ki
  float invSampleFreq;
  float roll, pitch, yaw;
  char anglesComputed;
  static float invSqrt(float x);
  void computeAngles();

  //-------------------------------------------------------------------------------------------
  // Function declarations

public:
  Adafruit_Mahony();
  virtual void begin(float sampleFrequency) {
    invSampleFreq = 1.0f / sampleFrequency;
  }
  virtual void update(float gx, float gy, float gz, float ax, float ay,
                      float az, float mx, float my, float mz);
  void updateIMU(float gx, float gy, float gz, float ax, float ay, float az);

  virtual float getRoll() {
    if (!anglesComputed)
      computeAngles();
    return roll * 57.29578f;
  }

  virtual float getPitch() {
    if (!anglesComputed)
      computeAngles();
    return pitch * 57.29578f;
  }

  virtual float getYaw() {
    if (!anglesComputed)
      computeAngles();
    return yaw * 57.29578f + 180.0f;
  }

  float getRollRadians() {
    if (!anglesComputed)
      computeAngles();
    return roll;
  }
  float getPitchRadians() {
    if (!anglesComputed)
      computeAngles();
    return pitch;
  }
  float getYawRadians() {
    if (!anglesComputed)
      computeAngles();
    return yaw;
  }

  virtual void getQuaternion(float *w, float *x, float *y, float *z) {
    *w = q0;
    *x = q1;
    *y = q2;
    *z = q3;
  }
};

#endif
