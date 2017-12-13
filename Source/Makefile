SRC= \
  src/Application.cpp \
  src/Component.cpp \
  src/GameObject.cpp \
  src/Scene.cpp \
  src/Components/Transform.cpp \
  src/Components/Camera.cpp \
  src/Components/Input.cpp \
  src/Components/TriangleRenderer.cpp \
  src/main.cpp \
  src/ref.cpp

CFLAGS=/DGLEW_STATIC /DFREEGLUT_LIB_PRAGMAS=0 /MD /Iinclude
CXXFLAGS=/EHsc
LDFLAGS=opengl32.lib lib\freeglut.lib lib\glew.lib lib\SDL2.lib

all: lab1.exe

lab1.exe: $(SRC)
	cl $(CFLAGS) $(CXXFLAGS) $(SRC) $(LDFLAGS) /Felab1.exe

clean:
	del lab1.exe
	del *.obj
