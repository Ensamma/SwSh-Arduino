
cd %~dp0\ClientProject
@call Cleanup.cmd

cd %~dp0\DeviceSource
@call !Cleanup.cmd

cd %~dp0\GeneratorSource
@call Cleanup.cmd

cd %~dp0\GeneratorLauncher
@call Cleanup.cmd

cd %~dp0\SerialPrograms
@call Cleanup.cmd


