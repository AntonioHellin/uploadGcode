/**
 * Client-side file upload and asynchronous analysis trigger.
 */

$(function () {
    $('#send').click(uploadGcodeFiles);
});

function uploadGcodeFiles() {
    var fileInputElement = document.getElementById("archivos");
    var files = fileInputElement.files;

    if (!files || files.length === 0) {
        displayMessage("Please select at least one G-code file to upload.");
        return;
    }

    var formData = new FormData();
    for (var i = 0; i < files.length; i++) {
        formData.append('file_' + i, files[i]);
    }

    $.ajax({
        url: 'upload.php',
        type: 'POST',
        contentType: false,
        data: formData,
        processData: false,
        cache: false
    }).done(function (response) {
        displayMessage(response);
    }).fail(function (xhr, status, error) {
        displayMessage("Error uploading file: " + error);
    });
}

function displayMessage(messageContent) {
    $('.message').html(messageContent);
    $('.message').show('slow');
}