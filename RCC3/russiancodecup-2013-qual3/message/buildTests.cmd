@echo off

set problem=message
set author=nv
rem you can set lang as dpr, java, cpp or python
set lang=cpp

echo Generating tests...
mkdir tests
pushd src
python gen.py
popd

echo Compiling checker...

if exist check.dpr goto checkDpr
if exist check.java goto checkJava

echo Checker not found!
goto end

:checkDpr

C:\FPC\2.2.2\bin\i386-win32\fpc.exe -cc check.dpr

goto endCheck

:checkJava

rmdir /S /Q __tmp 2> nul
mkdir __tmp
javac -classpath "__check;%..\..\..\lib\testlib4j.jar" -sourcepath . -d __tmp Check.java
copy /Y ..\..\..\lib\testlib4j.jar __tmp    > nul
pushd __tmp
call jar xf testlib4j.jar
echo Main-Class: ru.ifmo.testlib.CheckerFramework> META-INF/manifest.1
echo Checker-Class: Check>> META-INF/manifest.1
del /S /Q *.java > nul
del testlib4j.jar > nul
call jar cfm check.jar META-INF/manifest.1 *.class ru
copy /Y check.jar .. > nul
popd

rmdir /S /Q __tmp

goto endCheck

:endCheck

if not exist Validate.java goto novalidate

echo Compiling validator...

rmdir /S /Q __tmp 2> nul
mkdir __tmp
javac -sourcepath . -d __tmp Validate.java
pushd __tmp
mkdir META-INF
echo Main-Class: Validate> META-INF/manifest.1
call jar cfm validate.jar META-INF/manifest.1 *.class
copy /Y validate.jar .. > nul
popd
rmdir /S /Q __tmp

:novalidate

echo Generating answers...

if [%lang%]==[java] javac %problem%_%author%.java -encoding utf8
if [%lang%]==[cpp] g++ -O2 %problem%_%author%.cpp -o %problem%_%author%.exe
if [%lang%]==[dpr] dcc32 -cc %problem%_%author%.dpr

for %%i in (tests\??) do (
    echo Test %%i
    copy %%i %problem%.in > nul
    if exist validate.jar (
    java -jar validate.jar < %problem%.in
    if errorlevel 1 (
        echo Validator rejects test %%i
        goto end
    )
    echo Validator accepts test %%i
    )

    if [%lang%]==[java] java -Xmx256M -Xss64M %problem%_%author% < %problem%.in > %problem%.out
    if [%lang%]==[cpp] %problem%_%author%  < %problem%.in > %problem%.out
    if [%lang%]==[dpr] %problem%_%author% < %problem%.in > %problem%.out
    if [%lang%]==[python] python %problem%_%author%.py < %problem%.in > %problem%.out

    copy %problem%.out %%i.a > nul
    echo Check %%i
    if exist check.jar java -jar check.jar %%i %%i.a %%i.a
    if exist check.exe check.exe %%i %%i.a %%i.a
)

:end
pause