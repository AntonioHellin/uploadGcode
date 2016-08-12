<?php
$ruta = './Files/';			//Save location
$message = '';				
foreach ($_FILES as $key)	//Bucle
{	
	if($key['error'] == UPLOAD_ERR_OK ){		//Check if the file is done properly
		$NombreOriginal = $key['name'];			//Get the Original filename		
		$temporal = $key['tmp_name'];			//Get the Original filepath
		$Destino = $ruta.$NombreOriginal;		//Create a new destination path
			
		move_uploaded_file($temporal, $Destino);		//Move the file to the path ./File/
		$file_upload = $ruta . basename($key['name']);	//$file_upload is, for examplo, test.gcode
		
		//Execute tools (C++) --> filetest.exe
		//Pass by reference the uploaded file --> $file_upload 
		//
		//argv[0] --> filetest.exe
		//argv[1] --> $file_upload
		//

		system("filetest.exe $file_upload");					

	}

	//File successful

	if ($key['error']==''){
		$message .= '-> File <b>'.$NombreOriginal.'</b> analyzed satisfactorily. <br>';
	}

	//File not successful

	if ($key['error']!=''){
		$message .= '-> Impossible to open <b>'.$NombreOriginal.'</b> because of: <br>'.$key['error']; 
	}
}
echo $message;
?>