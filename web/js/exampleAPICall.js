function getHelloWorld() {
    fetch("http://localhost:12051/")

        .then(response => response.json())
        .then(json => {
            console.log(json);
        })
}

document.getElementById("myButton").addEventListener("click", getHelloWorld);