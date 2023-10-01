FROM nginx:alpine-slim

# Delete default page and create necessary directories
RUN rm -rf /usr/share/nginx/html/*
RUN mkdir /usr/share/nginx/backend

# Install php and necessary packages
RUN apk add php
RUN apk add php-fpm
RUN apk add php-json


# Install python3 and pip3 and necessary packages
RUN apk add py3-pip

# Copy files from repository to container
COPY web /usr/share/nginx/html

EXPOSE 80
CMD ["nginx", "-g", "daemon off;"]
