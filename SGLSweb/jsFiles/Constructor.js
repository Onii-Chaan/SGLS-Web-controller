function createDynamicContent() {

    createColl(document.body);//izveido saved pogu un tās kontentu
    createSubColl();//izveido papildus divas

    document.body.appendChild(buildElementNode('DIV', 'buttonGroupHolder'));//izveido lampu pogu un grupu pogu atrašanās vietu
    document.getElementsByClassName('buttonGroupHolder')[0].id = 'groupHolder';//pievieno id pogu div elementam

    createLampButts();//izveido lampu pogas
    createExploreColl(document.body);//izveido explore sadaļu

    for (var i = 0; i < document.getElementsByClassName('elemPlaceHolder').length; i++) {//izveido konstantu krāsu un funkciju parent div lielumu, lai varētu
        //  ar atbilstošajām pogām aizpildīt visu laukumu
        document.getElementsByClassName('elemPlaceHolder')[i].style.width =
            Math.ceil(document.getElementsByClassName('elemPlaceHolder')[i].clientWidth) + 'px';
    }
}

/*ExploreArr masīvā glabājas visas explore pogu vērtības*/
var exploreArr = [
    ['SameColor', 123, 123, 123, 123],
    ['hmhmmhh', 0, 23, 0, 122],
    ['word', 255, 255, 0, 0],
    ['manyWords', 10, 10, 23, 18],
    ['manyMore', 10, 23, 15, 200],
    ['Yeye', 100, 200, 100, 0],
    ['pum_pum', 25, 10],
    ['animManim', 50, 0],
    ['someAnim', 10, 100],
    ['oldAnim', 19, 230],
    ['NewAnim', 7, 123]
];

var colorAnimBlockObjArr = [];
function createExploreColl(placeHolder) {//izveido explore collapsible
    var collapsibleObj = new CollapsibleButton(
        new Icon("arrow", "medIcon"),
        "Explore",
        placeHolder,
        new Icon("explore", "medIcon")
    );
    collapsibleObj.buildCollapseButton();
    blockWidthCount = 0;
    // console.log('//////////////////////////////////////////////////////////////////////////////////');
    for (var i = 0; i < exploreArr.length; i++) {//izveido krāsu pogas un saliek tās collapsible pogas kontentā
        if (exploreArr[i].length == 5) {//ja masīva elementa atbilst krāsai 
            colorAnimBlockObjArr.push(
                new ColorBlock(
                    exploreArr[i][0],
                    exploreArr[i].slice(1, 5),
                    'colorBlock',
                    addExploreButton
                )
            );
        } else {
            colorAnimBlockObjArr.push(
                new ColorBlock(
                    exploreArr[i][0],
                    exploreArr[i].slice(1, 3),
                    'colorBlock',
                    addExploreButton
                )
            );
        }
        addColorBlock(i, collapsibleObj, colorAnimBlockObjArr, exploreArr.length);
    }
}

var blockWidthCount = 0;//skaita platumu krāsu bloku radīšanas brīdī
function addColorBlock(j, collObj, objArr, arrLen) {//veido krāsu blokus to atbilstošajā vietā, atbilstošajā lielumā
    collObj.updateContent(objArr[j].build());//uzbūvē krāsu pogu
    objArr[j].grow();//izveido krāsu bloku platumu
    blockWidthCount += objArr[j].blockWidth();//skaita uz priekšu rindas platumu
    // console.log('BEF_LEN: ', objArr[j].blockWidth());
    if (
        blockWidthCount >= collObj.contentLength() ||
        j == arrLen - 1
    ) {//pārbauda vai pēdējo krāsu bloku ir jāpaplašina
        // console.log('A');
        if (
            blockWidthCount - objArr[j].blockWidth() !=
            collObj.contentLength() && j > 0 && j != arrLen - 1
        ) {//pagarina krāsas bloku līdz galam pa kreisi
            objArr[j - 1].grow(
                collObj.contentLength() - (blockWidthCount - objArr[j].blockWidth())
            );
            // console.log('B');
        }
        else if (
            j == arrLen - 1
        ) {
            objArr[j].grow(collObj.contentLength() - blockWidthCount);
            // console.log('D');
        }
        blockWidthCount = objArr[j].blockWidth();//atgriežas uz nākamo rindiņu
    } else if (
        objArr[j].blockWidth() > collObj.contentLength() - blockWidthCount
    ) {
        // console.log('E');

        objArr[j - 1].grow(
            collObj.contentLength() - (blockWidthCount - objArr[j].blockWidth() + 1)
        );
        blockWidthCount = objArr[j].blockWidth();//ieņem nākamā elementa lielumu nākamajā rindiņā
    }
    if (blockWidthCount >= collObj.contentLength()) {
        blockWidthCount = 0;
    }
    //  console.log(objArr[j]);
    //console.log(j);
    //  console.log(collObj);
    // console.log(objArr);
    // console.log('AFTER_LEN: ', objArr[j].blockWidth());
    // console.log('CONTENT_LENGTH', collObj.contentLength());
    // console.log('BLOCK_SUM', blockWidthCount);
    // console.log(arrLen);
    // console.log(objArr[j].show());
    // console.log('---------------------------------------------------');
}




