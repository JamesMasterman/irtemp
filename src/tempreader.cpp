#include "tempreader.h"


TempReader::TempReader()
{

}

TempReader::~TempReader()
{

}

double TempReader::GetTemp()
{
  const double Offset = 1;
  const double VPerValue = (3300.0/4096.0) / 1000.0;
  double temp = (analogRead(A3) * VPerValue) /3.0 * 450.0 - 70.0;
  return temp + Offset;
}
