cl /EHsc /c /I "C:\freeglut\include" clock.cpp
link /LIBPATH:"C:\freeglut\lib" clock.obj freeglut.lib gdi32.lib kernel32.lib user32.lib opengl32.lib
clock.exe