function createColl(placeHolder) {//Izveido collapsible div objektu
    var collapsibleObj = new CollapsibleButton(
        new Icon("arrow", "medIcon"), "Saved", placeHolder, new Icon("bookmark", "medIcon")
    );
    collapsibleObj.buildCollapseButton();
}


function checkRotateElement(checkNode1, checkNode2, styleToApply) {//Pagriež atbilstošo ikonu, ja pogā atrodas vairāk kā viena
    if (checkNode1.nodeName == "P") {//gadījumam, kad pogā atrodas vairāk kā viena ikona
        checkNode2.style = styleToApply;//rotē bultiņu
    } else {
        checkNode1.style = styleToApply;//rotē bultiņu
    }
}


var collObjArr = [0, 0, 0];//Masīvs, kurā atrodas visi collapsible objekti
var collObjArrCount = 0;//skaita uz priekšu jauno objektu pozīcijas masīvā


var rgbw = [
    [255, 255, 255, 0],
    [255, 255, 0, 0],
    [0, 255, 255, 0],
    [255, 0, 255, 10],
    [255, 255, 0, 120],
    [0, 255, 255, 0],
    [0, 255, 255, 0],
    [0, 255, 255, 0]
];//šajā sarakstā glabājas 4 krāsu rgbw vērtības
var rgbwNames = ['SomeColor1', 'SmallerColorLol', 'A', 'Here',
    'InternalSuffering', 'words', 'manyWords', 'lettersColor'];

var colorBlockObjArr = [];

var funcNum = [
    [2, 100],
    [3, 213],
    [15, 1],
    [23, 0],
    [22, 11],
    [76, 233],
    [1, 677]
];

var funcNames = ['bitch', 'function', 'colors', 'this', 'test1', 'testdos', 'testtres'];
var funcBlockObjArr = [];

blockWidthCount = 0;//skaita uz priekšu krāsu bloku kopējo platumu rindā un salīdzina ar to atrašanās bloku platumu

function createSubColl() {
    var collapsibleObj = new CollapsibleButton(
        new Icon("arrow", "medIcon"),
        "Colors",
        document.getElementsByClassName("elemPlaceHolder")[0],
        '',
        'colorBlockContent'
    );
    collapsibleObj.buildCollapseButton();
    blockWidthCount = 0;
    for (var i = 0; i < rgbw.length; i++) {
        //izveido krāsu pogas un saliek tās collapsible pogas kontentā
        colorBlockObjArr.push(
            new ColorBlock(
                rgbwNames[i],
                rgbw[i],
                'colorBlock',
                editColorButton)
        );
        addColorBlock(i, collapsibleObj, colorBlockObjArr, rgbw.length);//!!!!!
        colorCount++;//skaita uz priekšu cik ir krāsu pogu
    }

    collapsibleObj = new CollapsibleButton(
        new Icon("arrow", "medIcon"),
        "Animations",
        document.getElementsByClassName("elemPlaceHolder")[0],
        '',
        'animBlockContent'
    );//izveido animāciju collapsible pogu

    collapsibleObj.buildCollapseButton();

    for (i = 0; i < funcNum.length; i++) {//izveido animāciju pogas un saliek tās collapsible pogas kontentā
        funcBlockObjArr.push(new AnimationsBlock(funcNames[i], funcNum[i], 'animBlock', editAnimButton));
        collapsibleObj.updateContent(funcBlockObjArr[i].buildAnimBlock());

        animCount++;//skaita uz priekšu cik ir animāciju pogu
    }
}



var lampGroups = [
    ['Room1', '1-5#'],
    ['BedRoom', '2-8#'],
    ['Garden', '6-7#']
];//ienākošo lampu grupu datu masīvs
var lampNum = 6;
var lampButton;//lampu pogas mainīgais


