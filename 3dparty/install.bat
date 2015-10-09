call "%VS140COMNTOOLS%\VsMSBuildCmd.bat"
msbuild.exe "solution/INSTALL.vcxproj" /nologo /t:Build /p:Configuration="Debug">install_d.log 2>&1
msbuild.exe "solution/INSTALL.vcxproj" /nologo /t:Build /p:Configuration="Release">install.log 2>&1