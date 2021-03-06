function parseToRGBA(stringToParse) {//sadala style rgb un rgba uz skaitliskām krāsu vērtībām
    var m;
    if (stringToParse.indexOf('rgba') == -1) {//pārbauda vai krāsas ir jāsadala pēc rgb vai pēc rgba tipa
        m = stringToParse.match(/^rgb\s*\(\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*\)$/i);
        return [m[1], m[2], m[3], 0];
    } else {
        m = stringToParse.match(/^rgba\s*\(\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*(0\.(\d+))\s*\)$/i);
        m[4] = scaleToRange(m[4], 1.00, 0.00, 0, 255);
        return [m[1], m[2], m[3], m[4]];
    }
}

function stringColorSet(rgbwArr) {//Si funkcija parveido rgbw krasu vertibas String rindina. Gatavu izsutisanai

    var countString = "";
    var rgbwString = '';

    for (var i = 0; i < rgbwArr.length; i++) {//Nosaka vai saraksta skaitli ir divcipara vai viencipara vai trisciparu skaitlis un atbilstosi pieliek nulles
        if (rgbwArr[i] >= 100) {
            countString = rgbwArr[i];
        } else if (rgbwArr[i] < 100 && rgbwArr[i] >= 10) {
            countString = "0" + rgbwArr[i];
        } else {
            countString = "00" + rgbwArr[i];
        }
        rgbwString += countString;
        countString = "";
    }
    return rgbwString;
}

function stringFunctionSet(funcNum, funcPar) {//izveido funkciju nosūtāmo stringa otro daļu
    var sendOut = '';
    if (funcNum < 10) {
        sendOut = '0' + funcNum;
    } else {
        sendOut = funcNum;
    }
    if (funcPar >= 100) {
        sendOut += funcPar;
    } else if (funcPar < 100 && funcPar >= 10) {
        sendOut += "0" + funcPar;
    } else {
        sendOut += "00" + funcPar;
    }
    return sendOut;
}

function sendValue(dataType, lampNum, colorOutput) {//parāda nosūtamos datus
    var sendPar = '';
    sendPar = "<" + dataType + lampNum + colorOutput + ">";
    ajaxConsoleSend(sendPar);
}

function createGroupString(from, to) {//izveido grupas string mainīgo
    // console.log('a');
    return from + '-' + to + '#';
}

function ajaxConsoleSend(dataName) {//'izsūta' datus uz konsoli
    console.log('AJAX SEND: ', dataName);
}

function methodize(methodize_func, methodize_scope) {//nepieciešams, lai objektiem varētu pievienot eventus
    return (function () { methodize_func.call(methodize_scope); });
}


var checkInput = (inputData, valType = 'String') => {//Pārbauda vai ievadītā stringa dati ir atbilstoši    
    if (inputData.length > 32 && valType == 'String') {//Pārbauda vai ievadītais strings nav garāks par 32 simboliem
        alert('Input must be no longer than 32 characters!');
        return false;
    } else if (inputData.length == 0) {//Pārbauda vai ievadītais lauciņš nav tukšs
        alert('Input must not be empty!');
        return false;
    } else if (//Pārbauda vai pirmā ievadītā vērtība nav lielāka par otro
        inputData[0] > inputData[1] &&
        valType === 'number' &&
        !isNaN(inputData[0]) &&
        !isNaN(inputData[1]) &&
        inputData.constructor === Array
    ) {
        alert('First number must be smaller or equal than second!');
        return false;
    } else if (isNaN(inputData) && valType == 'number' && !Array.isArray(inputData)) {//Pārbauda vai ievadītais skaitlis ir skaitlis nevis strings
        alert('You must input a number!');
        return false;
    } else if (valType == 'number' && !Array.isArray(inputData) && inputData < 0) {
        alert('Input must be bigger than 0!');
        return false;
    } else {//Ja netika izpildīts neviens no iepriekšējiem nosacījumiem, tad pārbaude ir bijusi veiksmīga un netika atrastas nekādas kļūdas
        return true;
    }
}


function scaleToRange(number, fromMin, fromHigh, toMin, toHigh) {//Si funkcija parveido skaitli no vienas kopas uz citu
    return Math.round(((number - fromMin) / (fromHigh - fromMin)) * (toHigh - toMin) + toMin);
}


function checkPassEq(formId) { //for double password inputs both passwords should be checked for equality
    if (formId.elements[0].value == formId.elements[1].value)
        checkForm(formId, 4)
    else {
        alert("Not equal passwords");
        formId.reset();
    }
}

