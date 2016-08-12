$(function(){
	$('#send').click(UploadGcodeFiles); //Click in botton send --> execute function UploadGcodeFiles
});

function UploadGcodeFiles(){	
		var archivos = document.getElementById("archivos");	//Create object with the element "archivos" (input file with id = archivos)
		var archivo = archivos.files;						//Get files from the input file
		var archivos = new FormData();
		for(i=0; i<archivo.length; i++){
			archivos.append('archivo'+i,archivo[i]);
		}
		
		//Ajax function

		$.ajax({
			url:'upload.php',	//Url
			type:'POST',		//Method
			contentType:false,
			data:archivos,		//Object "archivos"
			processData:false,
			cache:false
		}).done(function(msg){	
			MensajeFinal(msg)	//Final message
		});
}

function MensajeFinal(msg){
	$('.message').html(msg);
	$('.message').show('slow');
}