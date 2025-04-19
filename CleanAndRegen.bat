@echo off
SETLOCAL

REM Set your project path and name
SET PROJECT_PATH=%~dp0
SET UPROJECT_NAME=CallOfFruity.uproject

REM Delete folders
echo Deleting Intermediate, Binaries, and Saved...
rmdir /s /q "%PROJECT_PATH%Intermediate"
rmdir /s /q "%PROJECT_PATH%Binaries"
rmdir /s /q "%PROJECT_PATH%Saved"

REM Regenerate project files
echo Regenerating Visual Studio project files...
"%PROGRAMFILES%\Epic Games\UE_5.4\Engine\Binaries\Win64\UnrealVersionSelector.exe" /projectfiles "%PROJECT_PATH%%UPROJECT_NAME%"

echo Done.
pause
