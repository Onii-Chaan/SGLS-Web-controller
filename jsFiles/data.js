function parseToRGBA(stringToParse) {//sadala style rgb un rgba uz skaitliskām krāsu vērtībām
    var m;
    if (stringToParse.indexOf('rgba') == -1) {//pārbauda vai krāsas ir jāsadala pēc rgb vai pēc rgba tipa
        m = stringToParse.match(/^rgb\s*\(\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*\)$/i);
        return [m[1], m[2], m[3], 0];
    } else {
        m = stringToParse.match(/^rgba\s*\(\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*(0\.(\d+))\s*\)$/i);
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

    console.log(sendPar);
    /*else if (dataType == 2) {//funkciju nosutisana
      sendPar.innerText = "<" + dataType + "00" + sendValueOutput + "000" + ">";//pedejas tris nulles ir prieks parametru iestatisanas. pagaidam netiek izmantots
    } else if (dataType == 3) {//gaismas muzikas nosutisana
      sendPar.innerText = "<3>";
    } else if (dataType == 0) {//saskaitisanas nosutisana
      sendPar.innerText = "<000>";
    }*/
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


var checkInput = (inputData) => {//Pārbauda vai ievadītā stringa dati ir atbilstoši
    if(inputData.length > 32){
        alert('Input must be no longer than 32 characters');
        return false;
    } else if(inputData.length == 0){
        alert('Input must not be empty');
        return false;
    }
}












var apConnectionState;//Seko tam vai ir savienojums ar softAP serveri

sendAjaxData(" ", "check_ap_connection");

showState(false, 'wlanState');
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




function sendAjaxData(dataToSend = "", dataTypeToSend = "", returnData = false) {//Nosūta datus uz serveri izmantojot AJAX
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);
            ajaxResponses(this.responseText);
            //if (returnData) {
            //return this.responseText;
            //}
        }
    };
    xhttp.open("POST", dataTypeToSend, true);
    xhttp.send(dataToSend);
}



var startConnectionTimeout;//Gaida atbildi no servera pusotru sekundi


function checkAPstate() {//Pārbauda savienojumu ar softAP
    startConnectionTimeout = setTimeout(function () { apConnectionState = false; showState(apConnectionState, 'softAPState') }, 1500);
    sendAjaxData(" ", "check_ap_connection");

    if(document.getElementById("controllerLink").text == ""){//pārbauda un iegūst wlan linku
        requestAPLink();///////////////Vai tas varēs nosūtīties kopā ar check ap connection??///////////////////
    }
} 



setInterval(function () { checkAPstate(); }, 5000);


// _yourDataName_ yourData 
function ajaxResponses(incText, payload = "") {
    if (incText.indexOf("_") == 0){//Ja ienāk mainīgie dati
        payload = incText.slice(incText.indexOf(" ")+1, incText.lastIndexOf(" "));
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


function requestAPLink(){//pieprasa wlan mdns linku ielādējot lapu
    sendAjaxData(" ", "wlan_link_request");
}


function connectToWlan(){//nosūta pieprasījumu pievienoties wlan tīklam
    sendAjaxData(" ", "connect_to_wlan");
}
