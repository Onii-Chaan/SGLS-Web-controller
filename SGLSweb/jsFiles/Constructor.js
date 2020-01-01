function createDynamicContent() {
    createColl(document.getElementById('collHolder'));//izveido saved pogu un tās kontentu
    createLampButts();//izveido lampu pogas
}


function createColl(placeHolder) {//Izveido collapsible div objektu
    var collapsibleObj = new CollapsibleButton(new Icon("arrow", "medIcon"), "Saved", placeHolder, new Icon("bookmark", "medIcon"));
    collapsibleObj.buildCollapseButton();

    collObjArr[collObjArrCount] = collapsibleObj;
    collObjArrCount += 1;

    createSubColl();//izveido papildus divas


    var coll = document.getElementsByClassName("collapsibleObj");

    for (i = 0; i < coll.length; i++) {
        checkRotateElement(coll[i].childNodes[1], coll[i].childNodes[2], 'transform: rotate(0deg);top: 3px; margin-right: 10px; margin-left: auto');
        coll[i].addEventListener("click", function () {//rotē bultiņu uz klikšķi un atver kontentu
            this.classList.toggle("active");
            var content = this.nextElementSibling;
            if (content.style.maxHeight) {
                checkRotateElement(content.previousSibling.childNodes[1], content.previousSibling.childNodes[2], 'transform: rotate(0deg);top: 3px; margin-right: 10px; margin-left: auto');
                content.style.maxHeight = null;
            } else {
                checkRotateElement(content.previousSibling.childNodes[1], content.previousSibling.childNodes[2], 'bottom: 6px; transform: rotate(180deg); margin-right: 14px; margin-left: auto');
                content.style.maxHeight = content.scrollHeight + "px";
                if (content.parentElement.parentElement != null) {//Nodrošina, ka kontents nekur nepazudīs izplešoties
                    content.parentElement.parentElement.style.maxHeight = 'inherit';
                }
            }
        });
    }
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


var rgbw = [[255, 255, 255, 0], [255, 255, 0, 0], [0, 255, 255, 0], [255, 0, 255, 10], [255, 255, 0, 120], [0, 255, 255, 0], [0, 255, 255, 0], [0, 255, 255, 0]];//šajā sarakstā glabājas 4 krāsu rgbw vērtības
var rgbwNames = ['SomeColor1', 'SmallerColorLol', 'A', 'Here', 'InternalSuffering', 'words', 'manyWords', 'lettersColor'];
var colorBlockObjArr = [];

var funcNum = [[2, 100], [3, 213], [15, 1], [23, 0], [22, 11], [76, 233], [1, 677]];
var funcNames = ['bitch', 'function', 'colors', 'this', 'test1', 'testdos', 'testtres'];
var funcBlockObjArr = [];

var colorBlockWidthCount = 0;//skaita uz priekšu krāsu bloku kopējo platumu rindā un salīdzina ar to atrašanās bloku platumu


function createSubColl() {
    collObjArr[collObjArrCount] = new CollapsibleButton(new Icon("arrow", "medIcon"), "Colors", document.getElementsByClassName("elemPlaceHolder")[0], '', 'colorBlockContent');
    collObjArr[collObjArrCount].buildCollapseButton();


    for (i = 0; i < rgbw.length; i++) {//izveido krāsu pogas un saliek tās collapsible pogas kontentā
        colorBlockObjArr.push(new ColorBlock(rgbwNames[i], rgbw[i], 'colorBlock'));
        collObjArr[collObjArrCount].updateContent(colorBlockObjArr[i].build());
        colorBlockObjArr[i].grow();//izveido krāsu bloku platumu
        colorBlockWidthCount += colorBlockObjArr[i].blockWidth();//skaita uz priekšu rindas platumu
        if (colorBlockWidthCount >= collObjArr[collObjArrCount].contentLength() || i == rgbw.length - 1) {//pārbauda vai pēdējo krāsu bloku ir jāpaplašina
            if (colorBlockWidthCount - colorBlockObjArr[i].blockWidth() != collObjArr[collObjArrCount].contentLength() && i > 0 && i != rgbw.length - 1) {//pagarina krāsas bloku līdz galam pa kreisi
                colorBlockObjArr[i - 1].grow(collObjArr[collObjArrCount].contentLength() - (colorBlockWidthCount - colorBlockObjArr[i].blockWidth()));
            }
            else if (i == rgbw.length - 1) {
                colorBlockObjArr[i].grow(collObjArr[collObjArrCount].contentLength() - colorBlockWidthCount - 1);
            }
            colorBlockWidthCount = colorBlockObjArr[i].blockWidth();//atgriežas uz nākamo rindiņu
        }
    }
    collObjArrCount += 1;//pabeidz pogas izveidi

    collObjArr[collObjArrCount] = new CollapsibleButton(new Icon("arrow", "medIcon"), "Animations", document.getElementsByClassName("elemPlaceHolder")[0], '', 'animBlockContent');//izveido animāciju collapsible pogu
    collObjArr[collObjArrCount].buildCollapseButton();

    for (i = 0; i < funcNum.length; i++) {//izveido animāciju pogas un saliek tās collapsible pogas kontentā
        funcBlockObjArr.push(new AnimationsBlock(funcNames[i], funcNum[i], 'animBlock'));
        collObjArr[collObjArrCount].updateContent(funcBlockObjArr[i].buildAnimBlock());
    }
    collObjArrCount += 1;//pabeidz pogas izveidi
}



var lampNum = 6;
var lampCombos = 3;
var lampCombNames = ['village', 'room1', 'anotherCombo'];//masīvs ar jau izveidoto lampu kombināciju nosaukumiem
var lampCombosVal = [[1, 5], [5, 8], [7, 7]];//masīvs ar jau izveidoto lampu kombināciju nosaukumiem
function createLampButts() {//izveido lampu pogas
    var lampButtPlace = document.getElementById('lampButtHold');//nnosaka lampu pogu atrašanās vietas
    var lampButton;//lampu pogas mainīgais

    for (i = 0; i < lampGroups.length; i++) {//izveido lampu grupu pogu
        lampButton = new LampBlock(lampGroups[i][0], lampGroups[i][1], new SettingsPopUp('Create new group', [['Type new name of group: ', 'bigInput'], ['Type which lamps you would like to group up: ', 'double'], ['From: ', 'smInput'], ['To: ', 'smInput']], 2, 1, 'group'));
        lampButton.build();
    }
    for (i = 0; i < lampNum + 1; i++) {//izveido parastas lampas pogu
        lampButton = new LampBlock('L' + (i + 1), i + 1);
        lampButton.build();
        if (i == lampNum) {//ja ir pienākusi pēdējās lampas izveide, tad izveido jauna kombo izveides pogu
            lampButton = new LampBlock('Create ultimate combo', '');
            lampButton.openOption();
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


backCover = buildElementNode('DIV', 'documentCover');
document.body.appendChild(backCover);
function backShadow(set) {//padara fonu tumšu, tiek izmantots priekš settings elementiem
    if (set) {
        backCover.style.display = 'block';
    } else {
        backCover.style.display = 'none';
    }
}