function checkForm(formId, passLength = 8) {//Pārbauda katru ievadīto form vērtību
    let form = formId;
    let sendGetData = true;
    let dataToSend = "";
    let doublePass = false;//seko tam, lai parole netiktu sūtīta divreiz dēļ pārbaudes 
    for (i = 0; i < form.length; i++) {//Iet cauri katram elementam iekš form un pārbauda vai tas ir derīgs
        var elementToCheck = form.elements[i];
        if (elementToCheck.name == 'ssid' || elementToCheck.name == 'pass' || elementToCheck.name == 'linkName') {
            if (elementToCheck.value.length > 32 && elementToCheck.name != 'linkName') {//Pārbauda vai ievadītā SSID simbolu garums nav lielāks par 32 baitiem
                sendGetData = false;
                alert("Your ssid name is longer than 32 symbols");
                break;
            } else if (!isASCII(elementToCheck.value)) {//Pārbauda vai ievadītā SSID simboli ir ASCII simboli
                sendGetData = false;
                alert("Your ssid name contains forbidden symbols");
                break;
            } else if (elementToCheck.value == '') {
                sendGetData = false;
                alert("You must fill all fields");
                break;
            }
        }
        if (elementToCheck.name == 'pass') {//Pārbauda vai paroles garums ir lielāks par 8 simboliem
            if (elementToCheck.value.length < passLength) {
                sendGetData = false;
                alert("Your password must be longer than " + passLength + " symbols");
                break;
            }
        }
        if (elementToCheck.name == 'number') {
            if (isNaN(elementToCheck.value)) {
                sendGetData = false;
                alert("You must input a number");
                break;
            } else if (elementToCheck.value > 30) {
                sendGetData = false;
                alert("Max quantity of lamps connected is 30");
                break;
            } else if (elementToCheck.value == '') {
                sendGetData = false;
                alert("You must fill all fields");
                break;
            }
        }
        if (elementToCheck.name == 'ssid') {
            dataToSend = dataToSend + "ssid=" + elementToCheck.value + "|";
        } else if (elementToCheck.name == 'pass' && doublePass == false) {
            doublePass = true;
            dataToSend = dataToSend + "pass=" + elementToCheck.value + "|";
        } else if (elementToCheck.name == 'linkName') {
            dataToSend = dataToSend + "linkName=" + elementToCheck.value + "|";
        } else if (elementToCheck.name == 'number') {
            dataToSend = dataToSend + "num=" + elementToCheck.value + "|";
        }
    }

    dataToSend = "type=" + dataToSend + "data=" + formId.getAttribute("name");
    if (sendGetData) {
        ajaxConsoleSend(dataToSend, formId);
        sendAjaxData(dataToSend, 'setJson');
    }
    form.reset();
}

function isASCII(valueToCheck) {//Funkcija, kas pārbauda vai simbols ir ASCII, vai arī nav, kā arī pārbauda atstarpes esamību
    for (var i = 0; i < valueToCheck.length; i++) {
        if (valueToCheck.charCodeAt(i) > 127 || valueToCheck.charCodeAt(i) == 32 || valueToCheck.charCodeAt(i) == 38 || valueToCheck.charCodeAt(i) == 124 || valueToCheck.charCodeAt(i) == 61) {
            return false;
        }
    }
    return true;
}


//Priekš divu masīvu salīdzināšanas
if (Array.prototype.equals)
    console.warn("Overriding existing Array.prototype.equals. Possible causes: New API defines the method, there's a framework conflict or you've got double inclusions in your code.");
// attach the .equals method to Array's prototype to call it on any array
Array.prototype.equals = function (array) {
    // if the other array is a falsy value, return
    if (!array)
        return false;

    // compare lengths - can save a lot of time 
    if (this.length != array.length)
        return false;

    for (var i = 0, l = this.length; i < l; i++) {
        // Check if we have nested arrays
        if (this[i] instanceof Array && array[i] instanceof Array) {
            // recurse into the nested arrays
            if (!this[i].equals(array[i]))
                return false;
        }
        else if (this[i] != array[i]) {
            // Warning - two different object instances will never be equal: {x:20} != {x:20}
            return false;
        }
    }
    return true;
}
// Hide method from for-in loops
Object.defineProperty(Array.prototype, "equals", { enumerable: false });


var findArrIndex = (arr, valueToFind) => {//atrod masīvu iekš 2d masīva un atgriež tā indeksu
    for (let i = 0; i < arr.length; i++) {
        if (arr[i].equals(valueToFind)) {//Izdzēš esošo vērtību no masīva
            return i;
        }
    }
}

var bringLastToFirst = (inputArr) => {//pārvieto masīva pēdējo elementu uz sākumu un atgriež jauno masīvu
    let lastVar = inputArr[inputArr.length - 1];//Masīvs tiek pielāgots salīdzināšanai
    inputArr.sort(function (x, y) { return x == lastVar ? -1 : y == lastVar ? 1 : 0; });
    return inputArr;
}


















