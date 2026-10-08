param([string]$Compiler = 'g++', [string]$Filter = '*.cpp')
$ErrorActionPreference = 'Stop'
$OutputEncoding = [Console]::OutputEncoding = [Text.UTF8Encoding]::new()
$root = $PSScriptRoot
$build = Join-Path ([IO.Path]::GetTempPath()) ('cpp-legacy-' + [guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $build | Out-Null
$passed = 0
$failed = 0
try {
    $files = @(Get-ChildItem -LiteralPath $root -Recurse -File -Filter $Filter | Where-Object { $_.Extension -eq '.cpp' })
    if ($files.Count -eq 0) { throw 'No exercise matched.' }
    foreach ($file in $files) {
        $exe = Join-Path $build ($file.BaseName + '.exe')
        $compileLog = Join-Path $build 'compile.txt'
        $compileError = Join-Path $build 'compile-errors.txt'
        $compileArgs = '-std=c++17 -Wall -Wextra -pedantic -Werror -pthread "' + $file.FullName + '" -o "' + $exe + '"'
        $compile = Start-Process -FilePath $Compiler -ArgumentList $compileArgs -WindowStyle Hidden -PassThru -RedirectStandardOutput $compileLog -RedirectStandardError $compileError
        # Cache the process handle so Windows PowerShell can retrieve ExitCode after exit.
        $compileHandle = $compile.Handle
        if (-not $compile.WaitForExit(60000)) { $compile.Kill(); throw ('Compile timeout: ' + $file.Name) }
        $compile.WaitForExit()
        if ($compile.ExitCode -ne 0) {
            Write-Output ('COMPILE FAIL ' + $file.Name)
            Get-Content -LiteralPath $compileError -Encoding UTF8
            $failed++
            continue
        }
        $out = Join-Path $build 'stdout.txt'
        $err = Join-Path $build 'stderr.txt'
        $run = Start-Process -FilePath $exe -WindowStyle Hidden -PassThru -RedirectStandardOutput $out -RedirectStandardError $err
        $runHandle = $run.Handle
        if (-not $run.WaitForExit(10000)) { $run.Kill(); throw ('Run timeout: ' + $file.Name) }
        $run.WaitForExit()
        if ($run.ExitCode -eq 0) { $passed++; Write-Output ('PASS ' + $file.Name) }
        else { $failed++; Write-Output ('FAIL ' + $file.Name); Get-Content $out,$err -Encoding UTF8 }
    }
    Write-Output "TOTAL=$($files.Count) PASS=$passed FAIL=$failed"
    if ($failed) { exit 1 }
}
finally {
    # Delete only this run's validated temporary directory.
    $resolved = [IO.Path]::GetFullPath($build)
    $tempRoot = [IO.Path]::GetFullPath([IO.Path]::GetTempPath()).TrimEnd('\') + '\'
    if ($resolved.StartsWith($tempRoot, [StringComparison]::OrdinalIgnoreCase) -and (Split-Path $resolved -Leaf) -match '^cpp-legacy-[0-9a-f]{32}$') {
        Remove-Item -LiteralPath $resolved -Recurse -Force
    }
}
