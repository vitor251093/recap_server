# Self-elevate the script if required
if (-Not ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] 'Administrator')) {
    if ([int](Get-CimInstance -Class Win32_OperatingSystem | Select-Object -ExpandProperty BuildNumber) -ge 6000) {
        $CommandLine = "-File `"" + $MyInvocation.MyCommand.Path + "`" " + $MyInvocation.UnboundArguments
        Start-Process -FilePath PowerShell.exe -Verb Runas -ArgumentList $CommandLine
        Exit
    }
}

$originalExe = Join-Path $PSScriptRoot "Darkspore.exe"
$newExe = Join-Path $PSScriptRoot "Darkspore_nossl.exe"

if ([System.IO.File]::Exists($newExe)) {
    Exit
}

$bInput = [System.IO.File]::ReadAllBytes($originalExe)

$bOriginal = [Byte[]](0x80, 0xBF, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x75)
$bSubstitu = [Byte[]](0x80, 0xBF, 0x2C, 0x01, 0x00, 0x00, 0x01, 0x75)
$bOutput = [Byte[]]("$bInput" -Replace "\b$bOriginal\b", "$bSubstitu" -Split '\s+')

[System.IO.File]::WriteAllBytes($newExe, $bOutput)
