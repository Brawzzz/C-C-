param($input_file , $output_file , $nmb_points)

$exe_file = "voronizing.exe"

if(Test-Path $exe_file){

    Write-Host "Running script ..."
    Write-Host ""

    & .\$exe_file $input_file $output_file $nmb_points
    
    if($?){
        Start-Process .\$output_file
    }
}
