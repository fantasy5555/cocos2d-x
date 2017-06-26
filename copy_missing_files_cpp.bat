@echo off

set projectEngineDir=cocos2d

xcopy /y /s /e /f /h "%COCOS2DX_ROOT%\cocos\editor-support\cocostudio\WidgetReader\SpineSkeletonReader"  "%projectEngineDir%\cocos\editor-support\cocostudio\WidgetReader\SpineSkeletonReader\"
xcopy /y /s /e /f /h "%COCOS2DX_ROOT%\cocos\editor-support\cocostudio\WidgetReader\RichTextReader"  "%projectEngineDir%\cocos\editor-support\cocostudio\WidgetReader\RichTextReader\"
xcopy /y /s /e /f /h "%COCOS2DX_ROOT%\cocos\editor-support\cocostudio\WidgetReader\ControlSwitchReader"  "%projectEngineDir%\cocos\editor-support\cocostudio\WidgetReader\ControlSwitchReader\"
xcopy /y /s /e /f /h "%COCOS2DX_ROOT%\cocos\editor-support\cocostudio\WidgetReader\RadioButtonReader"  "%projectEngineDir%\cocos\editor-support\cocostudio\WidgetReader\RadioButtonReader\"

copy /y "%COCOS2DX_ROOT%\cocos\editor-support\spine\SpineSkeletonCache.*"  "%projectEngineDir%\cocos\editor-support\spine\"

copy /y "%COCOS2DX_ROOT%\cocos\2d\libxreader*"  "%projectEngineDir%\cocos\2d\"
copy /y "%COCOS2DX_ROOT%\cocos\2d\resource.h"  "%projectEngineDir%\cocos\2d\"
copy /y "%COCOS2DX_ROOT%\external\glfw3\include\win32\glfw3ext.h" "%projectEngineDir%\external\glfw3\include\win32\glfw3ext.h"

rem copy dragonBones
xcopy /y /s /e /f /h "%COCOS2DX_ROOT%\cocos\editor-support\dragonBones"  "%projectEngineDir%\cocos\editor-support\dragonBones\"

ping /n 2 127.0.1>nul && goto :eof
