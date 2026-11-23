
$Project = "C:\VampetaOS"
$Output = [Environment]::GetFolderPath("Desktop") + "\VampetaOS_dump.txt"

$ExcludedDirs = @(
    ".git", "build", "managed_components",
    ".vscode", ".idea", "__pycache__"
)

$ExcludedFiles = @(
    "sdkconfig", "sdkconfig.old",
    ".env", ".env.local"
)

$BinaryExtensions = @(
    ".bin", ".elf", ".map", ".a", ".o", ".obj",
    ".lib", ".dll", ".exe", ".pyc", ".png",
    ".jpg", ".jpeg", ".gif", ".ico", ".pdf",
    ".zip", ".gz", ".tar", ".mp4", ".mp3",
    ".woff", ".woff2"
)

if (!(Test-Path $Project)) {
    Write-Host "Projeto nao encontrado!"
    exit 1
}

$Files = Get-ChildItem -LiteralPath $Project -Recurse -File -Force |
    Where-Object {
        $Relative = $_.FullName.Substring($Project.Length).TrimStart('\')
        $Parts = $Relative -split '\\'

        $Excluded = $false

        foreach ($Part in $Parts) {
            if ($ExcludedDirs -contains $Part) {
                $Excluded = $true
                break
            }
        }

        !$Excluded -and
        $_.Name -notin $ExcludedFiles -and
        $_.Extension -notin $BinaryExtensions -and
        $_.Length -lt 1MB -and
        $_.Name -notmatch '(?i)\.(pem|key|p12|pfx|jks)$'
    }

$Writer = [System.IO.StreamWriter]::new(
    $Output,
    $false,
    [System.Text.UTF8Encoding]::new($false)
)

try {
    foreach ($File in $Files) {
        $Relative = $File.FullName.Substring($Project.Length)

        Write-Host "Reading: $Relative"

        $Content = Get-Content -LiteralPath $File.FullName -Raw

        $Content = $Content -replace `
            '(?im)(\b(?:WIFI_PASSWORD|PASSWORD|API_KEY|SECRET_KEY|ACCESS_TOKEN)\s*=\s*")[^"]*(")', `
            '$1[REDACTED]$2'

        $Content = $Content -replace `
            '(?im)(\b(?:password|passwd|api_key|secret|access_token)\b\s*:\s*")[^"]*(")', `
            '$1[REDACTED]$2'

        $Writer.WriteLine("")
        $Writer.WriteLine("============================================================")
        $Writer.WriteLine("FILE: $Relative")
        $Writer.WriteLine("============================================================")
        $Writer.WriteLine($Content)
    }
}
finally {
    $Writer.Dispose()
}

Write-Host ""
Write-Host "EXPORT COMPLETED"
Write-Host "Files: $($Files.Count)"
Write-Host "Output: $Output"
