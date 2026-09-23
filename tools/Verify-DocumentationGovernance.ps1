[CmdletBinding()]
param(
    [string]$RepositoryRoot
)

$ErrorActionPreference = 'Stop'
if ([string]::IsNullOrWhiteSpace($RepositoryRoot)) {
    $RepositoryRoot = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
}

function Require([bool]$Condition, [string]$Message) {
    if (-not $Condition) { throw $Message }
}

function Get-Headings([string]$Text) {
    @([regex]::Matches($Text, '(?m)^#{1,6}\s+(.+?)\s*$') | ForEach-Object { $_.Groups[1].Value })
}

function Require-Title([string]$Path, [string]$Title) {
    $text = Get-Content -Raw -LiteralPath $Path
    Require ($text -match ('(?m)^# ' + [regex]::Escape($Title) + '$')) "$Path must start with '# $Title'."
}

$docs = Join-Path $RepositoryRoot 'docs'
$requiredFiles = @(
    'README.md', 'states/CURRENT.md', 'states/QUEUE.md', 'states/TODO.md',
    'rules/ARCHITECTURE.md', 'rules/CODING.md', 'rules/DOCUMENT.md', 'rules/EXECUTION.md',
    'design/GOAL.md', 'design/ARCHITECTURE.md', 'design/CODING.md', 'design/UI.md', 'design/ROADMAP.md',
    'etc/README.md', 'etc/operations/policy/source-policy.md'
)
foreach ($relative in $requiredFiles) {
    Require (Test-Path -LiteralPath (Join-Path $docs $relative)) "Missing governance authority: docs/$relative"
}

Require-Title (Join-Path $RepositoryRoot 'AGENTS.md') 'Agent Instructions'
Require-Title (Join-Path $RepositoryRoot 'CONTRIBUTING.md') 'Contributing'
Require-Title (Join-Path $docs 'README.md') 'Documentation Guide'
Require-Title (Join-Path $docs 'states/CURRENT.md') 'Project Status'
Require-Title (Join-Path $docs 'states/QUEUE.md') 'Queue'
Require-Title (Join-Path $docs 'states/TODO.md') 'Long-Term Review Ledger'

$current = Get-Content -Raw -LiteralPath (Join-Path $docs 'states/CURRENT.md')
Require (($current | Select-String -AllMatches -Pattern '(?m)^## Current Technical Baseline$').Matches.Count -eq 1) 'CURRENT.md must have exactly one Current Technical Baseline section.'
Require (($current | Select-String -AllMatches -Pattern '(?m)^## M\d+ T\d+ S\d+ Packet$').Matches.Count -eq 1) 'CURRENT.md must contain exactly one active M/T/S packet.'
foreach ($field in @('Identifier Mode', 'Admission And Approval', 'Objective', 'Non-goals', 'Reference Baseline', 'Candidate Proposal', 'Files And ABI Surface', 'Applicable Rules', 'Verification', 'Expected Markers', 'Asset Needs', 'Reporting Requirements', 'Stop Conditions', 'Exit Criteria', 'Original Owner Request', 'Similar-Issue Sweep')) {
    Require ($current -match ('(?m)^\|\s*' + [regex]::Escape($field) + '\s*\|\s*\S.+\|\s*$')) "CURRENT.md packet is missing '$field'."
}

$queue = Get-Content -Raw -LiteralPath (Join-Path $docs 'states/QUEUE.md')
$proposalFiles = @(Get-ChildItem -LiteralPath (Join-Path $docs 'proposals') -File -Filter '*.md')
Require ($proposalFiles.Count -gt 0) 'At least one proposal is required.'
foreach ($proposal in $proposalFiles) {
    Require ($queue -match [regex]::Escape("../proposals/$($proposal.Name)")) "Queue does not link proposal $($proposal.Name)."
}

$markdownFiles = @(Get-ChildItem -LiteralPath $RepositoryRoot -Recurse -File -Filter '*.md')
foreach ($file in $markdownFiles) {
    $text = Get-Content -Raw -LiteralPath $file.FullName
    Require ($text -notmatch '\uFFFD|Ã.|â.') "Possible encoding corruption in $($file.FullName)."
    Require ($text -notmatch '(?i)[a-z]:\\(?:users|repos|temp|appdata)\\') "Machine-local path in $($file.FullName)."
}

Write-Output 'Documentation governance checks passed.'
