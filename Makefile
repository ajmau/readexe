CPP_SOURCES := $(wildcard src/*.cpp)

readexe:
	g++ ${CPP_SOURCES} -o $@
