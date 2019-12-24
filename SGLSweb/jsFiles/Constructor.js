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
                    content.parentElement.parentElement.style.maxHeight = content.parentElement.parentElement.scrollHeight + content.scrollHeight + "px";
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

var funcNum = [[2, 100],[3, 213],[15, 1],[23, 0]];
var funcNames = ['bitch', 'function', 'colors', 'this'];
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
                colorBlockObjArr[i].grow(collObjArr[collObjArrCount].contentLength()  - colorBlockWidthCount -1);
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







