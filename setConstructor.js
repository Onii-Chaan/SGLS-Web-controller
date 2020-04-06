var SETT_TITLES = [
    'Choose connection mode',
    'Change your WiFi credentials',
    'Change your Access Point credentials',
    'Change you lamp quantity',
    'Change your controller link',
    'Factory reset',
    'About Us'
];//settings lapas collapsible pogu nosaukumi

var SETT_DATA = [
    [
        '',
        [
            'Input your new WiFi ssid:',
            'Input your new WiFi password:'
        ],
        'Save',
        [
            'ssid',
            'pass'
        ],
        'wlan'
    ],
    [
        '',
        [
            'Input your AP ssid:',
            'Input your AP password:'
        ],
        'Save',
        [
            'ssid',
            'pass'
        ],
        'softap'
    ],
    [
        '',
        ['Input how many RayLight lamps you have connected: '],
        'Save',
        ['number'],
        'newLampCount'
    ],
    [
        '',
        ['Input your new mDNS link:'],
        'Save',
        ['linkName'],
        'newMdns'
    ],
    [
        'Warning: If you reset the lamps, all your saved data will be lost and you will be returned to hub AP',
        '',
        'Reset',
        '',
        'type=data=factoryReset'
    ]
];//visi settings ievades un teksta dati


function createSettCols() {//Izveido settings lapas collapsible pogas
    //izveido pop about us sadaļu
    var collapsibleObj = new CollapsibleButton(
        new Icon("arrow", "medIcon"), SETT_TITLES[0], document.body
    );

    collapsibleObj.buildCollapseButton(); //creates radio input
    let formDiv = buildElementNode('DIV', 'formDiv');
    let aboutTitle = buildElementNode('P', 'formTitle');
    aboutTitle.innerHTML = 'If you choose WLAN, RayLight hub will connect to your local WiFi network, if Access Point, RayLight hub will create its own WiFi network, that you will be able to connect to.';
    formDiv.appendChild(aboutTitle);//izveido virsrakstu

    // let aboutText = buildElementNode('br');
    // formDiv.appendChild(aboutText);

    aboutText = buildElementNode('INPUT', 'radioIn');
    aboutText.setAttribute("type", "radio");
    aboutText.setAttribute("name", "mode");
    formDiv.appendChild(aboutText);

    aboutText = buildElementNode('SPAN');
    aboutText.innerText = " WLAN";
    formDiv.appendChild(aboutText);

    aboutText = buildElementNode('br');
    formDiv.appendChild(aboutText);


    aboutText = buildElementNode('INPUT', 'radioIn');
    aboutText.setAttribute("type", "radio");
    aboutText.setAttribute("name", "mode");
    formDiv.appendChild(aboutText);

    aboutText = buildElementNode('SPAN');
    aboutText.innerText = " Access Point";
    formDiv.appendChild(aboutText);

    aboutText = buildElementNode('br');
    formDiv.appendChild(aboutText);


    aboutText = buildElementNode('BUTTON', 'submitButton');
    aboutText.innerText = "Save";
    aboutText.classList.add("btn");
    aboutText.classList.add("btn-default");



    aboutText.onclick = function () { //reads radio values and sends neccessary data
        if (confirm("Are you sure you want to make these changes?")) {
            if (document.getElementsByClassName("radioIn")[0].checked) {
                sendAjaxData("type=changeWifi=WLAN", 'setJson');
            } else if (document.getElementsByClassName("radioIn")[1].checked) {
                sendAjaxData("type=changeWifi=softAp", 'setJson');
            } else {
                alert("You must check");
            }
        }
    }
    formDiv.appendChild(aboutText);
    document.getElementsByClassName('elemPlaceHolder')[0].appendChild(formDiv);



    for (var i = 1; i < SETT_TITLES.length; i++) {//Izveido pogas elementus      
        collapsibleObj = new CollapsibleButton(
            new Icon("arrow", "medIcon"), SETT_TITLES[i], document.body
        );
        collapsibleObj.buildCollapseButton();
    }

    for (var i = 0; i < SETT_DATA.length; i++) {//izveido visus input elementus atbilstoši SET_DATA masīvam
        var formObj = new InputForm(
            SETT_DATA[i][0],
            SETT_DATA[i][1],
            document.getElementsByClassName('elemPlaceHolder')[i + 1],
        );
        formObj.build(SETT_DATA[i][2], SETT_DATA[i][3], SETT_DATA[i][4]);
    }

    //izveido pop about us sadaļu
    formDiv = buildElementNode('DIV', 'formDiv');
    aboutTitle = buildElementNode('H3', 'formTitle');
    aboutTitle.innerHTML = 'Lighting Solutions Latvia, RayLight ';
    formDiv.appendChild(aboutTitle);//izveido virsrakstu
    formDiv.appendChild(buildElementNode('br'));
    aboutText = buildElementNode('P');
    aboutText.innerHTML = 'For technical support please contact us via email: martinnc@inbox.lv';
    formDiv.appendChild(aboutText);
    formDiv.appendChild(buildElementNode('br'));
    aboutLink = buildElementNode('A');
    aboutLink.innerHTML = 'Lighting Solutions Latvia';
    aboutLink.href = 'https://www.youtube.com/watch?v=_S7WEVLbQ-Y&t=260s';
    formDiv.appendChild(aboutLink);
    document.getElementsByClassName('elemPlaceHolder')[SETT_DATA.length + 1].appendChild(formDiv);
}



