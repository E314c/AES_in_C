@echo off
@rem go up one directory (out of /test/)
cd ..
@SET OUTPUT_FILE=test_fips.txt
@SET OUTPUT_PATH=tests/results/
@SET INPUT_FILE=data/fips.txt
@SET DEBUG_LEVEL=2
@rem Check for param 1, if so, set debug level
IF NOT "%1"=="" SET DEBUG_LEVEL=%1

AES_Ref -i "%INPUT_FILE%" -D %DEBUG_LEVEL% > "%OUTPUT_PATH%%OUTPUT_FILE%"
@rem open the file
if exist "C:\Program Files (x86)\Notepad++\notepad++.exe" (
    cd "C:\Program Files (x86)\Notepad++"
	echo "Notepad ++ exists on system, Opening in that"
	start notepad++ "%OUTPUT_PATH%%OUTPUT_FILE%"
) else (
    start notepad "%OUTPUT_PATH%%OUTPUT_FILE%"
)
cd tests
@rem un-comment this line if you need to pause the script at the end
rem pause
