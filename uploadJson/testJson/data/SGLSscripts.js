function onOffTextChange() {//seko līdzi tam, vai lampas ieslēgtas vai nē
  if (buttonOn) {
    buttonOn = false;
    ajaxConsoleSend('onoff ' + 'turnOff');
  } else {
    buttonOn = true;
    ajaxConsoleSend('onoff ' + 'turnOn');
  }
  sendAjaxData('type=turnOn=' + buttonOn, 'setJson');

}

document.getElementById('SGLSmainName').style.color = getContrast(document.getElementsByClassName("titleDiv")[0].style.background);


function okWhite() {//aprekina un iestata baltas krasas vertibu
  if (whiteSetOn == true) {
    document.getElementsByClassName("whiteCenterDiv")[0].style.display = "none";
    rgbw[3] = scaleToRange(newWhite, 0, 100, 0, 255);//Parveido procentus par viena baita vertibu
    if (rgbw[3] > 0) {//Nosaka vai balta krasa ir ieslegta vai ari nav
      whiteAllowed = true;
    } else {
      whiteAllowed = false;
    }
    dataType = 1;
    stringColorSet();//iestata parejas krasas un izvada vertibas
    whiteSetOn = false;
  }
}

function cancelWhite() {//iziet ara no baltas krasas iestatisanas lodzina nemainot nekadas vertibas
  if (whiteSetOn == true) {
    document.getElementsByClassName("whiteCenterDiv")[0].style.display = "none";
    whiteSetOn = false;
  }
}


function funcNumBuilder(num) {
  if (num >= 100) {
    return num;
  } else if (num >= 10 && num < 100) {
    return "0" + num;
  } else {
    return "00" + num;
  }
}



function valueState(valueStateOutput) {//parāda vai dati tiek saņemti vai nosūtīti kā arī citus paziņojumus
  document.getElementById("outputState").innerText = valueStateOutput;
}


function setBrightness(brightness) {
  if (dataType == 1) {
    for (var i = 0; i < 4; i++) {
      rgbw[i] = Math.round(scaleToRange(brightness, 0, 100, 0, rgbw[i]));
    }
    stringColorSet();
  }
}

//Paroles ievades dala
function submitPassword() {
  var password = "test";
  var passwordCheck = document.getElementById("passwordInput").value;
  if (passwordCheck == password) {
    window.location.href = "main.html";
  }
}
//Paroles ievades dala beidzas
