function onOffTextChange(){//seko līdzi tam, vai lampas ieslēgtas vai nē
  if (onOff){
    onOff = false;
    ajaxConsoleSend('turnOff');
    sendAjaxData('turnOff', 'onoff');
  } else{
    onOff = true;
    ajaxConsoleSend('turnOn');
    sendAjaxData('turnOn', 'onoff');
  }
  // console.log(onOff);
}




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

//Settings logs
// document.getElementsByClassName("optionsDiv")[0].style.display = "none";
// var openSettingsVar = false
// function openSettings() {
//   if (openSettingsVar == false) {

//     openSettingsVar = true;
//     document.getElementsByClassName("optionsDiv")[0].style.display = "block";
//   } else {

//     openSettingsVar = false;
//     document.getElementsByClassName("optionsDiv")[0].style.display = "none";
//   }
// }



//lai darbotos ar datiem neizmantojot WiFi, ir jāizveido input lodzinš, kur tiks iekšā rakstītas vērtības

//Settingos var mainīt paroli
//Settingos atrodas lampu parskaitisanas

//izveidot lampu pārskaitīšanās nosūtīšanu

//izveidot funkciju, kas sadalītu lampu skaita vērtību no iekavām un izmantotu to turpmākajā skriptā

//<200[001]000> funkciju nosutisanas paraugs
//<000> lampu parskaitisanas nosutisanas paraugs
//<3> gaismas muzikas nosutisanas paraugs
//funkciju numuri nav zinami tapec tie tika izteikti sada veida: rainbow=1, fade=2, blink=3, onOff=0
//slideru vertibu parveidosana no 0-100 uz 0-255. Skaitliska veida tiks paradits viss procentos izmantojot map funkciju

//izveidot tā, lai funkcijas darbotos tikai tad, ja on off būls būtu true
//BOOKMARK1 ir iespeja pie ieslegsanas un izslegsanas noslept funkcionalo lapas dalu tadejadi tai lietotajam uz to bridi tai nebus piekluves. Sis ir atrais variants kuru butu velams uzlabot ar sarezgitaku un izskatigaku variantu

//Izveidot labu un parskatamu dizainu atbilstosi dazadiem ekranu izmeriem











