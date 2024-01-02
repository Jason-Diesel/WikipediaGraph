#pragma once
#include <chrono>
//git
class DeltaTime {
private:
	std::chrono::steady_clock::time_point t_start;
	std::chrono::steady_clock::time_point t_end;
	double pDt;
public:
	DeltaTime();
	void restartClock();
	double dt()const;

};