# Run all Python scripts in the scripts directory

$scriptPath = Join-Path $PSScriptRoot "scripts"
$pythonScripts = Get-ChildItem -Path $scriptPath -Filter "*.py" | Sort-Object { [int]($_.Name -replace '^day(\d+).*', '$1') }, Name

Write-Host "=====================================" -ForegroundColor Cyan
Write-Host "Running all Python scripts" -ForegroundColor Cyan
Write-Host "Total scripts: $($pythonScripts.Count)" -ForegroundColor Cyan
Write-Host "=====================================" -ForegroundColor Cyan
Write-Host ""

$successCount = 0
$failCount = 0

foreach ($script in $pythonScripts) {
    Write-Host "Running: $($script.Name)" -ForegroundColor Yellow
    Write-Host "-------------------------------------"
    
    try {
        Push-Location $scriptPath
        python $script.Name
        Pop-Location
        if ($LASTEXITCODE -eq 0) {
            $successCount++
            Write-Host "Success" -ForegroundColor Green
        } else {
            $failCount++
            Write-Host "Failed with exit code: $LASTEXITCODE" -ForegroundColor Red
        }
    } catch {
        Pop-Location
        $failCount++
        Write-Host "Error: $_" -ForegroundColor Red
    }
    
    Write-Host ""
}

Write-Host "=====================================" -ForegroundColor Cyan
Write-Host "Summary" -ForegroundColor Cyan
Write-Host "Total: $($pythonScripts.Count) | Success: $successCount | Failed: $failCount" -ForegroundColor Cyan
Write-Host "=====================================" -ForegroundColor Cyan
