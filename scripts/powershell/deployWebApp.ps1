docker build -t heimdallr_image .
docker run -d -t -p 9000:80 --name heimdallrWebApp heimdallr_image
