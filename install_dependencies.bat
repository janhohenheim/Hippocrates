REM Install ImageMagick

REM Check if already downloaded
if exist "C:\Program Files\ImageMagick-6.9.6-Q16\" exit /b 0

REM Download from FTP
echo open ftp.imagemagick.org>> ImageMagick.ftp
echo cd pub/ImageMagick/binaries/>> ImageMagick.ftp
echo get ImageMagick-6.9.6-7-Q16-x64-dll.exe>> ImageMagick.ftp
echo quit>> ImageMagick.ftp

ftp -i -A -s:ImageMagick.ftp
del ImageMagick.ftp

REM Configure installation
echo [Setup]>> ImageMagick.cfg
echo Lang=default>> ImageMagick.cfg
echo Dir=C:\Program Files\ImageMagick-6.9.6-Q16>> ImageMagick.cfg
echo Group=ImageMagick 6.9.6 Q16 (64-bit)>> ImageMagick.cfg
echo NoIcons=0>> ImageMagick.cfg
echo Tasks=modifypath,install_devel>> ImageMagick.cfg

REM Install
ImageMagick-6.9.6-7-Q16-x64-dll.exe /sp /verysilent /norestart /loadinf="ImageMagick.cfg"
del ImageMagick.cfg