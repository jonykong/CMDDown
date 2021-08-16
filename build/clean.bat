echo "start clean CMDDown"
cd ..
del CMDDown.sln

echo "start clean application"
cd application/build
call clean.bat
cd ..
cd ..

echo "start clean src"
cd src/build
call clean.bat
cd ..
cd ..

echo "end clean CMDDown"