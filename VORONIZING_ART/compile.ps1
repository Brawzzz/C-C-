Write-Host "O-FILE COMPILATION ..."
Write-Host "gcc -I 'C:\SOFTS\ljpeg\libjpeg\include\' -I 'C:\SOFTS\lpng1640\libpng\include\libpng16' -c voronizing.c -o voronizing.o"
Write-Host ""
gcc -I "C:\SOFTS\ljpeg\libjpeg\include\" -I "C:\SOFTS\lpng1640\libpng\include\libpng16" -c voronizing.c -o voronizing.o

if($?){
    Write-Host "LINKING ..." 
    Write-Host "gcc voronizing.o -L 'C:\SOFTS\ljpeg\libjpeg\lib' -llibjpeg  -L 'C:\SOFTS\lpng1640\libpng\lib' -lpng -o voronizing.exe"
    Write-Host ""
    gcc voronizing.o -L "C:\SOFTS\ljpeg\libjpeg\lib" -llibjpeg  -L "C:\SOFTS\lpng1640\libpng\lib" -lpng -o voronizing.exe
}

rm *.o
Write-Host "COMPILATION DONE !"
Write-Host ""

