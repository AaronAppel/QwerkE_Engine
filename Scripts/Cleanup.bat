cd ../

del /Q /F instrumentor_log.json

del /Q /F /S /AH .vs
del /Q /F /S x64
rmdir /Q /S ".vs"
rmdir /Q /S x64

del /Q /F /S /AH Debug
rmdir /Q /S Debug

del /Q /F /S /AH Release
rmdir /Q /S Release

cd Engine_Components/RenderingEnv
del /Q /F /S Debug
del /Q /F /S x64
del /Q /F /S Release
rmdir /Q /S Debug
rmdir /Q /S x64
rmdir /Q /S Release
cd ../

cd Qwerk_Engine/QwerkE_Win32
del /Q /F /S Debug
del /Q /F /S x64
del /Q /F /S Release
rmdir /Q /S Debug
rmdir /Q /S x64
rmdir /Q /S Release
cd ../

cd Qwerk_Engine/QwerkE_Win64
del /Q /F /S Debug
del /Q /F /S x64
del /Q /F /S Release
rmdir /Q /S Debug
rmdir /Q /S x64
rmdir /Q /S Release
cd ../

cd Games
del /Q /F /S Debug
del /Q /F /S x64
del /Q /F /S Release
rmdir /Q /S Debug
rmdir /Q /S x64
rmdir /Q /S Release
cd ../

cd QwerkE_Framework
call Cleanup.bat
cd ../

cd QwerkE_Documentation
call Cleanup.bat
cd ../
