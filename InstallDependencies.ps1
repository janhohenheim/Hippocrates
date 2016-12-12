$config = """[Setup]
Lang=default
Dir=C:\Program Files\ImageMagick-6.9.6-Q8
Group=ImageMagick 6.9.6 Q8 (64-bit)
NoIcons=0
Tasks=modifypath,install_devel"""

$tmp = "$env:TMP\$([System.Guid]::NewGuid())"

$configFile = "$tmp\ImageMagick.cfg"
$downloadUrl = 'https://www.imagemagick.org/download/binaries/ImageMagick-6.9.6-8-Q8-x64-dll.exe'
$installer = "$tmp\imagemagick-installer.exe"

New-Item -ItemType Directory -Force -Path $tmp | Out-Null

Write-Host $config | Out-File $configFile

Write-Host -ForegroundColor Cyan "Starting download..."
Invoke-WebRequest -OutFile $installer -Uri $downloadUrl
Write-Host -ForegroundColor Green "Download complete."

Write-Host -ForegroundColor Cyan "Starting installer..."
Start-Process -FilePath $installer -ArgumentList @("/sp", "/verysilent", "/norestart", "/loadinf=ImageMagick.cfg") -Wait

Remove-Item -Force -Recurse $tmp
Write-Host -ForegroundColor Green "Installation complete."