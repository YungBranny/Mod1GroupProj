setlocal
@pushd

@echo argument 1 is %1%
@echo argument 2 is %2%


:: @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
:: parameters - we resolve these to absolute paths
:: @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

:: SOURCEFOLDER_IN is 1st param 
@set SOURCEFOLDER_IN=%1%

::resolve to abs path
@pushd
@cd %SOURCEFOLDER_IN%
@set SOURCEFOLDER_ABS=%CD%
@popd

@echo @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@echo @ Data Build Starting
@echo @
@echo @ Source Asset Folder: %SOURCEFOLDER_ABS%

:: output folderOUTPUTFOLDER_IN is 2nd param of batch file
@set OUTPUTFOLDER_IN=%2%

::resolve to abs path
@pushd
@cd %OUTPUTFOLDER_IN%
@set OUTPUTFOLDER_ABS=%CD%
@popd

@echo @ Output Asset Folder: %OUTPUTFOLDER_ABS%
@echo @
@echo @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

:: @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
:: copy assets from resources
:: @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@echo ----------------------------------------------------------------------------------------------------
@echo - Copying all files from resources to android assets files
@echo -
@echo -	Source folder: %SOURCEFOLDER_ABS%
@echo -	Output folder: %OUTPUTFOLDER_ABS%
@echo ----------------------------------------------------------------------------------------------------
:: /mir - mirror the folder structure
:: /xo	- excludes older files (i.e. only copy if newer)
:: /xf	- exclude files matching following wildcard
:: other switches reduce output verbosity
@robocopy /mir /xo /njh /njs /ns /nc /ndl /np %SOURCEFOLDER_ABS% %OUTPUTFOLDER_ABS% /xf *.oep


@echo @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@echo Data Build Finished
@echo @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@popd
endlocal
