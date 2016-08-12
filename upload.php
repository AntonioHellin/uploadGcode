<?php
$ruta = './Files/';
$message = '';
foreach ($_FILES as $key)
{
	if($key['error'] == UPLOAD_ERR_OK ){
		$NombreOriginal = $key['name'];
		$temporal = $key['tmp_name'];
		$Destino = $ruta.$NombreOriginal;	
			
		move_uploaded_file($temporal, $Destino);
		$file_upload = $ruta . basename($key['name']);
		//$file_upload = $ruta . basename($_FILES[$key['name']]);
		system("filetest.exe $file_upload");

	}

	if ($key['error']==''){
		$message .= '-> File <b>'.$NombreOriginal.'</b> analyzed satisfactorily. <br>';
	}
	if ($key['error']!=''){
		$message .= '-> Impossible to open <b>'.$NombreOriginal.'</b> because of: <br>'.$key['error']; 
	}
}
echo $message;
?>