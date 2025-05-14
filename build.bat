@echo off
setlocal enabledelayedexpansion

set "release_flag=true"

rem Check for the --release argument
:check_args
if "%~1"=="" goto end_check
if "%~1"=="--release" (
    set "release_flag=false"
)
shift
goto check_args
:end_check

set "build_dir=build"
if "!release_flag!"=="true" (
    set "build_dir=build\ookee"  rem Change to build\ookee if release_flag is set
)

rem Create the build directory
mkdir "!build_dir!" 2>nul

rem Compile the C code
zig cc ^
    -Wall ^
    -Werror ^
    -Os ^
    -DCLAY_WASM ^
    -mbulk-memory ^
    --target=wasm32 ^
    -nostdlib ^
    -fno-builtin ^
    -Wl,--strip-all ^
    -Wl,--export-dynamic ^
    -Wl,--no-entry ^
    -Wl,--export=__heap_base ^
    -Wl,--export=ACTIVE_RENDERER_INDEX ^
    -Wl,--initial-memory=6553600 ^
    -o "!build_dir!\index.wasm" ^
    main.c

rem Copy additional files
xcopy /E /I /Y fonts "!build_dir!\fonts"
copy .htaccess "!build_dir!\.htaccess"
copy index.html "!build_dir!\index.html"
xcopy /E /I /Y images "!build_dir!\images"

rem Run kraffiti command
kraffiti from=favicon.png to=!build_dir!\favicon.ico

if "!release_flag!"=="false" (
    echo Local dev mode activated.
    copy server.py "!build_dir!\server.py"
)

endlocal
