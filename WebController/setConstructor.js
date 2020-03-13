var SETT_TITLES = [
    'Change your network credetials',
    'Change your mDNS link',
    'Factory reset',
    'Update',
    'Return to SoftAP',
    'About Us'
];//settings lapas collapsible pogu nosaukumi

var SETT_DATA = [
    [
        'Change your network credentials: ',
        [
            'Input your new WLAN ssid:',
            'Input your new WLAN password:'
        ],
        'Save',
        [
            'ssid',
            'pass'
        ]
    ],
    [
        'Change your mDNS link: ',
        ['Input your new mDNS link:'],
        'Save',
        ['linkName']
    ],
    [
        'Warning: If you will reset the lamps, all your saved data will be lost and you will be returned to hub AP',
        '',
        'Reset',
        '',
        'factory reset'
    ],
    [
        'To update lamps, you have to make sure that your router is connected to internet. An update might take a while to execute. While updating please DO NOT turn off electricity',
        '',
        'Update',
        '',
        'Update'
    ],
    [
        'If you need to change the base options like',
        '',
        'Return',
        '',
        'return to softAP'
    ]
];//visi settings ievades un teksta dati

function createSettCols() {//Izveido settings lapas collapsible pogas
    for (var i = 0; i < 6; i++) {//Izveido pogas elementus      
        var collapsibleObj = new CollapsibleButton(
            new Icon("arrow", "medIcon"), SETT_TITLES[i], document.body
        );
        collapsibleObj.buildCollapseButton();
    }

    for (var i = 0; i < SETT_DATA.length; i++) {//izveido visus input elementus atbilstoši SET_DATA masīvam
        var formObj = new InputForm(
            SETT_DATA[i][0],
            SETT_DATA[i][1],
            document.getElementsByClassName('elemPlaceHolder')[i]
        );
        if(SETT_DATA[i] == 4){
            formObj.build(SETT_DATA[i][2], SETT_DATA[i][3]);
        } else{
            formObj.build(SETT_DATA[i][2], SETT_DATA[i][3], SETT_DATA[i][4]);
        }
    }

    //izveido pop about us sadaļu
    let formDiv = buildElementNode('DIV', 'formDiv');
    let aboutTitle = buildElementNode('H3', 'formTitle');
    aboutTitle.innerHTML = 'RayLight Lighting Solutions Latvia';
    formDiv.appendChild(aboutTitle);//izveido virsrakstu

    let aboutText = buildElementNode('P');
    aboutText.innerHTML = 'We are a company of ...';
    formDiv.appendChild(aboutText);
    
    let aboutLink = buildElementNode('A');
    aboutLink.innerHTML = 'LINK';
    aboutLink.href = 'https://www.youtube.com/watch?v=_S7WEVLbQ-Y&t=802s';
    formDiv.appendChild(aboutLink);
    document.getElementsByClassName('elemPlaceHolder')[SETT_DATA.length].appendChild(formDiv);
}



