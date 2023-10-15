# Install python and node js
sudo apk add py3-pip
sudo apk add nodejs
sudo apk add npm

# Install personal python library and added to python path
sudo mkdir /pythonLib
sudo chown vscode:vscode /pythonLib
cd /pythonLib
wget https://github.com/Artic42/pythonLib/releases/download/BigHorn-v0.2.1/pythonLib-BigHorn.0.2.1.tar
tar xvf *.tar
rm -f *.tar

# Install necesary python libs from pip 
# Required by the library
pip install colorama

# Required by project
pip install uvicorn
pip install fastapi

# Create folder needed inside the container
sudo mkdir /databases
sudo chown vscode:vscode /databases

# Install nginx web server and add current web page
sudo apk add nginx
sudo cp /workspaces/Heimdallr/nginx.conf /etc/nginx/nginx.conf
sudo cp -r /workspaces/Heimdallr/web/* /usr/share/nginx/
sudo chown -R nginx:nginx /usr/share/nginx

# Copy the new bash rc
cp /workspaces/Heimdallr/.devcontainer/bashrc.sh /home/vscode/.bashrc
cp /workspaces/Heimdallr/.devcontainer/bash_profile.sh /home/vscode/.bash_profile