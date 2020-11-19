CPP_SOURCES := $(wildcard src/*.cpp)

readexe:
	g++ -Wall -Wextra -W ${CPP_SOURCES} -o $@
