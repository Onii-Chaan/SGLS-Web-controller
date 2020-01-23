var settTitles = [
    'Change your network credetials',
    'Default reset',
    'Update',
    'Return to SoftAP',
    'About Us'
];//settings lapas collapsible pogu nosaukumi

function createSettCols() {//Izveido settings lapas collapsible pogas
    for (var i = 0; i < 5; i++) {//Izveido pogas elementus      
        var collapsibleObj = new CollapsibleButton(
            new Icon("arrow", "medIcon"), settTitles[i], document.body, new Icon("bookmark", "medIcon")
        );
        collapsibleObj.buildCollapseButton();
    }
    var formObj = new InputForm(
        'Change your network credentials: ',
        ['Input your new WLAN ssid:', 'Input your new WLAN password:'],
        document.getElementsByClassName('elemPlaceHolder')[0]
    );
    formObj.build();
}



