# Run all C++ scripts in the scripts directory

$scriptPath = Join-Path $PSScriptRoot "scripts"
$buildPath = Join-Path $PSScriptRoot "build"
$cppScripts = Get-ChildItem -Path $scriptPath -Filter "*.cpp" | Sort-Object { [int]($_.Name -replace '^day(\d+).*', '$1') }, Name

# Create build directory if it doesn't exist
if (-not (Test-Path $buildPath)) {
    New-Item -ItemType Directory -Path $buildPath | Out-Null
    Write-Host "Created build directory: $buildPath" -ForegroundColor Cyan
    Write-Host ""
}

Write-Host "=====================================" -ForegroundColor Cyan
Write-Host "Running all C++ scripts" -ForegroundColor Cyan
Write-Host "Total scripts: $($cppScripts.Count)" -ForegroundColor Cyan
Write-Host "=====================================" -ForegroundColor Cyan
Write-Host ""

$successCount = 0
$failCount = 0

foreach ($script in $cppScripts) {
    $baseName = [System.IO.Path]::GetFileNameWithoutExtension($script.Name)
    $exeName = "$baseName.exe"
    $exePath = Join-Path $buildPath $exeName
    
    Write-Host "Processing: $($script.Name)" -ForegroundColor Yellow
    Write-Host "-------------------------------------"
    
    # Compile
    Write-Host "Compiling..." -ForegroundColor Gray
    try {
        g++ -std=c++17 -O2 $script.FullName -o $exePath 2>&1 | Out-Null
        
        if ($LASTEXITCODE -ne 0) {
            $failCount++
            Write-Host "Compilation failed" -ForegroundColor Red
            Write-Host ""
            continue
        }
        
        # Run (change to scripts directory so relative paths work)
        Write-Host "Running..." -ForegroundColor Gray
        $originalLocation = Get-Location
        Set-Location $scriptPath
        & $exePath
        $exitCode = $LASTEXITCODE
        Set-Location $originalLocation
        
        if ($exitCode -eq 0) {
            $successCount++
            Write-Host "Success" -ForegroundColor Green
        } else {
            $failCount++
            Write-Host "Runtime failed with exit code: $exitCode" -ForegroundColor Red
        }
    } catch {
        $failCount++
        Write-Host "Error: $_" -ForegroundColor Red
    }
    
    Write-Host ""
}

Write-Host "=====================================" -ForegroundColor Cyan
Write-Host "Summary" -ForegroundColor Cyan
Write-Host "Total: $($cppScripts.Count) | Success: $successCount | Failed: $failCount" -ForegroundColor Cyan
Write-Host "=====================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "Compiled executables are in: $buildPath" -ForegroundColor Gray
