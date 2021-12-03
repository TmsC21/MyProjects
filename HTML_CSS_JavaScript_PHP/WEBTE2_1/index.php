<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Files upload</title>
    <link rel="stylesheet" href="style.css">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-BmbxuPwQa2lc/FVzBcNJ7UAyJxM6wuqIj61tLrc4wSX0szH/Ev+nYRRuWlolflfl" crossorigin="anonymous">
</head>

<body>

<div class="container" id="first">
    <form class="form-control" action="upload.php" enctype="multipart/form-data" method="post" id="formular">
        <label for="file-upload">File upload:</label>
        <input type="text" placeholder="File name" name="filename" id="input-text">
        <input type="file" id="file-upload" name="FileToUpload">
        <button class="btn btn-secondary" type="button" id="posli" >Submit</button>
        <div id="Text_upload"></div>
    </form>
</div>
<div class="container">
    <div class="col">
        <div id="table"></div>
    </div>
</div>
<script src="https://kit.fontawesome.com/e611225aec.js" crossorigin="anonymous"></script>
<script src="JavaScript.js"></script>
</body>
</html>

