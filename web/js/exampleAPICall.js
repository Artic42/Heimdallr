function getHelloWorld() {
    fetch(`http://${hostname}:8000/`)

        .then(response => response.json())
        .then(json => {
            console.log(json);
        })
    console.log(`This is the url I called to ${hostname}`)
}

function call() {
    fetch(`http://${hostname}:8000/respond1`)
    .then(response => response.json())
    .then(json => {
    console.log(json);
    if (json.code == 1) { changeImageToOk(); }
    else { changeImageToFail(); }
    })
}

function changeImageToOk() {
    console.log("Everything OK");
    var responseImg = document.getElementById("responseImg")
    responseImg.src = "../images/checked.png"
}

function changeImageToFail() {
    console.log("Everything fail");
    var responseImg = document.getElementById("responseImg")
    responseImg.src = "../images/cancel.png"
}

var hostname = window.location.hostname;
document.getElementById("myButton").addEventListener("click", call);

