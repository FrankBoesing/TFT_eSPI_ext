@echo off
rem 
rem This batch is (c) Frank Bösing, 13.01.2022
rem 
setlocal ENABLEDELAYEDEXPANSION

set ttf_libtype=ILI9341_t3_font_t

set wrk=%~p0
if not exist "%wrk%ttf2bdf.exe" (
  echo ttf2bdf.exe missing
  goto :error
)
if not exist "%wrk%bdf2c.exe" (
  echo bdf2c.exe missing
  goto :error
)

if "%~1"=="" (
  echo %~n0 files [-r] [sizes]
  echo -r recourse subdirectories
  echo sizes ex: 8,9,18,22
  goto :error
)


set "file=%~1"
if "%~2" == "-r" (
  set recursive=/R
  SHIFT
)

if "%~2" == "" (
  set sizes= 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 20, 21, 22, 24, 26, 28, 32, 40, 48, 60, 72, 96
) else (
  set sizes=%~2
)


if "%temp%" == "" (
  set tmpfile=%tmp%\ttf%RANDOM%.tmp
) else (
  if "%tmp%" == "" (
    set tmpfile=.\ttf%RANDOM%.tmp
  ) else (
    set tmpfile=%temp%\ttf%RANDOM%.tmp
  )
)


for %recursive% %%i in ("%file%") do (

  echo Converting %%i to bdf
  set newName=%%~pifont_%%~ni

  if exist "!newName!.c" del "!newName!.c"
  echo #include "font_!fname!.h">!newName!.c
  echo,>>"!newName!.c"

  if exist "!newName!.h" del "!newName!.h"
  echo #pragma once>"!newName!.h"
  echo #include "ILI9341_t3.h">>"!newName!.h"
  echo,>>"!newName!.h"
  echo #ifdef __cplusplus>>"!newName!.h"
  echo extern "C" {>>"!newName!.h"
  echo #endif>>"!newName!.h"
  echo,>>"!newName!.h"

  for %%p in ("%sizes:,=" "%") do (

      set /A n=%%~p
      "%wrk%ttf2bdf.exe" "%%i" -p !n! | "%wrk%bdf2c.exe" > %tmpfile%
      if not ERRORLEVEL 1 (
        type %tmpfile% | find "const !ttf_libtype! ">%tmpfile%2
        set /P f=<%tmpfile%2
        for /F "tokens=3" %%x in (%tmpfile%2) do set fnameS=%%x
        if not "!fnameS!"=="" (
          type %tmpfile% >>"!newName!.c"
          echo !fnameS!
          echo extern const !ttf_libtype! !fnameS!;>>"!newName!.h"
        )
      )
      set fnameS=
  )

  echo,>>"!newName!.h"
  echo #ifdef __cplusplus>>"!newName!.h"
  echo } // extern "C">>"!newName!.h"
  echo #endif>>"!newName!.h"

)

goto :end
:error
:end
  if exist %tmpfile% del %tmpfile%
  if exist %tmpfile%2 del %tmpfile%2
endlocal


