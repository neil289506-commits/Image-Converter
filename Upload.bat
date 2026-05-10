@echo off
echo [Git] 正在初始化並上傳檔案...

:: 1. 初始化 Git 倉庫
git init

:: 2. 加入所有檔案
git add .

:: 3. 提交紀錄 (Commit)
git commit -m "First commit: Image Converter Tool"

:: 4. 設定分支與遠端連結
git branch -M main
git remote add origin https://github.com/neil289506-commits/Image-Converter.git

:: 5. 強制上傳 (Push)
git push -u origin main

echo.
echo ======================================================
echo 上傳完成！去 GitHub 重新整理頁面看看吧。
echo ======================================================
pause