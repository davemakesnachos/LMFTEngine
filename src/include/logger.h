#ifndef LOGGER_H
#define LOGGER_H
#include <iomanip>
#include <iostream>
#include <SDL2/SDL.h>

static long long _startTime;

class Logger {
public:
	static void init(void) { _startTime = SDL_GetPerformanceCounter(); };
	static long long int ts(void) { return SDL_GetPerformanceCounter() - _startTime; }
};

std::string className(const std::string& prettyFunction);

#define __CLASS_NAME__ className(__PRETTY_FUNCTION__)

/* FORMAT STRINGS */
#define TIMESTAMP_FORMAT std::right << std::setw(16) << std::setfill('0')
#define LEVEL_FORMAT std::right << std::setw(9) << std::setfill(' ')
#define CLASS_NAME_FORMAT std::right << std::setw(26) << std::setfill(' ')
#define OUTPUT_FORMAT std::left << "\t"

#define DEBUG(a) std::cout << TIMESTAMP_FORMAT << Logger::ts() << " " << CLASS_NAME_FORMAT << __CLASS_NAME__ << LEVEL_FORMAT <<  "DEBUG" << OUTPUT_FORMAT << a << std::endl;
#define INFO(a) std::cout << TIMESTAMP_FORMAT << Logger::ts() << " " << CLASS_NAME_FORMAT << __CLASS_NAME__ << LEVEL_FORMAT <<  "INFO" << OUTPUT_FORMAT << a << std::endl;
#define WARN(a) std::cout << TIMESTAMP_FORMAT << Logger::ts() << " " << CLASS_NAME_FORMAT << __CLASS_NAME__ << LEVEL_FORMAT <<  "WARN" << OUTPUT_FORMAT << a << std::endl;
#define ERROR(a) std::cout << TIMESTAMP_FORMAT << Logger::ts() << " " << CLASS_NAME_FORMAT << __CLASS_NAME__ << LEVEL_FORMAT <<  "ERROR" << OUTPUT_FORMAT << a << std::endl;

#endif /* LOGGER_H */
