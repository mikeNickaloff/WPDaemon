// clang-format off
$(document).ready(function () {
    $('#loginForm').submit(submitForm);
    $("#siteForm").submit(addSite);
})
function open_new_site_dialog() {
   $("#siteDialog").show();
}
function addSite(event) {
    channel.objects.clientInteraction.add_site($('#sitename').val(), $('#sitepath').val(), function(arg) {
          alert(arg);
          $('#siteDialog').hide();
          display_all_sites();
    });
    if (event !== undefined)
        event.preventDefault()
    return false
}
function display_all_sites() {
    channel.objects.clientInteraction.websites(function(arg) {
        myObject = JSON.parse(arg)


        w3.show("website_selector");
        w3.displayObject('website_selector', JSON.parse(arg))
    });
}
function submitForm(event) {
    //console.log("DEBUG login: " + channel)

    channel.objects.clientInteraction.login($('#loginname').val(),
                                            $('#loginpassword').val(),
                                            function (arg) {
                                                //console.log("DEBUG login response: " + arg)
                                                if (arg === true) {
                                                    $('#loginError').hide();
                                                    document.getElementById('loginDialog').style.display = 'none';
                                                    window.scrollTo(0,document.getElementById("submodule-container").offsetTop);
                                                    window.loggedin = true;
                                                    channel.objects.clientInteraction.request_token(function(targs) { localStorage.setItem("TOKEN", targs); });
                                                    display_all_submodules();
                                                    display_all_sites();
                                                } else {
                                                    $('#LoginError').html(
                                                                "Invalid Username/Password")
                                                    $('#loginError').show()
                                                }
                                            });
    //console.log($('#loginname').val())
    if (event !== undefined)
        event.preventDefault()
    return false
}

$('#messageForm').submit(submitMessage)

function set_submodule(selectedSubmodule) {
    w3.hide("#submodule_selector");
    window.scrollTo(0,document.getElementById("submodule-container").offsetTop);
 channel.objects.clientInteraction.set_current_submodule(selectedSubmodule, function(args) {
     myObject = JSON.parse(args);


    w3.show("#command_selector");
     w3.hide("#parameter_selector");
     w3.displayObject('command_selector', JSON.parse(args)) });
    document.getElementById("submodule_name").innerHTML = "<i class='far fa-arrow-square-left'></i>Main Menu";
}
function display_all_submodules() {
    var myObject
    w3.hide("#command_selector");
    w3.hide("#parameter_selector");
    window.scrollTo(0,document.getElementById("submodule-container").offsetTop);
    channel.objects.clientInteraction.allowedSubmodules(
                function (arg) {
                    myObject = JSON.parse(arg)


                    w3.show("#submodule_selector");
                    w3.displayObject('submodule_selector', JSON.parse(arg))
                    w3.sortHTML('#submodule_selector', 'tr')

                })
}
function display_all_commands() {
    w3.hide("#parameter_selector");
    w3.show("#command_selector");
    w3.hide("#submodule_selector");
}
function submitMessage(event) {
    channel.objects.chatserver.sendMessage($('#loginname').val(),
                                           $('#message').val())
    $('#message').val('')
    if (event !== undefined)
        event.preventDefault()
    return false
}

// Toggle between showing and hiding the sidebar, and add overlay effect
function w3_open() {
    var mySidebar = document.getElementById("mySidebar")

    // Get the DIV with overlay effect
    var overlayBg = document.getElementById("myOverlay")

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
    var mySidebar = document.getElementById("mySidebar")

    // Get the DIV with overlay effect
    var overlayBg = document.getElementById("myOverlay")

    mySidebar.style.display = "none"
    overlayBg.style.display = "none"
}
function set_command(i_command) {
    w3.hide("#command_selector");
    window.scrollTo(0,document.getElementById("submodule-container").offsetTop);
 channel.objects.clientInteraction.set_current_command(i_command, function(args) {
     myObject = JSON.parse(args);


    w3.show("#parameter_selector");
     w3.displayObject('parameter_selector', JSON.parse(args)) });
    document.getElementById("command_name").innerHTML = "<i class='far fa-arrow-square-left'></i>Previous Menu";
}

function open_site_dashboard(i_site) {
    channel.objects.clientInteraction.set_current_site(i_site, function(args) {
        if (args === true) {

        } else {
            alert("Could not Access Site.\n Make sure the wp-config file is readable by the WPDaemon user.");
        }
    });
    /* perform site dashboard load */
} // clang-format on

function executeCommand() {
    var i;
    var params1;
    var u;
    var params2;
   params1 = document.querySelectorAll(".wp-parameter[type='text']");
    for (i=0; i<params1.length; i++) {
        channel.objects.clientInteraction.set_parameter_value(params1[i].name, params1[i].value);
    }
    params2 = document.querySelectorAll(".wp-parameter[type='checkbox']");
       for (u=0; u<params2.length; u++) {
           channel.objects.clientInteraction.set_parameter_value(params2[u].name, params2[u].checked);
       }
    channel.objects.clientInteraction.execute(function(args) { console.log(args);  $("#resultBox").html(args); $("#resultDialog").show(); });

}
