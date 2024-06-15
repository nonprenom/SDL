# Mingw cfg
CXX=x86_64-w64-mingw32-g++
CXXFLAGS=-std=c++11 -Wall -pedantic -Werror -Wshadow -Wstrict-aliasing -Wstrict-overflow -Os
# to compile with mingw libstd in static
CXXLDFLAGS=-s -static -lmingw32 -static-libgcc -static-libstdc++ -mconsole -mwindows # -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive

# SDL2 cfg
WINDOWS_SDK_SDL_LIB=/opt/windows/SDL2-2.30.3/x86_64-w64-mingw32
SDL2FLAGS=$(shell ${WINDOWS_SDK_SDL_LIB}/bin/sdl2-config --cflags)
SDL2LDFLAGS=$(shell ${WINDOWS_SDK_SDL_LIB}/bin/sdl2-config --static-libs)

export EXE_TIME := $(shell date +'%Y%m%d%H%M%S')

volumes : clean volumes.cpp Logger.o
	${CXX} volumes.cpp -o test-${EXE_TIME} ${CXXFLAGS} ${SDL2FLAGS} ${SDL2LDFLAGS} ${CXXLDFLAGS} Logger.o

Logger.o :
	${CXX} -c Logger.cpp ${CXXFLAGS}

clean: 
	rm -f test-*.exe