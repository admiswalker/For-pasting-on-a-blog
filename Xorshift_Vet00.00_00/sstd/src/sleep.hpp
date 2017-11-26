#pragma once
#include "typeDef.h"

#include "../compileOption.hpp"
#ifndef use_sstd_gcc4_4_7
	#include<thread>
	namespace sstd{
		inline void sleep_hour(uint rhs){ std::this_thread::sleep_for(std::chrono::hours       (rhs)); }
		inline void sleep_min (uint rhs){ std::this_thread::sleep_for(std::chrono::minutes     (rhs)); }
		inline void sleep_s   (uint rhs){ std::this_thread::sleep_for(std::chrono::seconds     (rhs)); }
		inline void sleep_ms  (uint rhs){ std::this_thread::sleep_for(std::chrono::milliseconds(rhs)); }
		inline void sleep_us  (uint rhs){ std::this_thread::sleep_for(std::chrono::microseconds(rhs)); }
		inline void sleep_ns  (uint rhs){ std::this_thread::sleep_for(std::chrono::nanoseconds (rhs)); }
	}
#else
	#ifdef _WIN32
		namespace sstd{
			inline void sleep_hour(uint rhs){ std::this_thread::sleep_for(std::chrono::hours       (rhs)); }
			inline void sleep_min (uint rhs){ std::this_thread::sleep_for(std::chrono::minutes     (rhs)); }
			inline void sleep_s   (uint rhs){ Sleep(rhs*1000); }
			inline void sleep_ms  (uint rhs){ Sleep(rhs     ); }
			inline void sleep_us  (uint rhs){ std::this_thread::sleep_for(std::chrono::microseconds(rhs)); }
			inline void sleep_ns  (uint rhs){ std::this_thread::sleep_for(std::chrono::nanoseconds (rhs)); }
		}
	#else
		#include <stdio.h>
		#include <unistd.h>
		namespace sstd{
			inline void sleep_hour(uint rhs){  sleep(rhs*60*60); }
			inline void sleep_min (uint rhs){  sleep(rhs*60   ); }
			inline void sleep_s   (uint rhs){  sleep(rhs      ); }
			inline void sleep_ms  (uint rhs){ usleep(rhs*1000 ); }
			inline void sleep_us  (uint rhs){ usleep(rhs      ); }
			inline void sleep_ns  (uint rhs){ printf("ERROR: use_sstd_gcc4_4_7 option not support sleep_ns()\n"); } // not support
		}
	#endif
#endif
