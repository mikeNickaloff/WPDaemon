$(document).ready(function () {
    $('#loginForm').submit(submitForm)

    function submitForm(event) {
        //console.log("DEBUG login: " + channel)
        console.log(channel.objects.clientInteraction.login(
                        $('#loginname').val(), $('#loginpassword').val(),
                        function (arg) {
                            //console.log("DEBUG login response: " + arg)
                            if (arg === true) {
                                $('#loginError').hide()
                                document.getElementById(
                                            'loginDialog').style.display = 'none'
                                window.loggedin = true
                                w3_open()
                            } else {
                                $('#LoginError').innerHTML(
                                            "Invalid Username/Password")
                                $('#loginError').show()
                            }
                        }))
        //console.log($('#loginname').val())
        if (event !== undefined)
            event.preventDefault()
        return false
    }
})
$('#messageForm').submit(submitMessage)

function submitMessage(event) {
    channel.objects.chatserver.sendMessage($('#loginname').val(),
                                           $('#message').val())
    $('#message').val('')
    if (event !== undefined)
        event.preventDefault()
    return false
}

var mySidebar = document.getElementById("mySidebar")

// Get the DIV with overlay effect
var overlayBg = document.getElementById("myOverlay")

// Toggle between showing and hiding the sidebar, and add overlay effect
function w3_open() {
    if (mySidebar.style.display === 'block') {
        mySidebar.style.display = 'none'
        overlayBg.style.display = "none"
    } else {
        mySidebar.style.display = 'block'
        overlayBg.style.display = "block"
    }
}

// Close the sidebar with the close button
function w3_close() {
    mySidebar.style.display = "none"
    overlayBg.style.display = "none"
}

function open_site_dashboard(i_site) {/* perform site dashboard load */
}
