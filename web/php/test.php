<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $name = $_POST["name"];
    $email = $_POST["email"];
    $data = "Name: $name\nEmail: $email\n";

    // Specify the path to the file where you want to store the data
    $file_path = "/var/www/html/form_data.txt";

    // Open the file in append mode and write the data
    file_put_contents($file_path, $data, FILE_APPEND | LOCK_EX);

    echo "Data has been successfully saved.";
}
?>
