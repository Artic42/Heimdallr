docker build -t heimdallr_image .
docker run -d -t -p 12050:80 --name heimdallrWebApp heimdallr_image
