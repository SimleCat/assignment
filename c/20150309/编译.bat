set INCLUDE="C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\include"

cl /c src/*.c /I include

link *.obj /OUT:bank.exe /LIBPATH:"C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\lib" /LIBPATH:"C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib"

del *.obj

pause