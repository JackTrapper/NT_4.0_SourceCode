rem    Check out the IFIMETRICS files

if not exist %1%\ifi  goto _end1

cd %1%\ifi

rem  Directory exists,  so off we go.

echo "Checking out the IFIMETRICS files for the %1% driver..."

out -f *.*

cd ..\..


:_end1
