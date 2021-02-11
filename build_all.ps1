param (
    [Parameter(Mandatory=$true)][ValidateSet('Release', 'Debug')]$config
)

cmake -G "Visual Studio 14 2015"  -A x64 .
cmake --build . --config $config -- /maxcpucount
