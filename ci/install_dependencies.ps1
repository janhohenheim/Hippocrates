$config = "[Setup]
Lang=default
Dir=C:\Program Files\ImageMagick
Group=ImageMagick 6.9.7 Q8 (64-bit)
NoIcons=0
Tasks=modifypath,install_devel
"

$tmp = "$env:TMP\$([System.Guid]::NewGuid())"

$configFile = "$tmp\ImageMagick.cfg"
$downloadUrl = 'https://www.imagemagick.org/download/binaries/ImageMagick-6.9.7-2-Q8-x64-dll.exe'
$installer = "$tmp\imagemagick-installer.exe"

if (Test-Path "C:\Program Files\ImageMagick") {
    Write-Host -ForegroundColor Yellow "Already installed. Aborting."
    Exit
}

New-Item -ItemType Directory -Force -Path $tmp | Out-Null

$config | Out-File $configFile

Write-Host -ForegroundColor Cyan "Starting download..."
Invoke-WebRequest -OutFile $installer -Uri $downloadUrl
Write-Host -ForegroundColor Green "Download complete."

Write-Host -ForegroundColor Cyan "Starting installer..."
Start-Process -FilePath $installer -ArgumentList @("/sp", "/verysilent", "/norestart", "/loadinf=`"$configFile`"") -Wait


Remove-Item -Force -Recurse $tmp
Write-Host -ForegroundColor Green "Installation complete."
