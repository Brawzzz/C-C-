$input_file = "test_jpeg"
$output_file_base_name = "output"

$output_extension = ".jpg"

$output_file = $output_file_base_name + $output_extension

$c_file = $input_file + ".c"
$o_file = $input_file + ".o"
$exe_file = $input_file + ".exe"

$include_path = "C:\SOFTS\ljpeg\libjpeg\include\"
$lib_path = "C:\SOFTS\ljpeg\libjpeg\lib\"

$lib_jpeg_name = "libjpeg"

Write-Host "Launching o-file compilation ..."
gcc -I $include_path -c $c_file -o $o_file

if($?){
    Write-Host "o-compilation done !"

    Write-Host "Launching exe-file compilation ..."
    gcc $o_file -L $lib_path -l $lib_jpeg_name -o $exe_file

    if($?){
        Write-Host "exe-compilation done !"

        Write-Host "Running exe-file ..."
        & .\$exe_file

        if($?){
            Write-Host "DONE !"
            rm *.o
            
            Start-Process .\$output_file
        }
        else{
            Write-Host "Running Failed !"
        }
    }
    else{
        Write-Host "exe-compilation failed !"
    }
}
else{
    Write-Host "o-ompilation failed !"
}