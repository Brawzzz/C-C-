Write-Host "O-FILE COMPILATION ..."
Write-Host "gcc -c Matrix.c -o Matrix.o"
Write-Host ""
gcc -c Matrix.c -o Matrix.o
gcc -c main.c -o main.o

if($?){
    Write-Host "LINKING ..." 
    Write-Host "gcc Matrix.o -o Matrix.exe"
    Write-Host ""
    gcc main.o Matrix.o -o main.exe
}

rm *.o
Write-Host "COMPILATION DONE !"
Write-Host ""

