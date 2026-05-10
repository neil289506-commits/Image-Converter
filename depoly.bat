@echo off
echo [系統] 正在準備部署...

:: 1. 設定 Qt 6.11.0 的路徑 (確保能找到 windeployqt)
set PATH=C:\Qt\6.11.0\msvc2022_64\bin;%PATH%

:: 2. 建立一個專屬的發布資料夾，避免弄髒原始碼資料夾
if not exist "Dist" mkdir "Dist"

:: 3. 把你剛剛編譯好的 exe 複製到 Dist (假設你在 Release 模式編譯)
:: 如果你的 exe 在根目錄，請改為 copy "ImageConverter.exe" "Dist\"
copy "release\ImageConverter.exe" "Dist\"

:: 4. 執行 windeployqt 自動抓取 DLL 與插件 (包含 imageformats)
echo [系統] 正在抓取必要的 DLL 與 WebP/AVIF 插件...
windeployqt --no-translations --compiler-runtime "Dist\ImageConverter.exe"

echo.
echo ======================================================
echo 部署完成！請到 Dist 資料夾執行 ImageConverter.exe
echo ======================================================
pause