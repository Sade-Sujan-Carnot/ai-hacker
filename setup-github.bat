@echo off
REM Git Setup Script - Push to GitHub

echo.
echo =====================================
echo  GIT & GITHUB SETUP
echo =====================================
echo.

REM Check if git is installed
git --version >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Git is not installed!
    echo Please install Git from: https://git-scm.com
    pause
    exit /b 1
)

REM Initialize git if not already done
if not exist .git (
    echo Initializing git repository...
    git init
    echo ✓ Git initialized
) else (
    echo ✓ Git already initialized
)

REM Configure git (optional)
echo.
echo Configuring git (optional)...
echo Enter your name (or press Enter to skip):
set /p git_name="> "
if not "%git_name%"=="" (
    git config user.name "%git_name%"
    echo ✓ User name set
)

echo Enter your email (or press Enter to skip):
set /p git_email="> "
if not "%git_email%"=="" (
    git config user.email "%git_email%"
    echo ✓ Email set
)

REM Add files
echo.
echo Adding files to git...
git add .
echo ✓ Files added

REM Initial commit
echo.
echo Creating initial commit...
git commit -m "Initial commit: Free Weather API with C++ backend and animated UI"
echo ✓ Commit created

REM Show instructions
echo.
echo =====================================
echo  NEXT STEPS - PUSH TO GITHUB
echo =====================================
echo.
echo 1. Create a GitHub account (if you don't have one):
echo    https://github.com/signup
echo.
echo 2. Create a new repository:
echo    https://github.com/new
echo.
echo    Name: weather-app-free-api
echo    Description: Free weather API with C++ backend
echo    Visibility: Public (for GitHub Pages)
echo    DO NOT init with README
echo.
echo 3. After creating the repo, run these commands:
echo.
echo    git remote add origin https://github.com/YOUR_USERNAME/weather-app-free-api.git
echo    git branch -M main
echo    git push -u origin main
echo.
echo 4. Replace YOUR_USERNAME with your actual GitHub username
echo.
echo =====================================
echo.
echo Current git status:
echo.
git status
echo.
echo.
pause
