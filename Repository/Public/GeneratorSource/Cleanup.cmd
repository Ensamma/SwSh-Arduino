cd %~dp0

del .qmake.stash
del *.log
del Makefile*
del object_script.*
del users*
del HexGenerator.pro.user
del Settings.json

rd /s /q "debug\"
rd /s /q "release\"
rd /s /q "GeneratorConfig\"
