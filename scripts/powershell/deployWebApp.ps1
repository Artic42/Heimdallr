docker build -t heimdallr_image .
docker run -d -t -p 12050:80 -p 12051:8000 --name heimdallrWebApp heimdallr_image
