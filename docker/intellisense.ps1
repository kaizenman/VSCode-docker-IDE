$WindowsKitsSourcePath = "C:\Program Files (x86)\Windows Kits\10\Include\10.0.17763.0\"
$MSVCIncludeSourcePath = "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Tools\MSVC\14.16.27023\include\"
$MSVCBuildToolsSourcePath = "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Tools\MSVC\14.16.27023\include\"

$WindowsKitsDestPath = "C:\include\WindowsKits\"
$MSVCIncludeDestPath = "C:\include\MSVC\"
$MSVCBuildToolsDestPath = "C:\include\MSVCBuildTools\"

Write-Host "Copying WindowsKits headers..."
Copy-Item $WindowsKitsSourcePath -Destination $WindowsKitsDestPath -Recurse
Write-Host "Copying MSVC headers..."
Copy-Item $MSVCIncludeSourcePath -Destination $MSVCIncludeDestPath -Recurse
Write-Host "Copying other headers..."
Copy-Item $MSVCBuildToolsSourcePath -Destination $MSVCBuildToolsDestPath -Recurse
Write-Host "Done"