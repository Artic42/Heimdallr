FROM nginx:alpine-slim

# Delete default page and create necessary directories
RUN rm -rf /usr/share/nginx/html/*

# Install php and necessary packages
RUN apk add php
RUN apk add php-fpm
RUN apk add php-json
RUN apk add php-mysqli
RUN apk add php-session
RUN mkdir -p /run/php


# Install python3 and pip3 and necessary packages
RUN apk add py3-pip

# Copy files from repository to container
COPY web /usr/share/nginx
COPY nginx.conf /etc/nginx/nginx.conf

EXPOSE 80
CMD ["nginx", "-g", "daemon off;"]

