FROM nginx:alpine-slim

# Delete default page and create necessary directories
RUN rm -rf /usr/share/nginx/html/*
RUN mkdir /usr/share/nginx/backend

# Install python3 and pip3 and necessary packages
RUN apk add py3-pip
RUN pip3 install cgi

# Copy files from repository to container
COPY web /usr/share/nginx/html
COPY backend /usr/share/nginx/backend

EXPOSE 80
CMD ["nginx", "-g", "daemon off;"]
