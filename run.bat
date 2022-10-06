@echo off

if [%1]==[] goto compile-run
if [%2]==[] (
call "C:\\Program Files\\Microsoft Visual Studio\\%1\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat" x64
) else (
call "C:\\Program Files\\Microsoft Visual Studio\\%1\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat" %2
)

:compile-run
if exist main.exe del main.exe

cl /EHsc main.cpp Graphics2D.cpp /I include /link /LIBPATH:lib /ENTRY:mainCRTStartup SDL2.lib SDL2main.lib SDL2_image.lib SDL2_ttf.lib shell32.lib user32.lib

if exist main.exe (
    cls
    main.exe
) else (
    echo:
    echo ERROR
)