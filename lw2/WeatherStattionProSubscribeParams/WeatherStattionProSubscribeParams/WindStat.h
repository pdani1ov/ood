#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>


class WindStat
{
public:
	void Update(double speed, double direction)
	{
			m_sumX += std::cos(direction * M_PI / 180) * speed;
			m_sumY += std::sin(direction * M_PI / 180) * speed;
	}

	double GetAverageSpeed() const
	{
		return std::sqrt(m_sumX * m_sumX + m_sumY * m_sumY);
	}

	double GetAverageDirection() const
	{
		double averageDir = std::atan2(m_sumY, m_sumX) * 180.0 / M_PI;
		if (averageDir < 0)
		{
			averageDir += 360;
		}
		return averageDir;
	}

private:
	double m_sumX = 0;
	double m_sumY = 0;
};