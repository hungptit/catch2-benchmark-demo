param (
    [Parameter(Mandatory=$true)][ValidateSet('Release', 'Debug')]$config
)

cmake -G "Visual Studio 16 2019"  -A x64 .
cmake --build . --config $config -- /maxcpucount
ctest -j3
