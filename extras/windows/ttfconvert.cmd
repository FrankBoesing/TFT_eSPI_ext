@echo off
setlocal ENABLEDELAYEDEXPANSION

set ttf_libtype=ILI9341_t3_font_t

set wrk=%~p0
if not exist %wrk%ttf2bdf.exe (
  echo ttf2bdf.exe missing
  goto :error
)
if not exist %wrk%bdf2c.exe (
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
  set tmpfile=%tmp%\~%RANDOM%.tmp
) else (
  if "%tmp%" == "" (
    set tmpfile=.\~%RANDOM%.tmp
  ) else (
    set tmpfile=%temp%\~%RANDOM%.tmp
  )
)


for %recursive% %%i in ("%file%") do (

  echo Converting %%i to bdf

  set pfad=%%~pi
  set fname=%%~ni
  set ext=%%~xi
  set tmpfile=%temp%\ttf~%RANDOM%.tmp

  if exist !pfad!font_!fname!.c del !pfad!font_!fname!.c
  if exist !pfad!font_!fname!.h del !pfad!font_!fname!.h
  echo #include "font_!fname!.h">!pfad!font_!fname!.c
  echo,>>!pfad!font_!fname!.c

  echo #pragma once>!pfad!font_!fname!.h
  echo #include "ILI9341_t3.h">>!pfad!font_!fname!.h
  echo,>>!pfad!font_!fname!.h
  echo #ifdef __cplusplus>>!pfad!font_!fname!.h
  echo extern "C" {>>!pfad!font_!fname!.h
  echo #endif>>!pfad!font_!fname!.h
  echo,>>!pfad!font_!fname!.h

  for %%p in ("%sizes:,=" "%") do (
      if exist "%tmpfile%" del %tmpfile%
      if exist "%tmpfile%2" del %tmpfile%2

      set /A n=%%~p
      %wrk%ttf2bdf.exe %%i -p !n! | %wrk%bdf2c.exe > %tmpfile%
      if not ERRORLEVEL 1 (
        type %tmpfile% | find "const !ttf_libtype! ">%tmpfile%2
        set /P f=<%tmpfile%2
        for /F "tokens=3" %%x in (%tmpfile%2) do set fnameS=%%x
        type %tmpfile% >> !pfad!font_!fname!.c
        if not "!fnameS!"=="" (
          echo Size !n!: !fnameS!
          echo extern const !ttf_libtype! !fnameS!;>>!pfad!font_!fname!.h
        )
      )
      set fnameS=
  )

  if exist "%tmpfile%" del %tmpfile%
  if exist "%tmpfile%2" del %tmpfile%2

  echo,>>!pfad!font_!fname!.h
  echo #ifdef __cplusplus>>!pfad!font_!fname!.h
  echo } // extern "C">>!pfad!font_!fname!.h
  echo #endif>>!pfad!font_!fname!.h

)

goto :end
:error
:end
endlocal


