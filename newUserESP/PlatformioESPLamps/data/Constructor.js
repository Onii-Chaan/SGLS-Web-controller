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
            // console.log(exploreArr[i].slice(1, 3));
            colorAnimBlockObjArr.push(
                new ColorBlock(
                    exploreArr[i][0],
                    exploreArr[i].slice(1, 3),
                    'animBlock',
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
    if (
        blockWidthCount >= collObj.contentLength() ||
        j == arrLen - 1
    ) {//pārbauda vai pēdējo krāsu bloku ir jāpaplašina
        if (
            blockWidthCount - objArr[j].blockWidth() !=
            collObj.contentLength() && j > 0 && j != arrLen - 1
        ) {//pagarina krāsas bloku līdz galam pa kreisi
            objArr[j - 1].grow(
                collObj.contentLength() - (blockWidthCount - objArr[j].blockWidth())
            );
        }
        else if (
            j == arrLen - 1
        ) {
            objArr[j].grow(collObj.contentLength() - blockWidthCount + 4);
        }
        blockWidthCount = objArr[j].blockWidth();//atgriežas uz nākamo rindiņu
    } else if (
        objArr[j].blockWidth() > collObj.contentLength() - blockWidthCount && j > 0
    ) {
        objArr[j - 1].grow(
            collObj.contentLength() - (blockWidthCount - objArr[j].blockWidth() - 4)
        );
        blockWidthCount = objArr[j].blockWidth();//ieņem nākamā elementa lielumu nākamajā rindiņā
    }
    if (blockWidthCount >= collObj.contentLength()) {
        blockWidthCount = 0;
    }
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



blockWidthCount = 0;//skaita uz priekšu krāsu bloku kopējo platumu rindā un salīdzina ar to atrašanās bloku platumu

var COLOR_COLLAPSIBLE_OBJ;
function createSubColl() {
    COLOR_COLLAPSIBLE_OBJ = new CollapsibleButton(
        new Icon("arrow", "medIcon"),
        "Colors",
        document.getElementsByClassName("elemPlaceHolder")[0],
        '',
        'colorBlockContent'
    );
    COLOR_COLLAPSIBLE_OBJ.buildCollapseButton();
    blockWidthCount = 0;
    for (var i = 0; i < rgbwArr.length; i++) {
        //izveido krāsu pogas un saliek tās collapsible pogas kontentā
        colorBlockObjArr.push(
            new ColorBlock(
                rgbwArr[i][0],
                rgbwArr[i].slice(1, 5),
                'colorBlock',
                editColorButton)
        );
        addColorBlock(i, COLOR_COLLAPSIBLE_OBJ, colorBlockObjArr, rgbwArr.length);//!!!!!
        colorCount++;//skaita uz priekšu cik ir krāsu pogu
    }

    var collapsibleObj = new CollapsibleButton(
        new Icon("arrow", "medIcon"),
        "Animations",
        document.getElementsByClassName("elemPlaceHolder")[0],
        '',
        'animBlockContent'
    );//izveido animāciju collapsible pogu

    collapsibleObj.buildCollapseButton();

    for (i = 0; i < funcArr.length; i++) {//izveido animāciju pogas un saliek tās collapsible pogas kontentā
        funcBlockObjArr.push(new AnimationsBlock(funcArr[i][0], funcArr[i].slice(1,3), 'animBlock', editAnimButton));
        collapsibleObj.updateContent(funcBlockObjArr[i].buildAnimBlock());

        animCount++;//skaita uz priekšu cik ir animāciju pogu
    }
}


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
            ['Edit animation speed: ', 'sliderInput']
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
    lampButton = new LampBlock('All', '1-' + lampNum + '#');//izveido pogu, kas ieslēdz visas lampas
    lampButton.build(document.getElementsByClassName('groupButtonHolder').length - 1);
    checkButtPlaceCount();

    for (i = 0; i < lampNum; i++) {//izveido parastas lampas pogu
        lampButton = new LampBlock('L' + (i + 1), i + 1);
        lampButton.build(document.getElementsByClassName('groupButtonHolder').length - 1);
        checkButtPlaceCount();
    }

    for (j = 0; j < lampGroups.length; j++) {//izveido lampu grupu pogu
        lampButton = new LampBlock(lampGroups[j][0], lampGroups[j][1], editGroupSettings);
        lampButton.build(document.getElementsByClassName('groupButtonHolder').length - 1);
        checkButtPlaceCount();
    }
    createNewLampGroup('Create new lamp group', 'newGroup', newGroupSettings);//izveido create new lamp group pogu
    checkButtPlaceCount();
    riseGroupButts();
}

function createNewLampGroup(name, value, settings = '', newButt = false) {//izveido jaunu lampu grupas pogu
    lampButton = new LampBlock(name, value, settings);
    let placeToBuildElems = document.getElementsByClassName('groupButtonHolder');
    if (!newButt) {//ja netiek pievienota jauna poga
        lampButton.build(placeToBuildElems.length - 1);
    } else {//ja tiek pievienota jauna poga
        if (
            placeToBuildElems[placeToBuildElems.length - 1]
                .getElementsByClassName('lampButton').length != 0
        ) {//ja pogas holderī nav vietas jaunai pogai
            placeToBuildElems[placeToBuildElems.length - 1]//novāc create new lamp group pogu
                .getElementsByClassName('lampButton')[placeToBuildElems[placeToBuildElems.length - 1]
                    .getElementsByClassName('lampButton').length - 1].remove();
            lampButton.build(placeToBuildElems.length - 1);//izveido elementu pēc pēdējās grupas pogas        
        } else {//ja pogas holderī vēl ir vieta jaunai pogai
            placeToBuildElems[placeToBuildElems.length - 2].getElementsByClassName('lampButton')//novāc pēdējo create lamp button pogu
            [placeToBuildElems[placeToBuildElems.length - 2].getElementsByClassName('lampButton').length - 1].remove();
            lampButton.build(placeToBuildElems.length - 2);//izveido elementu pēc pēdējās grupas pogas        
        }
        checkButtPlaceCount();
        riseGroupButts();
        createNewLampGroup('Create new lamp group', 'newGroup', newGroupSettings);//izveido create new lamp group pogu
        checkButtPlaceCount();
        riseGroupButts();
    }
}

function checkButtHolders() {//pārbauda vai ir nepieciešams pārvietot grupu pogas uz citiem div elementiem
    var groupDivs = document.getElementsByClassName('groupButtonHolder');
    for (var i = 0; i < groupDivs.length; i++) {
        while (
            groupDivs[i].getElementsByClassName('lampButton').length < 4 &&
            i != groupDivs.length - 1 &&
            groupDivs[i + 1].getElementsByClassName('lampButton').length > 0
        ) {
            groupDivs[i].appendChild(groupDivs[i + 1].getElementsByClassName('lampButton')[0])
        }
    }
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
                        .getElementsByClassName('lampButton')[j].style.width = '33.33%';
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
        if (classList.constructor === Array) {
            for (var i = 0; i < classList.length; i++) {
                builtElement.classList.add(classList[i]);
            }
        } else {
            builtElement.classList.add(classList);
        }
    }
    if (textToAdd != '') {
        builtElement.appendChild(document.createTextNode(textToAdd));
    }
    return builtElement;
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


var getContrast = function (rgbColor) {//pārbauda un atgriež fonta krāsu
    // Get YIQ ratio
    var yiq = ((rgbColor[0] * 299) + (rgbColor[1] * 587) + (rgbColor[2] * 114)) / 1000;
    // Check contrast
    return (yiq >= 128) ? 'black' : 'white';
};



