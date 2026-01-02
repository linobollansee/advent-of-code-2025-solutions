# Run all JavaScript scripts in the scripts directory

$scriptPath = Join-Path $PSScriptRoot "scripts"
$jsScripts = Get-ChildItem -Path $scriptPath -Filter "*.js" | Sort-Object { [int]($_.Name -replace '^day(\d+).*', '$1') }, Name

Write-Host "=====================================" -ForegroundColor Cyan
Write-Host "Running all JavaScript scripts" -ForegroundColor Cyan
Write-Host "Total scripts: $($jsScripts.Count)" -ForegroundColor Cyan
Write-Host "=====================================" -ForegroundColor Cyan
Write-Host ""

$successCount = 0
$failCount = 0

foreach ($script in $jsScripts) {
    Write-Host "Running: $($script.Name)" -ForegroundColor Yellow
    Write-Host "-------------------------------------"
    
    try {
        Push-Location $scriptPath
        node $script.Name
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
Write-Host "Total: $($jsScripts.Count) | Success: $successCount | Failed: $failCount" -ForegroundColor Cyan
Write-Host "=====================================" -ForegroundColor Cyan
