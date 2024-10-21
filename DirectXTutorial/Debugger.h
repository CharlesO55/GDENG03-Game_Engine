#pragma once

class Debugger {
public:
	static void Success(const char* t) {
		printf("\033[0;32m%s\033[0m\n", t);
	}
	
	static void Warning(const char* t) {
		printf("\033[0;33m%s\033[0m\n", t);
	}

	static void Error(const char* t) {
		printf("\033[31;7m%s\033[0m\n", t);
		throw t;
	}
};