var editGroupSettings;//liela ievade un tad from to ievade, nosūta ajax datus
var newGroupSettings;//liela ievade un tad from to ievade, izveido jaunu pogu nosūta ajax datus
var addExploreButton;//teksts un tikai save vai close
var newColorButton;//teksts un liela ievade, 3 pogas
var editColorButton;//teksts un liela ievade, 3 pogas, tiek piemērota saved krāsām
var editAnimButton;//teksts liela ievade, teksts, maza ievade, 3 pogas
function buildSettings() {//izveido visus settings objektus, lai tie būtu tikai vienā eksemplārā un joprojām pieejami visiem citiem elementiem 
    editGroupSettings = new SettingsPopUp(
        'Edit this group',
        [
            ['Update name of group: ', 'bigInput'],
            ['Type which lamps you would like to change in group: ', 'double'],
            ['From: ', 'smInput'],
            ['To: ', 'smInput']
        ],
        3,
        'group',
        0,
        'updateGroup'
    );
    editGroupSettings.build();
    editGroupSettings.closeSettings();


    newGroupSettings = new SettingsPopUp(
        'Create new group',
        [
            ['Type new name of group: ', 'bigInput'],
            ['Type which lamps you would like to group up: ', 'double'],
            ['From: ', 'smInput'],
            ['To: ', 'smInput']
        ],
        2,
        'group',
        1,
        'group'
    );
    newGroupSettings.build();
    newGroupSettings.closeSettings();


    addExploreButton = new SettingsPopUp(
        'Save this to your collection?',
        [],
        2,
        'add',
        2,
        'add'
    );
    addExploreButton.build();
    addExploreButton.closeSettings();


    newColorButton = new SettingsPopUp(
        'Save color to your collection',
        [
            ['Type the name of your new color: ', 'bigInput']
        ],
        2,
        'add',
        3,
        'color'
    );
    newColorButton.build();
    newColorButton.closeSettings();


    editColorButton = new SettingsPopUp(
        'Color options',
        [
            ['Edit color name: ', 'bigInput']
        ],
        3,
        'add',
        4,
        'updateColor'
    );
    editColorButton.build();
    editColorButton.closeSettings();


    editAnimButton = new SettingsPopUp(
        'Animation options',
        [
            ['Edit animation name: ', 'bigInput'],
            ['Edit animation parameter', 'smInput']
        ],
        3,
        'add',
        5,
        'updateAnimation'
    );
    editAnimButton.build();
    editAnimButton.closeSettings();
}



function checkButtPlaceCount() {//pārbauda vai ir nepieciešams veidot nākamo elementu, lai turētu grupu pogas
    // console.log(document.getElementsByClassName('groupButtonHolder')[createButtHolder(true) - 1].childElementCount);
    if (document.getElementsByClassName('groupButtonHolder')[createButtHolder(true) - 1].childElementCount == 4) {
        createButtHolder();
    }
}


var createButtHolder = (function () {//mainīgais, funkcija, kas skaita uz priekšu ģenerētos pogas turetāja elementus
    var buttonPlaceCount = 0;
    // console.log('firstTime');
    return function (ret = false) {
        // console.log('funcExc');
        if (ret) {
            // console.log('ret count');
            return buttonPlaceCount;
        } else {
            // console.log('append');
            buttonPlaceCount++;
            document.getElementById('groupHolder').appendChild(buildElementNode('DIV', 'groupButtonHolder'));
        }
    }
})();



function createLampButts() {//izveido lampu pogas
    createButtHolder();
    for (j = 0; j < lampGroups.length; j++) {//izveido lampu grupu pogu
        lampButton = new LampBlock(lampGroups[j][0], lampGroups[j][1], editGroupSettings);
        lampButton.build(document.getElementsByClassName('groupButtonHolder').length - 1);
        checkButtPlaceCount();
    }

    for (i = 0; i < lampNum; i++) {//izveido parastas lampas pogu
        lampButton = new LampBlock('L' + (i + 1), i + 1);
        lampButton.build(document.getElementsByClassName('groupButtonHolder').length - 1);
        checkButtPlaceCount();

    }
    createNewLampGroup('Create new lamp group', 'newGroup', newGroupSettings);//izveido create new lamp group pogu
    checkButtPlaceCount();
    riseGroupButts();
}


