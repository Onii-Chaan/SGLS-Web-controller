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

