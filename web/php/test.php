$myFile = fopen("test.txt", "w") or die("Unable to open file!");
$text = $_POST['name'];
fwrite($myFile, $text);
fclose($myFile);