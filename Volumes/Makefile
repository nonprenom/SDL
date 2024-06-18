BUILDDIR=.build
EXECUTABLE=volumes.exe

# Mingw cfg
CXX=x86_64-w64-mingw32-g++
CXXFLAGS=-std=c++11 -Wall -pedantic -Werror -Wshadow -Wstrict-aliasing -Wstrict-overflow -Os
# to compile with mingw libstd in static
CXXLDFLAGS=-s -static -lmingw32 -static-libgcc -static-libstdc++ -pthread -mconsole -mwindows  # -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive
# will output the binaries in this diretory to avoid problem with the anti-virus
WINOUTPUTDIR=/mnt/c/Essence_SC/tmp

# SDL2 cfg
WINDOWS_SDK_SDL_LIB=/opt/windows/SDL2-2.30.3/x86_64-w64-mingw32
SDL2FLAGS=$(shell ${WINDOWS_SDK_SDL_LIB}/bin/sdl2-config --cflags)
SDL2LDFLAGS=$(shell ${WINDOWS_SDK_SDL_LIB}/bin/sdl2-config --static-libs)

# Utils
UTILSDIR=../utils


INCS=-I${UTILSDIR}

${BUILDDIR}/${EXECUTABLE} : ${BUILDDIR} volumes.cpp ${BUILDDIR}/Logger.o ${BUILDDIR}/Window.o
	${CXX} volumes.cpp -o ${BUILDDIR}/${EXECUTABLE} ${CXXFLAGS} ${SDL2FLAGS} ${INCS} ${SDL2LDFLAGS} ${CXXLDFLAGS} ${BUILDDIR}/Logger.o ${BUILDDIR}/Window.o

${BUILDDIR}/Logger.o : ${UTILSDIR}/Logger.cpp ${UTILSDIR}/Logger.h
	${CXX} -c ${UTILSDIR}/Logger.cpp -o ${BUILDDIR}/Logger.o ${CXXFLAGS} ${INCS}

${BUILDDIR}/Window.o : ${UTILSDIR}/Window.cpp ${UTILSDIR}/Window.h
	${CXX} -c ${UTILSDIR}/Window.cpp -o ${BUILDDIR}/Window.o ${CXXFLAGS} ${SDL2FLAGS} ${INCS}

${BUILDDIR} :
	mkdir ${BUILDDIR}/

install:
	cp -fv ${BUILDDIR}/${EXECUTABLE} ${WINOUTPUTDIR}/${EXECUTABLE}
	ln -fvs ${WINOUTPUTDIR}/${EXECUTABLE} ${EXECUTABLE}

clean: 
	rm -fv "$(shell readlink -f ${EXECUTABLE})"
	rm -fv ${EXECUTABLE}
	rm -rfv ${BUILDDIR}/