function createNewLampGroup(name, value, settings = '', newButt = false) {//izveido jaunu lampu grupas pogu
    lampButton = new LampBlock(name, value, settings);
    if (!newButt) {//ja netiek pievienota jauna poga
        lampButton.build(document.getElementsByClassName('groupButtonHolder').length - 1);
    } else {//ja tiek pievienota jauna poga
        if (
            !document.getElementsByClassName('groupButtonHolder')
            [document.getElementsByClassName('groupButtonHolder').length - 1]
                .getElementsByClassName('lampButton').length == 0
        ) {//ja pogas holderī vēl ir vieta jaunai pogai
            document.getElementsByClassName('groupButtonHolder')//novāc create new lamp group pogu
            [document.getElementsByClassName('groupButtonHolder').length - 1]
                .getElementsByClassName('lampButton')[document.getElementsByClassName('groupButtonHolder')
                [document.getElementsByClassName('groupButtonHolder').length - 1]
                    .getElementsByClassName('lampButton').length - 1].remove();
            lampButton.build(document.getElementsByClassName('groupButtonHolder').length - 1);//izveido elementu pēc pēdējās grupas pogas        
        } else {//ja pogas holderī nav vietas jaunai pogai
            document.getElementsByClassName('groupButtonHolder')//novāc pēdējo create lamp button pogu
            [document.getElementsByClassName('groupButtonHolder').length - 2]
                .getElementsByClassName('lampButton')[document.getElementsByClassName('groupButtonHolder')
                [document.getElementsByClassName('groupButtonHolder').length - 2]
                    .getElementsByClassName('lampButton').length - 1].remove();

            lampButton.build(document.getElementsByClassName('groupButtonHolder').length - 2);//izveido elementu pēc pēdējās grupas pogas        
        }
        checkButtPlaceCount();
        riseGroupButts();
        createNewLampGroup('Create new lamp group', 'newGroup', newGroupSettings);//izveido create new lamp group pogu
        checkButtPlaceCount();
        riseGroupButts();
    }
}

function checkButtHolders() {//pārbauda vai ir nepieciešams pārvietot grupu pogas uz citiem div elementiem

}


function riseGroupButts() {//iestata group pogām to garumu
    for (var i = 0; i < document.getElementsByClassName('groupButtonHolder').length; i++) {
        for (var j = 0; j < document.getElementsByClassName('groupButtonHolder')[i].childElementCount; j++) {
            switch (document.getElementsByClassName('groupButtonHolder')[i].childElementCount) {
                case 1:
                    document.getElementsByClassName('groupButtonHolder')[i]
                        .getElementsByClassName('lampButton')[j].style.width = '100%';
                    break;
                case 2:
                    document.getElementsByClassName('groupButtonHolder')[i]
                        .getElementsByClassName('lampButton')[j].style.width = '50%';
                    break;
                case 3:
                    document.getElementsByClassName('groupButtonHolder')[i]
                        .getElementsByClassName('lampButton')[j].style.width = '33%';
                    break;
                case 4:
                    // console.log(document.getElementsByClassName('groupButtonHolder')[i].getElementsByClassName('lampButton')[j]);
                    document.getElementsByClassName('groupButtonHolder')[i]
                        .getElementsByClassName('lampButton')[j].style.width = '25%';
                    break;
                default:
                    break;
            }
        }
    }
}








function buildElementNode(type, classList = '', textToAdd = '') {//izveido un atgriež paragrāfu ar klasi
    var builtElement = document.createElement(type);
    if (classList != '') {
        builtElement.classList.add(classList);
    }
    if (textToAdd != '') {
        builtElement.appendChild(document.createTextNode(textToAdd));
    }
    return builtElement;
}


function createPopUp() {//izveido settings popUp
    // var createPopUp = new SettingsPopUp('Create new group', [['Type new name of group: ', 'bigInput'], ['Type which lamps you would like to group up: ', 'double'], ['From: ', 'smInput'], ['To: ', 'smInput']], 2, 1, 'group');
    // createPopUp.build();
}


backCover = buildElementNode('DIV', 'documentCover');//izveido lapas aptumšojošo div elementu
document.body.appendChild(backCover);
function backShadow(set) {//padara fonu tumšu, tiek izmantots priekš settings elementiem
    if (set) {
        backCover.style.display = 'block';
    } else {
        backCover.style.display = 'none';
    }
}


function createUserColor() {//saglabā lietotāja izvēlēto krāsu pēc 'Save this color' nospiešanas
    console.log('User Ok');
    newColorButton.open();
}

// window.onclick = e => {//būs nepieciešams, lai sekotu tam , kur notiek klikšķis, lai izvēlētos, vai atgriezt pogas default stāvokli vai nē
//     console.log(e.target);
//     console.log(e.target.tagName);
// } 