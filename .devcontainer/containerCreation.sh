# Install python and node js
sudo apk add py3-pip
sudo apk add nodejs
sudo apk add npm

# Install personal python library and added to python path
sudo mkdir /pythonLib
sudo chown vscode:vscode /pythonLib
cd /pythonLib
wget https://github.com/Artic42/pythonLib/releases/download/arun-v0.1/pythonLib-arun.tar
tar xvf *.tar
rm -f *.tar

# Install necesary python libs from pip 
# Required by the library
pip install colorama

# Required by project
pip install uvicorn
pip install fastapi