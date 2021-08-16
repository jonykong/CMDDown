@echo on
cd ..
qmake -spec win32-msvc -r -tp vc CMDDown.pro
cd build
@pause
