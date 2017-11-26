#include <time.h>
#include <string>

namespace sstd{
//	struct tm getTm_gm(0);       // get current time
//	struct tm getTm_local(0);    // get current time
//	time_t    getTime_gm(0);     // get current time
//	time_t    getTime_local(0);  // get current time
	
	struct tm time2tm       (time_t unixtime);
	time_t    tm2time       (struct tm& rhs);
	struct tm timeGm2tmLocal(time_t unixtime);
	time_t    tmLocal2timeGm(struct tm& rhs);
	std::string time2str    (time_t unixtime);
	std::string   tm2str    (struct tm& rhs);
	double      time2unixday(time_t unixtime);
	double        tm2unixday(struct tm& rhs);
	
//	struct tm timeLocal2tmGm(struct tm& rhs);
//	time_t    tmGm2timeLocal(struct tm& rhs);
//	time_t timeGm2timeLocal(time_t unixtime);
//	time_t timeGm2timeLocal(time_t unixtime);
//	time_t timeLocal2timeGm(time_t unixtime);
//	time_t timeLocal2timeGm(time_t unixtime);

	time_t    yday2time(uint year, uint yday);
	struct tm yday2tm  (uint year, uint yday);

//	print(time_t unixtime);
	void print(const struct tm& rhs);
	void for_printn(const struct tm& rhs);
}
