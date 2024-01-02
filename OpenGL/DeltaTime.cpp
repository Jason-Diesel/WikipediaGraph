#include "deltaTime.h"

DeltaTime::DeltaTime()
{
	this->pDt = 0;
	this->t_start = std::chrono::steady_clock::now();
	this->t_end = std::chrono::steady_clock::now();
}

void DeltaTime::restartClock()
{
	this->t_end = std::chrono::steady_clock::now();
	std::chrono::duration<double> runTime = this->t_end - this->t_start;
	this->pDt = runTime.count();
	this->t_start = std::chrono::steady_clock::now();
}

double DeltaTime::dt()const
{
	return this->pDt;
}