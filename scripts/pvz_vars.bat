@ECHO OFF
REM ---------------------------------------
REM Plants vs Zombies MSVC 2005 environment
REM ---------------------------------------

REM Base path to Visual Studio 2005
SET VS_BASE_PATH=C:\Program Files (x86)\Microsoft Visual Studio 8

REM Path to MSVC compiler
SET MS_VC_PATH=%VS_BASE_PATH%\VC\bin

REM Path to Windows SDK
SET WINSDK_DIR=C:\Program Files (x86)\Windows Kits\10

REM Optional DirectX SDK if needed
SET DXSDK_DIR=C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)

REM Add compiler and tools to PATH
SET PATH=%MS_VC_PATH%;%VS_BASE_PATH%\Common7\IDE;%WINSDK_DIR%\bin\x64;%PATH%

REM Include paths
SET INCLUDE=%DXSDK_DIR%\Include;%MS_VC_PATH%\..\..\include;%WINSDK_DIR%\Include\10.0.19041.0\ucrt;%WINSDK_DIR%\Include\10.0.19041.0\shared

REM Library paths
SET LIB=%DXSDK_DIR%\Lib;%MS_VC_PATH%\..\..\lib;%WINSDK_DIR%\Lib\10.0.19041.0\ucrt\x64;%WINSDK_DIR%\Lib\10.0.19041.0\um\x64

ECHO Plants vs Zombies MSVC 2005 environment setup complete.
ECHO Compiler path: %MS_VC_PATH%\cl.exe
