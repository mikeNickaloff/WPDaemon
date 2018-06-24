'use strict'
var wsUri = "wss://localhost:65300"
window.loggedin = false

window.onload = function () {
    var socket = new WebSocket(wsUri)

    socket.onclose = function () {
        console.error("web channel closed")
    }
    socket.onerror = function (error) {
        console.error("web channel error: " + error)
    }
    socket.onopen = function () {
        window.channel = new QWebChannel(socket, function (channel) {
            //connect to the changed signal of a property
            console.log("connected to " + window.channel)

            channel.objects.clientInteraction.requireLogin.connect(function () {
                $('#loginDialog').show()
            })
            var loginDialog = document.querySelector("#loginDialog")
            loginDialog.style.display = 'block'
        })
    }
}
