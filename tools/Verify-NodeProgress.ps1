param(
    [string]$RepositoryRoot = '.',
    [string]$AdmissionPath = ''
)
$ErrorActionPreference = 'Stop'

function Require($Condition, [string]$Message) {
    if (-not $Condition) { throw $Message }
}

$inventoryPath = Join-Path $RepositoryRoot 'docs/etc/architecture/smb1-rom-migration-inventory.md'
$progressPath = Join-Path $RepositoryRoot 'docs/states/NODE_PROGRESS.md'
$inventory = Get-Content -Raw -Encoding UTF8 -LiteralPath $inventoryPath
$progress = Get-Content -Raw -Encoding UTF8 -LiteralPath $progressPath
$rows = @(foreach ($line in ($inventory -split '\r?\n')) {
    if ($line -notmatch '^\|\s*\d+\s*\|') { continue }
    $cells = $line.Split('|')
    Require ($cells.Count -eq 7) "Inventory row must have five cells: $line"
    [pscustomobject]@{
        Line = [int]$cells[1].Trim()
        Label = $cells[2].Trim().Trim('`')
        Owner = $cells[3].Trim()
        Status = $cells[4].Trim()
        Evidence = $cells[5].Trim()
    }
})
Require ($rows.Count -gt 0) 'Inventory is empty.'
Require (@($rows | Group-Object Label | Where-Object Count -gt 1).Count -eq 0) 'Duplicate inventory labels.'
Require (@($rows | Group-Object Line | Where-Object Count -gt 1).Count -eq 0) 'Duplicate inventory source lines.'
Require ($inventory -match 'Assembly labels: `(\d+)`') 'Missing inventory total.'
Require ([int]$Matches[1] -eq $rows.Count) 'Inventory total disagrees with unique rows.'
$pendingStates = @('mapped, route trace pending', 'ported; route trace pending',
    'ported; focused smoke; route trace pending', 'structural extraction; route trace pending',
    'mapped; evidence incomplete', 'audited; evidence incomplete',
    'audited; mismatch', 'audited; revalidation required', 'audited; implementation missing')
