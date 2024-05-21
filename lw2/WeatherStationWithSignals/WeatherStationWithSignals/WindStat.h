#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>


class WindStat 
{
public:
	void Update(double speed, double direction) 
	{
		if (m_averageSpeed >= 0 && m_averageDirection >= 0) 
		{
			double sumX = std::cos(direction * M_PI / 180) * speed + std::cos(m_averageDirection * M_PI / 180) * m_averageSpeed;
			double sumY = std::sin(direction * M_PI / 180) * speed + std::sin(m_averageDirection * M_PI / 180) * m_averageSpeed;

			m_averageDirection = std::atan2(sumY, sumX) * 180.0 / M_PI;
			if (m_averageDirection < 0.0) {
				m_averageDirection += 360.0;
			}

			m_averageSpeed = std::sqrt(sumX * sumX + sumY * sumY);
		}
		else 
		{
			m_averageSpeed = speed;
			m_averageDirection = direction;
		}
	}

	double GetAverageSpeed() const
	{
		if (m_averageSpeed)
		{
			return m_averageSpeed;
		}
		return 0;
	}

	double GetAverageDirection() const
	{
		if (m_averageDirection)
		{
			return m_averageDirection;
		}
		return 0;
	}

private:
	double m_averageSpeed = -1;
	double m_averageDirection = -1;
};