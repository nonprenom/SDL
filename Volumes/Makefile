# Mingw cfg
CXX=x86_64-w64-mingw32-g++
CXXFLAGS=-std=c++11 -Wall -pedantic -Werror -Wshadow -Wstrict-aliasing -Wstrict-overflow -Os
# to compile with mingw libstd in static
CXXLDFLAGS=-s -static -lmingw32 -static-libgcc -static-libstdc++ -mconsole -mwindows # -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive
# wil output the binaries in this diretory to avoid problem with the anti-virus
WINOUTPUTDIR=/mnt/c/Essence_SC/tmp

# SDL2 cfg
WINDOWS_SDK_SDL_LIB=/opt/windows/SDL2-2.30.3/x86_64-w64-mingw32
SDL2FLAGS=$(shell ${WINDOWS_SDK_SDL_LIB}/bin/sdl2-config --cflags)
SDL2LDFLAGS=$(shell ${WINDOWS_SDK_SDL_LIB}/bin/sdl2-config --static-libs)

# Utils
UTILSDIR=../utils


INCS=-I${UTILSDIR}

volumes : volumes.cpp Logger.o Window.o
	${CXX} volumes.cpp -o test.exe ${CXXFLAGS} ${SDL2FLAGS} ${INCS} ${SDL2LDFLAGS} ${CXXLDFLAGS} Logger.o Window.o
	mv -fv test.exe ${WINOUTPUTDIR}/test.exe
	ln -fvs ${WINOUTPUTDIR}/test.exe test.exe

Logger.o : ${UTILSDIR}/Logger.cpp ${UTILSDIR}/Logger.h
	${CXX} -c ${UTILSDIR}/Logger.cpp ${CXXFLAGS} ${INCS}

Window.o : ${UTILSDIR}/Window.cpp ${UTILSDIR}/Window.h
	${CXX} -c ${UTILSDIR}/Window.cpp ${CXXFLAGS} ${SDL2FLAGS} ${INCS}

clean: 
	rm -fv "$(shell readlink -f test.exe)"
	rm -fv test.exe *.o