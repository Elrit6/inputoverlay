set VERSION=-std=c++17
set NLOHMANN=-ID:/nlohmann
set SDL_I=-ID:/SDL/include
set SDL_L=-LD:/SDL/lib -lSDL2 -llibSDL2_ttf

set APPNAME=app.exe

set FILE1=main
set FILE2=app
set FILE3=layoutParser
set FILE4=window
set FILE5=keyListener
set SRC1=src/%FILE1%.cpp
set SRC2=src/%FILE2%.cpp
set SRC3=src/%FILE3%.cpp
set SRC4=src/%FILE4%.cpp
set SRC5=src/%FILE5%.cpp
set OBJ1=obj/%FILE1%.obj
set OBJ2=obj/%FILE2%.obj
set OBJ3=obj/%FILE3%.obj
set OBJ4=obj/%FILE4%.obj
set OBJ5=obj/%FILE5%.obj

cls

g++ -c %SRC1% -o %OBJ1% %NLOHMANN% %SDL_I%
g++ -c %SRC2% -o %OBJ2% %NLOHMANN% %SDL_I%
g++ -c %SRC3% -o %OBJ3% %NLOHMANN% %VERSION%
g++ -c %SRC4% -o %OBJ4% %SDL_I% %VERSION%
g++ -c %SRC5% -o %OBJ5%

g++ %OBJ1% %OBJ2% %OBJ3% %OBJ4% %OBJ5% -o %APPNAME% %VERSION% %SDL_L%