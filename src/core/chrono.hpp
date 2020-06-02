#ifndef __ISICG_ISIR_CHRONO_HPP__
#define __ISICG_ISIR_CHRONO_HPP__

#include <chrono>

namespace ISICG_ISIR
{
	class Chrono
	{
		using Clock = std::chrono::high_resolution_clock;
		using Duration = std::chrono::duration<double>;

	public:
		void start()
		{
			begin = Clock::now();
		}
		void stop()
		{
			end = Clock::now();
		}
		double elapsedTime() const
		{
			return (std::chrono::duration_cast<Duration>(end - begin)).count();
		}

	private:
		Clock::time_point begin;
		Clock::time_point end;
	};
} 

#endif 
