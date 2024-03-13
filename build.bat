@echo off
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
call :Reset
set edcExitCode=0
set edcSavedPath=%PATH%
set edcSrcDir=%cd%\
set edcBuildDir=%cd%\out\build
set edcTempDir=%TEMP%\dce\
set edcBuildScriptVersion=1.0.0
set edcTargetEnv=X64
set edcCompiler=MSVC
if not exist %edcTempDir% mkdir %edcTempDir%
rm -rf %edcTempDir%*.*
if "%1" == "-h" (
   call :Usage
   goto complete
   )
if "%1" == "--help" ( 
    call :Usage
    goto complete
    )
    :: Output help information
:Usage
    echo Usage: build [options] [gcc]
    echo Run the bat file in the root directory of the project
    echo Options:
    echo  --help            Display these instructions and exit
    echo  --verbose         Display more messages
    echo  --compiler NAME   Set the compiler name to MSVC, Clang, or GNU 
    echo                    default is MSVC
    echo  --environment     Set the build target environment to X64, X86, 
    echo                    ARM, ARM64, IOS default is X64
    echo Examples:
    goto :EOF
:ParseSW
    if "%1" == "--verbose" goto SetVerbose
    if "%1" == "--compiler" goto SetCompiler
    if "%1" == "--environment" goto DoneSW
    if "%1" == "" goto DoneSW
    call Console_WriteLine E "%1 is not a valid option"
    call :Usage
    set edcExitCode=1
    goto complete
:SetVerbose
    set edcVerbose=Y
    call :Console_WriteLine I "Verbose messages is on"
    shift
    goto ParseSW
:SetCompiler
    shift
    if "%1" == "MSVC" goto SetMSVC
    if "%1" == "Clang" goto SetClang
    if "%1" == "GNU" goto SetGNU
    call Console_WriteLine E "%1 is not a valid compiler"
    set edcExitCode=1
    goto complete
:SetMSVC
		set edcCompiler=MSVC
		call :Console_WriteLine I "Compiler is MSVC"
		shift
		goto ParseSW  
:SetClang
		set edcCompiler=Clang
		call :Console_WriteLine I "Compiler is Clang"
		shift
		goto ParseSW
:SetGNU
		set edcCompiler=GNU
		call :Console_WriteLine I "Compiler is GNU"
		shift
		goto ParseSW
:: command line parsing completed
:DoneSW
:: Mainline continues
call :Console_WriteLine I "Build script version %edcBuildScriptVersion%"
if "%edcCompiler%"=="MSVC" (
    if "%edcMSVCInstallDir%"!="" (
        goto SetupMSCVEnv
    ) 
		set edcMSVCInstallvswhere="%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
    if not exist %edcMSVCInstallvswhere% (
				call :Console_WriteLine E "MSVC not installed"
				set edcExitCode=1
				goto complete
		)
    %edcMSVCInstallvshere% -latest -nocolor -property installationPath > %edcTempDir%msvcInstallDir.txt
    set edcMSVCInstallvswhere=
    set /p edcMSVCInstallDir=<%edcTempDir%msvcInstallDir.txt
    del %edcTempDir%msvcInstallDir.txt
    if not exist %edcMSVCInstallDir% (
    call :Console_WriteLine E "MSVC not installed"
        set %edcMSVCInstallDir=
				set edcExitCode=1
				goto complete
		)
:SetupMSCVEnv
		set edcMSVCEnvCmd=%edcMSVCInstallDir%\VC\Auxiliary\Build\vcvars64.bat
		if not exist %edcMSVCInstallDir% (
				call :Console_WriteLine E "vcvars64.bat not found"
				set edcExitCode=1
				goto complete
		)
		call :Console_WriteLine I "MSVC install directory is %edcMSVCInstallDir%"
		call :Console_WriteLine I "Setting up MSVC environment"
		call %edcMSVCInstallDir%
		if not exist %edcBuildDir% mkdir %edcBuildDir%
		cd %edcBuildDir%
		call :Console_WriteLine I "Building with MSVC"
		cmake -G "Visual Studio 15 2017 Win64" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=%edcBuildDir% %edcSrcDir%
		cmake --build . --config Release --target install
		if %ERRORLEVEL% NEQ 0 (
				call :Console_WriteLine E "MSVC build failed"
				set edcExitCode=1
				goto complete
		)
		call :Console_WriteLine I "MSVC build succeeded"
		goto complete
)
)
:: "c:\program files\microsoft visual studio\2022\community\common7\ide\commonextensions\microsoft\cmake\CMake\bin\cmake.exe"  
:: -G "Ninja"  
:: -DCMAKE_C_COMPILER:STRING="cl.exe" 
:: -DCMAKE_CXX_COMPILER:STRING="cl.exe" 
:: -DCMAKE_BUILD_TYPE:STRING="Debug" 
:: -DCMAKE_INSTALL_PREFIX:PATH="D:/sandbox/jackd/repos/edc/out/install/x64-debug"   
:: -DCMAKE_MAKE_PROGRAM="c:\program files\microsoft visual studio\2022\community\common7\ide\commonextensions\microsoft\cmake\Ninja\ninja.exe" 
:: "D:\sandbox\jackd\repos\edc"
goto :complete
:: Using these variables allows easy implementation of future options+
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: subroutine conditionally writes line to Console_WriteLine
:: Param %1 is the message Level
:: Message LEVEL:   T trace - only written with verbose=Y
::                  I info - always written
::                  W warn - always written
::                  E error - always written
::                  F fail - command line utility failed.
:: Param %2 %3 ... the text of the message.
:: return 0 always
:: Message format ddddd ttttt L mmmmmmmmmmm
:: where    ddddd is the date
::          ttttt is the time
::          L is the message level passed as %1
::          mmmmmmmmmmm is the message text
:: TODO: update with gnu printf command
:Console_WriteLine
    if "%edcVerbose%" == "N" (
        if "%1" == "T" goto :EOF
    )
    echo %DATE% %TIME% %*
    goto :EOF
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Reset process environment
    :Reset
    set edcVerbose=
    set edcSrcDir=
    set edcBuildDir=
    set edcTempDir=
    set edcBuildScriptVersion=
    set edcMSVCInstallDir=
    goto :EOF
    :: Resetore the path
:RestorePath
    path=%edcSavedPath%
    set edcSavedPath=
    goto :EOF
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: We are done, exit with return code.
:complete
    call :RestorePath
    call :Reset
    EXIT /b %edcExitCode%