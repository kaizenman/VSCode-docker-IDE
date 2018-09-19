$OpenGLIncludePath = "C:\.include"
$OpenGLDestPath = "C:\include"

Write-Host "Copying OpenGL headers..."
Copy-Item $OpenGLIncludePath -Destination $OpenGLDestPath -Recurse
Write-Host "Done"