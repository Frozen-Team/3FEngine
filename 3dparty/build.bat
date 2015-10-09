call "%VS140COMNTOOLS%\VsMSBuildCmd.bat"
msbuild.exe "solution/3dparty.sln" /nologo /t:Build /p:Configuration="Debug">build_d.log 2>&1
msbuild.exe "solution/3dparty.sln" /nologo /t:Build /p:Configuration="Release">build.log 2>&1