var apConnectionState;//Seko tam vai ir savienojums ar softAP serveri

// sendAjaxData("connData", "check_ap_connection");

// showState(false, 'wlanState');
//Jādarbojas balstoties uz AJAX saņemtajiem datiem
function showState(state, idToDisplay) {//Parāda uz lapas vai atbilstošā daļa ir pieejama , vai arī nē
    if (state) {//Maina tekstu un tā krāsu
        document.getElementById(idToDisplay).innerHTML = 'Available';
        document.getElementById(idToDisplay).style.color = 'green';
    } else {
        document.getElementById(idToDisplay).innerHTML = 'Unavailable';
        document.getElementById(idToDisplay).style.color = 'red';
    }
}

//ja signin un nav cookie tad nosūta papildus vērtību

function sendAjaxData(dataToSend = "", dataTypeToSend = "") {//Nosūta datus uz serveri izmantojot AJAX
    if (document.cookie == "") //gets time and sends it until sessid is optained in cookie
        dataToSend += ("|param=" + buildCookieTime());


    let xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            // console.log(this.responseText);
            if (this.responseURL.substring(this.responseURL.lastIndexOf('.') + 1) ==
                "html") {//if redirects to sign in
                window.location.href = this.responseURL;
            } else if (this.getResponseHeader("ReqRedirect") != null) {
                window.location.href = window.location.href
                    .substring(0, window.location.href.lastIndexOf('/')) +
                    this.getResponseHeader("ReqRedirect");
            }
        }
    };
    xhttp.open("POST", dataTypeToSend, true);

    if (document.cookie)
        xhttp.setRequestHeader("SESSID", document.cookie);

    xhttp.send(dataToSend);
}

var startConnectionTimeout;//Gaida atbildi no servera pusotru sekundi

function checkAPstate() {//Pārbauda savienojumu ar softAP
    startConnectionTimeout = setTimeout(function () { apConnectionState = false; showState(apConnectionState, 'softAPState') }, 1500);
    sendAjaxData(" ", "check_ap_connection");

    if (document.getElementById("controllerLink").text == "") {//pārbauda un iegūst wlan linku
        requestAPLink();///////////////Vai tas varēs nosūtīties kopā ar check ap connection??///////////////////
    }
}

function buildCookieTime() {//builds time for cookie expiration date
    var now = new Date();
    var time = now.getTime();
    var expireTime = time + 1000 * 36000;
    now.setTime(expireTime);
    return now.toGMTString();
}

// setInterval(function () { checkAPstate(); }, 5000);

// _yourDataName_ yourData 
function ajaxResponses(incText, payload = "") {
    if (incText.indexOf("_") == 0) {//Ja ienāk mainīgie dati
        payload = incText.slice(incText.indexOf(" ") + 1, incText.lastIndexOf(" "));
        incText = incText.slice(1, incText.lastIndexOf("_"));
    }
    switch (incText) {
        case "server_ap_ok"://Ja ir savienojums ar serveri
            clearTimeout(startConnectionTimeout);
            apConnectionState = true;
            showState(apConnectionState, 'softAPState');
            break;
        case "wlan_login_data_ok"://Ja veiksmīgi tika saglabāti dati
            alert("You have successfully changed your WLAN name and password");
            break;
        case "wlan_login_data_fail"://Ja uz esp netiek saglabāta dati
            alert("Changing your WLAN name and/or password has failed");
            break;
        case "wlan_link"://Ja tiek iegūts wlan links
            var link = payload + ".local";
            document.getElementById("controllerLink").innerHTML = link;
            document.getElementById("controllerLink").href = link;
            break;
    }
}


function requestAPLink() {//pieprasa wlan mdns linku ielādējot lapu
    sendAjaxData(" ", "wlan_link_request");
}

function connectToWlan() {//nosūta pieprasījumu pievienoties wlan tīklam
    sendAjaxData(" ", "connect_to_wlan");
}


var urlQuery = (params) => {//izveido izsūtāmo datu stringu url formātā
    return 'type=' + Object.keys(params)
        .map(k => k + '=' + params[k])
        .join('|');
}

var createDic = (keyArr, valArr) => {//Izveido dictionary no diviem masīviem
    var items = {};
    for (let i = 0; i < keyArr.length; i++) {
        items[keyArr[i]] = valArr[i];
    }
    return items;
}


var expoPar = (x) => { //calculates exponent value for animation parameters use https://www.desmos.com/calculator/3fisjexbvp for calculations
    let a = 0.93;
    let b = 1.007
    let c = 0.1;
    return Math.round(a * Math.pow(b, x) + c);
}

