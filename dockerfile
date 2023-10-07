FROM nginx:alpine-slim

# Delete default page and create necessary directories
RUN rm -rf /usr/share/nginx/html/*

# Install python3 and pip3 and necessary packages
RUN apk add py3-pip
RUN pip3 install --upgrade pip
RUN pip3 install fastapi
RUN pip3 install uvicorn

# Copy files from repository to container
COPY web /usr/share/nginx
COPY nginx.conf /etc/nginx/nginx.conf

RUN python3 /usr/share/nginx/python/API.py&


EXPOSE 80
CMD ["/usr/share/nginx/start.sh"]

