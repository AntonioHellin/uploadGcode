$(function(){
	$('#send').click(UploadGcodeFiles);
});

function UploadGcodeFiles(){	
		var archivos = document.getElementById("archivos");
		var archivo = archivos.files;
		var archivos = new FormData();
		for(i=0; i<archivo.length; i++){
			archivos.append('archivo'+i,archivo[i]);
		}
		
		$.ajax({
			url:'upload.php',
			type:'POST',
			contentType:false,
			data:archivos,
			processData:false,
			cache:false
		}).done(function(msg){
			MensajeFinal(msg)
		});
}

function MensajeFinal(msg){
	$('.message').html(msg);
	$('.message').show('slow');
}