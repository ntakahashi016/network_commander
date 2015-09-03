xcopy /C /Y debug\*.exe deploy\
xcopy /C /Y release\*.exe deploy\
windeployqt -qmldir %1 deploy