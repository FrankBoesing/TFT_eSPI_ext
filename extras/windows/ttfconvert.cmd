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
  set newName_c=%%~pifont_%%~ni.c
  set newName_h=%%~pifont_%%~ni.h

  if exist "!newName_c!" del "!newName_c!"
  echo #include "font_!fname!.h">!newName_c!
  echo,>>"!newName_c!"

  if exist "!newName_h!" del "!newName_h!"
  echo #pragma once>"!newName_h!"
  echo #include "ILI9341_t3.h">>"!newName_h!"
  echo,>>"!newName_h!"
  echo #ifdef __cplusplus>>"!newName_h!"
  echo extern "C" {>>"!newName_h!"
  echo #endif>>"!newName_h!"
  echo,>>"!newName_h!"

  for %%p in ("%sizes:,=" "%") do (
      set /A n=%%~p
      "%wrk%ttf2bdf.exe" "%%i" -p !n! | "%wrk%bdf2c.exe" > %tmpfile%
      if not ERRORLEVEL 1 (
        find "const !ttf_libtype! " %tmpfile%>%tmpfile%2        
        for /F "tokens=3" %%x in (%tmpfile%2) do set fnameS=%%x
        if not "!fnameS!"=="" (
          type %tmpfile%>>"!newName_c!"
          echo !fnameS!
          echo extern const !ttf_libtype! !fnameS!;>>"!newName_h!"
        )
      )
      set fnameS=
  )

  echo,>>"!newName_h!"
  echo #ifdef __cplusplus>>"!newName_h!"
  echo } // extern "C">>"!newName_h!"
  echo #endif>>"!newName_h!"

)

goto :end
:error
:end
  if exist %tmpfile% del %tmpfile%
  if exist %tmpfile%2 del %tmpfile%2
endlocal