foreach ($row in $rows) {
    Require ($row.Status -eq 'open' -or $row.Status -eq 'ROM-match complete' -or $pendingStates -contains $row.Status) "Unknown status for $($row.Label)."
    Require (-not [string]::IsNullOrWhiteSpace($row.Evidence)) "Missing evidence/disposition for $($row.Label)."
    if ($row.Status -ne 'open') {
        Require ($row.Owner -ne 'unassigned' -and $row.Owner.Length -gt 0) "Missing owner for $($row.Label)."
    }
    if ($row.Status -eq 'ROM-match complete') {
        Require ($row.Evidence -match '\[[^\]]+\]\([^)]+\)') "Completion needs a reviewable evidence link: $($row.Label)."
    }
}
$complete = @($rows | Where-Object Status -eq 'ROM-match complete')
$pending = @($rows | Where-Object { $pendingStates -contains $_.Status })
$open = @($rows | Where-Object Status -eq 'open')
foreach ($entry in @(@('ROM-match complete', $complete.Count),
        @('Mapped / audited, not complete', $pending.Count),
        @('Open / unmatched', $open.Count), @('\*\*Total\*\*', $rows.Count))) {
    Require ($progress -match ('(?m)^\| ' + $entry[0] + ' \| (?:\*\*)?([\d,]+)(?:\*\*)? \|')) "Missing progress counter: $($entry[0])."
    Require ([int]$Matches[1].Replace(',', '') -eq $entry[1]) "Incorrect progress counter: $($entry[0])."
}
function Read-NamedSection([string]$Heading) {
    $pattern = '(?ms)^## ' + $Heading + '[^\r\n]*\r?\n(.*?)(?=^## |\z)'
    Require ($progress -match $pattern) "Missing named section: $Heading"
    $section = $Matches[1]
    return @([regex]::Matches($section, '(?m)^\|\s*(\d+)\s*\|\s*`([^`]+)`\s*\|') |
        ForEach-Object { $_.Groups[1].Value + '|' + $_.Groups[2].Value })
}
foreach ($group in @(@('Mapped but not yet matched', $pending), @('Completed matches', $complete))) {
    $names = @(Read-NamedSection $group[0])
    $expected = @($group[1] | ForEach-Object { "$($_.Line)|$($_.Label)" })
    Require ($names.Count -eq $expected.Count) "Named list count differs: $($group[0])."
    if ($expected.Count -gt 0) {
        Require (@(Compare-Object $expected $names).Count -eq 0) "Named list differs: $($group[0])."
    }
}
$result = [ordered]@{ Total = $rows.Count; Complete = $complete.Count; MappedPending = $pending.Count; Open = $open.Count }
$censusPath = Join-Path $RepositoryRoot 'docs/etc/architecture/m2-t24-s1-full-node-census.md'
if (Test-Path -LiteralPath $censusPath) {
    $census = Get-Content -Raw -Encoding UTF8 -LiteralPath $censusPath
    $censusRows = @([regex]::Matches($census, '(?m)^\| <a id="node-([^"]+)"></a>(\d+) / `([^`]+)`'))
    Require ($censusRows.Count -eq $rows.Count) 'Full audit census must contain every inventory label exactly once.'
    $censusNames = @($censusRows | ForEach-Object { $_.Groups[2].Value + '|' + $_.Groups[3].Value })
    $inventoryNames = @($rows | ForEach-Object { "$($_.Line)|$($_.Label)" })
    Require (@($censusNames | Select-Object -Unique).Count -eq $rows.Count) 'Duplicate census label/line.'
    Require (@(Compare-Object $inventoryNames $censusNames).Count -eq 0) 'Census and inventory disagree.'
    foreach ($match in $censusRows) {
        Require ($match.Groups[1].Value -ceq $match.Groups[3].Value.ToLowerInvariant()) 'Census node anchor mismatch.'
    }
    $statusByLabel = @{}
    foreach ($row in $rows) { $statusByLabel[$row.Label] = $row.Status }
    foreach ($line in ($census -split '\r?\n')) {
        if ($line -notmatch '^\| <a id="node-[^"]+"></a>\d+ / `([^`]+)`') { continue }
        $label = $Matches[1]
        Require ($line.EndsWith('|') -and $line.Split('|').Count -eq 7) "Malformed census row: $label"
        Require ($line -match '\*\*([^*]+)\*\*:') "Missing census disposition: $label"
        Require ($Matches[1] -ceq $statusByLabel[$label]) "Census status disagrees with inventory: $label"
    }
}
if ($AdmissionPath) {
    $admission = Get-Content -Raw -LiteralPath $AdmissionPath | ConvertFrom-Json
    Require ($admission.baseline -eq $complete.Count) 'Admission baseline is stale.'
    Require ($admission.total -eq $rows.Count) 'Admission denominator is stale.'
    $scope = @($admission.scope)
    $expected = @($admission.expectedMatches)
    Require ($null -ne $admission.scope -and $null -ne $admission.expectedMatches) 'Supply scope and expectedMatches arrays (empty is allowed).'
    Require (@($scope | Select-Object -Unique).Count -eq $scope.Count) 'Duplicate scope labels.'
    Require (@($expected | Select-Object -Unique).Count -eq $expected.Count) 'Duplicate expected labels.'
    foreach ($label in $scope) { Require ($rows.Label -ccontains $label) "Unknown inventory label: $label" }
    foreach ($label in $expected) {
        Require ($scope -ccontains $label) "Expected label outside scope: $label"
        Require ($complete.Label -cnotcontains $label) "Already complete: $label"
    }
    Require ($admission.maximumComplete -eq ($complete.Count + $expected.Count)) 'Maximum closing count must equal baseline plus unique expected matches.'
    Require (@($admission.focusedTests).Count -gt 0 -and -not [string]::IsNullOrWhiteSpace(($admission.focusedTests -join ''))) 'Name focused tests.'
    Require (-not [string]::IsNullOrWhiteSpace($admission.romRoute)) 'Name a reproducible ROM route baseline.'
    $result.ScopeCount = $scope.Count
    $result.ExpectedDelta = $expected.Count
    $result.MaximumComplete = $admission.maximumComplete
    $result.Incoming = @($rows | Where-Object { $scope -ccontains $_.Label } | Select-Object Label, Status)
    $taskLedger = Join-Path $RepositoryRoot 'docs/states/NODE_TASK_LEDGER.json'
    if (Test-Path -LiteralPath $taskLedger) {
        & python (Join-Path $RepositoryRoot 'tools/node_task_ledger.py') --root $RepositoryRoot --admission $AdmissionPath
        Require ($LASTEXITCODE -eq 0) 'Node/S ownership or registered forecast admission check failed.'
    }
}
[pscustomobject]$result | ConvertTo-Json -Depth 4
